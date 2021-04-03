#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct MyXmlTree
{
	string tag;
	vector<pair<string, string>> attributes;
	MyXmlTree* parent = nullptr;
	vector<unique_ptr<MyXmlTree>> children;

	~MyXmlTree()
	{
		auto tmp = this->tag;
		int a = 1;
	}
};

MyXmlTree* CreateXmlTreeFrom(const vector<string>& strVect, const int vectIdx, MyXmlTree* parent)
{
	if (vectIdx >= strVect.size())
		return nullptr;

	MyXmlTree* xmlTree = nullptr;
	const string& str = strVect[vectIdx];

	if (str[0] == '<' && str[1] == '/') // string begins with "</" that is close tag
	{
		xmlTree = nullptr;
		MyXmlTree* grandParent = (parent == nullptr) ? nullptr : parent->parent;
		CreateXmlTreeFrom(strVect, vectIdx + 1, grandParent);
	}
	else // string begins with non close tag
	{
		const auto pos = str.find_first_of(" ", 0);
		xmlTree = new MyXmlTree();
		xmlTree->tag = str.substr(1, pos - 1);
		if (parent != nullptr)
		{
			xmlTree->parent = parent;
			unique_ptr<MyXmlTree> uptr(xmlTree);
			parent->children.push_back(move(uptr));
		}			
		CreateXmlTreeFrom(strVect, vectIdx + 1, xmlTree);
	}

	return xmlTree;
}

void parseAttr(const vector<string>& strVect, const int strvIdx, const string& query, const int queryIdx, const bool isTag)
{
	const auto nextDividerPos = query.find_first_of(".~", queryIdx);
	const bool isNextTag = query[nextDividerPos] == '.';
	const auto curQueryToken = query.substr(queryIdx, nextDividerPos - queryIdx);

	if (isTag) // is a tag
	{
		
	}
}

void parseAttr(const vector<string>& strVect, const vector<string>& qVect)
{
	auto xmlTree = CreateXmlTreeFrom(strVect, 0, nullptr);
	unique_ptr<MyXmlTree> uptr(xmlTree);

	for (int i = 0; i < qVect.size(); ++i)
		parseAttr(strVect, 0, qVect[i], 0, true);
}

int main()
{
	//ifstream fin("..\\input00.txt", std::ofstream::in); // Name1 Not Found! HelloWorld
	ifstream fin("..\\input01.txt", std::ofstream::in); // GoodVal	Not Found!	10	BadVal	Not Found!	auto	Not Found!	2   Not Found!  3

	int n, q;
	fin >> n;
	fin >> q;

	string tmp;
	getline(fin, tmp);
	vector<string> strvect;
	for (int i = 0; i < n; ++i)
	{
		string s;
		getline(fin, s);
		strvect.push_back(move(s));
	}

	vector<string> qvect;
	for (int i = 0; i < q; ++i)
	{
		string s;
		getline(fin, s);
		qvect.push_back(move(s));
	}

	parseAttr(strvect, qvect);
}

