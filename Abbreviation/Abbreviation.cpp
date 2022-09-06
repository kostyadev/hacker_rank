#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

bool dp[1011][1011];

string abbreviation(string s1, string s2)
{
    for (int i = 0; i <= s1.length(); i++)
    {
        for (int j = 0; j <= s2.length(); j++)
        {
            dp[i][j] = false;
        }
    }

    dp[0][0] = true;

    for (int i = 0; i < s1.length(); i++)
    {
        for (int j = 0; j <= s2.length(); j++)
        {
            if (dp[i][j])
            {
                if (j < s2.length() && (toupper(s1[i]) == s2[j]))
                    dp[i + 1][j + 1] = true;

                if (!isupper(s1[i]))
                    dp[i + 1][j] = true;
            }
        }
    }

    return dp[s1.length()][s2.length()] ? "YES" : "NO";
}

int main()
{
    ifstream fin("input03.txt", std::ofstream::in);

    string q_temp;
    getline(fin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(fin, a);

        string b;
        getline(fin, b);

        string result = abbreviation(a, b);

        cout << result << "\n";
    }

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
