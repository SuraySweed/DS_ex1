#ifndef ACTIVE_COMPANIES_H
#define ACTIVE_COMPANIES_H

#include "avl_tree.h"
#include "employees_id.h"
#include "employees_salary.h"
#include "active_employees.h"

class ActiveCompaniesData {
private:
	int company_id;
	AVLTree<EmployeeSalaryData> employeesBySalary; //by salary
	AVLTree<EmployeeIdData> employeesByID;    // by id
	EmployeeSalaryData* highestSalary;
	int numberOfEmployees;

public:
	ActiveCompaniesData(int company_id);
	ActiveCompaniesData(const ActiveCompaniesData& active_companies_data);
	~ActiveCompaniesData() = default;

	AVLTree<EmployeeIdData>& getActiveCompanyEmployeesByID() { return employeesByID; }
	AVLTree<EmployeeSalaryData>& getActiveCompanyEmployeesBySalary() { return employeesBySalary; }
	EmployeeSalaryData* getHighestSalary() { return highestSalary; }
	void setHighestSalary(EmployeeSalaryData* highest_salary);
	int getNumberOfEmployees() { return numberOfEmployees; }
	void incNumberOfEmployees() { numberOfEmployees++; }
	bool removeEmployee(int employeeID, int salary);
	void setNumberOfEmployees(int num) { numberOfEmployees = num; }
	void setActiveCompanyEmployeesByID(AVLTree<EmployeeIdData>& other);
	void setActiveCompanyEmployeesBySalary(AVLTree<EmployeeSalaryData>& other);

	bool operator<(const ActiveCompaniesData& other) const;
	bool operator>(const ActiveCompaniesData& other) const;
	bool operator==(const ActiveCompaniesData& other) const;
};

#endif //ACTIVE_COMPANIES_H_
