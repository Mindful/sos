#ifndef scheduler_h
#define scheduler_h
#include "heap.cpp"
using namespace std;

class scheduler{

public:
	void start();
	scheduler(int, int);

private:
	int freeProcs, usedProcs, nextId;
	list<job> runList;
	BinaryHeap<job*> waitQueue;
	const int inputInterval;
	void tick();
	void getInput();
	bool insertJob(string, int, int); 
	bool findDelShortest(job**);
	void submitJob();
	void runJob(job*);
	void print_jobs();
};

#endif