#include <iostream>
using namespace std;
template <typename Comparable>
class Pointer
{
  public:
    Pointer( Comparable *rhs = NULL ) : pointee( rhs ) { }

    bool operator<( const Pointer & rhs ) const
      { return *pointee < *rhs.pointee; }

    operator Comparable * ( ) const
    { 
        return pointee;
    }

    Comparable& operator*(){
        if (pointee==NULL){
            cout << "Attempt to dereference null pointer!." << endl;
        } 
        else {
            return *pointee; 
        }
    }
  private:
    Comparable *pointee;
};

int main(){
    return 0;
}