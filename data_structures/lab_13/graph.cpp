//unordered_map is a c++11 thing, so compilation may have to look like
//g++ graph.cpp -std=c++11

//There's some redundant or less-elegant-than-possible design here because I spent a little time
//confused about which parts of the algorithm referred to adjacent nodes and which referred only
//to nodes that were going "in" to other nodes. Also, there's a lot of extra code jsut to handle
//reading input and such. The input handling isn't super robust but it works with this file

//just run ./a.out test1.txt

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
	int indegree;

public:

	vertex(string n):name(n), indegree(0){}

	vector<vertex*>& getAdjacent(){return adjacent;}

	void addAdjacent(vertex* v){
		adjacent.push_back(v);
	}

	string getName(){return name;}

	string info(){
		string s = name+" input from: [";
		for(int i = 0; i < adjacent.size(); ++i){
			if(adjacent[i]!=NULL){
				s+=adjacent[i]->getName()+",";
			}
		}
		s[s.length()-1]=']';
		return s;
	}

	int getIndegree(){return indegree;}

	void reduce_indegree(){--indegree;}
	void increase_indegree(){++indegree;}
};


void topsort(vector<vertex*> vv){
	queue<vertex*> vq;
	int counter = 0;
	vertex* arr[vv.size()];

	for(int i = 0; i < vv.size(); ++i){
		cout << vv[i]->getName() << " indgree: " << vv[i]->getIndegree() << endl;
		if(vv[i]->getIndegree()==0){
			cout << "push " << vv[i]->getName() << endl;
			vq.push(vv[i]);
		}
	}

	while(!vq.empty()){
		vertex* v = vq.front();
		vq.pop();
		//our equivalent of v.topNum = ++counter
		arr[counter++]=v;

		for (int i = 0; i < v->getAdjacent().size(); ++i){
			vertex* current = v->getAdjacent()[i];
			current->reduce_indegree();
			cout << "reduce indegree on " << current->getName() << endl;
			if(current->getIndegree()==0){
				vq.push(current);
				cout << "push " << vv[i]->getName() << endl;
			}
		}
		
	}

	if (counter!=vv.size()){
		cout << "Counter (" << counter << ") did not equal vertex count(" << vv.size() <<
			"); the graph contains cycles." << endl;
	}

	for (int i = 0; i < vv.size(); ++i){
		cout << arr[i]->getName() << endl;
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
   		m[v1]->increase_indegree();
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