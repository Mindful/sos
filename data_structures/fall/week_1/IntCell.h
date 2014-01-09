#ifndef IntCell_H
#define IntCell_H
#include <iostream>

/**
 * A class for simulating an integer memory cell.
 */
class IntCell
{
  public:
    explicit IntCell( int initialValue = 0 );
    int read( ) const;
    void write( int x );
    IntCell operator+(const IntCell&);
    IntCell* operator+=(const IntCell&);
    IntCell operator-(const IntCell&);
    IntCell* operator-=(const IntCell&);
    friend std::ostream& operator<< (std::ostream&, const IntCell&);


  private:
    int storedValue;
};

#endif