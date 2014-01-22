using namespace std;

class job{
public:
	int procs, totalTicks, id;
	string description;
	job(string job_description, int n_procs, int n_ticks, int job_id) : description(job_description), 
		procs(n_procs), totalTicks(n_ticks), remainingTicks(n_ticks), id(job_id)
	{
	};

	// job(const job &j) : description(j.description), procs(j.procs), totalTicks(j.totalTicks), 
	// remainingTicks(j.remainingTicks), id(j.id){}

	job() : description("Empty Job"), procs(0), totalTicks(0), remainingTicks(0), id(0){}

private:
	int remainingTicks;

public:
	bool tick()
	{
		if (--remainingTicks<=0){
			return (bool)(remainingTicks=0); 
		}
		return true;
	}

	// bool operator<(const job& rhs) const{
	// 	return this->totalTicks < rhs.totalTicks;
	// }
};

	std::ostream& operator<<(std::ostream& os, const job &j)
	{
	  os << "Job ID: " << j.id << " Description: " << j.description << endl;
	  return os;
	}