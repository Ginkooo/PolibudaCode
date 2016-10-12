#include <stdio.h>
#include <stdlib.h>

struct Point {
	int x;
	int y;
};

int isOnAxis(struct Point point);
int isInEvenQuarter(struct Point point);
int isInOddQuarter(struct Point point);
int* SORT012(struct Point point[], int n);

int main(){
	int n;
	int i;
	int *temp;
	puts("Podaj ilosc punktow do wprowadzenia:");
	scanf("%d", &n);
	struct Point point[n];
	for (i=0; i<n; i++){
		printf("Point %d:\n", i);
		printf("x= ");
		scanf("%d", &point[i].x);
		printf("y= ");
		scanf("%d", &point[i].y);
	}
	temp=SORT012(point, n);
	puts("");
	puts("On axis:");
	for (i=0; i<temp[0]; i++)
		printf("%d %d\n", point[i].x, point[i].y);
	puts("In even quarter:");
	for (i=temp[0]; i<temp[1]; i++)
		printf("%d %d\n", point[i].x, point[i].y);
	puts("In odd quarter:");
	for (i=temp[1]+1; i<n; i++)
		printf("%d %d\n", point[i].x, point[i].y);
}

int* SORT012(struct Point point[], int n){
	int n1=-1;
	int n2=0;
	int n3=n;
	int *temp;
	temp=(int*)malloc(2*sizeof(int));
	struct Point p;
	while(n2<n3){
		p=point[n2];
		if (isInEvenQuarter(p) == 0)
			n2++;
		if (isOnAxis(p) == 0){
			n1++;
			point[n2]=point[n1];
			point[n1]=p;
			if (n1==n2)
				n2++;
		}
		if (isInOddQuarter(p) == 0){
			n3--;
			point[n2]=point[n3];
			point[n3]=p;
		}
	}
	temp[0]=n1+1;
	temp[1]=n2;
	return temp;
}


int isOnAxis(struct Point point){
	if (point.x==0 || point.y ==0)
		return 0;
	else
		return 1;
}
int isInEvenQuarter(struct Point point){
	if((point.x<0 && point.y>0) || (point.x>0 && point.y<0))
		return 0;
	else
		return 1;
}
int isInOddQuarter(struct Point point){
	if((point.x>0 && point.y>0) || (point.x<0 && point.y<0))
		return 0;
	else
		return 1;
}