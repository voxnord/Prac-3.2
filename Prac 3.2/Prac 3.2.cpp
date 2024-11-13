#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

class n1
{
public:

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

	cpResult CP(vector<point>& points)
	{
		auto distance = [](const point& p1, const point& p2) -> double { return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)); };
		auto compareX = [](const point& p1, const point& p2) -> bool { return p1.x < p2.x; };
		auto compareY = [](const point& p1, const point& p2) -> bool { return p1.y < p2.y; };
		auto bForce = [&](const vector<point>& points, int left, int right)
			{
				cpResult result{};

				result.distance = { numeric_limits<double>::infinity() };

				for (int i = left; i < right; ++i)
				{
					for (int j = i + 1; j < right; ++j)
					{
						double aDistance = distance(points[i], points[j]);
						if (aDistance < result.distance)
						{
							result.distance = aDistance;
							result.p1 = points[i];
							result.p2 = points[j];
						}
					}
				}

				return result;
			};

		auto sClosest = [&](vector<point>& strip, double doup)
			{
				cpResult result{};
				result.distance = doup;

				vector<point> sortStrip = strip;
				sort(sortStrip.begin(), sortStrip.end(), compareY);

				for (size_t i = 0; i < sortStrip.size(); ++i)
				{
					for (size_t j = i + 1; j < sortStrip.size() && (sortStrip[i].y - sortStrip[j].y) < result.distance; ++j)
					{
						double aDistance = distance(strip[i], strip[j]);
						if (aDistance < result.distance)
						{
							result.distance = aDistance;
							result.p1 = sortStrip[i];
							result.p2 = sortStrip[j];
						}
					}
				}

				return result;
			};

		function<cpResult(vector<point>&, int, int)> cUtil = [&](vector<point>& points, int left, int right)
			{
				if (right - left <= 3) return bForce(points, left, right);

				int middle = left + (right - left) / 2;

				cpResult lRes = cUtil(points, left, middle);
				cpResult rRes = cUtil(points, middle, right);
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

		sort(points.begin(), points.end(), compareX);

		return cUtil(points, 0, points.size());

	}
};

class n2
{
public:
	
	string karatsubaMultiply(const string& num1, const string& num2)
	{
		static int countRecursions = 0;

		auto addStr = [](const string& num1, const string& num2) -> string
			{
				string res;

				int carry{ 0 }, sum{ 0 };
				int i = num1.size() - 1, j = num2.size() - 1;
				
				while (i >= 0 || j >= 0 || carry)
				{
					sum = carry;

					if (i >= 0) sum += num1[i--] - '0';
					if (j >= 0) sum += num2[j--] - '0';

					res += (sum % 10) + '0';
					carry = sum / 10;
				}

				reverse(res.begin(), res.end());

				return res;
			};

		auto subStr = [](const string& num1, const string& num2) -> string
			{
				string res;

				int bor{ 0 }, diff{ 0 };

				int i = num1.size() - 1, j = num2.size();

				while (i >= 0 || j >= 0)
				{
					diff = (num1[i] - '0') - (j >= 0 ? (num2[j] - '0') : '0') - bor;

					if (diff < 0)
					{
						diff += 10;
						bor = 1;
					}
					else
					{
						bor = 0;
					}

					res += diff + '0';

					i--;
					j--;
				}

				while (res.size() > 1 && res.back() == '0')
				{
					res.pop_back();
				}

				reverse(res.begin(), res.end());

				return res;
			};

		auto shift = [](const string& num, int n) -> string { return num + string(n, '0'); };
	}
	
};

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

	n1 num1;
	vector<n1::point> Points{ {1, 3}, {2, 5}, {5, 4}, {1, 6} };

	cout << "\n1. Поиск пары ближайших точек." << endl;
	cout << "   Пары точек:";

	for (n1::point p : Points) cout << " (" << p.x << ", " << p.y << "); ";

	cout << endl;

	n1::cpResult res = num1.CP(Points);

	cout << "Минимальное расстояние: " << res.distance; 
	cout << " между парами" << " (" << res.p1.x << ", " << res.p1.y << ")";
	cout << " (" << res.p2.x << ", " << res.p2.y << ")";




	return 0;
}