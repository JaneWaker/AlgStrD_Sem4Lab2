#include <iostream>
using namespace std;

template <class T>
class BList
{
private:
	class Node
	{
	public:
		Node(T this_branch, int priority = 0, Node* previous_branch = nullptr, Node* next_branch = nullptr)
		{
			this->this_branch = this_branch;
			this->priority = priority;
			this->previous_branch = previous_branch;
			this->next_branch = next_branch;
		};
		~Node()
		{  }
		T this_branch;
		int priority;
		Node* next_branch;
		Node* previous_branch;
	private:

	};

	Node* first;
	Node* last;
	size_t size;

public:
	BList(Node* first = nullptr, Node* last = nullptr) {
		this->first = first;
		this->last = last;
		size = 0;
	};
	void push(T, int);
	size_t get_size();
	T pop_back();
	T get_front();
	T pop_front();
	int first_priority();
	int last_priority();
	bool IsEmpty();
	void clear();
	BList<T>* Copy();
	~BList()
	{
		while (first->next_branch != nullptr) {
			first = first->next_branch;
			delete first->previous_branch;
		}
		size = 0;
		delete first;
	};
};

template <class T>
void BList<T>::push(T add, int priority)
{
	if (size == 0)
	{
		first = new Node(add, priority);
		last = first;
	}
	else
	{
		Node* NewNode = new Node(add, priority);
		Node* current = first;
		while ((current->next_branch != NULL) && (NewNode->priority < current->priority))
		{
			current = current->next_branch;
		}
		if ((NewNode->priority <= current->priority) && (current->next_branch == NULL)) {
			NewNode->previous_branch = current;
			NewNode->next_branch = NULL;
			current->next_branch = NewNode;
			last = NewNode;
		}
		else if ((NewNode->priority >= current->priority) && (current->previous_branch == NULL))
		{
			NewNode->previous_branch = NULL;
			NewNode->next_branch = current;
			current->previous_branch = NewNode;
			first = NewNode;
		}
		else {
			NewNode->next_branch = current;
			NewNode->previous_branch = current->previous_branch;
			current->previous_branch->next_branch = NewNode;
			current->previous_branch = NewNode;

		}
	}
	size++;
}

template <class T>
size_t BList<T>::get_size() 
{
	return size;
}

template <class T>
T BList<T>::pop_front() 
{
	T data;
	if (size == 1)
	{
		data = first->this_branch;
		size = 0; 
		first = NULL;
		last = NULL;
	}
	else if (size > 1) 
	{
		data = first->this_branch;
		first = first->next_branch;
		delete first->previous_branch;
		first->previous_branch = NULL;
		size--;
	}
	else {
		throw out_of_range("Error");
	}
	return data;
}

template <class T>
T BList<T>::pop_back()
{
	T data;
	if (size == 1)
	{
		data = last->this_branch;
		size = 0;
		first = NULL;
		last = NULL;
	}
	else if (size > 1)
	{
		data = last->this_branch;
		last = last->previous_branch;
		delete last->next_branch;
		last->next_branch = NULL;
		size--;
	}
	else {
		throw out_of_range("Error");
	}
	return data;
}

template <class T>
int BList<T>::first_priority() {
	return first->priority;
}

template <class T>
int BList<T>::last_priority() {
	return last->priority;
}

template <class T>
void BList<T>::clear()
{
	if (first != NULL)
	{
		while (first->next_branch != NULL)
		{
			first = first->next_branch;
			delete first->previous_branch;
		}
		size = 0;
		first = NULL;
		last = NULL;
	}
}

template <class T>
bool BList<T>::IsEmpty() 
{
	if (first == NULL)
		return true;
	return false;
}

template <class T>
BList<T>* BList<T>::Copy() {
	BList<T>* NewQueue = new BList<T>();
	Node* current= first;
	while (current!= nullptr) {
		if (current== NULL) break;
		NewQueue->push(current->this_branch, current->priority);
		current= current->next_branch;
	}
	return NewQueue;
}

template <class T>
T BList<T>::get_front() {
	return first->this_branch;
}