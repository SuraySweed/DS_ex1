#include "companies.h"

CompanyData::CompanyData(int companyID, int value) :
	company_id(companyID), value(value) {}

/*
CompanyData::CompanyData(const CompanyData& company_data) : company_id(company_data.company_id), value(company_data.value) {}
*/
/*
CompanyData& CompanyData::operator=(const CompanyData& company_data)
{
	if (this == &company_data) {
		return *this;
	}
	company_id = company_data.company_id;

	return *this;
}
*/
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
