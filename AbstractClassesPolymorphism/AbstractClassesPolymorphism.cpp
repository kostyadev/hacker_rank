#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <fstream> 
using namespace std;

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
	map<int, Node*> mp; //map the key to the node in the linked list
	int cp;  //capacity
	Node* tail; // double linked list tail pointer
	Node* head; // double linked list head pointer
	virtual void set(int, int) = 0; //set function
	virtual int get(int) = 0; //get function

};

class LRUCache : public Cache
{
public:
	LRUCache(int capacity) : Cache()
	{
		cp = capacity;
		tail = nullptr;
		head = nullptr;
	}

	void set(int key, int val) override
	{
		auto it = mp.find(key);
		//need to insert a new Node?
		if (it == mp.end())
		{
			//remove old tail
			if (mp.size() == cp)
			{
				auto oldTail = tail;
				tail = oldTail->next;
				tail->prev = nullptr;
				mp.erase(oldTail->key);
				delete oldTail;
			}
			//add a new head
			auto oldHead = head;
			head = new Node(oldHead, nullptr, key, val);
			if (oldHead)
				oldHead->next = head;
			if (!tail)
				tail = head;
			mp[key] = head;
		}
		else //or move to the head
		{
			auto node = it->second;
			if (node != head)
			{
				if(node->next)
					node->next->prev = node->prev;
				node->next = nullptr;
				node->prev = head;
				head = node;
			}
			// with the same key ther can be different vaule, so set it
			node->value = val;
		}
	}

	int get(int key) override
	{
		auto it = mp.find(key);
		return it == mp.end() ? -1 : it->second->value;
	}
};

int main() 
{
	//ifstream fin("input11.txt", std::ofstream::in);
	//ifstream fin("input00.txt", std::ofstream::in);
	ifstream fin("input01.txt", std::ofstream::in);
	//ofstream fout("out01.txt", std::ofstream::out);

	int outCnt = 0;
	int n, capacity, i;
	fin >> n >> capacity;
	LRUCache l(capacity);
	for (i = 0; i < n; i++) {
		string command;
		fin >> command;
		if (command == "get") {
			int key;
			fin >> key;
			cout << l.get(key) << endl;
			outCnt++;
			if (key == 7)
				int a = 1;
		}
		else if (command == "set") {
			int key, value;
			fin >> key >> value;
			if (key == 7)
				int a = 1;
			l.set(key, value);
		}
	}

	fin.close();

	return 0;
}