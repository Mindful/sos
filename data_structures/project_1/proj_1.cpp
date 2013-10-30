// constructing vectors
#include <iostream>
#include <vector>
#include <string>
#include "job.cpp" //Must come before job. This will probably eventually be delegated to the makefile
#include "scheduler.cpp" //Includes scheduler.h
using namespace std;

int main (){  
	scheduler s = scheduler(4,5);
	s.start();
}