#include <stdio.h>
#include "stack.h"



int main(){
	Stack*s = NewStack(0,0);
	if(!s)
		return -1;
	int i = 0;
	DataType* d = NULL;
	for(i = 1 ; i <= 10 ; i++){
		StackPushOne(s,&i);
		printf("push one = %d,len = %d\n",i,StackLen(s));
	}
	
	DataType dd[5] = {11,22,33,44,55};
	StackPush(s,dd,5);
	printf("push many = {11,22,33,44,55},len = %d\n",StackLen(s));
	
	int len = StackLen(s);
	for(i = 1 ; i < len ; i++){
		d = StackPop(s);
		printf("pop one = %d,len = %d\n",*d,StackLen(s));
	}

	StackClear(s);

	//while(l = StackPop(s)){
	/*
	while(l = StackFront(s)){
		n = list_entry(l,Qnode,node);
		printf("%d\n",n->num);
		free(n);
	}
	free(s);
	*/
}
