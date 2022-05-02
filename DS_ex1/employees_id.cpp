#include "employees_id.h"

EmployeeIdData::EmployeeIdData(int employeeID, int employerID, int salary, int grade) : 
	employee_id(employeeID), employer_id(employerID), salary(salary), grade(grade) {}

EmployeeIdData::EmployeeIdData(const EmployeeIdData& employeeIdData) :
	employee_id(employeeIdData.employee_id), employer_id(employeeIdData.employer_id),
	salary(employeeIdData.salary), grade(employeeIdData.grade) {}
/*
EmployeeIdData::~EmployeeIdData() {}
*/
EmployeeIdData& EmployeeIdData::operator=(const EmployeeIdData& emploee_id_data)
{
	if (this == &emploee_id_data) {
		return *this;
	}
	employee_id = emploee_id_data.employee_id;
	employer_id = emploee_id_data.employer_id;
	salary = emploee_id_data.salary;
	grade = emploee_id_data.grade;

	return *this;
}

bool EmployeeIdData::operator<(const EmployeeIdData& other) const
{
	return (this->employee_id < other.employee_id);
}

bool EmployeeIdData::operator>(const EmployeeIdData& other) const
{
	return (this->employee_id > other.employee_id);
}

bool EmployeeIdData::operator==(const EmployeeIdData& other) const
{
	return (this->employee_id == other.employee_id);
}
