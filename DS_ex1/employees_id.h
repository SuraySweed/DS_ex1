#ifndef EMPLOYEES_ID_H
#define EMPLOYEES_ID_H

#include <iostream>
#include <utility>
#include <memory>
#include "avl_tree.h"
#include "employees_salary.h"


class EmployeeIdData {
private:
	int employee_id;
	std::shared_ptr<int> employer_id;
	int salary;
	int grade;

public:
	EmployeeIdData(int employeeID, std::shared_ptr<int> employerID, int salary, int grade);
	EmployeeIdData(const EmployeeIdData& employeeIdData) = default;
	~EmployeeIdData() = default;
	EmployeeIdData& operator=(EmployeeIdData&) = default;
	int getEmployeeID() { return employee_id; }
	int getEmployerIDInteger() { return *employer_id; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	
	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { *employer_id = newCompanyID; }

	bool operator<(const EmployeeIdData& other) const;
	bool operator>(const EmployeeIdData& other) const;
	bool operator==(const EmployeeIdData& other) const;
};
#endif //EMPLOYEES_ID_H_
