
//Given what we know about the array, this can be done with a binary search where the value we look for
//is the value of the index
#include <iostream>
using namespace std;

//returns -1 if not found
int search(int A[], int imin, int imax)
{
  while (imax >= imin)
    {
      int imid = imin+((imax-imin)/2);

      if (A[imid] < imid)
        imin = imid + 1;
      else if (A[imid] > imid)
        imax = imid - 1;
      else
        return imid;
    }
  return -1;
}

int main(){
  int test[10] = {-2, -1, 0, 3, 5};
  int result = search(test, 0, 4);
  cout << result << endl;
  return 0;
}