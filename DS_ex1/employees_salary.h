#ifndef EMPLOYEES_SALARY_H_
#define EMPLOYEES_SALARY_H_

class EmployeeSalaryData {
private:
	int employee_id;
	int employer_id;
	int salary;
	int grade;

public:
	EmployeeSalaryData(int employeeID, int employerID, int salary, int grade);
	EmployeeSalaryData(const EmployeeSalaryData& EmployeeSalaryData);
	~EmployeeSalaryData();
	EmployeeSalaryData& operator=(const EmployeeSalaryData&);
	int getEmployerID() { return employer_id; }
	int getSalary() { return salary; }
	int getGrade() { return grade; }

	void setSalary(int newSalary) { salary = newSalary; }
	void setGrade(int newGrade) { grade = newGrade; }
	void setEmployerID(int newCompanyID) { employer_id = newCompanyID; }

	bool operator<(const EmployeeSalaryData& other) const;
	bool operator>(const EmployeeSalaryData& other) const;
	bool operator==(const EmployeeSalaryData& other) const;
};

#endif //EMPLOYEES_SALARY_H_