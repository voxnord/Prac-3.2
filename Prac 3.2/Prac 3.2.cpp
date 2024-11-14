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

	struct clpResult
	{
		point p1;
		point p2;
		double distance;
	};

	clpResult ClosestPair(vector<point>& points)
	{
		auto distance = [](const point& p1, const point& p2) -> double { return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)); };
		auto compareX = [](const point& p1, const point& p2) -> bool { return p1.x < p2.x; };
		auto compareY = [](const point& p1, const point& p2) -> bool { return p1.y < p2.y; };

		auto bForce = [&](const vector<point>& points, int left, int right)
			{
				clpResult result{};

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
				clpResult result{};
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

		function<clpResult(vector<point>&, int, int)> cUtil = [&](vector<point>& points, int left, int right)
			{
				if (right - left <= 3) return bForce(points, left, right);

				int middle = left + (right - left) / 2;

				clpResult lRes = cUtil(points, left, middle);
				clpResult rRes = cUtil(points, middle, right);
				clpResult result = (lRes.distance < rRes.distance) ? lRes : rRes;

				vector<point> strip;
				for (int i = left; i < right; i++)
				{
					if (abs(points[i].x - points[middle].x) < result.distance)
					{
						strip.push_back(points[i]);
					}
				}

				clpResult sResult = sClosest(strip, result.distance);

				return (sResult.distance < result.distance) ? sResult : result;
			};

		sort(points.begin(), points.end(), compareX);

		return cUtil(points, 0, points.size());

	}
};

class n2
{
public:
	int countRecursions = 0;

	string karatsubaMultiply(const string& num1, const string& num2)
	{
		auto addStr = [&](const string& num1, const string& num2) -> string
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

		auto subStr = [&](const string& num1, const string& num2) -> string
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

		auto shiftStr = [](const string& num, int n) -> string { return num + string(n, '0'); };

		auto rmLZ = [&](const string& str) -> string
			{
				size_t firstNotOfZero = str.find_first_not_of('0');
				if (firstNotOfZero != string::npos)
				{
					return str.substr(firstNotOfZero);
				}
				return "0";
			};

		countRecursions++;

		int n = max(num1.size(), num2.size());

		if (n == 1)
		{
			int rs = (num1[0] - '0') * (num2[0] - '0');

			return to_string(rs);
		}

		string x = string(n - num1.size(), '0') + num1;
		string y = string(n - num2.size(), '0') + num2;

		int half = n / 2;

		string x1 = x.substr(0, half);
		string x0 = x.substr(half);

		string y1 = y.substr(0, half);
		string y0 = y.substr(half);

		string z2 = karatsubaMultiply(x1, y1);
		string z0 = karatsubaMultiply(x0, y0);
		string z1 = karatsubaMultiply(addStr(x1, x0), addStr(y1, y0));

		z1 = subStr(z1, addStr(z2, z0));

		string result = addStr(addStr(shiftStr(z2, 2 * (n - half)), shiftStr(z1, n - half)), z0);

		return rmLZ(result);
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

	n1::clpResult resClP = num1.ClosestPair(Points);

	cout << "Минимальное расстояние: " << resClP.distance; 
	cout << " между парами" << " (" << resClP.p1.x << ", " << resClP.p1.y << ")";
	cout << " (" << resClP.p2.x << ", " << resClP.p2.y << ")";

	n2 num2;

	string numK1{ "1234" }, numK2{ "5678" };
	int recursionCount = num2.countRecursions;

	string resKM(numK1, numK2);
	

	return 0;
}