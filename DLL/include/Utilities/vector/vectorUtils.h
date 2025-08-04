#pragma once
#include <vector>

using namespace std;

static class VectorUtils
{
public:

	template <typename T>
	static bool Contains(vector<T> vec, T obj)
	{
		bool containsObj = false;
		for (int i = 0; i < vec.size(); i++)
			if (vec.at(i) == obj)
			{
				containsObj = true;
				break;
			}

		return containsObj;
	}

	template <typename T>
	static vector<T> Remove(vector<T> vec, T obj)
	{
		vector<T> newVector;
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec.at(i) == obj)
				continue;

			newVector.push_back(vec.at(i));
		}
		return newVector;
	}

	template <typename T>
	static vector<T> Insert(vector<T> vec, T obj, int index)
	{
		vector<T> newVec;

		for (int i = 0; i < vec.size(); i++)
		{
			if (i == index)
			{
				vec.push_back(obj);
				continue;
			}
			vec.push_back(vec.at(i));
		}
		return newVec;
	}
};