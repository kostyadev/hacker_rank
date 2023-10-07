#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> 
#include <functional>
using namespace std;

vector<string> split_string(string);

void sortAndRemoveDuplicates(vector<int>& v)
{
	sort(v.begin(), v.end());
	auto last = std::unique(v.begin(), v.end());
	v.erase(last, v.end());
}

// Complete the triplets function below.
long triplets(vector<int> a, vector<int> b, vector<int> c)
{
	sortAndRemoveDuplicates(a);
	sortAndRemoveDuplicates(b);
	sortAndRemoveDuplicates(c);

	long tripletCnt = 0;
	for (int q : b)
	{
		auto ita = upper_bound(a.begin(), a.end(), q);
		ita--;

		auto itc = upper_bound(c.begin(), c.end(), q);
		itc--;

		if (ita != a.end() && itc != c.end())
		{
			auto dista = distance(a.begin(), ita);
			auto distc = distance(c.begin(), itc);
			tripletCnt += (dista + 1) * (distc + 1);
		}
	}

	return tripletCnt;
}

int main()
{
	ifstream fin("../input01.txt", std::ofstream::in);
	ofstream fout("../output01.txt", std::ofstream::out);

	string lenaLenbLenc_temp;
	getline(fin, lenaLenbLenc_temp);

	vector<string> lenaLenbLenc = split_string(lenaLenbLenc_temp);

	int lena = stoi(lenaLenbLenc[0]);

	int lenb = stoi(lenaLenbLenc[1]);

	int lenc = stoi(lenaLenbLenc[2]);

	string arra_temp_temp;
	getline(fin, arra_temp_temp);

	vector<string> arra_temp = split_string(arra_temp_temp);

	vector<int> arra(lena);

	for (int i = 0; i < lena; i++) {
		int arra_item = stoi(arra_temp[i]);

		arra[i] = arra_item;
	}

	string arrb_temp_temp;
	getline(fin, arrb_temp_temp);

	vector<string> arrb_temp = split_string(arrb_temp_temp);

	vector<int> arrb(lenb);

	for (int i = 0; i < lenb; i++) {
		int arrb_item = stoi(arrb_temp[i]);

		arrb[i] = arrb_item;
	}

	string arrc_temp_temp;
	getline(fin, arrc_temp_temp);

	vector<string> arrc_temp = split_string(arrc_temp_temp);

	vector<int> arrc(lenc);

	for (int i = 0; i < lenc; i++) {
		int arrc_item = stoi(arrc_temp[i]);

		arrc[i] = arrc_item;
	}

	long ans = triplets(arra, arrb, arrc);

	fout << ans << "\n";

	fout.close();

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


