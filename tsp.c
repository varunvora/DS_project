/*TSP*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define SIZE 10

typedef struct city {
	char *name;
	int x;
	int y;
}city;

city list[SIZE];
int list_size = -1;
double graph[SIZE][SIZE];

void updateGraph(city);

void newCity()
{
	char new_name[20];
	int X, Y;
	printf("Enter city name: ");
	scanf("%s", new_name);
	printf("Enter the X co-ordinate of %s (in km): ", new_name);
	scanf("%d", &X);
	printf("Enter the Y co-ordinate of %s (in km): ", new_name);
	scanf("%d", &Y);
	list[++list_size].name = new_name;
	list[list_size].x = X;
	list[list_size].y = Y;	
	updateGraph(list[list_size]);
}
double distance(city A, city B)
{
	return (sqrt(pow((A.x-B.x),2) + pow((A.y-B.y),2)));
}
void updateGraph(city A)
{
	int temp = list_size;
	for (temp = list_size; temp >= 0; temp--)
	{
		graph[list_size][temp] = distance(A, list[temp]);
		graph[temp][list_size] = graph[list_size][temp];
	}
}
void userInput()
{
	int temp, i;
	printf("Enter number of cities: ");
	scanf("%d", &temp);
	for(i = 0; i < temp; i++)
		newCity();
}
int main()
{
	userInput();
	printf("the first city: %s\n", list[0].name);
	printf("the first city: %s\n", list[1].name);
	int i, j;

	for(i = 0; i <= list_size; i++)
		printf("%s\t", list[i].name);
	printf("\n");
	for(i = 0; i <= list_size; i++)
	{
		printf("%s\t", list[i].name);
		for(j = 0; j <= list_size; j++)
			printf("%lf\t", graph[i][j]);
		printf("\n");
	}
	return 0;
}
