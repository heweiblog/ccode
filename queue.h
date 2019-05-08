#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <pthread.h>
#include "list.h"

typedef struct QueueType{
	int len;
	pthread_mutex_t lock;
	struct list_head head;
}Queue;

// 初始化
static inline Queue* NewQueue(){
	Queue * q = calloc(1,sizeof(Queue));
	if(!q)
		return NULL;
	
	pthread_mutex_init(&q->lock,NULL);
	INIT_LIST_HEAD(&q->head);
	return q;
}

// 队列大小 根据具体情况控制队列大小 返回0说明队列为空
static inline int QueueLen(Queue*q){
	if(!q)
		return -1;
	return q->len;
}

// 入队
static inline void QueuePush(Queue*q,struct list_head *l){
	if(!q || !l)
		return;

	pthread_mutex_lock(&q->lock);
	list_add_tail(l,&q->head);
	q->len++;
	pthread_mutex_unlock(&q->lock);
}

// 出队并删除节点 
static inline struct list_head* QueuePop(Queue*q){
	if(!q || QueueLen(q) <= 0)
		return NULL;
	
	struct list_head* l = NULL;
	pthread_mutex_lock(&q->lock);
	l = q->head.next;
	list_del(q->head.next);
	q->len--;
	pthread_mutex_unlock(&q->lock);

	return l;
}

// 出栈并删除节点 
static inline struct list_head* QueueFront(Queue*q){
	if(!q || QueueLen(q) <= 0)
		return NULL;
	
	struct list_head* l = NULL;
	pthread_mutex_lock(&q->lock);
	l = q->head.prev;
	list_del(q->head.prev);
	q->len--;
	pthread_mutex_unlock(&q->lock);

	return l;
}

#endif
