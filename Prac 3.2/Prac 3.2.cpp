#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

struct point
{
	double x;
	double y;
};

struct cpResult
{
	point p1;
	point p2;
	double distance;
};

cpResult n1(vector<point>& points)
{
	auto distance = [](const point& p1, const point& p2) { return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)); };
	auto bForce = [&](int left, int right)
		{
			cpResult result{};

			double rDistance = result.distance = { numeric_limits<double>::infinity() };
			auto point1 = result.p1;
			auto point2 = result.p2;

			for (int i = 0; i < right; i++)
			{
				for (int j = 1; j < left; j++)
				{
					double aDistance = distance(points[i], points[j]);
					if (aDistance < rDistance)
					{
						rDistance = aDistance;
						point1 = points[i];
						point2 = points[j];
					}
				}
			}

			return result;
		};

	auto sClosest = [&](vector<point>& strip, double doup)
		{
			cpResult result{};

			double rDistance = result.distance = doup;
			auto point1 = result.p1;
			auto point2 = result.p2;

			sort(strip.begin(), strip.end(), [](const point& p1, const point& p2) { return p1.y < p2.y; });

			for (int i = 0; i < strip.size(); i++)
			{
				for (int j = 1; j < strip.size() && (strip[i].y - strip[j].y) < rDistance; j++)
				{
					double aDistance = distance(strip[i], strip[j]);
					if (aDistance < rDistance)
					{
						rDistance = aDistance;
						point1 = strip[i];
						point2 = strip[j];
					}
				}
			}

			return result;
		};

	function<cpResult(int, int)> cUtil = [&](int left, int right)
		{
			if (right - left <= 3) return bForce(left, right);
			
			int middle = left + (right - left) / 2;

			cpResult lRes = cUtil(left, middle);
			cpResult rRes = cUtil(middle, right);
			cpResult result = (lRes.distance < rRes.distance) ? lRes : rRes;

			vector<point> strip;
			for (int i = left; i < right; i++)
			{
				if (abs(points[i].x - points[middle].x) < result.distance)
				{
					strip.push_back(points[i]);
				}
			}

			cpResult sResult = sClosest(strip, result.distance);

			return (sResult.distance < result.distance) ? sResult : result;
		};

	sort(points.begin(), points.end(), [](const point& p1, const point& p2) { return p1.x < p2.x; });

	return cUtil(0, points.size());

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