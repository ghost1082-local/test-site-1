/***********
Chris Liguz
Code Sample
3/24/08

Written as a quick sample to show that I am comfortable using certain programming practices.
Below I have coded :  
	An abstract class, with a virtual function. I used static and dynamic allocation to show use of pointers.
	2 template classes.	1) Just shows basic use of templates and an example of operator overloading.
						2) Shows a sequence template (inheriting the first). Takes an int to define size of array.
						
*Note : Normally I would separate the structures into appropriate headers and cpp's, but for simplicity I kept it in one file.
************/

#include <iostream>
using namespace std;

////////////////////////
///		Sample 1	////
///////////////////////
//Abstract base class with pure virtual function
class CShape
{
public:
    void setValues (int a, int b)
	{ width=a; height=b; }
	
    virtual int area (void) =0;
	
    void printArea (void)
	{ cout << this->area() << endl; }
	
protected:
    int width, height;
	
};

class CRectangle: public CShape				// Inherit CShape
{
public:
    int area (void)							// Define virtual function
	{ return (width * height); }
};

class CTriangle: public CShape				// Same as CRectangle
{
public:
    int area (void)
	{ return (width * height / 2); }
};

////////////////////////
///		Sample 2	////
///////////////////////
// Template 1
template <class T>
class CBunchOfStuff 
{
public:
	   CBunchOfStuff () {};							// Empty constructor
	   CBunchOfStuff (T a,T b);						// Constructor w/ 2 variables
	   CBunchOfStuff operator + (CBunchOfStuff);	// Overloading '+' operator
	   T getX (void);								// Getters
	   T getY (void);
	   
protected:
	T x,y;
};

// Template 2
template <class U,int N>							// U is the datatype, N defines how big memblock is
class CBunchOfStuff2 : public CBunchOfStuff<U>
{
public:
	CBunchOfStuff2 () {};						// Empty constructor
	CBunchOfStuff2 (U a, U b);					// Constructor w/ 2 variables
	void setMemblock (int x, U value);			// Set memblock location [x] to value
	U getMemblock (int x);						// Get memblock location [x]
	   
private:
	U memblock [N];
};

template <class T>								// Definition of constructor
CBunchOfStuff<T>::CBunchOfStuff (T a,T b)		// Takes on 2 variables of type 'T'
{
	x=a;
	y=b;
}

template <class T>
CBunchOfStuff<T> CBunchOfStuff<T>::operator+ (CBunchOfStuff parameter)	// Definition of + operator
{
	CBunchOfStuff temporary;					// Make a temp variable for storage
	temporary.x = x + parameter.x;				// x of previous var + x of parameter var goes into x of temporary var
	temporary.y = y + parameter.y;				// y of previous var + y of parameter var goes into y of temporary var
	return (temporary);
}

template <class T>
T CBunchOfStuff<T>::getX (void)					// Return x
{
	return x;
}

template <class T>
T CBunchOfStuff<T>::getY (void)					// Return y
{
	return y;
}

template <class U, int N>						// Definition of constructor
CBunchOfStuff2<U,N>::CBunchOfStuff2 (U a,U b)	// Takes on 2 variables of type 'U'
{
	x=a;
	y=b;
}

template <class U, int N>
void CBunchOfStuff2<U,N>::setMemblock (int x, U value)	// Set memblock location [x] to value of type 'U'
{
	memblock[x]=value;
}

template <class U, int N>
U CBunchOfStuff2<U,N>::getMemblock (int x)				// Return memblock location [x] in datatype 'U'
{
	return memblock[x];
}

//test harness
int main () 
{
	// Static allocation
	CRectangle rect;
	CTriangle trgl;
	CShape * pshape1 = &rect;
	CShape * pshape2 = &trgl;
	
	// Dynamic allocation
	CShape * pshape3 = new CRectangle;
	CShape * pshape4 = new CTriangle;
	
	pshape1->setValues (4,5);	// W * H
	pshape2->setValues (4,5);
	pshape3->setValues (4,5);
	pshape4->setValues (4,5);
	
	pshape1->printArea();		// 20
	pshape2->printArea();		// 10
	pshape3->printArea();		// 20
	pshape4->printArea();		// 10
	
	delete pshape3;			// Garbage collection
	delete pshape4;
	
	// First template examples
	CBunchOfStuff <int> a (3,1);	// a.x = 3 , a.y = 1
	CBunchOfStuff <int> b (1,2);	// b.x = 1 , b.y = 2
	CBunchOfStuff <int> c;			
	c = a + b;						// c.x = 1+3 , c.y = 1+2
	cout << c.getX() << "," << c.getY() << endl;	// 4,3
	
	// Second template examples
	CBunchOfStuff2 <int,1> inheritanceWorks (3,5);	// Just to show that inheriting worked
	CBunchOfStuff2 <int,5> integerNumbers;		// Datatype int, array size 5		
	CBunchOfStuff2 <double,10> floatingNumbers;	// Datatype double, array size 10

	inheritanceWorks.setMemblock (0,7);			// Set first block to 7
	integerNumbers.setMemblock (0,100);			// Set first block of int array to 100
	floatingNumbers.setMemblock (3,3.1416);		// Set third block of float array to pi

	cout << inheritanceWorks.getX() << "," << inheritanceWorks.getY() << '\n';	// 3,5
	cout << inheritanceWorks.getMemblock(0) << '\n';	// 7
	cout << integerNumbers.getMemblock(0) << '\n';	// 100
	cout << floatingNumbers.getMemblock(3) << '\n';	// 3.1416
	
	return 0;
}




