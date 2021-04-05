#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

int main()
{
	ifstream fin("..\\input10.txt", std::ofstream::in); // 5  9

	int n, q;
	fin >> n;
	fin >> q;

	// fill vectors
	vector<vector<int>> vv;
	vv.reserve(n);
	for (int i = 0; i < n; ++i)
	{
		int vSize;
		fin >> vSize;
		vector<int> v;
		v.reserve(vSize);
		for (int j = 0; j < vSize; ++j)
		{
			int val;
			fin >> val;
			v.push_back(val);
		}
		vv.push_back(move(v));
	}

	// fill queries
	vector<vector<int>> vq;
	vq.reserve(q);
	for (int i = 0; i < q; ++i)
	{
		vector<int> v(2);
		fin >> v[0] >> v[1];
		vq.push_back(move(v));
	}

	for (int i = 0; i < vq.size(); ++i)
	{
		int vvIdx = vq[i][0];
		int vIdx = vq[i][1];
		cout << vv[vvIdx][vIdx] << endl;
	}
	
	int a = 1;
}