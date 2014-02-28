#include <iostream>
#include <vector>
#include <utility>
using namespace std;

//I know the lab said "complete the trie" implemention and I am certainly basing mine off of theirs,
//but there wasn't an actual .h or .cpp file available and I'm finding I'm increasingly averse to 
//tweaking other people's code anyway, so basically just wrote this

class trie{
private:

	struct trieNode{
		char character;
		vector<trieNode*> children;

		trieNode(char c) : character(c){};
	};


	//This might be a weird way to conceptualize the "root" node, but there isn't actually a real
	//root node at all - just a bunch of first children.
	vector<trieNode*> root;

	//this is running infinitely if it finds any matches
	pair<int, trieNode*> trieMatchInternal(string s){
		char curChar = s[0];
		trieNode* curNode = NULL;
		int matches = 0;
		for(int i = 0; i < root.size(); ++i){
			if(root[i]->character==curChar){
				curNode = root[i];
				curChar = s[++matches]; //Increment matches and take the NEXT character
			}
		}

		if (!matches){
			pair<int, trieNode*> p(0, NULL);
			return p;
		}

		//We have a first node, we can start a traversal
		bool next = false;
		for(; matches <= s.length();){
			cout << "curNode: " << curNode->character << " matches: " << matches << endl;
			for(int i = 0; i < curNode->children.size(); ++i){
				if(curNode->children[i]->character==curChar){
					curNode = curNode->children[i];
					curChar = s[++matches];
					next = true;
				}
			}
			if(!next){
				pair<int, trieNode*> p(matches, curNode);
				return p;
			} else {
				next = false;
			}
		}
	}

public:
	int trieMatch(string s){
		return trieMatchInternal(s).first;
	}

	void trieAdd(string s){
		cout << "call add with string: " << s << endl;
		pair<int, trieNode*> matchResults = trieMatchInternal(s);
		trieNode * curNode = matchResults.second;
		int loc = 0;
		char curChar = s[loc];
		if(!curNode){
			curNode = new trieNode(curChar);
			root.push_back(curNode);
			++loc;
			cout << "new curnode : " << curNode->character << endl;
		} else{
			loc = matchResults.first; 
			//The # of matches is 1 more than the last match's place in the string,
			//which is also the location of the first character we have to insert
			cout << "found curnode : " << curNode->character << endl;		
		}
		curChar = s[loc];
		trieNode * temp = NULL;
		cout << "reach loop " << endl;
		for(;loc<s.length();++loc){
			temp = new trieNode(s[loc]);
			curNode->children.push_back(temp);
			curNode = temp;
			cout << "curNode: " << curNode->character << " stringLoc: " << loc << endl;
		}
	}


};