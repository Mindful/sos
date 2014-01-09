//I want to say for the record that I Googled around a little trying to get help solving this,
//and found a solution that is just astoundingly better than mine. I'm not using it because
//I was nowhere near thinking of it and I know this is supposed to be recursion review anyway, 
//but I feel like it's at least worth mentioning - and you can be sure this is what I'll use
//in real-world work from now on.

// void permutation(int k, string &s) 
// {
//     for(int j = 1; j < s.size(); ++j) 
//     {
//         swap(s, k % (j + 1), j); 
//         k = k / (j + 1);
//     }
// }

//In any case, my work is below
#include <iostream>
using namespace std;

void swap(string &str, int a, int b){
	char temp;
	temp = str[a];
	str[a]=str[b];
	str[b]=temp;
}
void calculatePermutation(string str, int end, int current = 0){
    if (current == end) {
        cout << str << endl;
        return;
    }
    else {
    for (int i = current; i <= end; i++) {
            swap(str, current, i);
            calculatePermutation(str, end, current + 1);
            swap(str, current, i);
        }
    }
}

void permute(const string &str){
	string p = str;
	calculatePermutation(p, p.size()-1);
}

void permute(const string &str, int low, int high){
	//I am taking low and high to be substring locations, because I don't know what else
	//they'd be
	string p = str.substr(low, high);
	calculatePermutation(p, p.size()-1);
}

int main(){
	permute("abcdefg", 1, 5);
	cout << "-------------------------" << endl;
	permute("abcd");
	return 0;
}