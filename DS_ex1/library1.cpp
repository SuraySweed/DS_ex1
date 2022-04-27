#include "library1.h"
#include "system_manager.h"

void* Init()
{
	SystemManager* DS = new SystemManager();
	return (void*)DS;
}


StatusType AddCompany(void* DS, int CompanyID, int Value)
{
	if(DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->AddCompany(CompanyID, Value);
}

StatusType AddEmployee(void* DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
	if(DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
}

StatusType RemoveCompany(void* DS, int CompanyID)
{
	if(DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->RemoveCompany(CompanyID);
}

StatusType RemoveEmployee(void* DS, int EmployeeID)
{
	if(DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->RemoveEmployee(EmployeeID);
}

StatusType GetCompanyInfo(void* DS, int CompanyID, int* Value, int* NumEmployees)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->GetCompanyInfo(CompanyID, Value, NumEmployees);
}

StatusType GetEmployeeInfo(void* DS, int EmployeeID, int* EmployerID, int* Salary, int* Grade)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
}

StatusType IncreaseCompanyValue(void* DS, int CompanyID, int ValueIncrease)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
}

StatusType PromoteEmployee(void* DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
}

StatusType HireEmployee(void* DS, int EmployeeID, int NewCompanyID)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->HireEmployee(EmployeeID, NewCompanyID);
}

StatusType AcquireCompany(void* DS, int AcquirerID, int TargetID, double Factor)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->AcquireCompany(AcquirerID, TargetID, Factor);
}

StatusType GetHighestEarner(void* DS, int CompanyID, int* EmployeeID)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->GetHighestEarner(CompanyID, EmployeeID);
}

StatusType GetAllEmployeesBySalary(void* DS, int CompanyID, int** Employees, int* NumOfEmployees)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
}

StatusType GetHighestEarnerInEachCompany(void* DS, int NumOfCompanies, int** Employees)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
}
/*
StatusType GetNumEmployeesMatching(void* DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade, int* TotalNumOfEmployees, int* NumOfEmployees)
{
	if (DS == NULL) return INVALID_INPUT;
	return ((SystemManager*)DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary,
		MinGrade, TotalNumOfEmployees, NumOfEmployees);
}
*/
void Quit(void** DS)
{
}


