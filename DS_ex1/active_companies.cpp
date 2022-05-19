#include "active_companies.h"

ActiveCompaniesData::ActiveCompaniesData(int company_id) : company_id(company_id), 
	employeesBySalary(AVLTree<EmployeeSalaryData>()), employeesByID(AVLTree<EmployeeIdData>()), 
	highestSalary(nullptr), numberOfEmployees(0) {}

ActiveCompaniesData::ActiveCompaniesData(const ActiveCompaniesData& active_companies_data) : 
	company_id(active_companies_data.company_id),
	employeesBySalary(AVLTree<EmployeeSalaryData>(active_companies_data.employeesBySalary)),
	employeesByID(AVLTree<EmployeeIdData>(active_companies_data.employeesByID)), 
	numberOfEmployees(active_companies_data.numberOfEmployees) {
		if(employeesBySalary.getRoot()) setHighestSalary(employeesBySalary.getMax(employeesBySalary.getRoot())->data);}

ActiveCompaniesData& ActiveCompaniesData::operator=(ActiveCompaniesData& other)
{
	if (this == &other) {
		return *this;
	}
	company_id = other.company_id;
	employeesBySalary = other.employeesBySalary;
	employeesByID = other.employeesByID;
	if(employeesBySalary.getRoot())
		setHighestSalary(employeesBySalary.getMax(employeesBySalary.getRoot())->data);
	numberOfEmployees = other.numberOfEmployees;

	return *this;
}

void ActiveCompaniesData::setHighestSalary(EmployeeSalaryData* highest_salary)
{
	highestSalary = highest_salary;
}

bool ActiveCompaniesData::removeEmployee(int employeeID, int salary)
{
	EmployeeSalaryData ESD(employeeID, 0, salary, 0);
	if (!employeesBySalary.find(employeesBySalary.getRoot(), ESD)) return false;
	EmployeeSalaryData* ESD_ptr = employeesBySalary.find(employeesBySalary.getRoot(), ESD)->data;

	EmployeeIdData EID(employeeID, 0, 0, 0);
	if (!employeesByID.find(employeesByID.getRoot(), EID)) return false;
	EmployeeIdData* EID_ptr = employeesByID.find(employeesByID.getRoot(), EID)->data;

	if (numberOfEmployees == 1) {
		if (!(employeesBySalary.remove(employeesBySalary.getRoot(), ESD_ptr)) &&
			!(employeesByID.remove(employeesByID.getRoot(), EID_ptr))) {
			numberOfEmployees--;
			highestSalary = nullptr;
			return true;
		}
	}
	else {
		if ((employeesBySalary.remove(employeesBySalary.getRoot(), ESD_ptr)) &&
			(employeesByID.remove(employeesByID.getRoot(), EID_ptr))) {
			numberOfEmployees--;
			setHighestSalary((employeesBySalary.getMax(employeesBySalary.getRoot()))->data);
			return true;
		}
	}

	return false;
}

void ActiveCompaniesData::setActiveCompanyEmployeesByID(AVLTree<EmployeeIdData>& other)
{
	employeesByID = other;
}

void ActiveCompaniesData::setActiveCompanyEmployeesBySalary(AVLTree<EmployeeSalaryData>& other)
{
	employeesBySalary = other;
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



