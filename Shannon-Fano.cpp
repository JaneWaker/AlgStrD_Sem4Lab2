#include "Shannon-Fano.h"
#include"Stack.h"

BList<char>* ShannonFano::probability(char* string, int* length) {
	BList<char>* symb = new BList<char>();
	int chars[256] = { 0 };
	int count = 0;
	for (int i = 0; (string[i] != i < *length && '\n'); i++)
	{
		chars[string[i]]++; count++;
	}
	for (int i = 0; i < 256; i++) {
		if (chars[i] != 0) symb->push((char)i, chars[i]);
	}
	*length = count;
	return symb;
}


void ShannonFano::Tree(Node* current) {
	if (current->symb->get_size() == 1) { 
		current->leaf = true; 
		return; 
	}
	BList<char>* symb = new BList<char>();
	symb = current->symb->Copy();
	Node* left = new Node();
	Node* right = new Node();
	int pLeft, pRight;
	pLeft = symb->first_priority(); 
	left->symb->push(symb->pop_front(), pLeft);
	pRight = symb->last_priority(); 
	right->symb->push(symb->pop_back(), pRight);
	while (!symb->IsEmpty()) {
		int pCurrent;
		if (pLeft > pRight) {
			pCurrent = symb->last_priority();
			right->symb->push(symb->pop_back(), pCurrent);
			pRight += pCurrent;
		}
		else {
			pCurrent = symb->first_priority();
			left->symb->push(symb->pop_front(), pCurrent);
			pLeft += pCurrent;
		}
	}
	left->all = pLeft;
	right->all = pRight;
	current->left = left;
	current->right = right;
	left->parent = current;
	right->parent = current;
	Tree(left);
	Tree(right);
}

void ShannonFano::MarkF(Node* root) {
	if (root == nullptr) {
		this->marks = nullptr;
		return;
	}
	Stack<Node*>* stack = new Stack<Node*>();
	stack->push(root);
	RedBlackTree<char, Mark*>* marks = new RedBlackTree<char, Mark*>();
	bool* CurrentMark = new bool[root->all / 2 + 1];
	Node* current = root;
	int deep = 0;
	if (root->leaf) { 
		deep = 1; 
		CurrentMark[0] = 0; 
	}
	while (!stack->IsEmpty()) {
		if (current->left != NULL) {
			CurrentMark[deep] = 1;
			deep++;
			if (current->right != NULL) {
				stack->push(current->right);
			}
			current = current->left;
		}
		else if (current->right != NULL) {
			CurrentMark[deep] = 0;
			deep++;
			current = current->right;
		}
		else {
			bool* finalCode = new bool[deep];
			for (int i = 0; i < deep; i++) finalCode[i] = CurrentMark[i];

			Mark* Code = new Mark(finalCode, deep);
			marks->insert((int)current->symb->get_front(), Code);

			while (stack->get_top() != current->right) {
				current = current->parent;
				deep--;
				if (current == nullptr) break;
			}
			current = stack->pop();
			CurrentMark[deep] = 0;
			deep++;
		}
	}
	this->marks = marks;
}

bool* ShannonFano::MarkString() {
	if (root == nullptr) return NULL;
	if (markString != NULL) return markString; //if we did this already
	BList<char>* symb = new BList<char>();
	symb = root->symb->Copy();

	int prior, codeLength = 0; char CurrentSymbol;
	while (!symb->IsEmpty()) {
		prior = symb->first_priority();
		CurrentSymbol = symb->pop_front();
		Mark* CurrentMark = marks->find(CurrentSymbol);
		codeLength += prior * CurrentMark->length;
	}

	this->markLength = codeLength;
	markString = new bool[codeLength];

	int currenti = 0, j = 0;
	for (int j = 0; j < inputLength; j++) {
		CurrentSymbol = input[j];
		Mark* CurrentMark = marks->find(CurrentSymbol);
		for (int i = 0; i < CurrentMark->length; i++) {
			markString[currenti] = CurrentMark->mark[i]; currenti++;
		}
	}

	return markString;
}

char* ShannonFano::DecodeString() {
	if (markString == NULL) return NULL;
	int curLength = 0;
	Node* current = root;
	char* string = new char[markLength];
	for (int i = 0; curLength < markLength && i < markLength;) {
		while (!current->leaf) {
			if (markString[i] == 1) {
				current = current->left;
			}
			else {
				current = current->right;
			}
			i++;
		}
		string[curLength] = current->symb->get_front();
		curLength++;
		current = root;
	}
	for (int i = 0; i < curLength + 1; i++) cout << string[i];
	char* finalString = new char[curLength + 1];
	for (int i = 0; i < curLength + 1; i++) finalString[i] = string[i];
	return finalString;
}

void ShannonFano::CodesOut() {
	char* chars = marks->get_keys();
	Mark** Symbs = marks->get_values();
	for (int i = 0; i < marks->get_size(); i++)
	{
		cout << endl << chars[i] << " ";
		for (int j = 0; j < Symbs[i]->length; j++)
			cout << Symbs[i]->mark[j];
	}
}

int ShannonFano::GetMarkLength() {
	return markLength; 
}

double ShannonFano::Coefficient() {
	return (double)sizeof(char) * inputLength * 8 / markLength; 
}