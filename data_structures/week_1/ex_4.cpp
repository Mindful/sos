#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


//Note that the way I wrote this, the resultant files do not include their 
//#include statements


void scan(string filename, stringstream &final){
	ifstream file;
	string buffer;
	file.open(filename.c_str());
	if (file.is_open()){
		while (getline(file, buffer))
		{
			if(buffer.substr(0,8)=="#include"){
				buffer = buffer.substr(9); //This is the file to include
				//Can't include the current file, or that would be bad
				//mind you two files could still include each other like this...
				if (buffer != filename){ 
					scan(buffer, final);
				}
			} 
			else{
				final << buffer << endl;
			}
		}
	}
}

void lines(){
	cout << "--------------------" << endl;
}

int main(int argc, char* argv[]){
	if (argc > 2){
		cout << "Warning: more than 1 argument detected.";
		cout << " Arguments other than the first will be ignored" << endl;
	} else if (argc == 1){
		return 0;
	}
	ifstream basefile;
	basefile.open(argv[1]);
	string buffer;
	stringstream final;
	cout << "Base file:" <<endl;
	lines();
	if (basefile.is_open()){
	    while (getline(basefile,buffer))
	    {
	      cout << buffer << endl;
	    }
	    basefile.close();
	}
	lines();
	scan(argv[1], final);
	cout << endl << "File after includes:" << endl;
	lines();
	cout << final.str() << endl;
	lines();

}
