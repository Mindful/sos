using namespace std;

class Employee
{
  public:
    const string & getName( ) const
      { return name; }

    bool operator==( const Employee & rhs ) const
      { return getName( ) == rhs.getName( ); }
    bool operator!=( const Employee & rhs ) const
      { return !( *this == rhs); }

     Employee(string n, int s, int age) : name(n), salary(s), seniority(age){}

  private:
    string name;
    double salary;
    int    seniority;

      // Additional private members not shown
};
