#ifndef EMPLOYEES_ID_H
#define EMPLOYEES_ID_H

#include <iostream>
#include "avl_tree.h"
#include "employees_salary.h"

class EmployeeIdData {
private:
	int employee_id;
	int employer_id;
	int* employerID_ptr;
	int salary;
	int grade;

public:
	EmployeeIdData(int employeeID, int employerID, int salary, int grade);
	EmployeeIdData(const EmployeeIdData& employeeIdData);
	~EmployeeIdData() = default;
	EmployeeIdData& operator=(EmployeeIdData&);
	int getEmployeeID() { return employee_id; }
	int getEmployerIDInteger() { return employer_id; }
	int& getEmployerID() { return employer_id; }
	int* getEmployerIDPtr() { return employerID_ptr; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	
	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { employer_id = newCompanyID; }
	void setEmployerIDPtr(int* companyPtr) { employerID_ptr = companyPtr; }
	bool operator<(const EmployeeIdData& other) const;
	bool operator>(const EmployeeIdData& other) const;
	bool operator==(const EmployeeIdData& other) const;
};
#endif //EMPLOYEES_ID_H_
