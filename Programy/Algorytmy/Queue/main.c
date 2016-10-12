#include <stdio.h>
#include <stdlib.h>

typedef struct element{
	int value;
	struct element *prev;
} elem_t;

typedef struct queue{
	elem_t* first;
	elem_t* last;
} queue_t;


queue_t* createQueue(){
	queue_t* newQueue = (queue_t*)malloc(sizeof(queue_t));
	newQueue->first = NULL;
	newQueue->last = NULL;
	return newQueue;
}

void enqueue(queue_t* queue, int value){
	elem_t* newNode = (elem_t*)malloc(sizeof(elem_t));
	newNode->value=value;
	newNode->prev=NULL;
	
	
	if (queue->first==NULL){
		queue->first=newNode;
		queue->last=newNode;
		return;
	}
	
	queue->last->prev=newNode;
	queue->last=newNode;
	
}

int dequeue(queue_t* queue){
	
	if (queue->first==NULL){
		return -1;
	}
	
	int value = queue->first->value;
	
	if (queue->first->prev==NULL){
		free(queue->first);
		queue->first=NULL;
		queue->last=NULL;
		return value;
	}
	
	elem_t* temp = queue->first->prev;
	free(queue->first);
	queue->first=temp;
	
	return value;
}

void printQueue(queue_t* queue){
	if (queue->first==NULL){
		printf("Queue is empty\n");
		return;
	}
	
	elem_t* temp = queue->first;
	
	while (temp->prev!=NULL){
		printf("%d ", temp->value);
		fflush(stdout);
		temp=temp->prev;
	}
	
	printf("%d \n", temp->value);
	fflush(stdout);
	
}

int main(){
	queue_t* myQueue = createQueue();
	int choice, value;
	for(;;){
		printf("1: Enqueue, 2: Dequeue, 3: Print queue - ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				printf("Input value: ");
				scanf("%d", &value);
				enqueue(myQueue, value);
				break;
			case 2:
				value=dequeue(myQueue);
				
				if (value==-1){
					printf("Queue is empty\n");
					break;
				}
				
				printf("Next value is: %d\n", value);
				break;
			case 3:
				printQueue(myQueue);
				break;
			default:
				printf("Wrong choice\n");
		}
	}
	
	
	
	return 0;
}