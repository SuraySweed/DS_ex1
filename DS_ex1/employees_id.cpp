#include "employees_id.h"

EmployeeIdData::EmployeeIdData(int employeeID, int employerID, int salary, int grade) : 
	employee_id(employeeID), employer_id(employerID),employerID_ptr(nullptr), salary(salary), grade(grade) {}

EmployeeIdData::EmployeeIdData(const EmployeeIdData& employeeIdData) :
	employee_id(employeeIdData.employee_id), employer_id(employeeIdData.employer_id),
	employerID_ptr(employeeIdData.employerID_ptr), salary(employeeIdData.salary), grade(employeeIdData.grade) {}


EmployeeIdData& EmployeeIdData::operator=(EmployeeIdData& employee_id_data)
{
	if (this == &employee_id_data) {
		return *this;
	}
	employee_id = employee_id_data.employee_id;
	salary = employee_id_data.salary;
	grade = employee_id_data.grade;
	employer_id = employee_id_data.employer_id;
	employerID_ptr = employee_id_data.employerID_ptr;

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
