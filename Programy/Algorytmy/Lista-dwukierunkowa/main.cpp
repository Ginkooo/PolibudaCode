#include <stdio.h>
#include <stdlib.h>


typedef struct element{
	int value;
	struct element *prev, *next;
} element;

typedef struct linked_list{
	element *start;
	int count;
}  ll;

ll* create_ll(){
	element *head = (element*)malloc(sizeof(element));
	head->value=0;
	head->prev=NULL;
	head->next=NULL;
	
	ll *linked_list = (ll*)malloc(sizeof(ll));
	linked_list->start=head;
	linked_list->count=0;
	return linked_list;
}


void print_ll(ll *linked_list){
	puts("");
	int index=0;
	element* temp=linked_list->start;
	if (temp->next!=NULL){
			temp=linked_list->start->next;
	}
	if (temp->next==NULL && temp->prev==NULL){
		
		printf("There is no elements"); return;
		}
	while (temp->next!=NULL){
		printf("ll[%d]=%d\n", index, temp->value);
		index++;
		temp=temp->next;
	}
	if (temp->prev!=NULL)
		printf("ll[%d]=%d\n", index, temp->value);
}

void print_ll_bck(ll *linked_list){
	int index=0;
	element *temp = linked_list->start;
	if (temp->next!=NULL)
			temp=linked_list->start->next;
	if (temp->next==NULL && temp->prev==NULL){
		
		printf("There is no elements"); return;
		}
	while(temp->next!=NULL){
		temp=temp->next;
		index++;
	}
	while (temp->prev!=NULL){
		printf("ll[%d]=%d\n", index, temp->value);
		index--;
		temp=temp->prev;
	}
}

void del_node_at_inx(ll* linked_list, int index){
	if (index<0) {printf("Index must ba grater or equal 0"); return; }
	int ix;
	element* temp=linked_list->start;
	for (ix=0; ix<=index; ix++){
	if (temp->next!=NULL)
		temp=temp->next;
	if (temp->next==NULL && ix<index)
		{
		printf("There is no such an index");
		return;
		}
	}
	if (temp->next!=NULL){
		temp->next->prev=temp->prev;
		temp->prev->next=temp->next;
		}
	else
		temp->prev->next=NULL;
	free(temp);
}

void add_node_at_inx(ll* linked_list, int value, int index){
	
	element* temp=linked_list->start;
	if (index<0) { printf("Error: index must be greater than 0"); fflush(stdout); return; }
	while(temp->next!=NULL && index>0){
		temp=temp->next;
		index--;
	}
		element* node = (element*)malloc(sizeof(element));
		node->next=temp->next;
		node->prev=temp;
		temp->next=node;
		node->value=value;
		if (node->next!=NULL)
			node->next->prev=node;
		linked_list->count++;
}

int get_node_inx_by_val(ll* linked_list, int value){
	element* temp= linked_list->start;
	int ix=0;
	while (temp->next!=NULL){
	if (temp->value==value)
		return ix;
		ix++;
		temp=temp->next;
	}
	if (temp->next==NULL)
		if (temp->value==value){
			ix++;
			return ix;
		}
		return -1;
	
}

void replace_node_by_value(ll* linked_list, int fromVal, int toVal){
	element* temp= linked_list->start;
	while (temp->next!=NULL){
	if (temp->value==fromVal){
		temp->value=toVal;
		return;
		}
		temp=temp->next;
	}
	if (temp->next==NULL)
		if (temp->value==fromVal){
			temp->value=toVal;
		}
}

void delete_node_by_value(ll* linked_list, int value){
	element* temp= linked_list->start;
	while (temp->next!=NULL){
	if (temp->value==value){
		temp->next->prev=temp->prev;
		temp->prev->next=temp->next;
		free(temp);
		return;
		}
		temp=temp->next;
	}
	if (temp->next==NULL)
		if (temp->value==value){
			temp->prev->next=NULL;
			return;
		}
}


	


int main(){
	ll* linked_list = create_ll();
	int choose, val, idx, toVal;
	while(1==1){
		printf("What do you want to do? 1-add an element, 2-print elements 3-print backwards, 4-Delete element at index, 5-Get first index by value, 6-replace values, 7-delete element by value: ");
		scanf("%d", &choose);
		switch(choose){
			case 1:
				printf("Input value of element and index you want to put it after: ");
				scanf("%d %d", &val, &idx);
				add_node_at_inx(linked_list, val, idx);
				break;
			case 2: print_ll(linked_list); printf("\n"); break;
			case 3: print_ll_bck(linked_list); printf("\n"); break;
			case 4: 
				printf("Input index of element you want to delete: ");
				scanf("%d", &idx);
				del_node_at_inx(linked_list, idx);
				break;
			case 5:
				printf("Input value you looking for: ");
				scanf("%d", &val);
				printf("Is at index %d", get_node_inx_by_val(linked_list, val));
				break;
			case 6:
				printf("Input value you want to replace and value to replace with: ");
				scanf("%d %d", &val, &toVal);
				replace_node_by_value(linked_list, val, toVal);
				break;
			case 7:
				printf("Input value to delete: ");
				scanf("%d", &val);
				delete_node_by_value(linked_list, val);
				break;
			default: printf("Wrong choice\n");
		}
		printf("\n\n\n\n");
	}
}
