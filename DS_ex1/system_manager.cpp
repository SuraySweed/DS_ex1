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

StatusType SystemManager::RemoveEmployee(int EmployeeID)
{
	if (EmployeeID <= 0)
		return INVALID_INPUT;

	//check if employee exist
	EmployeeIdData EID(EmployeeID, 0, 0, 0);
	EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	if (EID_ptr == nullptr)
		return FAILURE;

	//get the employees pionters
	EmployeeSalaryData ESD(EmployeeID, 0, EID_ptr->getSalary(), 0);
	EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD)->data;
	CompanyData CD(ESD_ptr->getEmployerID(), 0, 0);
	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;
	ActiveCompaniesData ACD(ESD_ptr->getEmployerID());
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;

	//remove from employees trees
	employeesTreeByID.remove(employeesTreeByID.getRoot(), EID_ptr);
	employeesTreeBySalary.remove(employeesTreeBySalary.getRoot(), ESD_ptr);
	CD_ptr->removeEmployee(EmployeeID);
	ACD_ptr->removeEmployee(EmployeeID, ESD_ptr->getSalary());

	//check if the company has no employees
	if (CD_ptr->getEmployeesNumber() == 0) {
		activeCompaniesTree.remove(activeCompaniesTree.getRoot(), ACD_ptr);
	}

	numberOfEmployees--;
	return SUCCESS;

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
	*Salary = EID_ptr->getSalary();
	*Grade = EID_ptr->getGrade();

	return SUCCESS;
}

StatusType SystemManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
{
	if (CompanyID <= 0 || ValueIncrease <= 0)
		return INVALID_INPUT;

	//get the company data adn update it
	CompanyData CD(CompanyID, 0, 0);
	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;
	if (CD_ptr == nullptr)
		return FAILURE;

	CD_ptr->setValue(CD_ptr->getCompanyValue() + ValueIncrease);

	return SUCCESS;
}

StatusType SystemManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
	if (EmployeeID <= 0 || SalaryIncrease <= 0) {
		return INVALID_INPUT;
	}
}







