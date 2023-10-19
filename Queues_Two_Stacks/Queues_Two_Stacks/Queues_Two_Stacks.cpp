#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> 
#include <stack>
#include <functional>
using namespace std;

class MyQueue {

public:
	stack<int> lifo, fifo;
	void push(int x) {
		lifo.push(x);
	}

	void pop() {
		if (!fifo.empty())
		{
			fifo.pop();
		}
		else
		{
			while (lifo.size() > 1)
			{
				fifo.push(lifo.top());
				lifo.pop();
			}
			lifo.pop();
		}
	}

	int front() {
		if (fifo.empty())
		{
			while (!lifo.empty())
			{
				fifo.push(lifo.top());
				lifo.pop();
			}
		}
		return fifo.top();;
	}
};

int main() 
{
	ifstream fin("../input00.txt", std::ofstream::in);

	MyQueue q1;
	int q, type, x;
	fin >> q;

	for (int i = 0; i < q; i++) {
		fin >> type;
		if (type == 1) {
			fin >> x;
			q1.push(x);
		}
		else if (type == 2) {
			q1.pop();
		}
		else cout << q1.front() << endl;
	}
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	return 0;
}