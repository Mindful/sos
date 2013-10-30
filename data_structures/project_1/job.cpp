using namespace std;

class job{
public:
	const int procs, totalTicks, id;
	const string description;
	job(string, int, int, int); //description, procs, ticks, id

private:
	int remainingTicks;

public:
	bool tick()
	{
		if (--remainingTicks<=0){
			return (bool)(remainingTicks=0); //Return 0, evaluating to false
		}
		return true;
	}
};