/*
 *          File: employee.h
 *        Author: Robert I. Pitts <rip@cs.bu.edu>
 * Last Modified: April 8, 2000
 *         Topic: Introduction to Inheritance in C++
 * ----------------------------------------------------------------
 *
 * Employee class definition.
 */

 using namespace std;

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#include <string>

class Employee {
public:
  Employee(string theName, float thePayRate);

  string getName() const;
  float getPayRate() const;
  void setName(string theName);
  void setPayRate(float thePayRate);

  float pay(float hoursWorked) const;

protected:
  string name;
  float payRate;
};

#endif /* not defined _EMPLOYEE_H */
