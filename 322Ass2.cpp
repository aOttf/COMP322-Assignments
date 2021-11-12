#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;
class Node {
public:
	Node();
	Node(int value, Node *next, Node *prev);
	~Node();
	int value;
	Node *next;
	Node *prev;
};
Node::Node() {
	this->value = 0;
	this->next = NULL;
	this->prev = NULL;
}
Node::Node(int value, Node *next, Node *prev) {
	this->value = value;
	this->next = next;
	this->prev = prev;
}
Node::~Node() {
}

class DLLStructure {
public:
	DLLStructure();
	DLLStructure(int *arr, int size);
	DLLStructure(const DLLStructure &dll);
	~DLLStructure();
	void printDLL();
	void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
	void InsertBefore(int valueToInsertBefore, int valueToBeInserted);
	void Delete(int value);
	//Insersion sort
	void Sort();
	bool IsEmpty();
	int getHead();
	int getTail();
	int getSize();
	int getMax();
	int getMin();
	//The following two methods will also update size, min and max
	void addNode(int data);

private:
	Node *first;
	Node *last;

};

DLLStructure::DLLStructure() {
	this->first = NULL;
	this->last = NULL;
}
DLLStructure::DLLStructure(int arr[], int size) {
	this->first = NULL;
	this->last = NULL;

	for (int i = 0; i < size; i++) {
		//add current node
		addNode(arr[i]);
	}

}
DLLStructure::DLLStructure(const DLLStructure &dll) {
	//deep copy of linked list
	this->first = NULL;
	this->last = NULL;

	//dll is empty
	if (dll.first) {
		Node *tmp = dll.first;
		while (tmp) {
			this->addNode(tmp->value);
			tmp = tmp->next;
		}

	}
}
DLLStructure::~DLLStructure() {
	Node *cur = this->first;
	while (cur) {
		Node *next = cur->next;
		delete cur;
		cur = next;
	}

}

void DLLStructure::printDLL() {
	Node *cur = this->first;
	while (cur != NULL) {
		cout << (cur->value);
		if (cur != last)
			cout << ',';
		cur = cur->next;
	}
	cout << endl;
}

void DLLStructure::addNode(int data) {
	Node *tmp = new Node(data, NULL, NULL);

	if (!(this->first)) {
		this->first = tmp;
		this->last = tmp;
		return;
	}

	(this->last)->next = tmp;
	tmp->prev = this->last;
	this->last = tmp;
}

void DLLStructure::InsertAfter(int val_after, int val_ins) {
	Node *cur = this->first;
	Node *tmp = new Node();
	tmp->value = val_ins;

//find the value
	while (cur) {
		if (cur->value == val_after) {
			tmp->prev = cur;
			tmp->next = cur->next;
			cur->next = tmp;

			if (cur == this->last)
				last = tmp;
			else
				(tmp->next)->prev = tmp;

			return;
		}
		cur = cur->next;
	}

//value not found; add the new node to the tail
	(this->last)->next = tmp;
	tmp->prev = this->last;
	this->last = tmp;

}

void DLLStructure::InsertBefore(int val_before, int val_ins) {
	this->InsertAfter(val_before, val_before);

	//get the position of the inserted node
	Node *cur = this->first;
	for (; cur->value != val_before; cur = cur->next)
		;

	if (cur == this->last) {
		//cur is the last
		Node *newlast = cur->prev;
		newlast->next = NULL;
		Node *newfirst = cur;
		newfirst->prev = NULL;
		newfirst->next = this->first;
		this->first->prev = newfirst;

		this->first = newfirst;
		this->last = newlast;
	}

	cur->value = val_ins;
}

void DLLStructure::Delete(int value) {
	Node *cur = this->first;
	for (; cur && cur->value != value; cur = cur->next)
		;
	if (cur) {

		if (cur == this->first) {
			(cur->next)->prev = NULL;
			this->first = cur->next;
			delete cur;

			return;
		}
		if (cur == this->last) {
			(cur->prev)->next = NULL;
			this->last = cur->prev;
			delete cur;

			return;
		}

		(cur->prev)->next = cur->next;
		(cur->next)->prev = cur->prev;
		delete cur;

	}

}

void DLLStructure::Sort() {
//current node waiting to be inserted
	Node *cur = (this->first)->next;
	while (cur) {
		//get the next node of the cur
		Node *next = cur->next;
		//case when cur is head or tail
		(cur->prev)->next = cur->next;
		if (cur != this->last)
			(cur->next)->prev = cur->prev;

		//node to be inserted after
		Node *shift = cur;
		for (; shift && shift->value >= cur->value; shift = shift->prev)
			;

		//shift = first_node s.t. value <  cur node
		if (shift) {
			//shift_value < cur_value
			(shift->next)->prev = cur;
			cur->next = shift->next;
			shift->next = cur;
		} else {
			//update the head of list
			(this->first)->prev = cur;
			cur->next = this->first;
			this->first = cur;
		}

		//insert next node
		cur->prev = shift;
		cur = next;
	}

//update tail of the list
	cur = first;
	while (cur->next) {
		cur = cur->next;
	}
	last = cur;
}

bool DLLStructure::IsEmpty() {
	return !(first);
}

int DLLStructure::getHead() {
	return (this->first)->value;
}

int DLLStructure::getTail() {
	return (this->last)->value;
}

int DLLStructure::getSize() {
	int sz = 0;
	Node *cur = first;
	while (cur) {
		sz++;
		cur = cur->next;
	}
	return sz;
}

int DLLStructure::getMax() {
	Node *cur = first;
	int max = std::numeric_limits<int>::min();
	while (cur) {
		if (cur->value > max)
			max = cur->value;
		cur = cur->next;
	}

	return max;
}

int DLLStructure::getMin() {
	Node *cur = first;
	int min = std::numeric_limits<int>::max();
	while (cur) {
		if (cur->value < min)
			min = cur->value;
		cur = cur->next;
	}

	return min;
}

int main() {
// Q 1, 2, 3 should obviously be implemented successfully
// in order to run the following code
	int array[5] = { 11, 2, 7, 22, 4 };
	DLLStructure dll(array, 5); // note that 5 is the size of the array
	dll.printDLL(); // the output should be: 11, 2, 7, 22, 4
	cout << "Number of elements in the list is: " << dll.getSize() << endl;
// Q 4
	dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
	dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4
	dll.InsertAfter(25, 7); // To insert 7 after the first occurence of 25
	dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4, 7
// Q 5
	dll.InsertBefore(7, 26); // To insert 26 before the first occurence of 7
	dll.printDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
	dll.InsertBefore(19, 12); // To insert 12 before the first occurence of 19
	dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
// Q 6
	dll.Delete(22);
	dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
// Q 7
	dll.Sort();
	dll.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
// Q 8
	if (dll.IsEmpty())
		cout << "The list is empty" << endl;
// Q 9
	cout << "Head element is: " << dll.getHead() << endl;
	cout << "Tail element is: " << dll.getTail() << endl;
// Q 10
	cout << "Number of elements in the list is: " << dll.getSize() << endl;
// Q 11
	cout << "Max element is: " << dll.getMax() << endl;
	cout << "Min element is: " << dll.getMin() << endl;

// Q 11 theory question
// print to the screen the written answer for the theory question
	cout
			<< "Set private fields int size, int min and int max. The getters just return size, min and max. Whenver the number of nodes or values of the nodes in the  list change, update size, min and max.";
	cout << endl;
// Q 12 theory question
// print to the screen the written answer for the theory question

// Q 12

	cout
			<< "The default cpoy constructor is not reliable because it's a shallow copy just by making this->first = dll.first, this->last = dll.last";
	cout << "If dll changes, this will also change." << endl;
	DLLStructure dll2(dll);
	dll2.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
	return 0;
}
