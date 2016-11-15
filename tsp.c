/*TSP
Last update: changed data type of co-ordinates to double
Updated om 14th November 2016 at 8 am*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<float.h>
#include<time.h>
#define SIZE 10

typedef struct city {
	char name[20];
	double x;
	double y;
}city;

city list[SIZE];
int list_size = -1; //stores city with the highest index in list
double graph[SIZE][SIZE];

/*Function prototypes*/
void updateGraph(city);
int flag(int, int);
void digittocity(int);
void newCity();
double distance(city, city);
int seed();
int factorial(int);
double dist(int); //path distance
void combination(int);
int equalsum(int, int);
void userInput();
void display_graph();
void nn();
void intro();
void bye();
/*End of function prototypes*/

int main()
{
	intro();
	userInput();
	display_graph();
	clock_t start = clock(), diff; //start calculating how long brute force takes
	combination(seed()); //brute force function
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
	start = clock(); //start calculating how long NN takes
	nn();
	diff = clock() - start;
	msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
	bye();
	return 0;
}

void intro()
{
	printf("\n---------------------------------------------------------------------------------------------------------------------\n\t\t\t\t\tTHE TRAVELLING SALESMAN PROBLEM\n Follow the instructions and we will give you the shortest path to visit each city and return to the original city\n---------------------------------------------------------------------------------------------------------------------\n");
}
void bye()
{
	printf("---------------------------------------------------------------------------------------------------------------------\n");
}
void newCity()
{
	char new_name[20];
	double X, Y;
	if (list_size == -1)
		printf("Enter name of the starting city: ");
	else
		printf("Enter next city name: ");
	scanf("%s", new_name);
	printf("Enter the X co-ordinate of %s (in km): ", new_name);
	scanf("%lf", &X);
	printf("Enter the Y co-ordinate of %s (in km): ", new_name);
	scanf("%lf", &Y);
	list_size++;
	int i;
	for(i = 0; new_name[i] != '\0'; i++)
		list[list_size].name[i] = new_name[i]; 
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

int seed()
{
	int temp = list_size - 1;
	long int first_path = 0;
	int i = 0;
	for (i=1;i<=list_size;i++)
	{
		first_path=first_path + i*pow(10,temp);
		temp--;
	}
	return first_path;
}
int factorial(int n)
{	int fact = 1;
	while(n)
	{
		fact = fact*n;
		n--;
	}
	return fact;
}

double dist(int n)
{
    int reverse = 0;
    double path = 0;
    while (n != 0)
    {
          reverse = reverse * 10;
          reverse = reverse + (n%10);
          n = n/10;
    }    
      int i, j = 0 ;
      while (reverse != 0)
      {
        i = reverse % 10;
        path = path + graph[j][i];
        j = i;
        reverse = reverse/10;
    }
    path = path + graph[j][0];
    return path;
}

void combination(int number)
{	
	int loop = (factorial(list_size))/2;
	double smallest = dist(number);
	int count=1, c = number;
	int num_return = number;
	while(count <= loop)
	{
		c += 9;
		if(flag(number, c))
		{
			if(dist(c) < smallest)
			{
				num_return = c;
				smallest = dist(c);		
			}
			count++;
		}
	}
	printf("\nBRUTE FORCE SEARCH\n");
	printf("Shortest path : ");
	digittocity(num_return);
	printf("Distance of shortest path: %lf km\n", smallest);
	printf("Combinations tried: %d\n", count-1);
}

int equalsum(int n1, int n2)
{
		int sum1, sum2, a, b;
		sum1 = 0;
		sum2 = 0;
		while(n1!=0){
			a = n1%10;
			sum1 = sum1 + a;
			n1 = n1/10;
		}
		while(n2!=0){
			b = n2%10;
			sum2 = sum2 + b;
			n2 = n2/10;
		}
		if(sum1 == sum2) return (1);
}

int flag (int num1, int num2) {
	if(!equalsum(num1, num2))
		return 0;
    int digits[10];
    int i;

    for (i = 0; i < 10; i++)      // Init all counts to zero.
        digits[i] = 0;

    while (num1 != 0) {           // Process all digits.
        digits[num1%10]++;        // Increment for least significant digit.
        num1 /= 10;               // Get next digit in sequence.
    }

    while (num2 != 0) {           // Same for num2 except decrement.
        digits[num2%10]--;
        num2 /= 10;
    }

    for (i = 0; i < 10; i++)
        if (digits[i] != 0)       // Any count different, not a permutation.
            return 0;

    return 1;                  // All count identical, was a permutation.
}

void digittocity(int number)
{	
	int temp;
	printf("%s -> ", list[0].name);
	for (temp=number; temp; temp /= 10)
		printf("%s -> ",list[temp%10].name);
	printf("%s\n", list[0].name);
}

void userInput()
{
	int temp, i;
	printf("Enter number of cities: ");
	scanf("%d", &temp);
	if (temp > SIZE)
	{
		printf("Please enter fewer number of cities\n");
		userInput();
		return;
	}
	for(i = 0; i < temp; i++)
		newCity();
}
void nn()
{ // assuming 4 cities
	bool visited[list_size+1]; //3+1 = 4
	int i = 0;
	int next_city_index;
	int cities_visited = 0;
	int current_city_index = 0;
	int path = 0;
	int count = 0;
	double smallest;
	for(cities_visited = 0; cities_visited < list_size; cities_visited++) //0 < 3 
	{
		smallest = DBL_MAX;
		visited[current_city_index] = true;
		for(i = 0; i <= list_size; i++) //0 <= 3
		{
			if ((!visited[i]) && (graph[current_city_index][i] < smallest))
			{
				smallest = graph[current_city_index][i];
				next_city_index = i;
			}
			count++; //just for no. of comparisons
		}
		current_city_index = next_city_index;
		path = path*10 + current_city_index;
	}
	printf("\nNEAREST NEIGHBOUR ALGORITHM\n");
	printf("Shortest path : ");
	digittocity(path);
	printf("Distance of shortest path = %lf km\n", dist(path));
	printf("Comparisons made = %d\n", count);
}
void display_graph()
{
	printf("\nGRAPH\n");
	int i, j;
	printf("\t");
	for(i = 0; i <= list_size; i++)
		printf("%s\t\t", list[i].name);
	printf("\n");
	for(i = 0; i <= list_size; i++)
	{
		printf("%s\t", list[i].name);
		for(j = 0; j <= list_size; j++)
			printf("%lf\t", graph[i][j]);
		printf("\n");
	}
}
