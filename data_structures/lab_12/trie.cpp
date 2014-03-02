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
		string value;

		trieNode(char c, string s) : character(c), value(s){};
	};


	//This might be a weird way to conceptualize the "root" node, but there isn't actually a real
	//root node at all - just a bunch of first children.
	vector<trieNode*> root;

	pair<string, trieNode*> trieMatchInternal(string s){
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
			pair<string, trieNode*> p("", NULL);
			return p;
		}

		//We have a first node, we can start a traversal
		bool next = false;
		for(; matches <= s.length();){
			
			for(int i = 0; i < curNode->children.size(); ++i){
				if(curNode->children[i]->character==curChar){
					curNode = curNode->children[i];
					curChar = s[++matches];
					next = true;
				}
			}
			if(!next){
				pair<string, trieNode*> p(curNode->value, curNode);
				return p;
			} else {
				next = false;
			}
		}
	}

public:

	//It seems a little weird to have an iterator.. and the original reason
	//that I wrote one isn't really valid now that I have a better understanding
	//of the problem. Oh well, it was interesting.
	class const_iterator{
	protected:
		trieNode* current;

		const_iterator(trieNode* t) : current(t){}


	public:
		const_iterator() : current(NULL){}

        char & operator* ( ) const
          { return current->character; }

        bool bad(){return current==NULL;}

        bool tryNext(char c){
        	for(int i = 0; i < current->children.size(); ++i){
        		if(current->children[i]->character==c){
        			current = current->children[i];
        			return true;
        		}
        	}
        	return false;
        }

    friend class trie;
	};

	const_iterator tryFirst(char c){
		for(int i = 0; i < root.size(); ++i){
			if(root[i]->character==c){
				const_iterator r(root[i]);
				return r;
			}
		}
		const_iterator r;
		return r;
	}

	string trieMatch(string s){
		return trieMatchInternal(s).first;
	}

	void trieAdd(string s){
		pair<string, trieNode*> matchResults = trieMatchInternal(s);
		trieNode * curNode = matchResults.second;
		int loc = 0;
		char curChar = s[loc];
		if(!curNode){
			curNode = new trieNode(curChar, s.substr(0, loc+1));
			root.push_back(curNode);
			++loc;
		} else{
			loc = matchResults.first.length(); 
			//The # of matches is 1 more than the last match's place in the string,
			//which is also the location of the first character we have to insert		
		}
		curChar = s[loc];
		trieNode * temp = NULL;
		
		for(;loc<s.length();++loc){
			temp = new trieNode(s[loc], s.substr(0, loc+1));
			curNode->children.push_back(temp);
			curNode = temp;
			
		}
	}


};