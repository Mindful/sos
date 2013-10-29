#ifndef scheduler_h
#define scheduler_h

#include <vector>
#include <string>
using namespace std;

class scheduler{

public:
	void start();


private:
	int freeProcs, usedProcs, nextId;
	void tick();
	int totalProcs(); //freeProcs + usedProcs
	//Required functions
	void insertJob(string job_description, int n_procs, int n_ticks); 
	//Validates that n_procs <= totalProcs() && n_ticks > 0
	//creates a job object based off description, with procs and ticks, and an id of nextId++;
	job findDelShortest()
	//find the node in the waitqueue that points to the job with the smallest number of ticks
	//delete that node and return the job





};

#endif