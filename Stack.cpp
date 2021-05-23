#include "Stack.h"
using namespace std;

template <typename T>
size_t Stack<T>::get_size()
{
	return size;
}

template <typename T>
void Stack<T>::push(T add)
{
	if (size == 0) 
	{
		first = new Node(add); 
		last = first;
	}
	else
	{
		Node* this_branch = new Node(add);
		this_branch->previous_branch = last;
		last->next_branch = this_branch;
		last = this_branch;  
	}
	size++;
}

template <typename T>
T Stack<T>::pop()
{
	T this_branch;
	if (size == 1)
	{
		size = 0;  
		this_branch = last->data;
		first = NULL;
		last = NULL;

	}
	else if (size > 1) 
	{
		this_branch = last->data;
		last = last->previous_branch; 
		delete last->next_branch;
		last->next_branch = NULL;
		size--;
	}
	else {  
		throw out_of_range("Error");
	}
	return this_branch;
}

template <typename T>
T Stack<T>::get_top() {
	return last->data;
}

template <typename T>
bool Stack<T>::IsEmpty()
{
	if (first == NULL) {
		return true;
	}
	return false;
}

template <typename T>
void Stack<T>::clear()
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