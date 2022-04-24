#include "active_companies.h"

ActiveCompaniesData::ActiveCompaniesData(int company_id) : company_id(company_id), 
	company_employees(AVLTree<ActiveEmployeeData>()){}

ActiveCompaniesData::ActiveCompaniesData(const ActiveCompaniesData& active_companies_data) : 
	company_id(active_companies_data.company_id),
	company_employees(AVLTree<ActiveEmployeeData>(active_companies_data.company_employees)) {}

ActiveCompaniesData::~ActiveCompaniesData() {}

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



