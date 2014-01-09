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
	bool insertJob(string, int, int); 
	bool findDelShortest(job**);
	void submitJob();
	void runJob(job*);
	void print_jobs();
};

#endif