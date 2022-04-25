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



