// CXE.h
// Colossus compiler
// CXE Interfaces - Colossus Translation Engine


// TODO:
// resolve fine access specs in C++
// foreach
// java
// c#


#pragma once

#include <string>
	using std::string;

#include "Exception.h"


enum Access
{
	ACC_PUBLIC, ACC_PROTECTED, ACC_PRIVATE, ACC_NONE
};
string access_text(Access a);

// Base class for a code element ///////////////////////////////////////////////

class Element
{
public:
	Element() {}
	Element(const string& s) : text(s) {}
	virtual ~Element() {}
	
	virtual string str() const;

protected:
	string text;
};

// represents a variable in the target language ////////////////////////////////

class Var : public Element
{
public:
	Var(const string& name) : Element(name) {}
	virtual ~Var() {}
};

// represents an expression in the target language /////////////////////////////

// The expression class(es) should be as universal as possible,
// e.g. operator overloading should be handled at the parser level
// and any arithmetic-form expression should be literal math ops.
class Expr : public Element
{
public:
	Expr(const string& content) : Element(content) {}
	Expr(Var& v) : Element(v.str()) {}
	virtual ~Expr() {}

	virtual Expr operator-() const;
	virtual Expr operator++();
	virtual Expr operator++(int dummy); // post inc
	virtual Expr operator--();
	virtual Expr operator--(int dummy); // post dec

	virtual Expr operator+(const Expr& e) const;
	virtual Expr operator-(const Expr& e) const;
	virtual Expr operator*(const Expr& e) const;
	virtual Expr operator/(const Expr& e) const;
	virtual Expr operator%(const Expr& e) const;
};

// represents a method or function in the target language //////////////////////

class Method : public Element
{
public:
	Method() {}
	Method(const string& name) : Element(name) {}
	virtual ~Method() {}
	
	virtual Var NewVar(const string& type, const string& name) = 0;
	virtual void Allocate(const Var& var, const string& type) = 0;

	// compile instructions into the method
	virtual Var Call(Method* method) = 0;
	virtual void CallVoid(Method* method) = 0;
	virtual Var Call(const Var& cls, Method* method) = 0;
	virtual void CallVoid(const Var& cls, Method* method) = 0;
	virtual void Assign(const Var&, const Expr&) = 0;
	virtual void Return(const Expr&) = 0;
	virtual void Return() = 0;
	
	virtual void End() = 0;

	virtual const string& Ret() = 0;
	virtual const string& Name() = 0;
	virtual const string& Params() = 0;
	virtual string Sig() const = 0;
	virtual const string& Body() const = 0;
};

// represents a class member of any sort ///////////////////////////////////////

struct Member : public Element
{
	Member(Access a, Element* e) : acc(a), e(e) {}
	~Member() { delete e; }

	Access acc;
	Element* e;
	
	virtual string str() const { return access_text(acc) + " " + e->str(); }
};

// represents a class in the target language ///////////////////////////////////

class Class : public Element
{
public:
	Class() : Element("{\n") {}
	virtual ~Class() {}
	
	virtual void SetAccess(Access a) = 0;

	virtual Method* Ctor() = 0;
	virtual Method* Dtor() = 0;

	virtual Method* Main() = 0;
	virtual Method* NewMethod(Access a, const string& ret, const string& name,
							  const string& params) = 0;
	virtual Var NewVar(Access a, const string& type, const string& name) = 0;
	
	virtual void End() = 0;
};

// defines a compilation unit //////////////////////////////////////////////////

class Module : public Element
{
public:
	virtual ~Module() {}

	virtual Class* NewClass(const string& name) = 0;
	virtual Class* NewClass(const string& name, const string& inheritance) = 0;
	virtual void End() = 0;
};

// platform-specific implementations, so only this header need be included /////

#include <vector>
#include "CXE_Common.h"
#include "CXE_Cpp.h"
#include "CXE_Java.h"
#include "CXE_Cs.h"
