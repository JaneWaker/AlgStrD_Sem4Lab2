#include "RB-Tree.h"
using namespace std;

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::insert(Key find, Value value) {
	Node* current = root, * parent;
	bool moveRight;
	size++;

	if (root == nil) {
		root = new Node(find, value, nil, nil, nil, Black);
		return;
	}
	parent = current;
	while (current != nil) {
		parent = current;
		if (find > current->find) {
			current = current->right;
			moveRight = true;
		}
		else {
			current = current->left;
			moveRight = false;
		}
	}

	if (moveRight) {
		parent->right = new Node(find, value, nil, nil, parent, Red);
		recovery(parent->right);
	}
	else {
		parent->left = new Node(find, value, nil, nil, parent, Red);
		recovery(parent->left);
	}

}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::recovery(Node* New_Node) {
	Node* parent, * grandParent;
	while (New_Node->parent->color == Red) {
		parent = New_Node->parent;
		grandParent = parent->parent;
		if (grandParent->left == parent) {
			if (grandParent->right->color == Red) {
				grandParent->right->color = Black;
				grandParent->left->color = Black;
				grandParent->color = Red;
				New_Node = grandParent;
			}
			else {
				if (parent->right == New_Node) {
					New_Node = parent;
					leftRotate(New_Node);
				}
				New_Node->parent->color = Black;
				New_Node->parent->parent->color = Red;
				rightRotate(New_Node->parent->parent);
			}
		}
		else {
			if (grandParent->left->color == Red) {
				grandParent->right->color = Black;
				grandParent->left->color = Black;
				grandParent->color = Red;
				New_Node = grandParent;
			}
			else {
				if (parent->left == New_Node) {
					New_Node = parent;
					rightRotate(New_Node);
				}
				New_Node->parent->color = Black;
				New_Node->parent->parent->color = Red;
				leftRotate(New_Node->parent->parent);
			}
		}
	}
	root->color = Black;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::leftRotate(Node* current_to_X) {
	if (current_to_X->right == nil) return;
	Node* current_to_Y = current_to_X->right;

	if (current_to_Y->left != nil) {
		current_to_X->right = current_to_Y->left;
		current_to_Y->left->parent = current_to_X;
	}
	else current_to_X->right = nil;

	if (current_to_Y != nil) {
		current_to_Y->parent = current_to_X->parent;
	}
	if (current_to_X->parent != nil) {
		if (current_to_X == current_to_X->parent->left) {
			current_to_X->parent->left = current_to_Y;
		}
		else {
			current_to_X->parent->right = current_to_Y;
		}
	}
	else {
		current_to_Y->parent = nil;
		root = current_to_Y;
	}
	current_to_Y->left = current_to_X;
	if (current_to_X != nil) {
		current_to_X->parent = current_to_Y;
	}

}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::rightRotate(Node* current_to_X) {

	Node* current_to_Y = current_to_X->left;

	current_to_X->left = current_to_Y->right;
	if (current_to_Y->right != nil) {
		current_to_Y->right->parent = current_to_X;
	}

	if (current_to_Y != nil) {
		current_to_Y->parent = current_to_X->parent;
	}
	if (current_to_X->parent != nil) {
		if (current_to_X == current_to_X->parent->right) {
			current_to_X->parent->right = current_to_Y;
		}
		else {
			current_to_X->parent->left = current_to_Y;
		}
	}
	else {
		root = current_to_Y;
	}
	current_to_Y->right = current_to_X;
	if (current_to_X != nil) {
		current_to_X->parent = current_to_Y;
	}
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::remove(Key find) {
	if (root == nil) {
		throw out_of_range("Tree is empty");
	}
	Node* ToDelete = root;
	while (ToDelete->find != find) {
		if (find > ToDelete->find) {
			ToDelete = ToDelete->right;
		}
		else {
			ToDelete = ToDelete->left;
		}
		if (ToDelete == nil) {
			throw out_of_range("No such element");
		}
	}

	Node* x, * min;
	bool originalColor = ToDelete->color;
	if (ToDelete->left == nil) {
		x = ToDelete->right;
		if (ToDelete->parent == nil) {
			root = x;
		}
		else
			if (ToDelete->parent->left == ToDelete) {
				ToDelete->parent->left = x;
			}
			else {
				ToDelete->parent->right = x;
			}
		x->parent = ToDelete->parent;
	}
	else if (ToDelete->right == nil) {
		x = ToDelete->left;
		if (ToDelete->parent == nil) {
			root = x;
		}
		else if (ToDelete->parent->left == ToDelete) {
			ToDelete->parent->left = x;
		}
		else {
			ToDelete->parent->right = x;
		}
		x->parent = ToDelete->parent;
	}
	else {
		Node* temp = ToDelete;
		min = ToDelete->right;
		while (min->left != nil) min = min->left;
		originalColor = min->color;
		ToDelete = min;
		x = ToDelete->right;
		if (ToDelete->parent == temp) {
			x->parent = ToDelete;
		}
		else {
			if (ToDelete->parent == nil) {
				root = x;
				ToDelete->right->parent = nil;
			}
			else if (ToDelete->parent->right == ToDelete) {
				ToDelete->parent->right = x;
			}
			else {
				ToDelete->parent->left = x;
			}
			x->parent = ToDelete->parent;
			ToDelete->right = temp->right;
			ToDelete->right->parent = ToDelete;


		}
		if (temp->parent == nil) {
			root = ToDelete;
		}
		else if (temp == temp->parent->left) {
			temp->parent->left = ToDelete;
		}
		else {
			temp->parent->right = ToDelete;
		}
		ToDelete->parent = temp->parent;
		ToDelete->left = temp->left;
		ToDelete->left->parent = ToDelete;
		ToDelete->color = temp->color;
	}
	if (originalColor == Black) recoveryRemove(x);
	size--;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::recoveryRemove(Node* x) {
	Node* brother;
	while (x != root && x->color == Black) {
		if (x == x->parent->left) {
			brother = x->parent->right;
			if (brother->color == Red) {
				brother->color = Black;
				x->parent->color = Red;
				leftRotate(x->parent);
				brother = x->parent->right;
			}
			if (brother->left->color == Black && brother->right->color == Black) {
				brother->color = Red;
				x = x->parent;
			}
			else {
				if (brother->right->color == Black) {
					brother->left->color = Black;
					brother->color = Red;
					rightRotate(brother);
					brother = x->parent->right;
				}
				brother->color = x->parent->color;
				x->parent->color = Black;
				brother->right->color = Black;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			brother = x->parent->left;
			if (brother->color == Red) {
				brother->color = Black;
				x->parent->color = Red;
				rightRotate(x->parent);
				brother = x->parent->left;
			}
			if (brother->right->color == Black && brother->left->color == Black) {
				brother->color = Red;
				x = x->parent;
			}
			else {
				if (brother->left->color == Black) {
					brother->right->color = Black;
					brother->color = Red;
					leftRotate(brother);
					brother = x->parent->left;
				}
				brother->color = x->parent->color;
				x->parent->color = Black;
				brother->left->color = Black;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = Black;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::clear() {
	while (root != nil) {
		remove(root->find);
		cout << endl;
		print();
	}
}

template<typename Key, typename Value>
Value RedBlackTree<Key, Value>::find(Key findKey) {
	Node* cur = root;
	while (cur->find != findKey) {
		if (findKey > cur->find) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
		if (cur == nil) {
			throw out_of_range("No such element");
		}
	}

	return cur->value;
}

template<typename Key, typename Value>
Key* RedBlackTree<Key, Value>::get_keys() {
	Key* arr = new Key[size]; int i = 0;
	dft_Iterator Iterator(root, nil);
	while (Iterator.has_next()) {
		arr[i] = Iterator.next()->find; i++;
	}
	return arr;
}

template<typename Key, typename Value>
Value* RedBlackTree<Key, Value>::get_values() {
	Value* arr = new Value[size]; int i = 0;
	dft_Iterator Iterator(root, nil);
	while (Iterator.has_next()) {
		arr[i] = Iterator.next()->value; i++;
	}
	return arr;
}

template<typename Key, typename Value>
void RedBlackTree<Key, Value>::print() {
	dft_Iterator Iterator(root, nil);
	Node* current;
	while (Iterator.has_next())
	{
		current = Iterator.next();
		cout << "\nKey: " << current->find << " Color: " << current->color << endl;;
		cout << "    Kids " << current->left->find << " " << current->right->find << endl;
	}
}

template<typename Key, typename Value>
bool RedBlackTree<Key, Value>::get_color(Key findKey) {
	Node* current = root;
	while (current->find != findKey) {
		if (findKey > current->find) {
			current = current->right;
		}
		else {
			current = current->left;
		}
		if (current == nil) {
			throw out_of_range("No such element");
		}
	}
	return current->color;
}

template<typename Key, typename Value>
int RedBlackTree<Key, Value>::get_size() {
	return size;
}