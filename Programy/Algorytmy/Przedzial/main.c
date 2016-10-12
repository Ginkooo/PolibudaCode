//Jeśli podać na sztywno tablice, to działa. Jeśli wprowadzić ją z klawiatury - nie działa. Nie mam pojęcia o co chodzi.


#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
	int firstNum;
	int lastNum;
}interval;

int SORT01(int tab[], int n);
void quicksort(int tab[], int lo, int hi);
int partition(int tab[], int lo, int hi);
interval lookforWidestInterval(int tab[], int n, int width);
int isInInterval(int num, int actual, int width);
int isEven(int num);

int main()
{
	int i;
	int n;
	// puts("Input numbers of elements in the array:");
	// scanf("%d", &n);
	// int tab[n];
 	// for(i=0; i<n; i++)
	// {
		// printf("tab[%d]= ", i);
		// scanf("%d", &tab[i]);
	// }
	int tab[] = {2,2,4,7,14,18,7,2,5};
	n=9;
	int lastEvenIndex=SORT01(tab, n);
	puts("SORT01:");
	for(int i=0; i<n; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
	quicksort(tab, 0, lastEvenIndex);
	puts("Even elements:");
	for(int i=0; i<=lastEvenIndex; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
	puts("Biggest interval:");
	interval tempInterval;
	tempInterval=lookforWidestInterval(tab, lastEvenIndex+1, 5);
	printf("\n<%d; %d>", tempInterval.firstNum, tempInterval.lastNum);
}

int SORT01(int tab[], int n)
{
	int p=n-1;
	int l=0;
	int temp;
	while (p>l)
	{
		while (isEven(tab[l]) == 0 && p>l)
			l++;
		while (isEven(tab[p])!=0 && p>l)
			p--;
		if (p>l)
		{
			temp=tab[p];
			tab[p]=tab[l];
			tab[l]=temp;
			p--;
			l++;
		}
	}
	if(isEven(tab[p])==0)
		return p;
	else
		return p-1;
}

void quicksort(int tab[], int lo, int hi)
{
	if (lo<hi)
	{
		int p=partition(tab, lo, hi);
		quicksort(tab, lo, p-1);
		quicksort(tab, p+1, hi);
	}
}

int partition(int tab[], int lo, int hi)
{
	int pivot=tab[hi];
	int temp;
	int i=lo;
	int j;
	for(j=lo; j<hi; j++)
	{
		if(tab[j]<=pivot)
		{
			temp=tab[j];
			tab[j]=tab[i];
			tab[i]=temp;
			i++;
		}
	}
	temp=tab[hi];
	tab[hi]=tab[i];
	tab[i]=temp;
	return i;
}

int isEven(int num)
{
	if (num%2==0)
		return 0;
	else
		return 1;

}

interval lookforWidestInterval(int tab[], int n, int width)
{
	interval widestInterval;
	int lastIndex = n-1;
	int l=0;
	int r;
	int temp;
	int maxInterval=0;
	while (tab[r]<=tab[lastIndex])
	{
		temp=0;
		r=l;
		while(r<lastIndex && isInInterval(tab[r], tab[l], width) == 0)
		{
			r++;
			temp++;
			if(isInInterval(tab[r], tab[l], width) != 0)
			{
				r--;
				temp--;
				break;
			}
		}
		
		if (temp>maxInterval)
		{
			maxInterval=temp;
			widestInterval.firstNum=tab[l];
			widestInterval.lastNum=tab[r];
		}
		
		l++;
	}
		return widestInterval;
}

int isInInterval(int num, int actual, int width)
{
	if (num-actual<=width)
		return 0;
	else 
		return 1;
}