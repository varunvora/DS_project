/*TSP*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<float.h>
#define SIZE 10

typedef struct city {
	char name[20];
	int x;
	int y;
}city;

city list[SIZE];
int list_size = -1;
double graph[SIZE][SIZE];

void updateGraph(city);
int flag(int, int);

void newCity()
{
	char new_name[20];
	int X, Y;
	if (list_size == -1)
		printf("Enter name of the starting city: ");
	else
		printf("Enter next city name: ");
	scanf("%s", new_name);
	printf("Enter the X co-ordinate of %s (in km): ", new_name);
	scanf("%d", &X);
	printf("Enter the Y co-ordinate of %s (in km): ", new_name);
	scanf("%d", &Y);
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

int seed(int x)
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
int factorial(int count)
{	int fact = 1;
	while(count>0)
	{
		fact = fact*count;
		count--;
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

int combination(int number)
{	
	int loop = (factorial(list_size))/2;
	double smallest = dist(number),count=1;int c = number;
	int num_return = number;
	while(count < loop)
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
	return num_return;
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
	for(i = 0; i < temp; i++)
		newCity();
}
int nn()
{ // assuming 4 cities
	bool visited[list_size+1]; //3+1 = 4
	int i = 0;
	int next_city_index;
	int cities_visited = 0;
	int current_city_index = 0;
	int path = 0;
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
		}
		current_city_index = next_city_index;
		path = path*10 + current_city_index;
	}
	return path;
}
int main()
{
	userInput();
	printf("the first city: %s\n", list[0].name);
	printf("the first city: %s\n", list[1].name);
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
	int ans = combination(seed(list_size));
	printf("\nFINAL ANSWER: %d\n", ans);
	digittocity(ans);
	ans = nn();
	printf("\nfinal nn answer: %d\n", ans);
	digittocity(ans);	
	return 0;
}
