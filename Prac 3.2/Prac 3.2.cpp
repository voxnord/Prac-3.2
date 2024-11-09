#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct point
{
	double x;
	double y;
};

void n1(vector<point> points)
{
	double p;

	for (size_t i = 0; i < points.size(); i++)
	{
		p = pow((points[i].x), 2) + pow((points[i].y), 2);
	}

	
}

void n2()
{

}

void n3()
{

}

void n4()
{
	
}

void n5()
{

}

void n6()
{

}

void n7()
{

}

void n8()
{

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<point> Points{ {1, 3}, {2, 5}, {5, 4}, {1, 6} };

	return 0;
}