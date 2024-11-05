#pragma once

template <typename T>
class Node
{
private:
	T data;
	Node<T>* next;

public:

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