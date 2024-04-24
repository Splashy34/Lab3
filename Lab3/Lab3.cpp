#include <iostream>
using namespace std;

class List

{
public:
	List();
	~List();
	void add(int data);
	void insert(int index, int data);
	void removeAt(int index);
	int elementAt(int index);
	int count() const;
	void insertBeforeNegative();
	void removeNegative();
	int count(int data) const;
	void clear();
private:
	class Node
	{
	public:
		Node* next;
		int data;
		Node(int data) : data(data), next(nullptr) {}
	};
	Node* tail;
	int size;
	Node* cachedNode;
	int cachedIndex;
	Node* getNode(int index)
	{
		Node* current;
		int start;

		if (index == 0)
		{
			return tail->next;
		}
		if (cachedIndex >= 0 && index > cachedIndex)
		{
			current = cachedNode->next;
			start = cachedIndex + 1;
		}
		else
		{
			current = tail->next;
			start = 0;
		}
		for (int i = start; i < index; ++i)
		{
			current = current->next;
		}
		return current;
	}
};

List::List()
{
	tail = nullptr;
	size = 0;
	cachedNode = nullptr;
	cachedIndex = -1;
}

List::~List()
{
	clear();
}

void List::add(int data)
{
	Node* newnode = new Node(data);
	if (tail == nullptr)
	{
		tail = newnode;
		newnode->next = newnode;
	}
	else
	{
	newnode->next = tail->next;
	tail->next = newnode;
	tail = newnode;
	}
	size++;
	cachedNode = tail;
	cachedIndex = -1;
}

void List::insert(int index, int data)
{
	Node* newnode = new Node(data);
	index = index % (size + 1);
	if (size == 0)
	{
		tail = newnode;
		newnode->next = newnode;
	}
	else
	{
		Node* prev;
		if (index == 0)
		{
			prev = tail;
		}
		else
		{
			prev = getNode(index - 1);
		}
		newnode->next = prev->next;
		prev->next = newnode;
		if (index == size)
		{
			tail = newnode;
		}
	}
	size++;
	cachedNode = newnode;
	cachedIndex = index;
}


void List::removeAt(int index) 
{
	if (size == 0) return;
	index = index % size;
	if (size == 1) 
	{
		delete tail;
		tail = nullptr;
		size = 0;
		cachedNode = nullptr;
		cachedIndex = -1;
		return;
	}
	Node* prev;
	Node* todel;
	if (index == 0)
	{
		prev = tail;
		todel = tail->next;
		tail->next = todel->next;
		if (tail == todel) tail = nullptr;
	}
	else
	{
		prev = getNode(index - 1);
		todel = prev->next;
		prev->next = todel->next;
	}
	if (todel == tail)
	{
		tail = prev;
	}
	if (cachedNode == todel)
	{
		cachedNode = nullptr;
		cachedIndex = -1;
	}
	else if (cachedIndex > index)
	{
		cachedIndex--;
	}
	delete todel;
	size--;
}

int List::elementAt(int index)
{
	if (size == 0)
	{
		return -1;
	}
	Node* node = getNode(index);
	return node->data;
}

int List::count() const
{
	return size;
}

void List:: insertBeforeNegative() 
{
	if (size == 0) return;

	Node* current = tail->next;
	Node* prev = tail;
	int currentIndex = 0;

	do 
	{
		if (current->data < 0) 
		{
			Node* newnode = new Node(1);
			if (current == tail->next)
			{
				newnode->next = tail->next;
				tail->next = newnode;
			}
			else
			{
				newnode->next = current;
				prev->next = newnode;
			}
			size++;
			if (currentIndex < cachedIndex) 
			{
				cachedIndex++;
			}
			else if (currentIndex == cachedIndex) 
			{
				cachedNode = newnode;
			}
		}
		prev = current;
		current = current->next;
		currentIndex++;
	} while (current != tail->next);
}


void List:: removeNegative() 
{
	if (size == 0 || tail == nullptr) return;
	Node* current = tail->next;
	Node* prev = tail;
	bool isTailNegative = tail->data < 0;
	int currentIndex = 0;
	while (current != tail)
	{
		if (current->data < 0)
		{
			if (current == cachedNode) 
			{
				cachedNode = prev;
				cachedIndex = currentIndex - 1;
			}
			else if (currentIndex < cachedIndex) 
			{
				cachedIndex--;
			}
			prev->next = current->next;
			delete current;
			current = prev->next;
			size--;
		}
		else 
		{
			prev = current;
			current = current->next;
		}
		currentIndex++;
	}
	if (isTailNegative && size > 0) 
	{
		if (tail == cachedNode)
		{
			cachedNode = prev;
			cachedIndex = size - 2;
		}
		prev->next = tail->next;
		delete tail;
		tail = prev;
		size--;
	}
	if (size == 0)
	{
		tail = nullptr;
		cachedNode = nullptr;
		cachedIndex = -1;
	}
}

int List::count(int data) const
{
	if (size == 0) return 0;
	int count = 0;
	Node* current = tail->next;
	do {
		if (current->data == data)
		{
			count++;
		}
		current = current->next;
	} while (current != tail->next);
	return count;
}

void List::clear()
{
	if (size == 0) return;
	Node* current = tail->next;
	while (size > 0)
	{
		Node* todel = current;
		current = current->next;
		delete todel;
		size--;
	}
	tail = nullptr;
	cachedNode = nullptr;
	cachedIndex = -1;
}

int main()
{
	List lst;
	int choise;
	int value = -1;
	int index;
	cout << "Enter values in the list (0 to stop): " << endl;
	while (true)
	{
		cin >> value;
		if (value == 0) break;
		lst.add(value);
	}
	do {
		cout << "1. Add an element\n";
		cout << "2. Insert an element\n";
		cout << "3. Remove at\n";
		cout << "4. Element at\n";
		cout << "5. Count number of elements\n";
		cout << "6. Insert 1 before negative elements\n";
		cout << "7. Remove negative elements\n";
		cout << "8. Count number of entries\n";
		cout << "9. Clear the list\n";
		cout << "0. Exit\n";
		cin >> choise;
		switch (choise)
		{
		case 1:
			cout << "Enter the element you want to add: " << endl;
			cin >> value;
			lst.add(value);
			cout << "The element is added." << endl;
			break;
		case 2:
			cout << "Enter the index and value to insert: " << endl;
			cin >> index >> value;
			lst.insert(index, value);
			cout << "The element is inserted." << endl;
			break;
		case 3:
			cout << "Enter the index of an element to remove: " << endl;
			cin >> index;
			lst.removeAt(index);
			cout << "The element is removed. " << endl;
			break;
		case 4:
			cout << "Enter the index of an element you want to get: " << endl;
			cin >> index;
			cout << "Element at " << index << ": " << lst.elementAt(index) << endl;
			break;
		case 5:
			cout << "Number of elements: " << lst.count() << endl;
			break;
		case 6:
			lst.insertBeforeNegative();
			cout << "Inserted 1 before all negative elements. " << endl;
			break;
		case 7:
			lst.removeNegative();
			cout << "All negative elements are removed. " << endl;
			break;
		case 8:
			cout << "Enter the element you want to count" << endl;
			cin >> value;
			cout << "Amount of entered element: " << lst.count(value) << endl;
			break;
		case 9:
			lst.clear();
			cout << "The list is cleared. " << endl;
			break;
		case 0:
			break;
		default:
			cout << "An unknown command. Try again. " << endl;
			break;
		}

	} while (choise != 0);
	return 0;
}