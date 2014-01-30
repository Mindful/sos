#include "supervisor.h"

Supervisor::Supervisor(string theName, float thePay, string theDepartment):Manager(theName, thePay, true), department(theDepartment){}

void Supervisor::setDept(string theDepartment){
	department = theDepartment;
}

string Supervisor::getDept(){
	return department;
}