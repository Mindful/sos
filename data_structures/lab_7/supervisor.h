#ifndef _SUPERVISOR_H
#define _SUPERVISOR_H


#include "manager.h"


class Supervisor : public Manager {
public:
	Supervisor(string theName,
				float thePay,
				string theDepartment);

	void setDept(string theDepartment);
	string getDept();
protected:
	string department;

private:
};


#endif /* not defined _SUPERVISOR_H */