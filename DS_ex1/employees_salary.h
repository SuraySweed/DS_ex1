#ifndef EMPLOYEES_SALARY_H_
#define EMPLOYEES_SALARY_H_

#include <iostream>

using std::shared_ptr;

class EmployeeSalaryData {
private:
	int employee_id;
	shared_ptr<int> employer_id;
	//int* employerID_ptr;
	int salary;
	int grade;

public:
	EmployeeSalaryData(int employeeID, shared_ptr<int> employerID, int salary, int grade);
	EmployeeSalaryData(const EmployeeSalaryData& EmployeeSalaryData) = default;
	~EmployeeSalaryData() = default;
	EmployeeSalaryData& operator=(EmployeeSalaryData&) = default;
	int getEmployerIDInteger() { return *employer_id; }
	//int& getEmployerID() { return employer_id; }
	//int* getEmployeeIDPtr() { return employerID_ptr; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	int getEmployeeID() { return employee_id; }

	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { *employer_id = newCompanyID; }
	//void setEmployerIDPtr(int* newCompanyID_ptr) { employerID_ptr = newCompanyID_ptr; }

	bool operator<(const EmployeeSalaryData& other) const;
	bool operator>(const EmployeeSalaryData& other) const;
	bool operator==(const EmployeeSalaryData& other) const;
};

#endif //EMPLOYEES_SALARY_H_