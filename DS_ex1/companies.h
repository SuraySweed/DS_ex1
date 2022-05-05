#ifndef COMPANIES_H
#define COMPANIES_H

#include <iostream>
#include "employees_id.h"
#include "avl_tree.h"

class CompanyData {
private:
	int company_id;
	int value;

public:
	CompanyData(int companyID, int value);
	CompanyData(const CompanyData& company_data);
	~CompanyData();
	CompanyData& operator=(const CompanyData&);

	int getCompanyID() { return company_id; }
	int getValue() { return value; }
	int getCompanyValue() { return value; }
	void setValue(int newValue) { value = newValue; }

	bool operator<(const CompanyData& other) const;
	bool operator>(const CompanyData& other) const;
	bool operator==(const CompanyData& other) const;
};

#endif //COMPANIES_H_
