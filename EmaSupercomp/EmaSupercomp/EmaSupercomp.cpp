#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

using  namespace std;

vector<string> split_string(string);

int getMaxPlusLen(int sIdx, int cIdx, const vector<string>& grid)
{
	int maxLen = std::min(grid.size(), grid[0].size());
	int retVal = 0;
	if (grid[sIdx].at(cIdx) == 'G')
	{
		retVal = 1;
	}
	else
	{
		return retVal;
	}

	for (int i = 1; i <= maxLen; ++i)
	{
		auto r = cIdx + i;
		auto l = cIdx - i;
		auto d = sIdx + i;
		auto u = sIdx - i;
		if (r >= grid[sIdx].size() || l < 0
			|| d >= grid.size() || u < 0)
		{
			break;
		}

		if (grid[sIdx][r] == 'G' && grid[sIdx][l] == 'G'
			&& grid[u][cIdx] == 'G' && grid[d][cIdx] == 'G')
		{
			++retVal;
		}
		else
		{
			break;
		}
	}

	return retVal;
}

bool plusesAreNotOverlapped(int r1, int c1, int len1, int r2, int c2, int len2)
{
	auto minLen = min(len1, len2);
	auto maxLen = max(len1, len2);
	auto dc = abs(c1 - c2);
	auto dr = abs(r1 - r2);
	bool caseOne = (dr < minLen && dr >= 1 && dc >= maxLen);
	bool caseTwo = (dc < minLen && dc >= 1 && dr >= maxLen);
	bool caseThree = (dr == 0 && dc >= (minLen + maxLen - 1));
	bool caseFour = (dc == 0 && dr >= (minLen + maxLen - 1));
	bool caseFive = (dc >= minLen && dr >= minLen);
	return caseOne || caseTwo || caseThree || caseFour || caseFive;
}

int getLenPairFor(int r, int c, int len, const vector<vector<int>>& plusLens)
{
	int maxLen = 0;
	for (int ir = 0; ir < plusLens.size(); ++ir)
	{
		for (int ic = 0; ic < plusLens[ir].size(); ++ic)
		{
			auto curLen = plusLens[ir][ic];
			while (curLen >= 1)
			{
				if (plusesAreNotOverlapped(r, c, len, ir, ic, curLen) && curLen > 0)
				{
					if (curLen > maxLen)
						maxLen = curLen;
				}
				--curLen;
			}
		}
	}

	return maxLen;
}

int twoPluses(const vector<string>& grid) 
{
	vector<vector<int>> plusLens;
	plusLens.reserve(grid.size());

	for (int strIdx = 0; strIdx < grid.size(); ++strIdx)
	{
		vector<int> row(grid[strIdx].size(), 0);
		for (int chIdx = 0; chIdx < grid[strIdx].size(); ++chIdx)
		{
			auto pLen = getMaxPlusLen(strIdx, chIdx, grid);
			row[chIdx] = pLen;
		}
		plusLens.push_back(row);
	}

	for(const auto& r : plusLens)
	{
		for (const auto c : r)
			cout << c << " ";
		cout << endl;
	}

	int maxVal = 0;
	for (int ir = 0; ir < plusLens.size(); ++ir)
	{
		for (int ic = 0; ic < plusLens[ir].size(); ++ic)
		{
			int len = plusLens[ir][ic];
			if (len == 0)
				continue;

 			while (len >= 1)
			{
				auto area1 = (len - 1) * 4 + 1;
				auto len2 = getLenPairFor(ir, ic, len, plusLens);
				auto area2 = (len2 - 1) * 4 + 1;
				auto val = area1 * area2;
				if (val > maxVal)
					maxVal = val;
				--len;
			}
		}
	}

	return maxVal;
}

int main()
{
	//ifstream fin("D:\\projects\\hacker_rank\\EmaSupercomp\\input00.txt", std::ofstream::in);
	//ifstream fin("D:\\projects\\hacker_rank\\EmaSupercomp\\input01.txt", std::ofstream::in);
	//ifstream fin("D:\\projects\\hacker_rank\\EmaSupercomp\\input03.txt", std::ofstream::in);
	ifstream fin("D:\\projects\\hacker_rank\\EmaSupercomp\\input09.txt", std::ofstream::in);
	//ifstream fin("D:\\projects\\hacker_rank\\EmaSupercomp\\input22.txt", std::ofstream::in);

	string nm_temp;
	getline(fin, nm_temp);

	vector<string> nm = split_string(nm_temp);

	int n = stoi(nm[0]);

	int m = stoi(nm[1]);

	vector<string> grid(n);

	for (int i = 0; i < n; i++) {
		string grid_item;
		getline(fin, grid_item);

		grid[i] = grid_item;
	}

	int result = twoPluses(grid);

	cout << result << "\n";

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}
