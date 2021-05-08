#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<int> circularArrayRotation(const vector<int>& a, const int k, const vector<int>& queries)
{
	const int kShift = k > a.size() ? k % a.size() : k;
	vector<int> res(queries.size());
	const int startPos = kShift == 0 ? 0 : a.size() - kShift;

	for (int i = 0; i < queries.size(); ++i)
	{
		int resIdx = startPos + queries[i];
		if (resIdx >= a.size())
		{
			resIdx = resIdx - a.size();
		}
		res[i] = a[resIdx];
	}

	return res;
}

int main()
{
	ifstream fin("..\\input15.txt", std::ofstream::in); // 2 3 1

	string first_multiple_input_temp;
	getline(fin, first_multiple_input_temp);

	vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

	int n = stoi(first_multiple_input[0]);

	int k = stoi(first_multiple_input[1]);

	int q = stoi(first_multiple_input[2]);

	string a_temp_temp;
	getline(fin, a_temp_temp);

	vector<string> a_temp = split(rtrim(a_temp_temp));

	vector<int> a(n);

	for (int i = 0; i < n; i++) {
		int a_item = stoi(a_temp[i]);

		a[i] = a_item;
	}

	vector<int> queries(q);

	for (int i = 0; i < q; i++) {
		string queries_item_temp;
		getline(fin, queries_item_temp);

		int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

		queries[i] = queries_item;
	}

	vector<int> result = circularArrayRotation(a, k, queries);

	for (size_t i = 0; i < result.size(); i++) {
		cout << result[i];

		if (i != result.size() - 1) {
			cout << "\n";
		}
	}

	cout << "\n";

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
