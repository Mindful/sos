#include "trie.cpp"

//requires g++ -std=c++11 because to_string is in C++11 and I'm lazy

//I just want to say that in retrospect, I have no idea why anyone would use a trie for this
//I'm glad I wrote my own trie (that was educational) and this problem is interesting, but unless
//I modeled the problem COMPLETELY incorrectly, it would have been faster/easier/equally efficient
//to just look compare these strings to the goal strings instead of using a trie

//I could see a slightly better way to do this by creeping out one character at a time 
//(this was the kind of thing I made the trie iterator for)
//and looking to see if that character matched was a viable next step in the trie - then we could make
//only a single pass throughout the entire grid. That said, it wouldn't be a huge improvement and you could
//do the same thing without the trie.



//Returning a vector because it's easier than returning an array
vector<string> findWords(string grid[], int gridSize, string wordList[], int wordListSize){
	vector<string> v(wordListSize);
	trie t;
	for(int i = 0; i < wordListSize; ++i){
		t.trieAdd(wordList[i]);
		v[i]="";
	}
	for(int o = 0; o < wordListSize; ++o){
		string s = wordList[o];
		string result;
		for(int row = 0; row < gridSize; ++row){
			for (int col = 0; col < grid[row].length(); ++col){
				string right = grid[row].substr(col, col+s.length());
				string down(' ', s.length());
				string downRight(' ', s.length());
				for(int k = 0; k < down.length(); ++k){
					down[k] = (row+k<gridSize) ? grid[row+k][col] : ' ';
					downRight[k] = (row+k<gridSize && col+k<grid[row+k].length()) ? grid[row+k][col+k] : ' ';

				}
				if(t.trieMatch(down) == s || t.trieMatch(right) == s || t.trieMatch(downRight) == s){
					cout << "found " << s << "at row: " << row << " col: " << col << endl;
					string temp = to_string(row) + " " + to_string(col);
					if(v[o]=="")v[o] = temp;
				}
				 // cout << "down: " << down << endl;
				 // cout << "right: " << right << endl;
				 // cout << "downRight: " << downRight << endl;
			}
		}
	}
	return v;

}


void testMethod(){
	trie t;
	t.trieAdd("test");
	t.trieAdd("cutey");
	t.trieAdd("tense");
	string s;
	trie::const_iterator c = t.tryFirst('c');
	if(c.bad()) cout << "c no good" << endl;
	else cout << "c good" << endl;
		trie::const_iterator d = t.tryFirst('d');
	if(d.bad()) cout << "d no good" << endl;
	else cout << "d good" << endl;
	while(s!="exit"){
		cin >> s;
		cout << "match: " << t.trieMatch(s) << endl;
		if(c.tryNext(s[0])) cout << "moved to " << *c << endl;
		else cout << s[0] << " no good " << endl;
	}
}


int main(){
	string grid1[] = {"TEST",
 					 "GOAT",
 					 "BOAT"};
	string wordList1[] = {"GOAT", "BOAT", "TEST"};
	vector<string> v1 =	findWords(grid1, 3, wordList1, 3);
	for (int i = 0; i < v1.size(); ++i){
		cout << i << " : " << v1[i] << endl;
	}
	string grid2[] = {"SXXX",
 "XQXM",
 "XXLA",
 "XXXR"};
 	string wordList2[] = {"SQL", "RAM"};
	vector<string> v2 =	findWords(grid2, 4, wordList2, 2);
	for (int i = 0; i < v2.size(); ++i){
		cout << i << " : " << v2[i] << endl;
	}
	string grid3[] = {"EASYTOFINDEAGSRVHOTCJYG",
 "FLVENKDHCESOXXXXFAGJKEO",
 "YHEDYNAIRQGIZECGXQLKDBI",
 "DEIJFKABAQSIHSNDLOMYJIN",
 "CKXINIMMNGRNSNRGIWQLWOG",
 "VOFQDROQGCWDKOUYRAFUCDO",
 "PFLXWTYKOITSURQJGEGSPGG"};
 string wordList3[] = {"EASYTOFIND", "DIAG", "GOING", "THISISTOOLONGTOFITINTHISPUZZLE"};
 	vector<string> v3 =	findWords(grid3, 7, wordList3, 4);
 	for (int i = 0; i < v3.size(); ++i){
		cout << i << " : " << v3[i] << endl;
	}

	//testMethod();
	return 0;
}