### Operator Overloading and `const` keyword
#### Using `const`
Consider the declaration of the following `Map<K,V>` class member function: 
```
template <class K, class V>
V const & Map<K,V>::get(const K& key) const
{ ... }
```
Explain what each of the 3 `const` keywords (ordered from left to right) will cause the compiler to check/enforce: 

**Returned value/reference is constant; function cannot modify parameter; function cannot modify properties of enclosing class**

#### Operator Overloading
Consider the following function signature. Explain the rationale behind the choice of return value. 
`ostream& operator<< (ostream& o, const LinkedList &ll);`
**Solution:** it should return a reference to the original ostream to handle operation chaining. 

### Rule of 3
#### Conceptual
Suppose that you have a class which requires a deep copy. Which functions must you define? (Mark all that apply.)

[ ] Copy constructor
[ ] Destructor
[ ] Assignment operator

**They should all be checked**

#### Implementing Deep Copy Constructors
Consider the following code: 
```
class IntArray {
	public: 
		IntArray(const IntArray& other); 
		// other class functions are here, which you don't need to worry about
	private: 
		int* myarray; // data
		int used; // number of elements in the array
		int alloc; // number of allocated indices. Unused indices have garbage values
}; 
class ArrayOfArrays {
	public: 
		ArrayOfArrays(const ArrayOfArrays& other); 
		// other class functions are here, which you don't need to worry about
	private: 
		IntArray** myarray; // an array of IntArray pointers
		int used; // number of arrays in myarray
		int alloc; // number of allocated indices. Unused indices have garbage values
}; 
```
Implement deep copy constructors for both `IntArray` and `ArrayOfArrays`. 

**Solution**
```
IntArray::IntArray(const IntArray& other)
: used(other.used), alloc(other.alloc) {
	myarray = new int[alloc]; 
	for (int i = 0; i < used; i++)
		myarray[i] = other.myarray[i]; 
}
ArrayOfArrays::ArrayOfArrays(const ArrayOfArrays& other)
: used(other.used), alloc(other.alloc) {
	myarray = new IntArray[alloc];
	for (int i = 0; i < used; i++) 
		myarray[i] = new IntArray(other.myarray[i]); 
}
```

### ADTs
For each of these descriptions, indicate what ADT is appropriate to store the following information and show what types would be used for the template arguments (e.g. `map<string, int>` or `list<double>`). If you think that there are multiple equally good options, feel free to justify the choice you make. 

- Data structure allowing you to find a book's title from its ISBN number (13 characters, mostly digits, but could contain the letter 'X'). **`map<string, string>` where the key is the ISBN and the value is the title**

- Data structure storing the type of obstacle at each square of a 40 x 40 level of an arcade game. **`list<list<string> >` where the outer list represents rows and the inner list represents columns**

- Waitlist of students who want to enroll in CS104, but couldn't get in yet. **`queue<int>` where students are represented by their ID number**

- Data structure to store the content of each line of code in a possibly long C++ program. **`list<string>` where the index corresponds to a line number in the code**

- A data structure that allows you to input an academic semester and find all students who earned an A in CS104 that semester. **`map<string, vector<int> >` where string is the term and int is a USC ID**

### STL
#### Example of Using STL Stack
Imagine that you are writing a simple game for young children to learn to recognize and match shapes. For our purposes, shapes are restricted to squares and circles. Shapes arrive over time and fall on a stack of items.

At each point, the child may press one of two buttons, 'L' and 'R'. 'L' should be the button to press if there is a square on top, and 'R' if there is a circle on top. More precisely, the rules are as follows: 

- If the child presses the correct button ('L' when the top shape is a square, 'R' when it is a circle), the child gets a point, and the top shape disappears. 
- If the child presses the wrong button ('L' when the top shape is a circle, 'R' when it is a square), the chold loses a point (the points could become negative), and no shape disappears. 
- If the child presses a button when the stack is empty, nothing happens. 
- The game starts at 0 points. 
- Items appear at a regular pace, and their appearance has nothing to do with what buttons are pressed. 
- The game may end even when there are still items left. 

You will be given a sequence consisting of the letters 'L', 'R', 'S', 'C' (representing the pressing of the two buttons, and the arrival of the two shapes, respectively), and are to determine from it the final score of the child. We promise that the sequence will only contain only those four letters, and nothing else. 

As an example, for the sequence "SCLLR", the final score will be -1, and there will be a square left in the end. The two presses of the 'L' button are wrong, so each incurs a penalty of 1 point and changes nothing. The press of 'R' is correct, so it earns a point and makes the circle disappear, but the square remains. 

Hint: the use of a stack is strongly recommended. So much that we already enter `#include<stack>` for you. That gives you a templated `stack<T>` class, which provides the functions `void push(T), void pop(), T top()`, and `bool isEmpty()`. You can use this without defining your own stack. 

Insert your code in the following: 

```
#include <stack>
#include <iostream>
using namespace std; 

int main() {
	string s; // the sequence of characters describing the game's events
	int score = 0; 
	cin >> s; 

	// your code goes here
	cout << "The score is " << score << endl; 
	return 0; 
}
```

**Solution**
``` 
int main() {
	string s; 
	int score = 0; 
	cin >> s; 

	stack<char> inputs; 

	for (int i = 0; i < s.size(); i++) {
		char c = s[i]; 

		if (c == 'R') {
			if (!inputs.empty()) {
				if (inputs.top() == 'C') {
					inputs.pop(); 
					score++; 
				} else {
					score--; 
				}
			} else {
				score--; 
			}
		} else if (c == 'L') {
			if (!inputs.empty()) {
				if (inputs.top() == 'C') {
					inputs.pop(); 
					score++; 
				} else {
					score--; 
				}
			} else {
				score--; 
			}
		} else {
			inputs.push(c); 
		}
	}

	cout << "The score is " << score << endl; 
	return 0; 
}
```

### Recursion
#### Printing a Singly Linked List
In this problem, we will work on a singly linked list of integers. The items are of the following type: 
```
struct IntItem { 
	int value; 
	IntItem* next; 
	IntItem (int v, IntItem* n) { value = v, next = n; }
}; 
```
Write a *recursive* function `printLL` to print all items in the linked list in the order in which they appear in the list, on one line. For full credit, you should print an endline after the last number, but you will get most of the credit if you do not print it. Your function *must* be recursive, and it must fit the following definition: `void printLL (IntItem* head)`

**Solution**
```
void PrintLL(IntItem* head) {
	if (head == NULL) {
		cout << endl; 
		return; 
	}
	cout << head->value << " "; 
	return printLL(head->next); 
}
```

#### Reversing a Singly Linked List
You are given the head pointer to a linked list. Implement a function that returns a Linked List in the reverse order (e.g. 1->3->5 becomes 5->3->1). You should not declare new items but instead modifying pointers of existing elements.

```
struct Node {
	int val; 
	Node* next; 

	Node(int v) : val(v), next(NULL) {}
	Node() : val(0), next(NULL) {}
}; 

Node* reverse (Node* head) {
	// TODO 
}

// Example usage
int main() {
	Node* head = new Node(1); 
	head->next = new Node(3); 
	head->next->next = new Node(5); 

	Node* new_head = reverse(head); 

	// should get 5->3->1
}
```

**Solution**
```
Node* reverse(Node* head) {
	if (head == NULL || head->next == NULL)
		return head; 
	
	/* reverse the rest of the list and put the first element at the end */
	Node* rest = reverse (head->next); 
	head->next->next = head; 

	head->next = NULL; 

	return rest;
}
```

### Design Problems, Exceptions, Templates, and Inheritance
#### Implementing LimitedList, using Exceptions
A `LimitedList` is a modified version of a `List` that has a capacity it should not exceed. Given the below header file, complete the implementation for `LimitedList::insert (int i, const T & item)`. Some of it has already been completed for you. Just for fun, let's make a custom exception class that will print out an interesting error message when you try to insert into a full list. You will need to write and use a custom exception, `CapacityException(int capacity)`.
```
#include <stdexcept>
class CapacityException : public std::exception 
{
public:
  CapacityException(int capacity) 
  : msg(/* What would be a meaningful message? */)
  {
  }
  virtual const char* what() const noexcept
  {
    return msg.c_str();
  }
private:
  std::string msg;
};

class LimitedList {
  public: 
    LimitedList(int capacity); 
    /* creates a list fixed to this capacity. It can still grow and shrink with insert/remove, but if an insert would make the size exceed the capacity, it will throw an exception. */

    void set (int i, const string& item); // Exactly the same as standard set
    const string& get (int i) const; // Exactly the same as standard get
    void remove (int i); // Exactly the same as standard remove

    void insert (int i, const string& item) {
      /* almost the same as standard insert, except that if the list is full, it will throw an exception rather than resizing. In the case of the exception being thrown, it will not alter the list. */
      if ( /* TODO - condition to check if exception should be thrown */ ) {
        /* TODO - throw custom CapacityException */



      }

      standardInsertHelper (int i, const string& item); 
    }
  
  protected: 
    int find (const string& item) const; 
    /* returns the first location at which item is stored in the list. Returns -1 if the item isn't in the list */

  private: 
    void standardInsertHepler (int i, const string& item); // Exactly the same as standard insert
    int capacity; 
    int size; 
}; 
```
**Solution**
```
#include <stdexcept>
class CapacityException : public std::exception 
{
public:
  CapacityException(int capacity) 
  : msg("Inserting would exceed capacity of " + std::to_string(capacity))
  }
  virtual const char* what() const noexcept
  {
    return msg.c_str();
  }
private:
  std::string msg;
};
```
`If` statement in `LimitedList::insert()`: 
```
if (size >= capacity) {
	throw CapacityException(capacity); 
}
```

#### Templating LimitedList
Given the above header file for `LimitedList`, modify it to make `LimitedList` a templated class such that the elements in the list are of type `T`. You do not need to modify the implementations of any functions; just rewrite their function signatures if needed. 

**Solution**
```
template <class T>
class LimitedList {
	public:
		LimitedList(int capacity); 
		void set (int i, const T& item); 
		const T& get (int i) const; 
		void remove (int i); 
		void insert (int i, const T& item); 
	protected:
		int find (const T& item) const; 
	private: 
		void standardInsertHelper (int i, const T& item); 
		int capacity; 
		int size; 
}; 
```

#### Implementing a Forgetful Brain
In this problem, you will be implementing a data structure for a "forgetful brain". The waya forgetful brain works is as follows: it has a fixed and limited capacity for facts (which for our purposes are just strings). Initially, your brain is empty. As you learn more facts, they are added to the brain. When the brain is full, any newly added fact displaces one that was previously there, meaning that you forget the previous fact. Which fact gets displaced? The one that was used least recently. There are two ways in which your brain can use a fact: (1) Learning a new fact is using it; that is, you remember the things you learned recently. (2) You can deliberately recall a fact. 

As an example, suppose that your brain has a capacity of 3 facts, and you learn A, B, C in order. Then, you recall A, and then you learn D. At this point, B is the least recently used fact, so you forget B in order to learn D. When you learn E, you next forget C, and if you learn F, you forget A. If instead, you recalled A again before learning F, then you would next forget D. The `Brain` class thus looks as follows:

```
class Brain {
	public: 
		Brain (int capacity); 
			// Create a new Brain with the given fixed capacity
		void remember (const string& fact); 
			/* access the fact, i.e., mark it as freshly remembered. 
			   We will never ask you to remember a fact that you haven't learned */
		void learn (const string& fact);
			/* add the given fact to the brain, and mark it as freshly remembered.
			   If the brain is full, throw out the least recently used fact
			   to make room for the newly added fact. */
}; 
```

In order to implement `Brain`, you should use your *templated* `LimitedList<T>` class. 

How should you use `LimitedList` to build `Brain`? Inheritance (if so, what type), composition, or other? Why?

**`Brain : protected LimitedList<std::string>` because facts are strings and the implementation of LimitedList should be hidden**

Give an implementation of the `Brain` class by adding your code in the following piece of code. 

```
class Brain
// relevant code here if you want
{
	public: 
		Brain (int capacity)
		{





		}
		
		void remember (const string & fact) {





		}

		void learn (const string & fact) {






		}
	
	private: // any data or methods you would like to add



}; 
```

**Solution**
```
class Brain : protected LimitedList<std::string>
{
	public: 
		Brain (int capacity) : LimitedList<std::string>(capacity) {}
		
		void remember (const string & fact) {
		        int loc = find(fact);
			if (loc == -1) return;
			this->remove(loc); 
			this->insert(0, fact); 
		}

		void learn (const string & fact) {
			try {
				this->insert(0, fact); 
			} catch (CapacityException ce) {
				this->remove(this->size() - 1); 
				this->insert(0, fact); 
			}
		}
	
	private: // any data or methods you would like to add
}; 
``` 

### Static vs. Dynamic Binding
Identify and explain any errors you see in the following code.

```
#include <iostream> 
class BaseClass {
	public: 
		virtual ~BaseClass() {}; 
}; 
class SubClass : public BaseClass {}; 
int main() {
	SubClass* s = new BaseClass; 
	delete s; 
	return 0; 
}
```

**Solution:** The base class should not be the runtime type here if the sub class destructor is to be called. 
