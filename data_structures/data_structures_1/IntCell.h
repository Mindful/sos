#ifndef IntCell_H
#define IntCell_H

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


  private:
    int storedValue;
};

#endif