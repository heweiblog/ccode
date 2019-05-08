#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "type.h"

typedef struct StackType{
	size_t len;
	size_t cap;
	pthread_mutex_t lock;
	DataType* ptr;
}Stack;

// 栈初始化
static inline Stack* NewStack(size_t len,size_t cap){
	Stack* s = calloc(1,sizeof(Stack));
	if(!s || len > cap)
		return NULL;
	if(cap > 0){
		s->ptr = calloc(cap,sizeof(DataType));
		if(!s->ptr){
			free(s);
			return NULL;
		}
	}
	s->len = len;
	s->cap = cap;
	pthread_mutex_init(&s->lock,NULL);
	return s;	
}

// 获取栈长度
static inline int StackLen(Stack*s){
	if(!s)
		return -1;
	return s->len;
}

// 获取栈容量
static inline int StackCap(Stack*s){
	if(!s)
		return -1;
	return s->cap;
}

// 入栈 一次性可入栈多个元素
static inline int StackPush(Stack*s,DataType*d,size_t size){
	if(!s || !d)
		return -1;
	DataType*pd = NULL;
	pthread_mutex_lock(&s->lock);
	if(size+s->len > s->cap){
		pd = calloc((size+s->cap)*2,sizeof(DataType));
		if(!pd){
			pthread_mutex_unlock(&s->lock);
			return 0;
		}
		if(s->len > 0){
			memcpy(pd,s->ptr,s->len*sizeof(DataType));
		}
		if(s->cap > 0){
			free(s->ptr);
		}
		s->ptr = pd;
	}
	memcpy(s->ptr+s->len,d,size*sizeof(DataType));
	s->len += size;
	pthread_mutex_unlock(&s->lock);
	return size;
}

// 入栈 一次性入栈1个元素
static inline int StackPushOne(Stack*s,DataType*d){
	if(!s || !d)
		return -1;
	DataType*pd = NULL;
	pthread_mutex_lock(&s->lock);
	if(1+s->len > s->cap){
		pd = calloc((1+s->cap)*2,sizeof(DataType));
		if(!pd){
			pthread_mutex_unlock(&s->lock);
			return 0;
		}
		if(s->len > 0){
			memcpy(pd,s->ptr,s->len*sizeof(DataType));
		}
		if(s->cap > 0){
			free(s->ptr);
		}
		s->ptr = pd;
	}
	memcpy(s->ptr+s->len,d,sizeof(DataType));
	s->len++;
	pthread_mutex_unlock(&s->lock);
	return 1;
}

// 出栈 一次出栈一个元素 
static inline DataType* StackPop(Stack*s){
	if(!StackLen(s))	
		return NULL;
	DataType* d = NULL;
	pthread_mutex_lock(&s->lock);
	d = &s->ptr[s->len-1];
	s->len--;
	pthread_mutex_unlock(&s->lock);
	return d;
}

static inline void StackClear(Stack*s){
	if(!s)
		return;
	pthread_mutex_lock(&s->lock);
	if(!s->ptr)	
		free(s->ptr);
	s->len = 0;
	s->cap = 0;
	pthread_mutex_unlock(&s->lock);
	free(s);
}

#endif
