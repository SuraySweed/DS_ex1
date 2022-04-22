#include "employees_salary.h"

EmployeeSalaryData::EmployeeSalaryData(int employeeID, int employerID, int salary, int grade) :	
	employee_id(employeeID), employer_id(employerID), salary(salary), grade(grade) {}

EmployeeSalaryData::EmployeeSalaryData(const EmployeeSalaryData& EmployeeSalaryData) :
	employee_id(EmployeeSalaryData.employee_id), employer_id(EmployeeSalaryData.employer_id),
	salary(EmployeeSalaryData.salary), grade(EmployeeSalaryData.grade) {}

EmployeeSalaryData::~EmployeeSalaryData() {}

EmployeeSalaryData& EmployeeSalaryData::operator=(const EmployeeSalaryData& emploee_salary_data)
{
	if (this == &emploee_salary_data) {
		return *this;
	}
	employee_id = emploee_salary_data.employee_id;
	employer_id = emploee_salary_data.employer_id;
	salary = emploee_salary_data.salary;
	grade = emploee_salary_data.grade;

	return *this;
}

bool EmployeeSalaryData::operator<(const EmployeeSalaryData& other) const
{
	return (this->salary < other.salary);
}

bool EmployeeSalaryData::operator>(const EmployeeSalaryData& other) const
{
	return (this->salary > other.salary);
}

bool EmployeeSalaryData::operator==(const EmployeeSalaryData& other) const
{
	return (this->salary == other.salary);
}
