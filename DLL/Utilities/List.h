#pragma once
#include "Node.h"

// Definitions in .h explanation
//https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c

template <typename T>
class List
{
private:
	Node<T>* first;
	int count;

public:

	List()
	{
		first = nullptr;
		this->count = 0;
	}
	~List()
	{
		Clear();
	}

	int GetCount()
	{
		return count;
	}

	void PushFront(T data)
	{
		Node<T>* nodeToPush = new Node<T>(data);
		nodeToPush->SetNext(first);
		first = nodeToPush;
		count++;
	}

	void PushBack(T data)
	{
		Node<T>* nodeToPush = new Node<T>(data);
		Node<T>* lastNode = GetLastNode();
		if (lastNode != nullptr)
			lastNode->SetNext(nodeToPush);
		else
			first = nodeToPush;
		count++;
	}

	void Insert(T data, int index)
	{
		if (index == 0)
		{
			PushFront(data);
		}
		else if (index < count && index > 0)
		{
			if (GetNodeAt(index - 1)->GetNext() != nullptr)
			{
				Node<T>* next = GetNodeAt(index - 1)->GetNext();
				Node<T>* insertedNode = new Node<T>(data);
				GetNodeAt(index - 1)->SetNext(insertedNode);
				insertedNode->SetNext(next);
				count++;
			}
			else
			{
				Node<T>* insertedNode = new Node<T>(data);
				GetPenultimateNode()->SetNext(insertedNode);
				count++;
			}
		}
	}

	T PopFront()
	{
		T poppedData;
		if (first != nullptr)
		{
			Node<T>* next = first->GetNext();
			poppedData = first->GetData();
			first->SetNext(nullptr);
			delete first;
			first = next;
			count--;
		}
		return poppedData;
	}

	T PopBack()
	{
		T lastNodeData;
		if (first != nullptr)
		{
			Node<T>* lastNode = GetLastNode();
			lastNodeData = lastNode->GetData();
			Node<T>* penultimateNode = GetPenultimateNode();
			if (penultimateNode != nullptr)
				penultimateNode->SetNext(nullptr);
			else
				first = nullptr;

			delete lastNode;
			count--;
		}
		return lastNodeData;
	}

	T PopAt(int index)
	{
		T nodeToPopData;
		if (index == 0)
		{
			if (first->GetNext() != nullptr)
			{
				Node<T>* newFirst = first->GetNext();
				nodeToPopData = first->GetData();
				first->SetNext(nullptr);
				delete first;
				first = newFirst;
				count--;
			}
			else
			{
				delete first;
				first = nullptr;
				nodeToPopData = T();
				count = 0;
			}
			return nodeToPopData;
		}
		if (index < count && index != 0)
		{
			Node<T>* nodeToPop = GetNodeAt(index);
			nodeToPopData = nodeToPop->GetData();
			if (nodeToPop->GetNext() != nullptr)
			{
				GetNodeAt(index - 1)->SetNext(nodeToPop->GetNext());
				nodeToPop->SetNext(nullptr);
				delete nodeToPop;
				nodeToPop = nullptr;
			}
			else
			{
				GetPenultimateNode()->SetNext(nullptr);
				delete nodeToPop;
			}
			count--;
			return nodeToPopData;
		}
	}

	void Clear()
	{
		if (first != nullptr)
		{
			delete first;
			first = nullptr;
			count = 0;
		}
	}

	Node<T>* GetLastNode()
	{
		Node<T>* lastNode = first;

		if (first != nullptr)
		{
			while (lastNode->GetNext() != nullptr)
			{
				lastNode = lastNode->GetNext();
			}
		}

		return lastNode;
	}

	Node<T>* GetPenultimateNode()
	{
		Node<T>* lastNode = first;
		Node<T>* penultimateNode = nullptr;
		if (first)
		{
			while (lastNode->GetNext() != nullptr)
			{
				penultimateNode = lastNode;
				lastNode = lastNode->GetNext();
			}
		}
		return penultimateNode;
	}

	T GetValueAt(int index)
	{
		Node<T>* node = nullptr;
		if (index < count)
			for (int i = 0; i <= index; i++)
			{
				if (i == 0)
					node = first;
				else
					node = node->GetNext();
			}
		return node->GetData();
	}

	Node<T>* GetNodeAt(int index)
	{
		Node<T>* node = nullptr;
		if (index < count)
			for (int i = 0; i <= index; i++)
			{
				if (i == 0)
					node = first;
				else
					node = node->GetNext();
			}
		return node;
	}

	bool Contains(T data)
	{
		for (int i = 0; i < count; i++)
		{
			if (GetValueAt(i) == data)
				return true;
		}
		return false;
	}

	void Remove(T data)
	{
		if (Contains(data))
		{
			for (int i = 0; i < count; i++)
			{
				if (GetValueAt(i) == data)
				{
					PopAt(i);
					return;
				}
			}
		}
	}
};