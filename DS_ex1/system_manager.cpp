#include "system_manager.h"
#include "library1.h"

SystemManager::SystemManager() : employeesTreeByID(AVLTree<EmployeeIdData>()), 
	employeesTreeBySalary(AVLTree<EmployeeSalaryData>()), companiesTreeByID(AVLTree<CompanyData>()), 
	activeCompaniesTree(AVLTree<ActiveCompaniesData>()), numberOfEmployees(0), numberOfCompanies(0), highestSalaryAll(nullptr) {}

SystemManager::SystemManager(const SystemManager& system_manager) : 
	employeesTreeByID(AVLTree<EmployeeIdData>(system_manager.employeesTreeByID)), 
	employeesTreeBySalary(AVLTree<EmployeeSalaryData>(system_manager.employeesTreeBySalary)),
	companiesTreeByID(AVLTree<CompanyData>(system_manager.companiesTreeByID)),
	activeCompaniesTree(AVLTree<ActiveCompaniesData>(system_manager.activeCompaniesTree)),
	numberOfEmployees(system_manager.numberOfEmployees), numberOfCompanies(system_manager.numberOfCompanies), 
	highestSalaryAll(new EmployeeSalaryData(*(system_manager.highestSalaryAll))) {}

SystemManager::~SystemManager() {}

StatusType SystemManager::AddCompany(int CompanyID, int Value)
{
	if (CompanyID <= 0 || Value <= 0) {
		return INVALID_INPUT;
	}

	CompanyData CD = CompanyData(CompanyID, 0, Value);

	if (companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}

	if (companiesTreeByID.insert(companiesTreeByID.getRoot(), &CD)) {
		numberOfCompanies++;
		return SUCCESS;
	}
}

StatusType SystemManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
	if (EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade <= 0) {
		return INVALID_INPUT;
	}

	EmployeeIdData EID(EmployeeID, CompanyID, Salary, Grade);
	CompanyData CD(CompanyID, 0, 0); 
	EmployeeSalaryData ESD(EmployeeID, CompanyID, Salary, Grade); 

	if (employeesTreeByID.find(employeesTreeByID.getRoot(), EID) ||
		!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}

	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;

	if (employeesTreeByID.insert(employeesTreeByID.getRoot(), &EID) && 
		employeesTreeBySalary.insert(employeesTreeBySalary.getRoot(), &ESD) &&
		CD_ptr->getEmployeesTreeInCompany().insert(CD_ptr->getEmployeesTreeInCompany().getRoot(), &EID)) {

		numberOfEmployees++;
		CD_ptr->incEmployeesNumber();
		highestSalaryAll = employeesTreeBySalary.getMax(employeesTreeBySalary.getRoot())->data;
	}
	
	//ActiveEmployeeData AED(EmployeeID, Salary); 
	ActiveCompaniesData ACD(CompanyID);
	if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
		activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &ACD);
	}

	//problem in 2nd line
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	ACD_ptr->getActiveCompanyEmployees().insert(ACD_ptr->getActiveCompanyEmployees().getRoot(), &ESD);
	ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployees().getMax(ACD_ptr->getActiveCompanyEmployees().getRoot())->data);

	return SUCCESS;
}

StatusType SystemManager::RemoveCompany(int CompanyID)
{
	if (CompanyID <= 0) {
		return INVALID_INPUT;
	}

	CompanyData CD(CompanyID, 0, 0);
	if (!companiesTreeByID.find(companiesTreeByID.getRoot(), CD) || 
		((companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data)->getEmployeesNumber()) > 0) {
		return FAILURE;
	}
	companiesTreeByID.remove(companiesTreeByID.getRoot(), &CD);
	return SUCCESS;
}

/// NEEEDDD TOOOO DOOOOO
StatusType SystemManager::RemoveEmployee(int EmployeeID)
{
	return StatusType();
}

StatusType SystemManager::GetCompanyInfo(int CompanyID, int* Value, int* NumEmployees)
{
	if (!Value || !NumEmployees || CompanyID <= 0)
	{
		return INVALID_INPUT;
	}
	CompanyData CD(CompanyID, 0, 0);
	if (companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}
	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;
	*Value = CD_ptr->getCompanyValue();
	*NumEmployees = CD_ptr->getEmployeesNumber();
	return SUCCESS;
}

StatusType SystemManager::GetEmployeeInfo(int EmployeeID, int* EmployerID, int* Salary, int* Grade)
{
	if (!EmployerID || !Salary || !Grade || EmployeeID <= 0) {
		return INVALID_INPUT;
	}
	EmployeeIdData EID(EmployeeID, 0, 0, 0);
	if (!(employeesTreeByID.find(employeesTreeByID.getRoot(), EID))) {
		return FAILURE;
	}
	EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	*EmployerID = EID_ptr->getEmployerID();
	*Salary = EID_ptr->getEmployeeSalay();
	*Grade = EID_ptr->getEmployeeGrade();

	return SUCCESS;
}




