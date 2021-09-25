#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumBribes' function below.
 *
 * The function accepts INTEGER_ARRAY q as parameter.
 */

struct Moving
{
	int val = 0;
	int bribes = 0;
};

// Complete the minimumBribes function below.
void minimumBribes(const vector<int>& q) {
	int totalBribes = 0;

	int expectedFirst = 1;
	int expectedSecond = 2;
	int expectedThird = 3;

	for (unsigned int i = 0; i < q.size(); ++i) {
		if (q[i] == expectedFirst) {
			expectedFirst = expectedSecond;
			expectedSecond = expectedThird;
			++expectedThird;
		}
		else if (q[i] == expectedSecond) {
			++totalBribes;
			expectedSecond = expectedThird;
			++expectedThird;
		}
		else if (q[i] == expectedThird) {
			totalBribes += 2;
			++expectedThird;
		}
		else {
			cout << "Too chaotic" << endl;
			return;
		}
	}

	cout << totalBribes << endl;
}

int main()
{
	//ifstream fin("..\\input00.txt", std::ofstream::in); // 3	Too chaotic
	//ifstream fin("..\\input01.txt", std::ofstream::in); // Too chaotic	7
	ifstream fin("..\\input02.txt", std::ofstream::in); // 966

	string t_temp;
	getline(fin, t_temp);

	int t = stoi(ltrim(rtrim(t_temp)));

	for (int t_itr = 0; t_itr < t; t_itr++) {
		string n_temp;
		getline(fin, n_temp);

		int n = stoi(ltrim(rtrim(n_temp)));

		string q_temp_temp;
		getline(fin, q_temp_temp);

		vector<string> q_temp = split(rtrim(q_temp_temp));

		vector<int> q(n);

		for (int i = 0; i < n; i++) {
			int q_item = stoi(q_temp[i]);

			q[i] = q_item;
		}

		minimumBribes(q);
	}

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