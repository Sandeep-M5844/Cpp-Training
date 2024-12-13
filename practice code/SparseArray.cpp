// SparseArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include<map>

using namespace std;
// sparse array using the CSR-> compressed sparse row

// optimized sparse using the map -> dictonry of keys...
class SparseArray
{
public:
	int default_value = 0;
	map<int, int > mp;

	void insert(int index,int value)
	{
		if (value != default_value)
		{
			mp[index] = value;
		}
		else
			mp.erase(value);
	}
	void get(int index)
	{
		auto it = mp.find(index);
		if (it != mp.end())
			cout << it->second;
		else
			cout << "index out of range"<<endl;
	}

	void display()
	{
		for (auto it : mp)
		{
			cout << "index at" << it.first << " value:" << it.second<<endl;
		}
	}

	// lets create a spase array insert function using the functors concept

	void operator()(int index, int value)
	{
		if (value != default_value)
		{
			mp[index] = value;
		}
		else
			mp.erase(value);
	}



};

int main()
{
	void(SparseArray:: * fun_get)(int); // created a pointer to a function
	fun_get = &SparseArray::get; // assigning the function address tot the a pointer --> function pointer
	SparseArray s;
	s(4, 100); // calling operator overloading using the functors
	s.insert(1, 10);
	s.insert(2, 100);
	s.insert(3, 0);
	//s.insert(3, 5);
	s.get(3);
	
	(s.*fun_get)(4); // calling the function pointer
	s.display();

	return 0;
}