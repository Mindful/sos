#include "scheduler.h"

//todo: what's generating segmentation faults here is very likely attempting to iterate empty queues
//the for loops that use waitQueue and runQueue should validate that there are objects in those queues
//before attempting to perform any kind of iteration on them

int getInt(string prompt){
	int val;
	string input;
	while(true){
		cout << prompt << endl;
		getline(cin, input); //Get the text value, put it into string input
		stringstream temp(input); //Convert the text value into a stringstream
		if (temp >> val){
			return val;
		}
	}
}

scheduler::scheduler(int processors, int inputInterval) : freeProcs(processors), inputInterval(inputInterval)
{
}

void scheduler::insertJob(string job_description, int n_procs, int n_ticks){
	//TODO: validate that this isn't more than the processors we have
	//also validate no negatives
	job j(job_description, n_procs, n_ticks, ++nextId);
	waitQueue.push_front(j);
}

bool scheduler::findDelShortest(job** buffer){
	//todo: I think this is iterating backwards, given we want a queue and not a stack.
	int min = -1; //invalid min, so we know if it hasn't been set
	for(list<job>::iterator it=waitQueue.begin(); it != waitQueue.end(); ++it){
		if (it->procs <= freeProcs && (min == -1 || it->totalTicks < min)) 
		{
			*buffer = new job(*it); //Copy the saved job into something so we can return it, since erase cleans memory too
			waitQueue.erase(it); //using the iterator we have makes this O(1)
			return true;
		}
	}
	*buffer = NULL;
	return false;
}

void scheduler::getInput()
{
	bool input = true;
	string buffer;
	int n_procs, n_ticks;
	while(input)
	{
		cout << "Would you like to enter a job? (y/n)" << endl;
		getline(cin, buffer);
		if (buffer == "n" || buffer == "N"){
			return;
		}
		else if (buffer != "y" && buffer != "Y"){
			cout << "Unrecognized input. Please try again" << endl;
		}
		else{
			cout << "Please enter a job description" << endl;
			getline(cin, buffer);
			n_procs = getInt("Please enter a number of required processors");
			n_ticks = getInt("Please enter a number of ticks");
			insertJob(buffer, n_procs, n_ticks); 
		}

	}

}

void scheduler::tick(){
	job *j; //holds found job, if any
	while (findDelShortest(&j)){
		runJob(j); //J copied into runqueue
		delete j; //to prevent memory leak
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
	runQueue.push_front(*j);
	freeProcs-=j->procs;
	usedProcs+=j->procs;
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
			i = 0;
		}
		tick();
	}
}
