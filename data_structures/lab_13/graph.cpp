//unordered_map is a c++11 thing, so compilation may have to look like
//g++ graph.cpp -std=c++11

//I would note that given that I'm storing things as an adjacency list, the easier
//way to do this would just be to sort these as a list of integers based on the size
//of their adjacent vectors, which would be outrageously trivial

#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class vertex{
	string name;
	vector<vertex*> adjacent;

public:

	vertex(string n):name(n){}

	void setAdjacent(vertex* v[], int size){
		adjacent.clear();
		adjacent.resize(size);
		for (int i = 0; i < size; ++i){
			adjacent[i]=v[i];
		}
	}

	void addAdjacent(vertex* v){
		adjacent.push_back(v);
	}

	string getName(){return name;}

	string info(){
		string s = name+" adjacent to: [";
		for(int i = 0; i < adjacent.size(); ++i){
			if(adjacent[i]!=NULL){
				s+=adjacent[i]->getName()+",";
			}
		}
		s[s.length()-1]=']';
		return s;
	}

	int indegree(){return adjacent.size();}

	void reduce_indegree(){adjacent.pop_back();}
};


void topsort(vector<vertex*> vv){
	queue<vertex*> vq;
	int counter = 0;
	vertex* arr[vv.size()];

	for(int i = 0; i < vv.size(); ++i){
		if(vv[i]->indegree()==0){
			vq.push(vq);
		}
	}

	while(!vq.empty()!){
		vertex* v = vq.front();
		vq.pop();
		//our equivalent of v.topNum = ++counter
		arr[counter++]=v;
		
	}

}

int main(int argc, char* argv[]) { 
   if(argc<2){
   	 cout << "Cannot run the program without a filename argument." << endl;
   	 return 1;
   }
   string filename = argv[1];
   ifstream myfile(filename);
   string line;
   unordered_map<string, vertex*> m;
   //We read the file twice. Of course the same operations could be done reading
   //the file once and it would be slightly more efficient, but it would be
   //substantially more work for very little gain.
   if (myfile.is_open()){
    //Find all the vertices
   	while(getline(myfile, line)){
   		string v1 = line.substr(line.find(" ")+1);
   		string v2 = line.substr(0, line.find(" "));

   		if(m.count(v1)==0){
   			cout << "Found vertex " << v1 << "." << endl;
   			m[v1]=new vertex(v1);
   		}

   		if(m.count(v2)==0){
   			cout << "Found vertex " << v2 << "." << endl;
   			m[v2]=new vertex(v2);
   		}
   	}
   	myfile.clear();
   	myfile.seekg(0);
   	//Now build a proper adjacency list using the vertices
   	while(getline(myfile, line)){
   		string v1 = line.substr(line.find(" ")+1);
   		string v2 = line.substr(0, line.find(" "));
   		//All the vertices should be in the map already
   		m[v1]->addAdjacent(m[v2]);
   		m[v2]->addAdjacent(m[v1]);
   	}

   	vector<vertex*> l;
   	for ( auto it = m.begin(); it != m.end(); ++it ){
   		cout << it->second->info() << endl;
   		l.push_back(it->second);
   	}

   	topsort(l);


   } else {
   	cout << "Could not open the file: " << filename << "." << endl;
   }
   return 0; 
}