#include "scheduler.h"
#include <cstdlib>

int getInt(string prompt){
	int val;
	string input;
	while(true){
		cout << prompt << endl;
		getline(cin, input); 
		stringstream temp(input); //Convert the text value into a stringstream, so we can make it an int
		if (temp >> val){
			return val;
		}
	}
}

bool compareJobs(job* lhs, job* rhs) {
	if (lhs==NULL) cout << "LHS NULL " << endl;
	if (rhs==NULL) cout << "RHS NULL " << endl;
	return lhs->totalTicks < rhs->totalTicks;
}

scheduler::scheduler(int processors, int inputInterval) : freeProcs(processors), inputInterval(inputInterval), nextId(0),
waitQueue(compareJobs, 10)
{
}

bool scheduler::insertJob(string job_description, int n_procs, int n_ticks){
	if (!(n_procs > freeProcs + usedProcs || n_ticks <= 0)){
		job* j= new job(job_description, n_procs, n_ticks, ++nextId);
		waitQueue.insert(j);
		return true;
	}
	return false;
}

bool scheduler::findDelShortest(job** buffer){
	bool found =false;

	// cout << "finddelshortest" << endl;
	// cout << "free procs " << freeProcs << endl;

	//As per the spec, we give up if the minimum isn't going to work
	//with our number of free processors
	if (!waitQueue.isEmpty()){
		job * j = waitQueue.findMin();
		if (j->procs <= freeProcs){
			found = true;
			*buffer = j;
			waitQueue.deleteMin();
		}
	}
	return found;
}

void scheduler::getInput()
{
	bool input = true;
	string buffer;
	int n_procs, n_ticks;
	while(input)
	{
		cout << "Would you like to enter a job? (y/n/exit)" << endl;
		getline(cin, buffer);
		if (buffer == "n" || buffer == "N"){
			return;
		}
		else if (buffer == "exit"){
			exit(0);
		}
		else if (buffer != "y" && buffer != "Y"){
			cout << "Unrecognized input. Please try again" << endl;
		}
		else{
			cout << "Please enter a job description" << endl;
			getline(cin, buffer);
			n_procs = getInt("Please enter a number of required processors");
			n_ticks = getInt("Please enter a number of ticks");
			if (!insertJob(buffer, n_procs, n_ticks))
				cout << "Job failed: not enough processors or invalid tick quantity." << endl; 
		}

	}

}

void scheduler::tick(){
	job *j; //buffer that holds found job, if any
	while (findDelShortest(&j)){
		runJob(j); //J copied into runList
		delete j; 
	}

	for(list<job>::iterator it=runList.begin(); it != runList.end(); ++it){
		if (!it->tick()) //if this job is finished
		{
			usedProcs -= it->procs;
			freeProcs += it->procs;
			cout << "Job with description \"" << it->description << "\" finished after " 
				<< it->totalTicks << " ticks on " << it->procs << " processors" << endl;
			//using the iterator we have makes this O(1)
			runList.erase(it--); //the -- is very important because erase invalidates the iterator
		};
	}
}

void scheduler::runJob(job *j){
	runList.push_back(*j);
	freeProcs-=j->procs;
	usedProcs+=j->procs;
}

void printlist(list<job> & l){
	for (list<job>::iterator it = l.begin(); it != l.end(); ++it){
		cout << *it;
	}
	cout << endl;
}

void scheduler::print_jobs(){
	cout << "waitQueue: " << endl; waitQueue.printHeap();
	cout << "runList: " << endl;  printlist(runList);
}

void scheduler::start()
{
	int i = 0;
	while (true)
	{
		if (++i == inputInterval)
		{
			cout << inputInterval << " ticks elapsed." << endl;
			getInput();
			print_jobs();
			i = 0;
		}
		tick();
	}
}
