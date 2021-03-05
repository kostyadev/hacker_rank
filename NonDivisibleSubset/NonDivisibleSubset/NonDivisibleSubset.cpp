#include <iostream>
#include <vector>
#include <fstream> 
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

int nonDivisibleSubset(const int k, const vector<int>& s) 
{
	vector<int> remainderCnt(k, 0);

	for (int val : s)
	{
		auto rmdr = val % k;
		remainderCnt[rmdr] += 1;
	}

	int maxCnt = 0;
	for (int i = 1; i < remainderCnt.size(); ++i)
	{
 		if (remainderCnt[i] == 0)
			continue;

		int rmdr2 = k - i;
		int curCnt = 0;
		for (int j = 1; j < remainderCnt.size(); ++j)
		{
			if ((rmdr2 + j) == k)
				continue;

			if ((j + j) == k)
				continue;
			
			curCnt += remainderCnt[j];
		}

		if (curCnt == 11)
			int a = 1;

		if (curCnt > maxCnt)
			maxCnt = curCnt;
	}

	return maxCnt;
}

int main()
{
	//ifstream fin("D:\\projects\\hacker_rank\\NonDivisibleSubset\\input00.txt", std::ofstream::in); // 3
	ifstream fin("D:\\projects\\hacker_rank\\NonDivisibleSubset\\input16.txt", std::ofstream::in); // 11

	string first_multiple_input_temp;
	getline(fin, first_multiple_input_temp);

	vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

	int n = stoi(first_multiple_input[0]);

	int k = stoi(first_multiple_input[1]);

	string s_temp_temp;
	getline(fin, s_temp_temp);

	vector<string> s_temp = split(rtrim(s_temp_temp));

	vector<int> s(n);

	for (int i = 0; i < n; i++) {
		int s_item = stoi(s_temp[i]);

		s[i] = s_item;
	}

	int result = nonDivisibleSubset(k, s);

	cout << result << "\n";

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