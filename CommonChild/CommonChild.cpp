#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>

using namespace std;

/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */

int commonChild(string s1, string s2)
{
    auto n = s1.length();
    auto m = s2.length();
    
    //fill matrix with zeros
    vector<vector<uint16_t>> lcs;
    for (int i = 0; i < n; ++i)
        lcs.push_back(vector<uint16_t>(m, 0));

    // do the job
    for (int i = 0; i < s1.length(); ++i)
        for (int j = 0; j < s2.length(); ++j)
            if (s1[i] == s2[j])
            {
                auto tmp = (i == 0 || j == 0) ? 0 : lcs[i - 1][j - 1];
                lcs[i][j] = tmp + 1;
            }
            else
            {
                auto tmp1 = j == 0 ? 0 : lcs[i][j - 1];
                auto tmp2 = i == 0 ? 0 : lcs[i - 1][j];
                lcs[i][j] = max(tmp1, tmp2);
            }
                
    return lcs[n - 1][m - 1];
}

int main()
{
    ifstream fin("input01.txt", std::ofstream::in); // expected: 15

    string s1;
    getline(fin, s1);

    string s2;
    getline(fin, s2);

    int result = commonChild(s1, s2);

    cout << result << "\n";

    return 0;
}

