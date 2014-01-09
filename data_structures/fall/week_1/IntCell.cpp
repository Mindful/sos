#include "IntCell.h"
using namespace std;

/**
 * Construct the IntCell with initialValue
 */
IntCell::IntCell( int initialValue ) : storedValue( initialValue )
{
}

/**
 * Return the stored value.
 */
int IntCell::read( ) const
{
    return storedValue;
}

/**
 * Store x.
 */
void IntCell::write( int x )
{
    storedValue = x;
}

IntCell IntCell::operator+(const IntCell& i){
	return IntCell(this->read() + i.read() );

}

IntCell* IntCell::operator+=(const IntCell& i){
	this->write(this->read() + i.read());
	return this;
}


//Make sure the order is correct here when we're talking about subtraction
IntCell IntCell::operator-(const IntCell& i){
	return IntCell(this->read() - i.read() );

}

IntCell* IntCell::operator-=(const IntCell& i){
	this->write(this->read() - i.read());
	return this;
}

std::ostream& operator<< (std::ostream& stream, const IntCell& i){
	stream << i.storedValue;
}

void testCell()
{
	IntCell a(3);
	IntCell b(2);
	IntCell c = a + b;
	//c is a new IntCell with the value of a+b
	cout << a.read() << " + " << b.read() << " = " << c.read() << endl;
	cout << c.read() << " + " << a.read() << " = ";
	c += a;
	//now c's value has been updated to be that of c+a
	cout << c.read() << endl;

	IntCell d = a - b;
	//d is a new IntCell with the value of a - b;
	cout << a.read() << " - " << b.read() << " = " << d.read() << endl;
	cout << c.read() << " - " << a.read() << " = ";
	c -= a;
	//now c's value has been updated to be that of c-a
	cout << c.read() << endl;
} 