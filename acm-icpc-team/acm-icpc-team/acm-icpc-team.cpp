#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

int getTopicSum(const string& s1, const string& s2)
{
	int sum = 0;
	for (int i = 0; i < s1.size(); ++i)
		sum += ((s1[i] == '0') && (s2[i] == '0')) ? 0 : 1;
	return sum;
}

vector<int> acmTeam(const vector<string>& topic) 
{
	struct StrCnt { string str; int cnt; int oldIdx; };
	vector<StrCnt> v;
	v.reserve(topic.size());
	for (int i = 0; i < topic.size(); ++i)
	{
		StrCnt sc;
		sc.str = topic[i];
		sc.cnt = count_if(sc.str.begin(), sc.str.end(), [](const char ch) { return ch == '1'; });
		sc.oldIdx = i;
		v.push_back(sc);
	}
	
	// reverse order sort
	sort(v.begin(), v.end(), [](const StrCnt& a, const StrCnt& b) { return a.cnt > b.cnt; });

	int maxSum = 0;
	int cmdCnt = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i].cnt == 0)
			break;

		for (int j = 0; j < v.size(); ++j)
		{
			if (v[j].cnt == 0)
				break;

			if (i == j)
				continue;

			int sum = getTopicSum(v[i].str, v[j].str);
			if (sum == maxSum)
			{
				cmdCnt++;
			} 
			else if (sum > maxSum)
			{
				maxSum = sum;
				cmdCnt = 1;
			}
		}
	}

	return {maxSum, cmdCnt / 2}; // cmdCnt divide to 2 because we calculate each set of topics two times
}

int main()
{
	//ifstream fin("..\\input00.txt", std::ofstream::in); // 5 2
	ifstream fin("..\\input08.txt", std::ofstream::in); // 5 6

	string first_multiple_input_temp;
	getline(fin, first_multiple_input_temp);

	vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

	int n = stoi(first_multiple_input[0]);

	int m = stoi(first_multiple_input[1]);

	vector<string> topic(n);

	for (int i = 0; i < n; i++) {
		string topic_item;
		getline(fin, topic_item);

		topic[i] = topic_item;
	}

	vector<int> result = acmTeam(topic);

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
