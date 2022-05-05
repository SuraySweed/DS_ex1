#ifndef EMPLOYEES_ID_H
#define EMPLOYEES_ID_H

#include <iostream>
#include "avl_tree.h"
#include "employees_salary.h"

class EmployeeIdData {
private:
	int employee_id;
	int employer_id;
	int salary;
	int grade;
	Node<EmployeeIdData>* employeePtrInAllIDTree;//i hate you
	Node<EmployeeSalaryData>* employeePtrInAllSalaryTree;

public:
	EmployeeIdData(int employeeID, int employerID, int salary, int grade);
	EmployeeIdData(const EmployeeIdData& employeeIdData);
	~EmployeeIdData();
	EmployeeIdData& operator=(const EmployeeIdData&);
	int getEmployerID() { return employer_id; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }
	Node<EmployeeIdData>* getEmployeePtrByID() { return employeePtrInAllIDTree; }
	Node<EmployeeSalaryData>* getEmploeePtrBySalary() { return employeePtrInAllSalaryTree; }
	
	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { employer_id = newCompanyID; }
	void setEmployeePtrByID(Node<EmployeeIdData>* node) { employeePtrInAllIDTree = node; }
	void setEmploeePtrBySalary(Node<EmployeeSalaryData>* node) { employeePtrInAllSalaryTree = node; }

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
