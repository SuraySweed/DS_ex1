#ifndef ACTIVE_COMPANIES_H
#define ACTIVE_COMPANIES_H

#include "avl_tree.h"
#include "employees_id.h"
#include "employees_salary.h"
#include "active_employees.h"

class ActiveCompaniesData {
private:
	int company_id;
	AVLTree<EmployeeSalaryData> company_employees; //by id
	EmployeeSalaryData* highestSalary;

public:
	ActiveCompaniesData(int company_id);
	ActiveCompaniesData(const ActiveCompaniesData& active_companies_data);
	~ActiveCompaniesData();

	AVLTree<EmployeeSalaryData>& getActiveCompanyEmployees() { return company_employees; }
	EmployeeSalaryData* getHighestSalary() { return highestSalary; }
	void setHighestSalary(EmployeeSalaryData* highest_salary);

	bool operator<(const ActiveCompaniesData& other) const;
	bool operator>(const ActiveCompaniesData& other) const;
	bool operator==(const ActiveCompaniesData& other) const;
};

#endif //ACTIVE_COMPANIES_H_
