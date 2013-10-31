#include "scheduler.h"

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
	//NYI
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

			//get actual job info, check for validity. use helper function
			//to loop for valid input on each thing.
			cout << "Please enter a job description" << endl;
			getline(cin, buffer);
			n_procs = getInt("Please enter a number of required processors");
			n_ticks = getInt("Please enter a number of ticks");
			insertJob(buffer, n_procs, n_ticks); 
		}

	}

}

void scheduler::tick(){
	for(list<job>::iterator it=runQueue.begin(); it != runQueue.end(); ++it){
		if (!it->tick()) //if this job is finished
		{
			//free processors
			//print job completion
			runQueue.erase(it); //using the iterator we have makes this O(1)
		}
	}
	//traverse the runqueue. tick on each job, and perform removals if their ticks return false
}

void scheduler::start()
{
	int i = 0;
	while (true)
	{
		if (++i == inputInterval)
		{
			getInput();
			i = 0;
		}
		tick();
	}
}
