#include <iostream>
#include <fstream>
#include <deque> 
#include <vector> 
#include <set>

using namespace std;

void printKMax(const vector<int>& arr, int k)
{
	std::deque<int> Qi(k);

	/* Process first k (or first window)
	 elements of array */
	int i;
	for (i = 0; i < k; ++i)
	{

		// For every element, the prev.
		// smaller elements are useless so
		// remove them from Qi
		while ((!Qi.empty()) && arr[i] >=
			arr[Qi.back()])

			// Remove from rear
			Qi.pop_back();

		// Add new element at rear of queue
		Qi.push_back(i);
	}

	// Process rest of the elements, 
	// i.e., from arr[k] to arr[n-1]
	for (; i < arr.size(); ++i)
	{

		// The element at the front of 
		// the queue is the largest element of
		// prev. window, so print it
		cout << arr[Qi.front()] << " ";

		// Remove the elements which 
		// are out of this window
		while ((!Qi.empty()) && Qi.front() <=
			i - k)

			// Remove from front of queue
			Qi.pop_front();

		// Remove all elements 
		// smaller than the curr.
		// being added element (remove 
		// useless elements)
		while ((!Qi.empty()) && arr[i] >=
			arr[Qi.back()])
			Qi.pop_back();

		// Add current element at the rear of Qi
		Qi.push_back(i);
	}

	// Print the maximum element 
	// of last window
	cout << arr[Qi.front()] << endl;
}

int main() 
{
	ifstream fin("..\\input00.txt", std::ofstream::in); // 4 6 6 4  	8 8 8 10
	//ifstream fin("..\\input01.txt", std::ofstream::in); 

	int t;
	fin >> t;
	while (t > 0) {
		int n, k;
		fin >> n >> k;
		int i;
		vector<int> arr(n);
		for (i = 0; i < n; i++)
			fin >> arr[i];
		printKMax(arr, k);
		t--;
	}

	return 0;
}