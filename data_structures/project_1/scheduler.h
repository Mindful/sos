#ifndef scheduler_h
#define scheduler_h
using namespace std;

class scheduler{

public:
	void start();
	scheduler(int, int);

private:
	int freeProcs, usedProcs, nextId;
	list<job> waitQueue, runQueue;
	const int inputInterval;
	void tick();
	void getInput();
	//calls submitJob on any valid input
	int totalProcs(); //freeProcs + usedProcs
	//Required functions
	bool insertJob(string, int, int); 
	//Validates that n_procs <= totalProcs() && n_ticks > 0
	//creates a job object based off description, with procs and ticks, and an id of nextId++;
	bool findDelShortest(job**);
	//find the node in the waitqueue that points to the job with the smallest number of ticks
	//delete that node and return the job
	void submitJob();
	//
	void runJob(job*);
	void print_jobs();





};

#endif