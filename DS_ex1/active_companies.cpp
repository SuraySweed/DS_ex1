#include "active_companies.h"

ActiveCompaniesData::ActiveCompaniesData(int company_id) : company_id(company_id), 
	employeesBySalary(AVLTree<EmployeeSalaryData>()), employeesByID(AVLTree<EmployeeIdData>()), 
	highestSalary(nullptr), numberOfEmployees(0) {}

ActiveCompaniesData::ActiveCompaniesData(const ActiveCompaniesData& active_companies_data) : 
	company_id(active_companies_data.company_id),
	employeesBySalary(AVLTree<EmployeeSalaryData>(active_companies_data.employeesBySalary)),
	employeesByID(AVLTree<EmployeeIdData>(active_companies_data.employeesByID)), 
	highestSalary(active_companies_data.highestSalary), numberOfEmployees(active_companies_data.numberOfEmployees) {}

ActiveCompaniesData::~ActiveCompaniesData() {}

void ActiveCompaniesData::setHighestSalary(EmployeeSalaryData* highest_salary)
{
	highestSalary = highest_salary;
}

bool ActiveCompaniesData::removeEmployee(int employeeID, int salary)
{
	EmployeeSalaryData ESD(employeeID, 0, salary, 0);
	EmployeeSalaryData* ESD_ptr = employeesBySalary.find(employeesBySalary.getRoot(), ESD)->data;

	EmployeeIdData EID(employeeID, 0, 0, 0);
	EmployeeIdData* EID_ptr = employeesByID.find(employeesByID.getRoot(), EID)->data;

	if (employeesBySalary.remove(employeesBySalary.getRoot(), ESD_ptr) && employeesByID.remove(employeesByID.getRoot(), EID_ptr)) {
		numberOfEmployees--;
		if (numberOfEmployees != 0) {
			setHighestSalary(employeesBySalary.getMax(employeesBySalary.getRoot())->data);
		}
		else {
			highestSalary = nullptr;
		}
		return true;
	}

	return false;
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



