#include <functional>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
class Employee
{
  public:
    void setValue( const string & n, double s )
      { name = n; salary = s; }

    const string & getName( ) const
      { return name; }
    void print( ostream & out ) const
      { out << name << " (" << salary << ")"; }
    bool operator< ( const Employee & rhs ) const
      { return salary < rhs.salary; }

    // Other general accessors and mutators, not shown
  private:
    string name;
    double salary;
};

  // Define an output operator for Employee
ostream & operator<< ( ostream & out, const Employee & rhs )
{
    rhs.print( out );
    return out;
}

//code{text}
// Generic findMax, with a function object, C++ style.
// Precondition: a.size( ) > 0.
template <typename Object, typename Comparator>
const Object & findMax( const vector<Object> & arr, Comparator isLessThan )
{
    int maxIndex = 0;

    for( int i = 1; i < arr.size( ); i++ )
        if( isLessThan( arr[ maxIndex ], arr[ i ] ) )
            maxIndex = i;

    return arr[ maxIndex ];
}

// Generic findMax, using default ordering.
template <typename Object>
const Object & findMax( const vector<Object> & arr )
{
    return findMax( arr, less<Object>( ) );
}


class EmployeeCompare
{
  public:
    bool operator( )( const Employee & lhs, const Employee & rhs ) const
      { return strcasecmp( lhs.getName().c_str( ), rhs.getName().c_str( ) ) < 0; }
};

int main( )
{
    vector<Employee> v( 4 );

     v[0].setValue( "George Bush", 400000.00 );
     v[1].setValue( "Bill Gates", 2000000000.00 );
     v[2].setValue( "Dr. Phil", 13000000.00 );
     v[2].setValue( "zena, warrior princess", 30000000.00 );
     cout << "Naive findMax: " << findMax( v ) << endl;
     cout << "Case insensitive findMax: " << findMax(v, EmployeeCompare()) << endl;


    return 0;
}