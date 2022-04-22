#include "companies.h"

CompanyData::CompanyData(int companyID, int employeesNumber, int value) :
	company_id(companyID), employees_number(employeesNumber), value(value),
	company_employees(AVLTree<EmployeeIdData>()) {}

CompanyData::CompanyData(const CompanyData& company_data) : company_id(company_data.company_id),
	employees_number(company_data.employees_number), value(company_data.value),
	company_employees(AVLTree<EmployeeIdData>(company_data.company_employees)) {}

CompanyData::~CompanyData() {}

CompanyData& CompanyData::operator=(const CompanyData& company_data)
{
	if (this == &company_data) {
		return *this;
	}
	company_id = company_data.company_id;
	employees_number = company_data.employees_number;
	company_employees = company_data.company_employees;

	return *this;
}

bool CompanyData::operator<(const CompanyData& other) const
{
	return (this->company_id < other.company_id);
}

bool CompanyData::operator>(const CompanyData& other) const
{
	return (this->company_id > other.company_id);
}

bool CompanyData::operator==(const CompanyData& other) const
{
	return (this->company_id == other.company_id);
}
