#pragma once
#include <type_traits>

using namespace std;

template <typename T>
class Node
{
private:
	T data;
	Node<T>* next = nullptr;

public:

	Node()
	{
		if (is_pointer<T>::value)
			this->data = nullptr;

		next = nullptr;
	}
	Node(T data)
	{
		this->data = data;
		next = nullptr;
	}

	~Node()
	{
		if (next != nullptr)
		{
			delete next;
		}
	}

	Node<T>* GetNext()
	{
		return next;
	}

	void SetNext(Node<T>* next)
	{
		this->next = next;
	}

	T GetData()
	{
		return data;
	}
};