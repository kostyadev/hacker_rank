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

/*
 * Complete the 'sockMerchant' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER_ARRAY ar
 */

int sockMerchant(int n, vector<int> ar)
{
	sort(ar.begin(), ar.end());
	int curColor = ar[0];
	int curColorCnt = 1;
	int pairCnt = 0;
	for (int i = 1; i < ar.size(); ++i)
	{
		if (ar[i] == curColor)
		{
			curColorCnt++;
		}
		else
		{
			int curColorPairCnt = trunc(curColorCnt / 2);
			pairCnt += curColorPairCnt;
			curColor = ar[i];
			curColorCnt = 1;
		}
	}

	if (curColorCnt > 1)
	{
		int curColorPairCnt = trunc(curColorCnt / 2);
		pairCnt += curColorPairCnt;
	}

	return pairCnt;
}

int main()
{

	ifstream fin("../input01.txt", std::ofstream::in);
	ofstream fout("../output01.txt", std::ofstream::out);

	string n_temp;
	getline(fin, n_temp);

	int n = stoi(ltrim(rtrim(n_temp)));

	string ar_temp_temp;
	getline(fin, ar_temp_temp);

	vector<string> ar_temp = split(rtrim(ar_temp_temp));

	vector<int> ar(n);

	for (int i = 0; i < n; i++) {
		int ar_item = stoi(ar_temp[i]);

		ar[i] = ar_item;
	}
	int v = trunc(10.9f);

	//ar = { 1, 2, 4, 5, 6, 7, 7 };
	int result = sockMerchant(ar.size(), ar);

	fout << result << "\n";

	fout.close();

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
