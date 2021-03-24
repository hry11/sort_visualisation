#include <iostream>
#include <ctime>
#include <math.h>//ceil
#include <SFML/Graphics.hpp>
#include <unistd.h> //sleep() function
using namespace std;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Sort",sf::Style::Default);

void randfill(int *arr, int len, int min, int max)
{
	int i;
	for(i=0; i<len; i++)
	{
		*(arr+i) = rand()%(max-min)+min;
	}
}

int display(int *arr, int len) //could be optimized by only displaying the rectangles corresponding to the values that have changed in the array, but performance is satisfying
{
	sf::RectangleShape rectangles[len];
	int i;
	int height = window.getSize().y; //screen height
	int scalar = 1; //scalar for rectangle height
	int width = window.getSize().x; //screen width
	int rect_width = width/(len);
	//cout << "\n screen: " << width << "	rect: " << rect_width << "\n\n\n";
	int rect_height;
	window.clear();
	for(i=0; i<len; i++)
	{
		rect_height = *(arr+i)*scalar;
		rectangles[i].setSize(sf::Vector2f(rect_width, rect_height));
		rectangles[i].setFillColor(sf::Color(255, 255, 255));
		rectangles[i].setOutlineThickness(1);
		rectangles[i].setOutlineColor(sf::Color(0, 0, 0));
		rectangles[i].setPosition(i*rect_width, height-rect_height);
		window.draw(rectangles[i]);
	}
	window.display();
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return 0;
		}
	}
	return 0;
}

int text_display(int *arr, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		cout << *(arr+i) << "; ";
	}
	cout << "\n";
	return 0;
}

int swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
	return 0;
}

int bubble_sort(int *arr, int len)
{
	int i;
	bool done=false;
	while(!done)
	{
		done = true;
		for(i=0; i<len-1; i++)
		{
			if(*(arr+i)>*(arr+i+1))
			{
				swap(arr+i, arr+i+1);
				//display(arr, len);
				done = false;
			}
		}
		display(arr, len); //faster here
	}
	return 0;
}

int selection_sort(int *arr, int len)
{
	int i, j;
	int *min;
	for(i=0; i<len-1; i++)
	{
		min = arr+i;
		for(j=i; j<len; j++)
		{
			if(*(arr+j)<*min)
			{
				min = arr+j;
			}	
		}	
		display(arr, len);
		swap(arr+i, min);
	}
	return 0;
}

int insertion_sort(int *arr, int len)
{
	int i, j;
	for(i=1; i<len; i++)
	{
		j = i;
		while(j>0 && *(arr+j-1)>*(arr+j))
		{
			swap(arr+j, arr+j-1);
			display(arr, len);
			j -= 1;
		}
	}
	return 0;
}

int merge(int *arr, int left, int mid, int right, int len)
{
	int i=0;
	int l=left, m=mid, r=right, supcount=mid+1, infcount=left;
	int temp[r-l+1];
	while(infcount<=m && supcount<=r)
	{
		if(*(arr+infcount)<*(arr+supcount))
		{
			temp[i]=*(arr+infcount);
			infcount++;
		}
		else
		{
			temp[i]=*(arr+supcount);
			supcount++;
		}
		i++;
	}
	while(infcount<=m)
	{
			temp[i]=*(arr+infcount);
			infcount++;
			i++;
	}
	while(supcount<=r)
	{
			temp[i]=*(arr+supcount);
			supcount++;
			i++;
	}
	//add the merged list to our original one
	for(i=l; i<=r; i++)
	{
		*(arr+i)=temp[i-l];
		display(arr, len);
	}
	return 0;
}

int merge_sort(int *arr, int left, int right, int len) //best way to not make length global
{
	int mid = left+(right-left)/2;
	if(right-left >= 1)
	{
		merge_sort(arr, left, mid, len);
		merge_sort(arr, mid+1, right, len);
		merge(arr, left, mid, right, len);
	}
	return 0;
}

int partition(int *arr, int left, int right, int len)
{
	int i, j=left;
	for(i=left; i<right; i++)
	{
		if(*(arr+i)<*(arr+right))
		{
			swap(arr+i, arr+j);
			display(arr, len);
			j++;
		}
	}
	swap(arr+right, arr+j);
	return j;
}

int quicksort(int *arr, int left, int right, int len) //once again, adds a few more bytes to each stack frame but its reasonable
{
	int p;
	if(right-left > 0)
	{
		//int mid = left+(right-left)/2;
		p=partition(arr, left, right, len);
		quicksort(arr, left, p-1, len);
		quicksort(arr, p+1, right, len);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int size = atoi(argv[1]);
	int *arr_ptr = (int*) malloc(size*sizeof(int));
	window.setFramerateLimit(60);
	randfill(arr_ptr, size, 1, 1000);
	//bubble_sort(arr_ptr, size);
	//selection_sort(arr_ptr, size);
	//insertion_sort(arr_ptr, size);
	//merge_sort(arr_ptr, 0, size-1, size);
	quicksort(arr_ptr, 0, size, size);
	text_display(arr_ptr, size);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		    	if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
		}
	}
	return 0;
}
