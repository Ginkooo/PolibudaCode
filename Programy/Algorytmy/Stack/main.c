#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
	int value;
	struct Element *prev;
} element;

element* createStack();
void push(element **lastStackEl, int value);
int pop(element **lastStackEl);
void printStack(element **lastStackEl);


int main()
{
	int i;
	int n;
	int temp;
	
	element* myStack=createStack();
	
	printf("How many elements you want to push?: ");
	scanf("%d", &n);
	for (i=0; i<n; i++)
	{
		printf("%d. element: ", i);
		scanf("%d", &temp);
		push(&myStack, temp);
	}
	printStack(&myStack);
	printf("How many elements you want to pop?: ");
	scanf("%d", &n);
	for (i=n; i>0; i--)
	{
		if (myStack->value==0)
		{
			puts("That was last element");
			break;
		}
		
		printf("%d. element: %d\n", i, pop(&myStack));
	}
	
}

element* createStack()
{
	element* temp = (element*)malloc(sizeof(element));
	temp->value=0;
	temp->prev=0;
	return temp;
}

void push(element **lastStackEl, int value)
{
	element *temp=(element*)malloc(sizeof(element));
	temp->value=value;
	temp->prev=*lastStackEl;
	*lastStackEl=temp;
}

int pop(element **lastStackEl)
{	
	int poppedValue = (*lastStackEl)->value;
	element *temp = (*lastStackEl)->prev;
	free(*lastStackEl);
	*lastStackEl=temp;
	return poppedValue;
}

void printStack(element **lastStackEl){
	element *temp = *lastStackEl;
	while (temp->prev!=NULL){
		printf("%d ", temp->value);
		temp=temp->prev;
	}
}
