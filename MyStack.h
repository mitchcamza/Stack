#ifndef H_StackType
#define H_StackType
 
#include <iostream>
#include <cassert>
#include "StackADT.h"


bool isInLanguageL(std::string w);
// tests whether a word, w is in L, where w = a^nb^n

bool isInLanguageL2(std::string w);
// tests whether a word, w is in L, where w = a^nb^n+1

bool isInLanguageL3(std::string w);
// tests whether a word, w is in L, where w = a^nb^n+1


template <class Type>
class StackType: public StackADT<Type>
{
public:
    const StackType<Type>& operator=(const StackType<Type>&); 
      //Overload the assignment operator.

    void initializeStack();
      //Function to initialize the stack to an empty state.
      //Postcondition: stackTop = 0;

    bool isEmptyStack() const;
      //Function to determine whether the stack is empty.
      //Postcondition: Returns true if the stack is empty,
      //    otherwise returns false.

    bool isFullStack() const;
      //Function to determine whether the stack is full.
      //Postcondition: Returns true if the stack is full,
      //    otherwise returns false.

    void push(const Type& newItem);
      //Function to add newItem to the stack.
      //Precondition: The stack exists and is not full.
      //Postcondition: The stack is changed and newItem is
      //    added to the top of the stack.

    Type top() const;
      //Function to return the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: If the stack is empty, the program 
      //    terminates; otherwise, the top element of the stack
      //    is returned.

    void pop();
      //Function to remove the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: The stack is changed and the top element is
      //    removed from the stack.
	
	void reverseStack(StackType<Type> &otherStack);
	// copies the elements of a stack into another stack in reverse order
	// postcondition: the contents of the destination stack are destroyed
	// and the original stack remains unchanged
	
    StackType(int stackSize = 100); 
      //Constructor
      //Create an array of the size stackSize to hold 
      //the stack elements. The default stack size is 100.
      //Postcondition: The variable list contains the base address 
      //   of the array, stackTop = 0, and maxStackSize = stackSize

    StackType(const StackType<Type>& otherStack); 
      //Copy constructor

    ~StackType(); 
      //Destructor
      //Remove all the elements from the stack.
      //Postcondition: The array (list) holding the stack 
      //    elements is deleted.

private:
    int maxStackSize; 	//variable to store the maximum stack size
    int stackTop;     	//variable to point to the top of the stack
    Type *list; 		//pointer to the array that holds the stack elements

    void copyStack(const StackType<Type>& otherStack); 
      //Function to make a copy of otherStack.
      //Postcondition: A copy of otherStack is created and assigned
      //    to this stack.
};



template <class Type>
bool sameStack (StackType<Type> s, StackType<Type> w) // synonym: identicalStack
// Tests whether two stacks contain the same elements
// Returns true if the stacks contain the same elements.
// Returns false otheriwse.
// (Exam question uses pass by value)
{
	if (s.isEmptyStack() && w.isEmptyStack())	// both stacks are empty
	{
		return true;
	}

	else if (s.isEmptyStack() || w.isEmptyStack())	// one of the stacks, but not both is empty
	{
		return false;
	}

	else if (s.top() != w.top())	// the first elements differ
	{
		return false;
	}

	else // both stacks are not empty
	{
		s.pop();
		w.pop();
		return sameStack(s, w);	// recursive function call
	}
}


template <class Type>
void StackType<Type>::reverseStack(StackType<Type> &theStack)
{
	theStack.initializeStack();
	
	while (!this->isEmptyStack())
	{
		theStack.push(this->top());
		this->pop();
	}
}


template <class Type>
const StackType<Type>& StackType<Type>::operator=(const StackType<Type>& otherStack)
{
	if (this != &otherStack)	// avoid self-copy
	{
		copyStack(otherStack);
	}
	return *this;
}


template <class Type>
void StackType<Type>::initializeStack()
{
	stackTop = 0;
}

template <class Type>
bool StackType<Type>::isEmptyStack() const
{
	return (stackTop == 0);
}

template <class Type>
bool StackType<Type>::isFullStack() const
{
	return (stackTop == maxStackSize);
}

template <class Type>
void StackType<Type>::push(const Type& newItem)
{
	if (!isFullStack())	// make sure that the stack is not full (avoid overflow)
	{
		list[stackTop] = newItem;	// store newItem at the top of the stack
		stackTop++;					// increment stackTop
	}
	
	else
	{
		std::cout << "Cannot add to a full stack." << std::endl;
	}
}

template <class Type>
Type StackType<Type>::top() const
{
	assert (stackTop != 0);
	return (list[stackTop - 1]);
}

template <class Type>
void StackType<Type>::pop()
{
	if (!isEmptyStack())	// avoid underflow
	{
		stackTop--;
	}
	
	else
	{
		std::cout << "Cannot remove from an empty stack." << std::endl;
	}
}

template <class Type>
StackType<Type>::StackType(int stackSize)
{
	if (stackSize <= 0)
	{
		std::cout << "Size of the array to hold the stack must be positive." << std::endl;
		std::cout << "Creating array of size 100." << std::endl;
		maxStackSize = 100;
	}
	
	else
	{
		maxStackSize = stackSize;
	}
	stackTop = 0;
	list = new Type[maxStackSize];
}

template <class Type>
StackType<Type>::StackType(const StackType<Type>& otherStack)
{
	list = NULL;
	copyStack(otherStack);
}

template <class Type>
void StackType<Type>::copyStack(const StackType<Type>& otherStack)
{
	delete[] list;
	maxStackSize = otherStack.maxStackSize;
	stackTop = otherStack.stackTop;
	list = new Type[maxStackSize];
	
	for (int j = 0; j < stackTop; j++)
	{
		list[j] = otherStack.list[j];
	}
}


template <class Type>
StackType<Type>::~StackType<Type>()
{
	delete[] list;
}




bool isInLanguageL(std::string w)
{
	StackType<char> s;
	int index = 0;
	while (w[index] == 'a')
	{
		s.push('x');
		index++;
	}
		
	while (w[index] == 'b')
	{
		if (!s.isEmptyStack())
		{
			if (s.top() == 'x')
			{
				s.pop();
			}
		}
		else
		{
			return false;
		}
		index++;
	}
	return (index == w.length() && s.isEmptyStack());
}


bool isInLanguageL2(std::string w)
{
	StackType<char> s;
	int index = 0;
	while (w[index] == 'a')
	{
		s.push('x');
		index++;
	}
	
	// Special case: add an extra 'b', since L = {a^n, b^n+1}
	if (w[index] == 'b')
	{
		s.push('x');
	}
	
	while (w[index] == 'b')
	{
		if (!s.isEmptyStack())
		{
			if (s.top() == 'x')
			{
				s.pop();
			}
		}
		else
		{
			return false;
		}
		index++;
	}
	return (index == w.length() && s.isEmptyStack());
}


bool isInLanguageL3(std::string w)
{
	StackType<char> s;
	int index = 0;
	while (w[index] == 'a')
	{
		s.push('x');
		index++;
	}
	
	// Special case: remove an extra 'b', since L = {a^n, b^n-1}
	if (w[index] == 'b')
	{
		s.pop();
	}
	
	while (w[index] == 'b')
	{
		if (!s.isEmptyStack())
		{
			if (s.top() == 'x')
			{
				s.pop();
			}
		}
		else
		{
			return false;
		}
		index++;
	}
	return (index == w.length() && s.isEmptyStack());
}


// Alternative L2: passes test cases
//bool isInLanguageL2(std::string w)
//// accepts words with {a^n, b^n+1}, n>= 1
//// this will require two stacks
//{
//	StackType<int> stackA;
//	StackType<int> stackB;
//	unsigned int index = 0;
//	unsigned int aCount = 0;
//	unsigned int bCount = 0;
//
//	while (w[index] == 'a')
//	{
//		stackA.push(index);
//		index++;
//		aCount++;
//	}
//
//	while (w[index] == 'b')
//	{
//		stackB.push(index);
//		index++;
//		bCount++;
//	}
//
//	while (!stackA.isEmptyStack() && !stackB.isEmptyStack())
//	{
//		stackA.pop();
//		stackB.pop();
//	}
//
//	if (stackA.isEmptyStack() && !stackB.isEmptyStack())
//	{
//		return bCount - aCount == 1;
//	}
//
//	else
//	{
//		return false;
//	}
//}

#endif

