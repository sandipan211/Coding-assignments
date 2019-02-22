// CPP program to set the leftmost unset bit
#include <iostream>
using namespace std;

// set left most unset bit
int setleftmostunsetbit(int n)
{
	// if number contain all
	// 1 then return n
	if ((n & (n + 1)) == 0)
		return n;

	// Find position of leftmost unset bit.
	int pos = 0;
	for (int temp=n, count=0; temp>0;
						temp>>=1, count++)

		// if temp L.S.B is zero
		// then unset bit pos is
		// change
		if ((temp & 1) == 0) 
			pos = count; 
	cout<<"pos = \n"<<pos;
	// return OR of number and
	// unset bit pos
	return (n | (1 << (pos)));
}

// Driver Function
int main()
{
	int n = 172;
	cout << setleftmostunsetbit(n);
	return 0;
}