using namespace std;

class job{
public:
	const int procs, totalTicks, id;
	const string description;
	job(string job_description, int n_procs, int n_ticks, int job_id) : description(job_description), 
		procs(n_procs), totalTicks(n_ticks), remainingTicks(n_ticks), id(job_id)
	{
	};

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