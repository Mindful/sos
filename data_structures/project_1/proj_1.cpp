// constructing vectors
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "job.cpp" //Must come before job. This will probably eventually be delegated to the makefile
#include "scheduler.cpp" //Includes scheduler.h
using namespace std;

int main (){  
	scheduler s = scheduler(4,5);
	s.start();
}

//the wait queue needs to be a nactual queue, with order mattering as we want the first item with a low enough
//number of required processors

//the runqueue is just.. whatever. It can probably just be a linked list. not a vector because we'd make tons of
//holes in it with unfinished jobs