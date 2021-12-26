#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <fstream> 
#include <functional>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

void updateFreqToVal(unordered_map<int, unordered_set<int>>& freqToVal,
	int val, int oldFreq, int newFreq)
{
	auto it = freqToVal.find(oldFreq);
	if (it != freqToVal.end())
		it->second.erase(val);

	if (newFreq > 0)
		freqToVal[newFreq].insert(val);
}

vector<int> freqQuery(const vector<vector<int>>& queries)
{
	vector<int> out;

	const int INS = 1;
	const int DEL = 2;
	const int CHK = 3;

	unordered_map<int, int> valToFreq;
	unordered_map<int, unordered_set<int>> freqToVal;

	for (size_t i = 0; i < queries.size(); ++i)
	{
		const int op = queries[i][0];
		const int val = queries[i][1];
		auto it = valToFreq.find(val);
		if (op == INS)
		{
			if (it == valToFreq.end())
			{
				valToFreq[val] = 1;
				updateFreqToVal(freqToVal, val, 0, 1);
			}
			else
			{
				auto oldFreq = it->second;
				auto newFreq = it->second + 1;
				it->second = newFreq;
				updateFreqToVal(freqToVal, val, oldFreq, newFreq);
			}

		}
		else if (op == DEL)
		{
			if (it != valToFreq.end())
			{
				auto oldFreq = it->second;
				auto newFreq = it->second > 0 ? it->second - 1 : 0;
				it->second = newFreq;
				updateFreqToVal(freqToVal, val, oldFreq, newFreq);
			}
		}
		else if (op == CHK)
		{
			auto it = freqToVal.find(val);
			if (it != freqToVal.end() && it->second.size() > 0)
				out.push_back(1);
			else
				out.push_back(0);
		}

		if (out.size() == 85)
			int a = 1;
	}

	return move(out);
}

int main()
{
	ifstream fin("../input05.txt", std::ofstream::in);
	ofstream fout("../output05.txt", std::ofstream::out);

	string q_temp;
	getline(fin, q_temp);

	int q = stoi(ltrim(rtrim(q_temp)));

	vector<vector<int>> queries(q);

	for (int i = 0; i < q; i++) {
		queries[i].resize(2);

		string queries_row_temp_temp;
		getline(fin, queries_row_temp_temp);

		vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

		for (int j = 0; j < 2; j++) {
			int queries_row_item = stoi(queries_row_temp[j]);

			queries[i][j] = queries_row_item;
		}
	}

	vector<int> ans = freqQuery(queries);

	for (int i = 0; i < ans.size(); i++) {
		fout << ans[i];

		if (i != ans.size() - 1) {
			fout << "\n";
		}
	}

	fout << "\n";

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
