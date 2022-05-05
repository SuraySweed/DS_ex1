#ifndef EMPLOYEES_ID_H
#define EMPLOYEES_ID_H

#include <iostream>
#include "avl_tree.h"
#include "employees_salary.h"

class EmployeeIdData {
private:
	int employee_id;
	int* employer_id;
	int salary;
	int grade;

public:
	EmployeeIdData(int employeeID, int employerID, int salary, int grade);
	EmployeeIdData(const EmployeeIdData& employeeIdData);
	~EmployeeIdData();
	EmployeeIdData& operator=(EmployeeIdData&);
	int* getEmployerID() { return employer_id; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	
	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { *employer_id = newCompanyID; }
	void setEmployerIDPtr(int* companyPtr) { employer_id = companyPtr; }
	bool operator<(const EmployeeIdData& other) const;
	bool operator>(const EmployeeIdData& other) const;
	bool operator==(const EmployeeIdData& other) const;
};
#endif //EMPLOYEES_ID_H_
