#include "active_companies.h"

ActiveCompaniesData::ActiveCompaniesData(int company_id) : company_id(company_id), 
	company_employees(AVLTree<EmployeeSalaryData>()), highestSalary(nullptr) {}

ActiveCompaniesData::ActiveCompaniesData(const ActiveCompaniesData& active_companies_data) : 
	company_id(active_companies_data.company_id),
	company_employees(AVLTree<EmployeeSalaryData>(active_companies_data.company_employees)) {}

ActiveCompaniesData::~ActiveCompaniesData() {}

void ActiveCompaniesData::setHighestSalary(EmployeeSalaryData* highest_salary)
{
	highestSalary = highest_salary;
}

void ActiveCompaniesData::removeEmployee(int employeeID, int salary)
{
	EmployeeSalaryData ESD(employeeID, 0, salary, 0);
	EmployeeSalaryData* ESD_ptr = company_employees.find(company_employees.getRoot(), ESD)->data;
	company_employees.remove(company_employees.getRoot(), ESD_ptr);
	
}

bool ActiveCompaniesData::operator<(const ActiveCompaniesData& other) const
{
	return (this->company_id < other.company_id);
}

bool ActiveCompaniesData::operator>(const ActiveCompaniesData& other) const
{
	return (this->company_id > other.company_id);
}

bool ActiveCompaniesData::operator==(const ActiveCompaniesData& other) const
{
	return (this->company_id == other.company_id);
}



