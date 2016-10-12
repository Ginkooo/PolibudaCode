#include <stdio.h>

struct Student {
	int nr_index;
	int ocena;
};

int SORT01(struct Student student[], int n);

int main()
{
	int n;
	int i;
	int temp;
	printf("Podaj ilosc studentow\n");
	scanf("%d", &n);
	struct Student student[n];
	for (i=0; i<n; i++)
	{
		printf("Podaj numer indeksu %d studenta i jego ocene\n", i);
		scanf("%d %d", &student[i].nr_index, &student[i].ocena);
	}
	temp=SORT01(student, n);
	puts("Zdali:");
	for (i=0; i<=temp; i++)
		printf("%d\n", student[i].nr_index );
	puts("");
	puts("Nie zdali:");
	for (i=temp+1; i<n; i++)
		printf("%d\n", student[i].nr_index);

	return 0;
}

int SORT01(struct Student student[], int n)
{
	int i;
	for (i=0; i<n; i++)
			printf("%d ", student[i].nr_index);
	int l=0;
	int p=n-1;
	struct Student temp;
	while(p>l)
	{
		while ((student[l].ocena>=3) && (p>l))
			l++;
		while((student[p].ocena)<3 && (p>l))
			p--;
		if (p>l)
		{
			temp=student[p];
			student[p]=student[l];
			student[l]=temp;
			l++;
			p--;
		}

		for (i=0; i<n; i++)
			printf("%d ", student[i].nr_index);
		puts("");
	}
	if (student[p].ocena>=3)
		return p;
	else
		return p+1;
}


