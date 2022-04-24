#include "library1.h"
#include "system_manager.h"

void* Init()
{
	SystemManager* DS = new SystemManager();
	return (void*)DS;
}

/*
//check if DS is nullptr --- neeeeeddddd
StatusType AddCompany(void* DS, int CompanyID, int Value)
{
	return ((SystemManager*)DS)->AddCompany(CompanyID, Value);
}

StatusType AddEmployee(void* DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
	return ((SystemManager*)DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
}

StatusType RemoveCompany(void* DS, int CompanyID)
{
	return ((SystemManager*)DS)->RemoveCompany(CompanyID);
}

StatusType RemoveEmployee(void* DS, int EmployeeID)
{
	return StatusType();
}

StatusType GetCompanyInfo(void* DS, int CompanyID, int* Value, int* NumEmployees)
{
	return StatusType();
}

StatusType GetEmployeeInfo(void* DS, int EmployeeID, int* EmployerID, int* Salary, int* Grade)
{
	return StatusType();
}

StatusType IncreaseCompanyValue(void* DS, int CompanyID, int ValueIncrease)
{
	return StatusType();
}

StatusType PromoteEmployee(void* DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
	return StatusType();
}

StatusType HireEmployee(void* DS, int EmployeeID, int NewCompanyID)
{
	return StatusType();
}

StatusType AcquireCompany(void* DS, int AcquirerID, int TargetID, double Factor)
{
	return StatusType();
}

StatusType GetHighestEarner(void* DS, int CompanyID, int* EmployeeID)
{
	return StatusType();
}

StatusType GetAllEmployeesBySalary(void* DS, int CompanyID, int** Employees, int* NumOfEmployees)
{
	return StatusType();
}

StatusType GetHighestEarnerInEachCompany(void* DS, int NumOfCompanies, int** Employees)
{
	return StatusType();
}

StatusType GetNumEmployeesMatching(void* DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary, int MinGrade, int* TotalNumOfEmployees, int* NumOfEmployees)
{
	return StatusType();
}

void Quit(void** DS)
{
}


*/