#pragma once
#include"Node.h"
template <class T>
class NodeList
{
protected:
	Node<T>* head;
	int length;
public:
	NodeList();
	~NodeList();
	friend class Editor;
	Node<T>* GetItemPtr(int position) const;
	bool Delete(int position);
	bool Insert(int position, T& e);
};

template<class T>
Node<T>* NodeList<T>::GetItemPtr(int position) const
{
	if (position == 0)
		return head;
	Node<T>* temp;
	temp = head->next;
	int pos = 1;
	while (temp != head && pos < position)
	{
		temp = temp->next;
		pos++;
	}
	if (temp != head && pos == position)
	{
		return temp;
	}
	else
		return NULL;
}

template<class T>
NodeList<T>::NodeList()
{
	head = new Node<T>;
	head->next = head;
	length = 0;
}

template<class T>
NodeList<T>::~NodeList()
{
}

template<class T>
bool NodeList<T>::Delete(int position)
{
	if (position < 1 || position > length)
	{
		return false;
	}
	else
	{
		Node<T>* temp = GetItemPtr(position);
		temp->prep->next = temp->next;
		temp->next->prep = temp->prep;
		delete temp;
		length--;
		return true;
	}
}

template<class T>
bool NodeList<T>::Insert(int position, T& e)
{
	if (position < 1 )
	{
		return false;
	}
	else
	{
		Node<T>* temp = GetItemPtr(position - 1);
		Node<T>* newptr, *nextptr;
		nextptr = temp->next;
		newptr = new Node<T>(e, nextptr, temp);
		temp->next = newptr;
		nextptr->prep = newptr;
		length++;
		return true;
	}
}
