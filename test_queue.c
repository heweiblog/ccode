#include <stdio.h>
#include "queue.h"

typedef struct queue_node{
	int num;
	struct list_head node;
}Qnode;

int main(){
	Queue*q = NewQueue();
	if(!q)
		return -1;
	int i = 0;
	for(i = 1 ; i < 10 ; i++){
		Qnode* n = calloc(1,sizeof(Qnode));
		n->num = i;
		QueuePush(q,&n->node);
	}
	
	struct list_head* l = NULL;
	Qnode* n = NULL;
	//while(l = QueuePop(q)){
	while(l = QueueFront(q)){
		n = list_entry(l,Qnode,node);
		printf("%d\n",n->num);
		free(n);
	}
	free(q);
}
