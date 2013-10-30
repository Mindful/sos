#include "scheduler.h"

scheduler::scheduler(int processors, int inputInterval) : freeProcs(processors), inputInterval(inputInterval)
{
}

void scheduler::getInput(){

}

void scheduler::tick(){
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
