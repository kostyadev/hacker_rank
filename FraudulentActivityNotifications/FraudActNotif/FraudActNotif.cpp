#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using  namespace std;

multiset<int>::iterator multiSetRmVal(multiset<int>& mset, const multiset<int>::iterator medIt, const int rmVal)
{
	const bool isOdd = mset.size() % 2 == 0;
	auto medItNew = medIt;

	if (isOdd)
	{
		if (rmVal < *medIt) // remove from left side of ordered set
		{
			//  1 (2) 3 4 --> 2 (3) 4
			++medItNew;
			auto rmIt = mset.find(rmVal);
			mset.erase(rmIt);
		}
		else if (rmVal > *medIt)  // remove from right side of ordered set
		{
			//  1 (2) 3 4 --> 1 (2) 4
			auto rmIt = mset.find(rmVal);
			mset.erase(rmIt);
		}
		else // remove from center
		{
			// a) 1 (2) 2 3 --> 1 (2) 3
			// b) 1 2 (2) 2 2 3 --> 1 2 (2) 2 3
			// c) 1 (2) 3 4 --> 1 (3) 4
			++medItNew;
			mset.erase(medIt);
		}
	}
	else // not odd
	{
		if (rmVal < *medIt) // remove from left side of ordered set
		{
			//  1 2 (3) 4 5 --> 1 (3) 4 5
			auto rmIt = mset.find(rmVal);
			mset.erase(rmIt);
		}
		else if (rmVal > *medIt)  // remove from right side of ordered set
		{
			//  1 2 (3) 4 5 --> 1 (2) 3 5
			--medItNew;
			auto rmIt = mset.find(rmVal);
			mset.erase(rmIt);
		}
		else // remove from center
		{
			// a) 1 2 (2) 2 3 --> 1 (2) 2 3
			// b) 1 (2) 3 --> (1) 3
			// c) 1 2 (2) 3 4 --> 1 (2) 3 4
			--medItNew;
			mset.erase(medIt);
		}
	}

	return medItNew;
}

multiset<int>::iterator multiSetInsVal(multiset<int>& mset, const multiset<int>::iterator medIt, const int insVal)
{
	const bool isOdd = mset.size() % 2 == 0;
	auto medItNew = medIt;

	if (isOdd)
	{
		if (insVal < *medIt) // insert to left side of ordered set
		{
			//  1 (2) 3 4 --> 1 1 (2) 3 4
			mset.insert(insVal);
		}
		else if (insVal > *medIt)  // add right side of ordered set
		{
			//  1 (2) 3 4 --> 1 2 (3) 4 5
			mset.insert(insVal);
			++medItNew;
		}
		else // add to center
		{
			// a) 1 (2) 2 3 --> 1 2 (2) 2 3
			// b) 1 (2) 3 4 --> 1 2 (2) 3 4
			// c) 1 2 (2) 2 2 3 --> 1 2 2 (2) 2 2 3
			mset.insert(insVal);
			++medItNew;
		}
	}
	else // not odd
	{
		if (insVal < *medIt) // insert to left side of ordered set
		{
			//  1 2 (3) 4 5 --> 1 1 (2) 3 4 5
			mset.insert(insVal);
			--medItNew;
		}
		else if (insVal > *medIt)  // add right side of ordered set
		{
			//  1 2 (3) 4 5 --> 1 2 (3) 4 5 6
			mset.insert(insVal);
		}
		else // add to center
		{
			// a) 1 2 (3) 4 5 --> 1 2 (3) 3 4 5
			// b) 1 2 (2) 2 3 --> 1 2 (2) 2 2 3
			// c) 1 (2) 3 --> 1 (2) 2 3
			mset.insert(insVal);
		}
	}

	return medItNew;
}

double msetGetMedVal(const multiset<int>& mset, const multiset<int>::iterator medIt)
{
	const bool isOdd = mset.size() % 2 == 0;
	double medVal = 0.0;
	if (isOdd)
	{
		auto medIt2 = medIt;
		++medIt2;
		medVal = (*medIt + *medIt2) / 2.0;
	}
	else
	{
		medVal = *medIt;
	}

	return medVal;
}

int activityNotifications(const vector<int>& expenditure, const int d)
{
	// initial filling
	multiset<int> mset;
	mset.insert(expenditure[0]);
	auto medIt = mset.begin(); // init pointer to a median value
	for (int i = 1; i < d; ++i)
		medIt = multiSetInsVal(mset, medIt, expenditure[i]);

	int notifCnt = 0;
	for (int i = d; i < expenditure.size(); ++i)
	{
		const int curVal = expenditure[i];

		auto medVal = msetGetMedVal(mset, medIt);

		if (curVal >= (medVal * 2.0) )
			notifCnt++;

		const int rmVal = expenditure[i - d];

		medIt = multiSetRmVal(mset, medIt, rmVal);
		medIt = multiSetInsVal(mset, medIt, curVal);
	}

	return notifCnt;
}

vector<string> split_string(string);

void multisetPrn(const multiset<int>& mset, multiset<int>::iterator medIt)
{
	int i = 0;
	for (auto it = mset.begin(); it != mset.end(); ++it)
	{
		if(it == medIt)
			cout << "([" << i << "])=" << *it << ", ";
		else
			cout << "[" << i << "]=" << *it << ", ";
		++i;
	}
		
	cout << endl;
}

int main()
{
	/*auto vect = { 1, 1, 2, 2, 3, 3 };
	multiset<int> set(vect);
	multisetPrn(set, set.find(5));

	auto medIt = set.begin();
	const auto medIdx = set.size() % 2 == 0 ? ( set.size() / 2) - 1 : (set.size() / 2);
	for (int i = 0; i < medIdx; ++i)
	{
		++medIt;
	}

	cout << "remove " << endl;
	multisetPrn(set, medIt);
	medIt = multiSetRmVal(set, medIt, 1);
	multisetPrn(set, medIt);
	medIt = multiSetRmVal(set, medIt, 3);
	multisetPrn(set, medIt);
	medIt = multiSetRmVal(set, medIt, 2);
	multisetPrn(set, medIt);
	medIt = multiSetRmVal(set, medIt, 1);
	multisetPrn(set, medIt);

	cout << "insert " << endl;
	medIt = multiSetInsVal(set, medIt, 1);
	multisetPrn(set, medIt);
	medIt = multiSetInsVal(set, medIt, 2);
	multisetPrn(set, medIt);
	medIt = multiSetInsVal(set, medIt, 3);
	multisetPrn(set, medIt);
	medIt = multiSetInsVal(set, medIt, 1);
	multisetPrn(set, medIt);

	return 0;*/
	
	//ifstream fin("D:\\projects\\hacker_rank\\FraudulentActivityNotifications\\input00.txt", std::ofstream::in); // 2
	ifstream fin("D:\\projects\\hacker_rank\\FraudulentActivityNotifications\\input05.txt", std::ofstream::in); // 926
	//ifstream fin("D:\\projects\\hacker_rank\\FraudulentActivityNotifications\\input06.txt", std::ofstream::in); // 0
	//ifstream fin("D:\\projects\\hacker_rank\\FraudulentActivityNotifications\\input07.txt", std::ofstream::in); // 1

	string nd_temp;
	getline(fin, nd_temp);
	vector<string> nd = split_string(nd_temp);

	int n = stoi(nd[0]);
	int d = stoi(nd[1]);

	string expenditure_temp_temp;
	getline(fin, expenditure_temp_temp);

	vector<string> expenditure_temp = split_string(expenditure_temp_temp);
	vector<int> expenditure(n);

	for (int i = 0; i < n; i++) {
		int expenditure_item = stoi(expenditure_temp[i]);
		expenditure[i] = expenditure_item;
	}

	int result = activityNotifications(expenditure, d);
	cout << result << "\n";

	return 0;
}

vector<string> split_string(string input_string) 
{
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