#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <map>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long long countTriplets(vector<long> arr, long k)
{
	long long count = 0;
	unordered_map<long long, long long> left, right;

	for (int i = 0; i < arr.size(); i++)
	{
		right[arr[i]]++;
	}

	for (int i = 0; i < arr.size(); i++)
	{
		right[arr[i]]--;
		if (arr[i] % k == 0)
		{
			count += left[arr[i] / k] * right[arr[i] * k];
		}
		left[arr[i]]++;
	}

	return count;
}

long countTripletsSlow(vector<long> arr, long r) 
{
	long count = 0;
	for (size_t i = 0; i < arr.size() - 2; ++i)
	{
		auto x = arr[i];
		auto xr = x * r;
		auto xrr = xr * r;
		int xrCnt = 0;
		int xrrCnt = 0; 
		
		for (size_t j = i + 1; j < arr.size() - 1; ++j)
			for (size_t k = j + 1; k < arr.size(); ++k)
				if (arr[j] == xr && arr[k] == xrr)
					++count;
	}

	return count;
}

int main()
{
	//ifstream fin("input00.txt", std::ofstream::in); // 2
	//ifstream fin("input02.txt", std::ofstream::in); // 161700
	ifstream fin("input03.txt", std::ofstream::in); //166661666700000

	string nr_temp;
	getline(fin, nr_temp);

	vector<string> nr = split(rtrim(nr_temp));

	int n = stoi(nr[0]);

	long r = stol(nr[1]);

	string arr_temp_temp;
	getline(fin, arr_temp_temp);

	vector<string> arr_temp = split(rtrim(arr_temp_temp));

	vector<long> arr(n);

	for (int i = 0; i < n; i++) {
		long arr_item = stol(arr_temp[i]);

		arr[i] = arr_item;
	}

	long long ans = countTriplets(arr, r);

	cout << ans << "\n";

	return 0;
}

string ltrim(const string &str) {
	string s(str);

	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
	);

	return s;
}

string rtrim(const string &str) {
	string s(str);

	s.erase(
		find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
		s.end()
	);

	return s;
}

vector<string> split(const string &str) {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}
