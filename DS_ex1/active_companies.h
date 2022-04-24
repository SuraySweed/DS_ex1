#ifndef ACTIVE_COMPANIES_H
#define ACTIVE_COMPANIES_H

#include "avl_tree.h"
#include "employees_id.h"
#include "employees_salary.h"
#include "active_employees.h"

/*
class ActiveEmployeeData {
private:
	int employee_id;
	int salary;

public:
	ActiveEmployeeData(int employee_id, int salary) : employee_id(employee_id), salary(salary) {}
	ActiveEmployeeData(ActiveEmployeeData& active_employee_data) : employee_id(active_employee_data.employee_id), 
		salary(active_employee_data.salary) {}

	~ActiveEmployeeData() {}

	bool operator>(const ActiveEmployeeData& other) const {
		if (this->salary > other.salary) {
			return true;
		}
		else if (this->salary == other.salary) {
			return (this->employee_id < other.employee_id);
		}
		return false;
	}
	bool operator<(const ActiveEmployeeData& other) const {
		if (this->salary < other.salary) {
			return true;
		}
		else if (this->salary == other.salary) {
			return (this->employee_id > other.employee_id);
		}
		return false;
	}
	
	bool operator==(const ActiveEmployeeData& other) const {
		return ((this->salary == other.salary) && (this->employee_id == other.employee_id));
	}
};
*/
class ActiveCompaniesData {
private:
	int company_id;
	AVLTree<ActiveEmployeeData> company_employees; //by id

public:
	ActiveCompaniesData(int company_id);
	ActiveCompaniesData(const ActiveCompaniesData& active_companies_data);
	~ActiveCompaniesData();

	AVLTree<ActiveEmployeeData>& getActiveCompanyEmployees() { return company_employees; }

	bool operator<(const ActiveCompaniesData& other) const;
	bool operator>(const ActiveCompaniesData& other) const;
	bool operator==(const ActiveCompaniesData& other) const;
};

#endif //ACTIVE_COMPANIES_H_
