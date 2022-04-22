#ifndef COMPANIES_H
#define COMPANIES_H

#include <iostream>
#include "employees_id.h"
#include "avl_tree.h"

class CompanyData {
private:
	int company_id;
	int employees_number;
	int value;
	AVLTree<EmployeeIdData> company_employees; 

public:
	CompanyData(int companyID, int employeesNumber, int value);
	CompanyData(const CompanyData& company_data);
	~CompanyData();
	CompanyData& operator=(const CompanyData&);

	bool operator<(const CompanyData& other) const;
	bool operator>(const CompanyData& other) const;
	bool operator==(const CompanyData& other) const;
};

#endif //COMPANIES_H_
