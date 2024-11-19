#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <numeric>
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
private:
	
	string addStr(const string& num1, const string& num2)
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
	}

	string subString(const string& num1, const string& num2)
	{
		string res;

		int bor{ 0 }, diff{ 0 };

		int i = num1.size() - 1, j = num2.size() - 1;

		while (i >= 0 || j >= 0)
		{
			diff = (num1[i] - '0') - (j >= 0 ? (num2[j] - '0') : 0) - bor;

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
	}

	string shiftStr(const string& num, int n) { return num + string(n, '0'); };

	string rmLZ(const string& str)
	{
		size_t firstNotOfZero = str.find_first_not_of('0');
		if (firstNotOfZero != string::npos)
		{
			return str.substr(firstNotOfZero);
		}
		return "0";
	}

public:
	int countRecursions = 0;

	string karatsubaMultiply(const string& num1, const string& num2)
	{
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

		z1 = subString(z1, addStr(z2, z0));

		string result = addStr(addStr(shiftStr(z2, 2 * (n - half)), shiftStr(z1, n - half)), z0);

		return rmLZ(result);
	}
	
};

class n3
{
private:
	int partition(vector<int>& nums, int left, int right, int pivotIndex) 
	{
		int pivotValue = nums[pivotIndex];
		swap(nums[pivotIndex], nums[right]);
		int storeIndex = left;

		for (int i = left; i < right; i++) 
		{
			if (nums[i] < pivotValue) 
			{
				swap(nums[storeIndex], nums[i]);
				storeIndex++;
			}
		}

		swap(nums[right], nums[storeIndex]);
		return storeIndex;
	}

	int quickSelect(vector<int>& nums, int left, int right, int k) 
	{
		if (left == right) 
		{
			return nums[left];
		}

		int pivotIndex = left + rand() % (right - left + 1);
		pivotIndex = partition(nums, left, right, pivotIndex);

		if (k == pivotIndex) 
		{
			return nums[k];
		}
		else if (k < pivotIndex) 
		{
			return quickSelect(nums, left, pivotIndex - 1, k);
		}
		else 
		{
			return quickSelect(nums, pivotIndex + 1, right, k);
		}
	}

public:

	double findMedian(vector<int>& nums) 
	{
		int n = nums.size();
		if (n % 2 == 1) 
		{
			return quickSelect(nums, 0, n - 1, n / 2);
		}
		else 
		{
			int leftMid = quickSelect(nums, 0, n - 1, n / 2 - 1);
			int rightMid = quickSelect(nums, 0, n - 1, n / 2);
			return (leftMid + rightMid) / 2.0;
		}
	}

};

double n4(double a, int n)
{
    if (n == 0) 
	{
        return 1;
    }

    double halfPower = n4(a, n / 2);

    if (n % 2 == 0) 
	{
        return halfPower * halfPower;
    } 
	else 
	{
        return a * halfPower * halfPower;
    }
}

string n5(const string& s1, const string& s2)
{
	static unordered_map<string, string> memo;

	string key = s1 + "|" + s2;

	if (memo.find(key) != memo.end()) 
	{
		return memo[key];
	}

	if (s1.empty() || s2.empty()) 
	{
		return "";
	}

	if (s1[0] == s2[0]) 
	{
		string result = s1[0] + n5(s1.substr(1), s2.substr(1));
		memo[key] = result;
		return result;
	}

	string result1 = n5(s1.substr(1), s2);
	string result2 = n5(s1, s2.substr(1));

	string result = (result1.size() > result2.size()) ? result1 : result2;
	memo[key] = result;
	return result;
}

class n6
{

public:
	struct FPoint 
	{
		double x, y;

		bool operator<(const FPoint& p) const 
		{
			return x < p.x || (x == p.x && y < p.y);
		}
	};
private:
	int orientation(const FPoint& a, const FPoint& b, const FPoint& c)
	{
		double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
		if (val == 0) return 0;
		return (val > 0) ? 1 : -1;
	}
public:
	vector<FPoint> convexHull(vector<FPoint>& points)
	{
		int n = points.size();
		if (n < 3) return points;

		sort(points.begin(), points.end());

		vector<FPoint> hull;

		for (const auto& p : points) 
		{
			while (hull.size() >= 2 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], p) != -1) 
			{
				hull.pop_back();
			}
			hull.push_back(p);
		}

		size_t t = hull.size() + 1;
		for (int i = n - 1; i >= 0; --i) 
		{
			while (hull.size() >= t && orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != -1) 
			{
				hull.pop_back();
			}
			hull.push_back(points[i]);
		}

		hull.pop_back();

		return hull;
	}
};

class n7
{
private:
	int calculateTotalSum(const vector<int>& nums)
	{
		return accumulate(nums.begin(), nums.end(), 0);
	}

	vector<vector<bool>> initializeDPTable(int n, int halfSum)
	{
		vector<vector<bool>> dp(n + 1, vector<bool>(halfSum + 1, false));
		dp[0][0] = true;
		return dp;
	}

	void fillDPTable(const vector<int>& nums, vector<vector<bool>>& dp, int halfSum)
	{
		int n = nums.size();
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 0; j <= halfSum; ++j)
			{
				dp[i][j] = dp[i - 1][j]; // �� ����� ������� �������
				if (j >= nums[i - 1])
				{
					dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]]; // ����� ������� �������
				}
			}
		}
	}

	int findBestSum(const vector<vector<bool>>& dp, int n, int halfSum)
	{
		for (int j = halfSum; j >= 0; --j)
		{
			if (dp[n][j])
			{
				return j;
			}
		}
		return 0;
	}

	pair<vector<int>, vector<int>> restoreGroups(const vector<int>& nums, int bestSum, const vector<vector<bool>>& dp)
	{
		vector<int> group1, group2;
		int sum1 = bestSum;
		int n = nums.size();

		for (int i = n; i > 0; --i)
		{
			if (sum1 >= nums[i - 1] && dp[i - 1][sum1 - nums[i - 1]])
			{
				group1.push_back(nums[i - 1]);
				sum1 -= nums[i - 1];
			}
			else
			{
				group2.push_back(nums[i - 1]);
			}
		}

		return { group1, group2 };
	}
public:
	pair<vector<int>, vector<int>> partitionWithMinDifference(const vector<int>& nums) 
	{
		int totalSum = calculateTotalSum(nums);
		int halfSum = totalSum / 2;

		vector<vector<bool>> dp = initializeDPTable(nums.size(), halfSum);

		fillDPTable(nums, dp, halfSum);

		int bestSum = findBestSum(dp, nums.size(), halfSum);

		return restoreGroups(nums, bestSum, dp);
	}
};

class n8
{
public:
	struct Group 
	{
		vector<int> elements;
		int sum = 0;
	};

	vector<Group> partitionArray(const vector<int>& nums, int k) 
	{
		vector<Group> groups(k);

		vector<int> sortedNums = nums;
		sort(sortedNums.rbegin(), sortedNums.rend());

		for (int num : sortedNums) 
		{
			auto minGroup = min_element(groups.begin(), groups.end(), [](const Group& a, const Group& b) { return a.sum < b.sum; });
			minGroup->elements.push_back(num);
			minGroup->sum += num;
		}

		return groups;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// ������� 1: ���� ��������� �����
	n1 num1;
	vector<n1::point> Points{ {1, 3}, {2, 5}, {5, 4}, {1, 6} };
	cout << "\n1. ����� ���� ��������� �����." << endl;
	cout << "   ���� �����:";
	for (n1::point p : Points) cout << " (" << p.x << ", " << p.y << "); ";
	cout << endl;
	n1::clpResult resClP = num1.ClosestPair(Points);
	cout << "   ����������� ����������: " << resClP.distance; 
	cout << " ����� ������" << " (" << resClP.p1.x << ", " << resClP.p1.y << ")";
	cout << " (" << resClP.p2.x << ", " << resClP.p2.y << ")" << endl;

	// ������� 2: �������� ��������
	n2 num2;
	cout << "\n2. ���������(�������� ��������). " << endl;
	string numK1{ "1234" }, numK2{ "5678" };
	string resKM = num2.karatsubaMultiply(numK1, numK2);
	int recursionCount = num2.countRecursions;
	cout << "   ��������� " << numK1 << " * " << numK2 << " = " << resKM << endl;
	cout << "   ���������� ����������� �������: " << recursionCount << endl;

	// ������� 3: �������
	n3 num3;
	vector<int> arr{ 3, 2, 4, 7, 3, 8, 6 };
	cout << "\n3. ���������� �������." << endl;
	cout << "   ������: ";
	for (int n : arr) { cout << n << " "; } 
	cout << endl;
	cout << "   �������: " << num3.findMedian(arr) << endl;

	// ������� 4: ���������� � �������(������� ��������)
	double a{ 4.67 }; int b{ 3 };
	cout << "\n4. ���������� � �������." << endl;
	cout << "   ����� " << "a(" << a << ")" << "^" << "b(" << b << ")" << endl;
	cout << "   ���������: " << n4(a, b) << endl;

	// ������� 5: �������� ���������� ���������� ����� ���������
	string str1{ "Hello, world!" }, str2{ "Bye-bye, universe!" };
	cout << "\n5. ���������� ����� ���������." << endl;
	cout << "   ������ 1: " << str1 << "; " << "������ 2: " << str2 << endl;
	cout << "   LCS: " << n5(str1, str2) << endl;

	// ������� 6: �������� ���������� �������� ��������
	n6 num6;
	vector<n6::FPoint> points{ { 3.3, 2.1 }, {4.5, 6.7 }, {3.1, 5.6}, {2.0, 3.5} };
	cout << "\n6. ���������� �������� ��������." << endl;
	cout << "   �������:" << endl << "   ";
	vector<n6::FPoint> hull = num6.convexHull(points);
	for (const n6::FPoint& p : hull)
	{
		cout << "(" << p.x << ", " << p.y << "); ";
	}
	cout << endl;

	// ������� 7: ����������� ������� ���� ���� ����� ��������
	
	// ������� 8: ����������� ������� ���� k ����� ��������
	

	return 0;
}