#include <iostream>
#include <vector>
#include <fstream> 
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

vector<string> split_string(string);

vector<int> cutTheSticks(const vector<int>& arr)
{
	vector<int> sortArr = arr;
	sort(sortArr.begin(), sortArr.end());
	vector<int> res;
	res.push_back(sortArr.size());
	int prevVal = sortArr[0];
	for (int i = 1; i < sortArr.size(); ++i)
	{
		if (sortArr[i] > prevVal)
			res.push_back(sortArr.size() - i);

		prevVal = sortArr[i];
	}

	return move(res);
}

int main()
{
	ifstream fin("..\\input08.txt", std::ofstream::in); // 6 4 2 1
	//ifstream fin("..\\input09.txt", std::ofstream::in); // 8 6 4 1

	string arr_temp_temp;
	getline(fin, arr_temp_temp);
	int n = stoi(arr_temp_temp);

	getline(fin, arr_temp_temp);
	vector<string> arr_temp = split_string(arr_temp_temp);

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		int arr_item = stoi(arr_temp[i]);

		arr[i] = arr_item;
	}

	vector<int> result = cutTheSticks(arr);

	for (int i = 0; i < result.size(); i++) {
		cout << result[i];

		if (i != result.size() - 1) {
			cout << "\n";
		}
	}

	cout << "\n";

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
