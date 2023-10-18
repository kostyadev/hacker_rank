#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> 
#include <stack>
#include <functional>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'isBalanced' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

bool isOppositeTo(const char openBracket, const char closeBraket)
{
	if (openBracket == '(' && closeBraket == ')')
		return true;

	if (openBracket == '{' && closeBraket == '}')
		return true;

	if (openBracket == '[' && closeBraket == ']')
		return true;

	return false;
}

bool isOpenBracket(const char ch)
{
	if (ch == '(' || ch == '{' || ch == '[')
		return true;

	return false;
}

string isBalanced(string s)
{
	stack<char> st;
	for (char ch : s)
	{
		if (isOpenBracket(ch))
		{
			st.push(ch);
		}
		else // 
		{
			if (st.empty())
				return "NO";

			char topCh = st.top();
			if (isOppositeTo(topCh, ch))
			{
				st.pop();
			}
			else
			{
				return "NO";
			}
		}

	}

	return st.empty() ?"YES" : "NO";
}

int main()
{
	ifstream fin("../input05.txt", std::ofstream::in);
	ofstream fout("../output05.txt", std::ofstream::out);

	string t_temp;
	getline(fin, t_temp);

	int t = stoi(ltrim(rtrim(t_temp)));

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string s;
		getline(fin, s);

		string result = isBalanced(s);

		fout << result << "\n";
	}

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