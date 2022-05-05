#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include "avl_tree.h"
#include "employees_id.h"
#include "employees_salary.h"
#include "companies.h"
#include "active_companies.h"
#include "library1.h"

class SystemManager {
private:
	AVLTree<EmployeeIdData> employeesTreeByID;
	AVLTree<EmployeeSalaryData> employeesTreeBySalary;
	AVLTree<CompanyData> companiesTreeByID;
	AVLTree<ActiveCompaniesData> activeCompaniesTree;

	int numberOfEmployees;
	int numberOfCompanies;
    EmployeeSalaryData* highestSalaryAll;
    void updateEmployerIDByIDInCompany(Node<EmployeeIdData>* root, int companyID);
    void updateEmployerIDBySalaryInCompany(Node<EmployeeSalaryData>* root, int companyID);

public:
	SystemManager();
	SystemManager(const SystemManager& system_manager);
    ~SystemManager() = default;

    StatusType AddCompany(int CompanyID, int Value);
    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
    StatusType RemoveCompany(int CompanyID);
    StatusType RemoveEmployee(int EmployeeID);
    StatusType GetCompanyInfo(int CompanyID, int* Value, int* NumEmployees);
    StatusType GetEmployeeInfo(int EmployeeID, int* EmployerID, int* Salary, int* Grade);
    StatusType IncreaseCompanyValue(int CompanyID, int ValueIncrease);
    StatusType PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);
    StatusType HireEmployee(int EmployeeID, int NewCompanyID);
    StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);
    StatusType GetHighestEarner(int CompanyID, int* EmployeeID);
    StatusType GetAllEmployeesBySalary(int CompanyID, int** Employees, int* NumOfEmployees);
    StatusType GetHighestEarnerInEachCompany(int NumOfCompanies, int** Employees);
    StatusType GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, 
        int MinGrade, int* TotalNumOfEmployees, int* NumOfEmployees);
};

#endif //SYSTEM_MANAGER_H