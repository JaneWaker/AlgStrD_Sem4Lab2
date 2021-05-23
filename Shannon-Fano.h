#pragma once
#include "RB-Tree.cpp"
#include "Queue.cpp"

class ShannonFano
{
private:
	class Node {
	public:
		BList<char>* symb;
		int all;
		bool leaf;
		Node* left;
		Node* right;
		Node* parent;

		Node() {
			this->left = nullptr; this->right = nullptr; this->parent = nullptr;
			this->symb = new BList<char>();
			this->leaf = false;
			this->all = 0;
		}
	};
	class Mark {
	public:
		bool* mark;
		int length;

		Mark(bool* mark = nullptr, int length = 0) { 
			this->mark = mark; 
			this->length = length; 
		}
	};

	Node* root;
	char* input;
	int inputLength;
	RedBlackTree<char, Mark*>* marks;
	bool* markString;
	int markLength;

	BList<char>* probability(char*, int*);
	void Tree(Node*);
	void MarkF(Node*);

public:
	ShannonFano(char* string, int stringLength) {
		this->markString = NULL;
		this->markLength = 0;
		this->input = string;
		this->inputLength = stringLength;
		if (stringLength == 0) { 
			root = nullptr; 
		}
		else {
			root = new Node();
			root->symb = probability(string, &stringLength);
			root->all = stringLength;
			if (root->symb->get_size() == 1) {
				root->leaf = true;
			}
			else { 
				root->leaf = false; 
				Tree(root); 
			}
		}
		MarkF(root);
	}

	bool* MarkString(); 
	int GetMarkLength();
	double Coefficient();
	char* DecodeString(); 
	void CodesOut(); 

	~ShannonFano() {};
};
