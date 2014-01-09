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

scheduler::scheduler(int processors, int inputInterval) : freeProcs(processors), inputInterval(inputInterval), nextId(0)
{
}

bool scheduler::insertJob(string job_description, int n_procs, int n_ticks){
	if (!(n_procs > freeProcs + usedProcs || n_ticks <= 0)){
		job j(job_description, n_procs, n_ticks, ++nextId);
		waitQueue.push_back(j);
		return true;
	}
	return false;
}

bool scheduler::findDelShortest(job** buffer){
	bool found =false;
	int min;
	list<job>::iterator shortestJob;
	for(list<job>::iterator it=waitQueue.begin(); it != waitQueue.end(); ++it){
		if (it->procs <= freeProcs && (!found || it->totalTicks < min))
		{
			found = true;
			min = it->totalTicks;
			shortestJob = it;
		}
	}
	if (found){
		*buffer = new job(*shortestJob); //Using the default copy constructor to store our job in the buffer.
		waitQueue.erase(shortestJob); //using the iterator we have makes this O(1)
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
		runJob(j); //J copied into runqueue
		delete j; 
	}

	for(list<job>::iterator it=runQueue.begin(); it != runQueue.end(); ++it){
		if (!it->tick()) //if this job is finished
		{
			usedProcs -= it->procs;
			freeProcs += it->procs;
			cout << "Job with description \"" << it->description << "\" finished after " 
				<< it->totalTicks << " ticks on " << it->procs << " processors" << endl;
			//using the iterator we have makes this O(1)
			runQueue.erase(it--); //the -- is very important because erase invalidates the iterator
		};
	}
}

void scheduler::runJob(job *j){
	runQueue.push_back(*j);
	freeProcs-=j->procs;
	usedProcs+=j->procs;
}

void printlist(list<job> & l){
	for (list<job>::iterator it = l.begin(); it != l.end(); ++it){
		cout << it->id << " " << it->description << ", ";
	}
	cout << endl;
}

void scheduler::print_jobs(){
	cout << "waitQueue: " << endl; printlist(waitQueue);
	cout << "runQueue: " << endl;  printlist(runQueue);
}

void scheduler::start()
{
	int i = 0;
	while (true)
	{
		if (++i == inputInterval)
		{
			cout << inputInterval << " ticks elapsed." << endl;
			print_jobs();
			getInput();
			i = 0;
		}
		tick();
	}
}
