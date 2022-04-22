#ifndef ACTIVE_COMPANIES_H
#define ACTIVE_COMPANIES_H

#include "avl_tree.h"
#include "employees_id.h"
#include "employees_salary.h"

class ActiveCompaniesData {
private:
	int company_id;
	int employees_number;
	int value;
	AVLTree<EmployeeIdData> company_employees; //by salary

public:
	ActiveCompaniesData();
	ActiveCompaniesData(const ActiveCompaniesData& active_companies_data);
	~ActiveCompaniesData();

	bool operator<(const ActiveCompaniesData& other) const;
	bool operator>(const ActiveCompaniesData& other) const;
	bool operator==(const ActiveCompaniesData& other) const;
};

#endif //ACTIVE_COMPANIES_H_
