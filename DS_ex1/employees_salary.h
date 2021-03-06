#ifndef EMPLOYEES_SALARY_H_
#define EMPLOYEES_SALARY_H_

#include <iostream>
#include <utility>
#include <memory>

class EmployeeSalaryData {
private:
	int employee_id;
	std::shared_ptr<int> employer_id;
	int salary;
	int grade;

public:
	EmployeeSalaryData(int employeeID, std::shared_ptr<int> employerID, int salary, int grade);
	EmployeeSalaryData(const EmployeeSalaryData& EmployeeSalaryData) = default;
	~EmployeeSalaryData() = default;
	EmployeeSalaryData& operator=(EmployeeSalaryData&) = default;
	int getEmployerIDInteger() { return *employer_id; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	int getEmployeeID() { return employee_id; }

	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { *employer_id = newCompanyID; }

	bool operator<(const EmployeeSalaryData& other) const;
	bool operator>(const EmployeeSalaryData& other) const;
	bool operator==(const EmployeeSalaryData& other) const;
};

#endif //EMPLOYEES_SALARY_H_