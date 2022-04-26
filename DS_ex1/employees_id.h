#ifndef EMPLOYEES_ID_H
#define EMPLOYEES_ID_H

#include <iostream>

class EmployeeIdData {
private:
	int employee_id;
	int employer_id;
	int salary;
	int grade;

public:
	EmployeeIdData(int employeeID, int employerID, int salary, int grade);
	EmployeeIdData(const EmployeeIdData& employeeIdData);
	~EmployeeIdData();
	EmployeeIdData& operator=(const EmployeeIdData&);
	int getEmployerID() { return employer_id; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	
	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { employer_id = newCompanyID; }

	bool operator<(const EmployeeIdData& other) const;
	bool operator>(const EmployeeIdData& other) const;
	bool operator==(const EmployeeIdData& other) const;
	//bool operator>(const EmployeeIdData& employee_data1, const EmployeeIdData& employee_data2);
};
/*
class employeesID {
private:
	AVLTree<EmployeeIdData> employees_tree;

public:
	employeesID();
	employeesID(const employeesID& empolyees_id);
	~employeesID();
	employeesID& operator=(const employeesID&);

	void addEmployee(int employeeID, int companyID, int salary, int grade);
	void removeEmploee(int employeeID);
	void getEmployeeInfo(int employeeID, int* employerID, int* salary, int* grade);
	void promoteEmployee(int employeeID, int salaryIncrease, int bumpGrade);
	void hireEmployee(int employeeID, int newCompanyID);
};
*/
#endif //EMPLOYEES_ID_H_
