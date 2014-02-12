#include <iostream>
#include <stack>
#include <vector>

using namespace std;

//I know my Xs and Ys are switched, so to speak, but multidimensional arrays
//look different than they act...

//Also Y is inverted technically
//this double-array thing was not so good for me

enum pathState {viable, blocked, taken};
enum direction {north, south, east, west};

class pathRecord{
public:
	pathState north;
	pathState south;
	pathState east;
	pathState west;
	int x,y;

	pathRecord(int X, int Y) : x(X), y(Y){}

};


//Ones are walls, 0s are viable paths
//The win condition is reaching the right wall
bool maze [10][10] = {
  { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
  { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
  { 1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
  { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
  { 1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
  { 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
  { 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
  { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
  { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}
  };

class navigator{

private:
	stack<pathRecord> pathStack;
	int x,y, width, height;
	bool navigating;
	direction lastPath;
	vector< stack<pathRecord> > paths;
	stack<pathRecord> shortestPath;

public:
	navigator(bool maze[][10], int height) : navigating(true),x(0),y(0),height(height){
		width = 10;
		y = -1;
		//We're assuming the width is 10 here because C++ won't take variably sized
		//multidimensional arrays as arguments and rewriting this to use vectors would
		//just have wasted time

		//Find start location on left wall
		for (int i = 0; i < height; ++i){
			if(!maze[i][0]){
				y = i;
				break;
			}
		}

		if (y==-1){
			cout << "Unable to find start location." << endl;
			navigating = false;
		} else {
			cout << "Starting at (0," << y << ")" << endl;
		}
	}

	bool move(pathRecord &p){
		if (p.east == viable){
			p.east = taken;
			lastPath = east;
			++x;
			cout << "> to (" << x << "," << y << ")" << endl;
		} else if (p.south == viable){
			p.south = taken;
			lastPath = south;
			--y;
			cout << "^ to (" << x << "," << y << ")" << endl;
		} else if (p.north == viable){
			p.north = taken;
			lastPath = north;
			++y;
			cout << "v to (" << x << "," << y << ")" << endl;
		} else if (p.west == viable){
			p.west = taken;
			lastPath = west;
			--x;
			cout << "< to (" << x << "," << y << ")" << endl;
		} else {
			cout << "Blocked at (" << x << "," << y << ")" << endl;
			return false;
		}
		return true;
	}

	void printPath(pathRecord &p){

	}

	void navigate(){
		while(navigating){
			// if (x == width-1){
			// 	cout << "End of maze reached!" << endl; //x >= width -1 means we've finished
			// 	navigating = false;
			// 	break;
			// }
			pathRecord p(x,y);
			//These checks also need to look at the top of the stack

			if (y+1 < height && !maze[y+1][x]) p.north = viable;
			else p.north = blocked; 

			if (y-1 >= 0 && !maze[y-1][x]) p.south = viable;
			else p.south = blocked;

			if (x+1 < width && !maze[y][x+1]) p.east = viable;
			else p.east = blocked;

			if (x-1 >= 0 && !maze[y][x-1]) p.west = viable;
			else p.west = blocked;

			if (lastPath==north) p.south=taken;
			if (lastPath==south) p.north=taken;
			if (lastPath==west) p.east=taken;
			if (lastPath==east) p.west=taken;

			if (x == width-1 || !move(p)){
			        if (x == width-1) {
				  cout << " ~*~ Path found! ~*~" << endl;
				  pathStack.push(p);
				  paths.push_back(pathStack);
				}

				bool stuck = true;
				//Needs to work better when blocked
				while(stuck){
					if(pathStack.empty()){
						stuck = false;
						navigating = false;
						cout << "Dead-ended!" << endl;
						break;
					}

					p = pathStack.top(); //Get a location
					pathStack.pop();
					x = p.x;
					y = p.y;
					if(move(p)) stuck = false;
				}
			} else pathStack.push(p); //Push the current location, either new or backed into
		}
		if ( paths.size() ){
		    shortestPath = paths[0];
		    for (int i=0; i<paths.size(); ++i){
			if ( paths[i].size() < shortestPath.size() )
			   shortestPath = paths[i];
		    }
		} else {
		    cout << "No paths found" << endl;
		}
	}
	
	void printShortestPath(){
	     while( !paths.empty() && !shortestPath.empty()){
		  cout << "(" << shortestPath.top().x << " , " << shortestPath.top().y << ")" << endl;
		  shortestPath.pop();
	     }
	}
};




int main(){
	navigator n(maze,10);
	n.navigate();
	n.printShortestPath();
	return 0;
}