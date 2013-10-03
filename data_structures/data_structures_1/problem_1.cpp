#include <iostream>
using namespace std;


int main()
{
  cout << "Hello world! Please enter 3 integers" << endl;
  const int ARR_SIZE = 3;
  int arr[ARR_SIZE];
  for (int i = 0; i < ARR_SIZE; i++){
  	cin >> arr[i];
  }
  int min = arr[0], max= arr[0], avg = 0;
  //This makes the first iteration of the loop redundant for max and min, but we 
  //need it for the averages.
  cout << "Forward:" << endl;
  for (int i = 0; i < ARR_SIZE; i++){
  	if (arr[i] > max){
  		max = arr[i];
  	}
  	if (arr[i] < min){
  		min = arr[i];
  	}
  	cout << arr[i] << " "; 
  	avg += arr[i];
  }
  cout << endl << "Backward:" << endl;
  for (int i = ARR_SIZE -1; i >= 0; i--){
  	cout << arr[i] << " ";
  }
  avg /= ARR_SIZE;
  cout << endl << "Max:" << max << endl << "Min:" << min << endl << "Average (rounded):" << avg << endl;
  return 0;
}