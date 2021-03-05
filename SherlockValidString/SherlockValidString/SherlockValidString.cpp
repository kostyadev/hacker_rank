#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <functional>

using namespace std;

string isValid(const string& s) 
{
	vector<int> chCnt(int('z' - 'a') + 1, 0);

	for (char ch : s)
	{
		const int chIdx = ch - 'a';
		chCnt[chIdx] += 1;
	}

	int idx1 = -1;
	int idx2 = -1;
	for (int i = 0; i < chCnt.size(); ++i)
	{
		if (idx1 == -1 && chCnt[i] > 0)
		{
			idx1 = i;
			continue;
		}

		if (idx1 != -1 && idx2 == -1 && chCnt[i] != chCnt[idx1] && chCnt[i] > 0)
		{
			idx2 = i;
			break;
		}
	}

	bool yes = true;
	if (idx2 != -1)
	{
		const auto cnt1 = count(chCnt.begin(), chCnt.end(), chCnt[idx1]);
		const auto cnt2 = count(chCnt.begin(), chCnt.end(), chCnt[idx2]);
		const int decrCntIdx = (cnt1 > cnt2) ? idx2 : idx1;
		chCnt[decrCntIdx] -= 1;
		const auto idx = chCnt[idx1] > chCnt[idx2] ? idx1 : idx2;
		const auto cntCnt = count(chCnt.begin(), chCnt.end(), chCnt[idx]);
		const auto zeroCnt = count(chCnt.begin(), chCnt.end(), 0);
		yes = (zeroCnt + cntCnt) == chCnt.size();
	}

	return yes ? "YES" : "NO";
}

int main()
{
	//ifstream fin("D:\\projects\\hacker_rank\\SherlockValidString\\input00.txt", std::ofstream::in); // NO
	//ifstream fin("D:\\projects\\hacker_rank\\SherlockValidString\\input01.txt", std::ofstream::in); // NO
	ifstream fin("D:\\projects\\hacker_rank\\SherlockValidString\\input02.txt", std::ofstream::in); // YES
	//ifstream fin("D:\\projects\\hacker_rank\\SherlockValidString\\input04.txt", std::ofstream::in); // YES
	//ifstream fin("D:\\projects\\hacker_rank\\SherlockValidString\\input18.txt", std::ofstream::in); // YES

	string s;
	getline(fin, s);

	string result = isValid(s);

	cout << result << "\n";

	return 0;
}