#include "employees_salary.h"

EmployeeSalaryData::EmployeeSalaryData(int employeeID, int employerID, int salary, int grade) :	
	employee_id(employeeID), employer_id(new int(employerID)), salary(salary), grade(grade) {}

EmployeeSalaryData::EmployeeSalaryData(const EmployeeSalaryData& EmployeeSalaryData) :
	employee_id(EmployeeSalaryData.employee_id), employer_id(new int(*(EmployeeSalaryData.employer_id))),
	salary(EmployeeSalaryData.salary), grade(EmployeeSalaryData.grade) {}

EmployeeSalaryData::~EmployeeSalaryData()
{
	if (employer_id && *employer_id > 0) {
		delete employer_id;
	}
	employer_id = nullptr;
}

EmployeeSalaryData& EmployeeSalaryData::operator=(EmployeeSalaryData& employee_salary_data)
{
	if (this == &employee_salary_data) {
		return *this;
	}
	employee_id = employee_salary_data.employee_id;
	salary = employee_salary_data.salary;
	grade = employee_salary_data.grade;
	//delete this->employer_id;
	this->employer_id = employee_salary_data.employer_id;
	//employee_salary_data.employer_id = nullptr;
	return *this;
}

bool EmployeeSalaryData::operator<(const EmployeeSalaryData& other) const
{
	if (this->salary < other.salary) {
		return true;
	}
	else if (this->salary == other.salary) {
		return (this->employee_id > other.employee_id);
	}
	return false;
}

bool EmployeeSalaryData::operator>(const EmployeeSalaryData& other) const
{
	if (this->salary > other.salary) {
		return true;
	}
	else if (this->salary == other.salary) {
		return (this->employee_id < other.employee_id);
	}
	return false;
}

bool EmployeeSalaryData::operator==(const EmployeeSalaryData& other) const
{
	return((this->salary == other.salary) && (this->employee_id == other.employee_id));
}
