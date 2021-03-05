#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

#include <limits>
unsigned int st_max = std::numeric_limits<size_t>::max(); // special "denied" value

void almost_sorted(const vector<int>& arr)
{
	size_t indA = st_max;
	size_t indB = st_max;
	bool revSort = true; // is revert-sorted sub-array
	bool canBeSorted = true;
	size_t nonOrderedItemsCnt = 0;

	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			if (indA == st_max)
			{
				indA = i - 1;
				indB = i;
			}
			else
			{
				auto oldIndB = indB;
				indB = i;
				if ((indB - oldIndB) > 1)
					revSort = false;
			}

			nonOrderedItemsCnt++;
		}
	}

	cout << "size " << arr.size();
	cout << ", arr[" << indA << "] = " << arr[indA] << ", arr[" << indB << "] = " << arr[indB] 
		<< ", revSort " << revSort << ", nonOrderedItemsCnt " << nonOrderedItemsCnt << endl;

	if ((indB + 1) < arr.size() && arr[indA] > arr[indB + 1])
		canBeSorted = false;

	if (arr[indB] > arr[indA + 1])
		canBeSorted = false;

	if (indA > 0 && (arr[indB] < arr[indA - 1]))
		canBeSorted = false;

	if (nonOrderedItemsCnt > 2 && !revSort)
		canBeSorted = false;


	if (canBeSorted)
	{
		cout << "yes" << endl;
		cout << (revSort && ((indB - indA) > 2) ? "reverse " : "swap ") << indA + 1 << " " << indB + 1 << endl;
	}
	else
	{
		cout << "no" << endl;
	}

	////////////////////
	// debug code
	
	auto arrTmp = arr;
	if ((indB - indA) >= 2 && revSort && canBeSorted)
	{
		size_t j = indB;
		for (size_t i = indA; i < j; ++i)
		{
			swap(arrTmp[i], arrTmp[j]);
			--j;
		}
	}
	else if(canBeSorted)
	{
		swap(arrTmp[indA], arrTmp[indB]);
	}

	const bool isSorted = is_sorted(arrTmp.begin(), arrTmp.end());
	cout << (isSorted ? "sorted" : "not sorted") << ", " << (canBeSorted ? "can be sorted " : "can't be sorted") << ", " << (canBeSorted == isSorted ? "EXPECTED" : "ERROR") << endl;
}

int main()
{
	std::string line;
	std::ifstream infile("D:\\projects\\hackerrank\\almost_sorted\\AlmostSorted\\Debug\\data.txt");
	vector<int> v;
	int val;
	while (infile >> val)
	{
		v.push_back(val);
	}

	// 12345678 - sorted
	// 18345672 - swap arr[2] (==8) and arr[8] (==2)
	// 12347658 - reverse 765

	almost_sorted(v);
	/*
	almost_sorted({ 1, 2, 3, 4, 7, 6, 5, 8 });
	almost_sorted({ 2, 1, 3, 4, 5, 6, 8, 7 }); //can't be sorted
	almost_sorted({ 1, 2, 3, 4, 5, 6, 8, 7 });
	almost_sorted({ 1, 2, 7, 4, 5, 6, 3, 8 });
	almost_sorted({ 1, 2, 3, 5, 4, 6, 7, 8 });
	almost_sorted({ 4, 3, 2, 1, 5, 6, 7, 8 });
	almost_sorted({ 3, 1, 2 });// can't be sorted
	*/
}