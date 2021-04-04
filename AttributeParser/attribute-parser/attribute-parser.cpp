#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

struct MyXmlTree
{
	string tag;
	vector<pair<string, string>> attributes;
	MyXmlTree* parent = nullptr;
	vector<unique_ptr<MyXmlTree>> children;
};

void fillAttributes(MyXmlTree* xmlTree, const string& str)
{
	const size_t eqPos = str.find_first_of("=", 0);
	if (eqPos == string::npos)
		return;

	const size_t pos = str.find_first_of(" ", 0);
	auto startAttrNamePos = str.find_first_not_of(' ', pos + 1);
	while (startAttrNamePos != string::npos)
	{
		const auto endAttrNamePos = str.find_first_of(" =", startAttrNamePos);
		const auto attrName = str.substr(startAttrNamePos, endAttrNamePos - startAttrNamePos);
		const auto startAttrValPos = str.find_first_of("\"", endAttrNamePos);
		const auto endAttrValPos = str.find_first_of("\"", startAttrValPos + 1);
		const auto attrVal = str.substr(startAttrValPos + 1, endAttrValPos - startAttrValPos - 1);
		startAttrNamePos = str.find_first_not_of(" />", endAttrValPos + 1);
		xmlTree->attributes.push_back(make_pair(attrName, attrVal));
	}
}

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
	else // string begins with other tag
	{
		const auto pos = str.find_first_of(" >", 0);
		xmlTree = new MyXmlTree();
		xmlTree->tag = str.substr(1, pos - 1);
		fillAttributes(xmlTree, str);
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

void findAttr(const MyXmlTree* xmlTree, const string& query)
{
	const auto delimPos = query.find_first_of(".~", 0);
	const auto tag = query.substr(0, delimPos);
	if (xmlTree->tag != tag)
	{
		cout << "Not Found!" << endl;
		return;
	}
	
	const bool isAttr = (query[delimPos] == '~');
	if (isAttr)
	{
		const auto attr = query.substr(delimPos + 1, query.size() - delimPos - 1);
		auto it = find_if(xmlTree->attributes.begin(), xmlTree->attributes.end(), [&attr](const auto& elem) {return elem.first == attr; });
		if (it != xmlTree->attributes.end())
		{
			cout << it->second << endl;
		}
		else
		{
			cout << "Not Found!" << endl;
			return;
		}
	}
	else
	{
		const auto nextDelimPos = query.find_first_of(".~", delimPos + 1);
		const auto childTag = query.substr(delimPos + 1, nextDelimPos - delimPos - 1);
		auto it = find_if(xmlTree->children.begin(), xmlTree->children.end(), [&childTag](const auto& elem) {return elem->tag == childTag; });
		if (it != xmlTree->children.end())
		{
			auto childXmlTree = it->get();
			const auto childQuery = query.substr(delimPos + 1, query.size() - delimPos - 1);
			findAttr(childXmlTree, childQuery);
		}
		else
		{
			cout << "Not Found!" << endl;
			return;
		}
	}
}

void parseAttr(const vector<string>& strVect, const vector<string>& qVect)
{
	vector<string> rootedStrVect;
	rootedStrVect.reserve(strVect.size() + 2);
	rootedStrVect.push_back("<root>");
	rootedStrVect.insert(rootedStrVect.end(), strVect.begin(), strVect.end());
	rootedStrVect.push_back("</root>");

	unique_ptr<MyXmlTree> xmlTreeUptr(CreateXmlTreeFrom(rootedStrVect, 0, nullptr));

	for (int i = 0; i < qVect.size(); ++i)
		findAttr(xmlTreeUptr.get(), "root." + qVect[i]);
}

int main()
{
	//ifstream fin("..\\input00.txt", std::ofstream::in); // Name1 Not Found! HelloWorld
	//ifstream fin("..\\input01.txt", std::ofstream::in); // GoodVal	Not Found!	10	BadVal	Not Found!	auto	Not Found!	2   Not Found!  3
	//ifstream fin("..\\input02.txt", std::ofstream::in); // tag_one	val_907		Not Found!		Not Found!
	ifstream fin("..\\input04.txt", std::ofstream::in); // 

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

