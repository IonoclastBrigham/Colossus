// gc.h
// Colossus Runtime
// garbage collector classes


#pragma once

#include <pthread.h>

#include "defs.h"
#include "util.h"
#include "Exception.h"


// Error Handling //////////////////////////////////////////////////////////////


#define __CONTAINER_VALIDATE_POINTER(p) \
	if(p == NULL) \
		throw Exception(__PRETTY_FUNCTION__, "Dereferencing NULL pointer.");
#define __CONTAINER_VALIDATE_ALLOC(p) \
	if(p == NULL) \
		throw Exception(__PRETTY_FUNCTION__, "Allocation failed.");
#define __CONTAINER_VALIDATE_NONEMPTY() \
	if(!this->size) \
		throw Exception(__PRETTY_FUNCTION__, "Accessing empty container.");
#define __CONTAINER_VALIDATE_INDEX(i) \
	if(i >= this->size) \
		throw Exception(__PRETTY_FUNCTION__, "Index out of bounds.");

#define __CONTAINER_RESIZE_INC() \
	if(this->size == this->capacity) \
		Reserve(this->capacity << 1); \
	this->size++;
#define __CONTAINER_RESIZE_ADD(count) \
	if(this->size + count > this->capacity) \
	{ \
		int cap = this->capacity; \
		do \
			cap <<= 1; \
		while(this->size + count > cap); \
		this->Reserve(cap); \
	}

/// Dynamic Array-based Container Interface + Base Functionality ///////////////

template <typename _T>
class Container
{
public:
	Container(size_t capacity) : size(0), capacity(0), data(NULL)
	{
		Reserve(capacity);
	}
	//Container(Container& c) {}
	virtual ~Container()
	{
		Clear();
		dealloc();
	}
	
	/// Memory Management ///
	virtual void Reserve(size_t count)
	{
		if(count <= capacity)
			return;
		
		if(data)
			data = (_T*)realloc(data, count * sizeof(_T));
		else
			data = (_T*)calloc(count, sizeof(_T));
		__CONTAINER_VALIDATE_ALLOC(data);
		capacity = count;
	}
	void Remove(size_t i)
	{
		__CONTAINER_VALIDATE_INDEX(i);
		data[i].~_T();
		if(size > i + 1)
			copy(data + i + 1, data + size, data + i);
		size--;
	}
	void Clear()
	{
		
		for(int i = 0; i < size; i++)
			data[i].~_T();
		size = 0;
	}
	bool Empty() const { return size == 0; }
	size_t Size() const { return size; }
	size_t Capacity() const { return capacity; }
	
	/// Element Access ///
	virtual _T& First() = 0;
	virtual _T& Last() = 0;
	virtual _T& operator[](size_t i) = 0;
	virtual void Create(size_t count) = 0;
	
protected:
	void dealloc()
	{
		if(data)
			free(data);
		data = NULL;
		size = capacity = 0;
	}
	
	size_t size, capacity;
	_T* data;
};

/// Dynamic Double-ended Circular Queue/////////////////////////////////////////

// TODO:
// Allocate in power-of-two chunks for efficiency, but
// ignore the last cell (making it effectively size 2^k - 1).
// Handle looping by always doing array[mask&(head+i)] which is a cheap
// alternative to mod or double compares.
// ex: 00001111 & 11111111 = 00001111 (-1 => 15)
// ex: 00001111 & 00010001 = 00000001 (17 => 1)

template <typename _T>
class Deq : public Container<_T>
{
public:
	Deq(size_t capacity = 64) : Container<_T>(capacity), head(0), tail(0) {}
	//virtual ~Deq() {}
	
	// overridden to handle non-contiguous copies
	void Reserve(size_t count)
	{
		if(this->data && count)
		{
			_T* ptmp = (_T*)calloc(count, sizeof(_T));
			__CONTAINER_VALIDATE_ALLOC(ptmp);
			if(head >= tail)	// case 1: data has wrapped around
			{
				if(this->head == this->tail == 0)	// tail-only wrapped head
				{
					std::copy(this->data + head, this->data + this->capacity,
							  ptmp);
				}
				else								// normal disjoint copy
				{
					std::copy(this->data + head, this->data + this->capacity, ptmp);
					std::copy(this->data, this->data + tail,
							  ptmp + this->capacity - head);
				}
			}
			else			// case 2: data is a contiguous block
			{
				std::copy(this->data + head, this->data + tail, ptmp);
			}
			this->capacity = count;
			free(this->data);
			this->data = ptmp;
			head = 0;
			tail = this->size;
		}
		else
			Container<_T>::Reserve(count);
	}
	
	_T& First()
	{
		__CONTAINER_VALIDATE_NONEMPTY();
		return this->data[head];
	}
	_T& Last()
	{
		__CONTAINER_VALIDATE_NONEMPTY();
		return this->data[tail-1];
	}
	_T& operator[](size_t i)
	{
		__CONTAINER_VALIDATE_INDEX(i);
		int index = head + i;
		WRAP_END(index, this->capacity);
		return this->data[index];
	}
	void Create(size_t count)
	{
		if(!count)
			return;
		
		__CONTAINER_RESIZE_ADD(count);
		try
		{
			new(this->data + tail) _T[count];	// initialize new objects
		}
		catch(...)
		{
			this->dealloc();
			throw;
		}
		this->size += count;
		tail += count;
		WRAP_END(tail, this->capacity);
	}
	void PushBack(const _T& val)
	{
		__CONTAINER_RESIZE_INC();
		this->data[tail++] = val;
		WRAP_END(tail, this->capacity);
	}
	void PushFront(const _T& val)
	{
		__CONTAINER_RESIZE_INC();
		if(head-- == tail)
		{
			tail--;
			WRAP_START(tail, this->capacity);
		}
		WRAP_START(head, this->capacity);
		this->data[head] = val;
	}
	_T PopBack()
	{
		_T tmp = Last(); // will throw on empty
		this->size--;
		this->data[tail--].~_T();
		WRAP_START(tail, this->capacity);
		return tmp;
	}
	_T PopFront()
	{
		_T tmp = First(); // will throw on empty
		this->size--;
		this->data[head++].~_T();
		WRAP_END(head, this->capacity);
		return tmp;
	}
	// TODO: optimize to copy down shorter partition
	void Remove(size_t i) // overload for special case in circular queue
	{
		// find and destruct element
		__CONTAINER_VALIDATE_INDEX(i);
		i += head;
		WRAP_END(i, this->capacity);
		this->data[i].~_T();
		
		// case: simple linear layout
		if(head < tail)
		{
			if(this->size > i + 1) // anything to copy?
				copy(this->data + i + 1, this->data + this->size,
					 this->data + i);
			tail--; // tail was > head so no need to wrap
		}
		// case: end wraps
		else 
		{
			// removing from wrapped region
			if(i < tail)
			{
				copy(this->data + i + 1, this->data + tail, this->data + i);
				tail--;
			}
			// removing from non-wrapped region
			else
			{
				copy(this->data + i + 1, this->data + this->capacity,
					 this->data + i);
				if(tail == 0)	// no actual data around wrap
					tail = this->capacity - 1;
				else			// bring one element to end and copy down
				{
					this->data[this->capacity - 1] = this->data[0];
					copy(this->data + 1, this->data + tail, this->data);
					tail--; // tail was at least 1, so no need to wrap
				}
			}
		}
		this->size--;
	}
protected:
	
	int head, tail;
};

/// Link-based Binary Search Tree //////////////////////////////////////////////


template<typename _T>
class BinTree
{
public:
	BinTree() : root(NULL), size(0) {}
	virtual ~BinTree() { delete root; }
	
	/// inner node class ///
	struct _node
	{
		_node(const _T& data) : data(data), left(NULL), right(NULL) {}
		~_node() { if(left) delete left; if(right) delete right; }
		_T data;
		_node* left, *right;
	};
	
	/// Tree Manipulation ///
	_node* Insert(const _T& val, bool overwrite = false)
	{
		if(root == NULL)
		{
			root = new _node(val);
			size++;
			return root;
		}
		_node* insert = NULL;
		_node* found = locate(root, insert, val);
		if(found)
		{
			if(overwrite)
				found->data = val;
			return found;
		}
		else // root was not NULL, so insert should be valid
		{
			size++;
			if(!insert)
				insert = root;
			if(val < insert->data)
			{
				insert->left = new _node(val);
				return insert->left;
			}
			else
			{
				insert->right = new _node(val);
				return insert->right;
			}
		}
	}
	_node* Remove(const _T& val)
	{
		parent = NULL;
		_node* target = locate(root, parent, val);
		return Remove(target, parent);
		//return parent;
	}
	_node* Remove(_node* target, _node* parent = NULL)
	{
		if(!target || Empty())
			return NULL;
		
		_node* child = NULL;
		if(!target->left && !target->right)		// no children
		{
			if(!parent)
				root = NULL;
			else
			{
				if(parent->left == target)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
		}
		else // has children
		{
			if(target->left && target->right)	// two children
			{
				// find successor node and disconnect from current parent
				_node* succpar = NULL;
				child = successor(target, succpar);
				if(succpar != target)
				{
					if(succpar->left == child)
						succpar->left = NULL;
					else
						succpar->right = NULL;
				}
				
				// reconnect dangling subtrees
				child->left = target->left; // there is no left subtree
				_node* bigend = child;
				while(bigend->right)
					bigend = bigend->right;
				bigend->right = target->right;
			}
			else								// one child
				// only child is successor
				child = (target->left ? target->left : target->right);
			
			// insert the successor node into position in the tree
			if(!parent && root)	// case: removing the root node
			{
				// left and right subtrees are already connected
				root = child;
			}
			else				// case: removing random branch node
			{
				if(parent->left == target)
					parent->left = child;
				else
					parent->right = child;
			}
			
			target->left = target->right = 0; // disconnect and remove
		}
		//delete target;
		size--;
		return target; //child;
	}
	
	_node* RotateLeft(_node* node)
	{
		if(!node)
			return NULL;
		_node* top = node->right;
		node->right = top->left;
		top->left = node;
		return top;
	}
	_node* RotateRight(_node* node)
	{
		if(!node)
			return NULL;
		_node* top = node->left;
		node->left = top->right;
		top->right = node;
		return top;
	}
	
	/// Node Search and Traversal ///
	_node* Search(const _T& val)
	{
		_node* dummy = NULL;
		return locate(root, dummy, val);
	}
	template<class Functor> void PreOrder(Functor f) { PreOrder(root, f); }
	template<class Functor>
	bool PreOrder(_node* top, Functor f)
	{
		if(!top)
			return true;
		if(!f(top))
			return false;
		if(!PreOrder(top->left, f))
			return false;
		return PreOrder(top->right, f);
	}
	template<class Functor> void InOrder(Functor f) { InOrder(root, f); }
	template<class Functor>
	bool InOrder(_node* top, Functor f)
	{
		if(!top)
			return true;
		if(!InOrder(top->left, f))
			return false;
		if(!f(top))
			return false;
		return InOrder(top->right, f);
	}
	template<class Functor> void PostOrder(Functor f) { PostOrder(root, f); }
	template<class Functor>
	bool PostOrder(_node* top, Functor f)
	{
		if(!top)
			return true;
		if(!PostOrder(top->left, f))
			return false;
		if(!PostOrder(top->right, f))
			return false;
		return f(top);
	}
	template<class Functor> void ReverseOrder(Functor f)
	{ ReverseOrder(root, f); }
	template<class Functor>
	bool ReverseOrder(_node* top, Functor f)
	{
		if(!top)
			return true;
		if(!ReverseOrder(top->right, f))
			return false;
		if(!f(top))
			return false;
		return ReverseOrder(top->left, f);
	}
	
	/// Internal state access ///
	inline void Clear() { delete root; root = NULL; size = 0; }
	inline size_t Size() { return size; }
	inline bool Empty() { return size == 0; }
	inline _node* Root() { return root; } // USE WITH CARE!
	inline _node* LastParent() { return parent; }
protected:
	// Modifies parent to immediate parent of (found|NULL) node.
	// Do NOT pass the tree root or a node link unless you want it to get nuked.
	// Returns: Found node, or NULL if it was not found.
	_node* locate(_node* node, _node*& parent, const _T& val)
	{
		if(node == NULL)
			return NULL;
		if(node->data == val)
			return node;
		if(val < node->data)
		{
			parent = node;
			return locate(node->left, parent, val);
		}
		else
		{
			parent = node;
			return locate(node->right, parent, val);
		}
	}
	inline _node* locate_parent(_node* node)
	{
		_node* parent = NULL;
		if(node)
			locate(root, parent, node->data);
		return parent;
	}
	inline _node* locate_sibling(_node* node, _node* parent)
	{
		if(!parent)
			return NULL;
		return parent->left == node ? parent->right : parent->left;
	}
	inline bool is_left(_node* node, _node* parent)
	{
		return parent && parent->left == node;
	}
	inline _node* successor(_node* node, _node*& succpar)
	{
		if(!node || !node->right)
			return NULL;
		succpar = node;
		node = node->right;
		while(node->left)
		{
			succpar = node;
			node = node->left;
		}
		return node;
	}
	
	_node* root, *parent;
	size_t size;
};

/// Red-Black Balanced Sorted Binary Tree //////////////////////////////////////

enum _Col { _RED = 0, _BLACK };
template<typename _T>
struct _col_node
{
	_col_node(const _T& val, _Col col = _RED) : data(val), color(col) {}
	bool operator<(const _col_node& n) const { return data < n.data; }
	bool operator==(const _col_node& n) const { return data == n.data; }
	_Col color;
	_T data;
};

template<typename _T>
class RedBlack : public BinTree<_col_node<_T> >
{
	using BinTree<_col_node<_T> >::RotateLeft;
	using BinTree<_col_node<_T> >::RotateRight;

	using BinTree<_col_node<_T> >::locate_parent;
	using BinTree<_col_node<_T> >::locate_sibling;
	using BinTree<_col_node<_T> >::is_left;

public:
	/// Types ///
	typedef BinTree<_col_node<_T> > _Super;
	typedef typename _Super::_node _node;
	
	/// Tree Manipulation ///
	_node* Insert(const _T& val, bool overwrite = false)
	{
		_node* n = this->_Super::Insert(val, overwrite);
		_node* parent = locate_parent(n);
		if(red_violation(parent))
			fixup(parent);
		this->root->data.color = _BLACK;
		return n;
	}
	_node* Remove(const _T& val)
	{
		_node* tmp = _Super::Remove(val);
		_node* parent = this->LastParent();
		if(red_violation(parent))
			fixup(parent);
		return tmp;
	}
	_node* Remove(_node* target, _node* parent = NULL)
	{
		_node* tmp = _Super::Remove(target, parent);
		if(red_violation(parent))
			fixup(parent);
		return tmp;
	}

	_node* Search(const _T& val)
	{
		return _Super::Search(_col_node<_T>(val));
	}
protected:
	bool red_violation(_node* parent)
	{
		return parent && parent->data.color == _RED &&
		((parent->left && parent->left->data.color == _RED) ||
		 (parent->right && parent->right->data.color == _RED));
	}
	void color_flip(_node* node)
	{
		if(!node)
			return;
		node->data.color = _RED;
		if(node->left)
			node->left->data.color = _BLACK;
		if(node->right)
			node->right->data.color = _BLACK;
	}
	void fixup(_node* parent)
	{
		if(parent && parent == this->root)
		{
			this->root->data.color = _BLACK;
			return;
		}
		
		_node* grandparent = locate_parent(parent);
		_node* greatgrandparent = locate_parent(grandparent);
		_node* uncle = locate_sibling(parent, grandparent);
		_node*& pivot = (greatgrandparent ?
						 (is_left(grandparent, greatgrandparent) ?
						  greatgrandparent->left :
						  greatgrandparent->right) :
						 this->root);
		if(uncle && uncle->data.color == _RED) // red uncle - color flip
		{
			color_flip(grandparent);
		}
		else // black uncle - rotate
		{
			if(parent->left && parent->left->data.color == _RED) // new is left
			{
				if(is_left(parent, grandparent)) // left-left
					pivot = RotateRight(grandparent);
				else							 // right-left
				{
					if(grandparent)
						grandparent->right = RotateRight(parent);
					pivot = RotateLeft(grandparent);
				}
			}
			else // new is right
			{
				if(!is_left(parent, grandparent)) // right-right
					pivot = RotateLeft(grandparent);
				else							 // left-right
				{
					if(grandparent)
						grandparent->left = RotateLeft(parent);
					pivot = RotateRight(grandparent);
				}
			}
			
			// reset colors after rotation
			pivot->data.color = _BLACK;
			if(pivot->left)
				pivot->left->data.color = _RED;
			if(pivot->right)
				pivot->right->data.color = _RED;
		}
	}
	
	
};

/// Reference Table as a Tree-Based Dictionary /////////////////////////////////

#define __REFTAB_FIND_KEY(k) \
	references.Search(table_entry(k))

class RefTable
{
public:
	
	// class level data definitions //
	
	// table entry structure
	struct table_entry
	{
		table_entry(const void* k, const int c) : key(k), count(c) {}
		table_entry(const void* k) : key(k), count(0) {}
		bool operator<(const table_entry& de) const { return key < de.key; }
		bool operator==(const table_entry& de) const { return key == de.key; }
		
		const void* key;
		int count;
	};
	// holds the table entries in the tree
	typedef RedBlack<table_entry>::_node _node;
	
	// C'tor //
	
	RefTable()
	{
		pthread_cond_init(&thread_cond, NULL);
		pthread_mutex_init(&table_lock, NULL);
		pthread_mutex_init(&queue_lock, NULL);
		pthread_create(&monitor, NULL, RefTable::collect, this);
	}
	
	// interface //
	
	void inc(void* k)
	{
		pthread_mutex_lock(&table_lock);
		references.Insert(table_entry(k), false)->data.data.count++;
		pthread_mutex_unlock(&table_lock);
	}
	
	void dec(void* k)
	{
		int& count = search(k);
		if(--count < 0)
			throw Exception(__PRETTY_FUNCTION__, \
				"(Runtime Error) Key does not exist in reftable.");
		if(count == 0)
		{
			//references.Remove(table_entry(k));
			pthread_mutex_lock(&queue_lock);
			garbage.PushBack(k);
			pthread_mutex_unlock(&queue_lock);
			pthread_cond_signal(&thread_cond);
		}
	}

protected:
	
	// Returns 0 if entry doesn't exist
	int& search(const void* k)
	{
		static int zero = 0;
		_node* n = __REFTAB_FIND_KEY(k);
		if(n == NULL)
			return zero;
		return n->data.data.count;
	}
	
	static void* collect(void*);
	
	// state data //

	RedBlack<table_entry> references;
	Deq<void*> garbage;

	pthread_t monitor;
	pthread_cond_t thread_cond;
	pthread_mutex_t table_lock;
	pthread_mutex_t queue_lock;
};