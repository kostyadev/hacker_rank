#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <string>
#include <math.h> 

using namespace std;

string encryption(const string& s)
{
	int rowCnt = floor(sqrt(s.size()));
	int colCnt = (rowCnt * rowCnt) == s.size() ? rowCnt : rowCnt + 1;

	if ((rowCnt * colCnt) < s.size())
		rowCnt++;

	/*for (int i = 0; i < rowCnt; ++i)
	{
		for (int j = 0; j < colCnt; ++j)
		{
			int idx = i * colCnt + j;
			auto ch = idx >= s.size() ? ' ': s[idx];
			cout << ch;
		}
		cout << endl;
	}*/

	string out;
	out.reserve(s.size() * 2);
	for (int i = 0; i < colCnt; ++i)
	{
		for (int j = 0; j < rowCnt; ++j)
		{
			int idx = j * colCnt + i;
			if(idx < s.size())
				out.push_back(s[idx]);
		}
		out.push_back(' ');
	}

	return out;
}

int main()
{
	//ifstream fin("..\\input00.txt", std::ofstream::in); // hae and via ecy
	//ifstream fin("..\\input01.txt", std::ofstream::in); // fto ehg ee dd
	ifstream fin("..\\input02.txt", std::ofstream::in);// clu hlt io

	string s;
	getline(fin, s);

	string result = encryption(s);

	cout << result << "\n";

	return 0;
}