#include "scheduler.h"

scheduler::scheduler(int processors, int inputInterval) : freeProcs(processors), inputInterval(inputInterval)
{
}

void scheduler::getInput()
{
	bool input = true;
	string buffer;
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
			while (true){

			}
		}

	}

}

void scheduler::tick(){
	for(list<int>::iterator it=runQueue.begin(); it != runQueue.end(); ++it;){
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
