// gc.cpp
// Colossus runtime
// garbage collection


#include <iostream>
	using std::cout;
	using std::endl;

#include "gc.h"


void* RefTable::collect(void* me)
{
	RefTable& table = *(RefTable*)me;
	Deq<void*>& garbage = table.garbage;
	RedBlack<table_entry>& references = table.references;
	void* k;

	//sleep(1); // guaranteed at least 1 second between gc runs
	pthread_mutex_lock(&table.queue_lock);
	while(1)
	{
		pthread_cond_wait(&table.thread_cond, &table.queue_lock); // sleep
		while(garbage.Size())
		{
			k = garbage.PopFront();
			pthread_mutex_unlock(&table.queue_lock);
			
			pthread_mutex_lock(&table.table_lock);
			references.Remove(table_entry(k));
			pthread_mutex_unlock(&table.table_lock);
			
			delete k;
			pthread_mutex_lock(&table.queue_lock);
		}
	}
	pthread_mutex_unlock(&table.queue_lock);

	return NULL;
}
