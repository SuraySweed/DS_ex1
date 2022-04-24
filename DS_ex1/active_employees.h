#ifndef ACTIVE_EMPLOYEES_H
#define ACTIVE_EMPLOYEES_H

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

#endif //ACTIVE_EMPLOYEES_H_