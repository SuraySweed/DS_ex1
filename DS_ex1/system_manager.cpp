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

	CompanyData CD = CompanyData(CompanyID, Value);

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
	CompanyData CD(CompanyID, 0); 
	EmployeeSalaryData ESD(EmployeeID, CompanyID, Salary, Grade); 

	if (employeesTreeByID.find(employeesTreeByID.getRoot(), EID) ||
		!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}

	ActiveCompaniesData ACD(CompanyID);
	if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
		activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &ACD);
	}
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;

	if (employeesTreeByID.insert(employeesTreeByID.getRoot(), &EID) && 
		employeesTreeBySalary.insert(employeesTreeBySalary.getRoot(), &ESD) &&
		ACD_ptr->getActiveCompanyEmployeesByID().insert(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), &EID) &&
		ACD_ptr->getActiveCompanyEmployeesBySalary().insert(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), &ESD)) {

		numberOfEmployees++;
		ACD_ptr->incNumberOfEmployees(); //for specific company
		highestSalaryAll = employeesTreeBySalary.getMax(employeesTreeBySalary.getRoot())->data;
	}
	
	ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);

	return SUCCESS;
}

StatusType SystemManager::RemoveCompany(int CompanyID)
{
	if (CompanyID <= 0) {
		return INVALID_INPUT;
	}

	CompanyData CD(CompanyID, 0);
	ActiveCompaniesData ACD(CompanyID);

	if (!companiesTreeByID.find(companiesTreeByID.getRoot(), CD) || 
		activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
		return FAILURE;
	}
	companiesTreeByID.remove(companiesTreeByID.getRoot(), &CD);
	numberOfCompanies--;

	return SUCCESS;
}

StatusType SystemManager::RemoveEmployee(int EmployeeID)
{
	if (EmployeeID <= 0)
		return INVALID_INPUT;

	//check if employee exist
	EmployeeIdData EID(EmployeeID, 0, 0, 0);
	if (!employeesTreeByID.find(employeesTreeByID.getRoot(), EID)) {
		return FAILURE;
	}
	EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	//get the employees pionters
	EmployeeSalaryData ESD(EmployeeID, 0, EID_ptr->getSalary(), 0);
	EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD)->data;
	CompanyData CD(ESD_ptr->getEmployerID(), 0);
	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;
	ActiveCompaniesData ACD(ESD_ptr->getEmployerID());
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;

	//remove from employees trees
	employeesTreeByID.remove(employeesTreeByID.getRoot(), EID_ptr);
	employeesTreeBySalary.remove(employeesTreeBySalary.getRoot(), ESD_ptr);
	ACD_ptr->removeEmployee(EmployeeID, ESD_ptr->getSalary());
	//ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployees().getMax(ACD_ptr->getActiveCompanyEmployees().getRoot())->data);

	//check if the company has no employees
	if (ACD_ptr->getNumberOfEmployees() == 0) {
		activeCompaniesTree.remove(activeCompaniesTree.getRoot(), ACD_ptr);
	}
	highestSalaryAll = employeesTreeBySalary.getMax(employeesTreeBySalary.getRoot())->data;
	numberOfEmployees--;

	return SUCCESS;
}

StatusType SystemManager::GetCompanyInfo(int CompanyID, int* Value, int* NumEmployees)
{
	if (!Value || !NumEmployees || CompanyID <= 0)
	{
		return INVALID_INPUT;
	}

	CompanyData CD(CompanyID, 0);
	if (!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}

	ActiveCompaniesData ACD(CompanyID);
	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;
	if (activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
		ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
		*NumEmployees = ACD_ptr->getNumberOfEmployees();
	}
	else {
		*NumEmployees = 0;
	}
	*Value = CD_ptr->getCompanyValue();

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

	//get the company data and update it
	CompanyData CD(CompanyID, 0);
	if (!companiesTreeByID.find(companiesTreeByID.getRoot(), CD))
		return FAILURE;

	CompanyData* CD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), CD)->data;
	CD_ptr->setValue(CD_ptr->getCompanyValue() + ValueIncrease);

	return SUCCESS;
}

StatusType SystemManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
	if (EmployeeID <= 0 || SalaryIncrease <= 0) {
		return INVALID_INPUT;
	}
	EmployeeIdData EID(EmployeeID, 0, 0, 0);

	if (!employeesTreeByID.find(employeesTreeByID.getRoot(), EID))
		return FAILURE;
	EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	EID_ptr->setSalary(EID_ptr->getSalary() + SalaryIncrease);
	if (BumpGrade > 0)
		EID_ptr->setGrade(EID_ptr->getGrade() + 1);

	EmployeeSalaryData ESD(EmployeeID, 0, 0, 0);
	EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD)->data;

	ESD_ptr->setSalary(ESD_ptr->getSalary() + SalaryIncrease);
	highestSalaryAll = employeesTreeBySalary.getMax(employeesTreeBySalary.getRoot())->data;

	ActiveCompaniesData ACD(ESD_ptr->getEmployerID());
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	EmployeeSalaryData* ESDInCompany_ptr = ACD_ptr->getActiveCompanyEmployeesBySalary().find(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD)->data;
	ESDInCompany_ptr->setSalary(ESDInCompany_ptr->getSalary() + SalaryIncrease);
	ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
	EmployeeIdData* EIDInCompany_ptr = ACD_ptr->getActiveCompanyEmployeesByID().find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID)->data;
	EIDInCompany_ptr->setSalary(EIDInCompany_ptr->getSalary() + SalaryIncrease);

	if (BumpGrade > 0) {
		ESD_ptr->setGrade(ESD_ptr->getGrade() + 1);
		EIDInCompany_ptr->setGrade(EIDInCompany_ptr->getGrade() + 1);
		ESDInCompany_ptr->setGrade(ESDInCompany_ptr->getGrade() + 1);
	}

	return SUCCESS;
}

StatusType SystemManager::HireEmployee(int EmployeeID, int NewCompanyID)
{
	if (EmployeeID <= 0 || NewCompanyID <= 0) {
		return INVALID_INPUT;
	}
	
	EmployeeIdData EID(EmployeeID, 0, 0, 0);
	CompanyData CD(NewCompanyID, 0);
	ActiveCompaniesData ACD(NewCompanyID);

	if (!employeesTreeByID.find(employeesTreeByID.getRoot(), EID) ||
		!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}

	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;

	if (ACD_ptr != nullptr) {
		AVLTree<EmployeeIdData> CompanyEmployees = ACD_ptr->getActiveCompanyEmployeesByID();
		if (CompanyEmployees.find(CompanyEmployees.getRoot(), EID))
			return FAILURE;
	}
	else {
		activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &ACD);
		ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	}

	//update the employees big trees
	EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	EmployeeSalaryData ESD(EmployeeID, 0, EID.getSalary(), 0);
	EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD)->data;
	int oldEmployerID = EID_ptr->getEmployerID();
	EID_ptr->setEmployerID(NewCompanyID);
	ESD_ptr->setEmployerID(NewCompanyID);

	//update employees trees in comapny
	ACD_ptr->getActiveCompanyEmployeesByID().insert(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID_ptr);
	ACD_ptr->getActiveCompanyEmployeesBySalary().insert(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD_ptr);
	ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
	ACD_ptr->incNumberOfEmployees();
	
	ActiveCompaniesData old_ACD(oldEmployerID);
	ActiveCompaniesData* old_ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), old_ACD)->data;
	int salary = EID_ptr->getSalary();
	old_ACD_ptr->removeEmployee(EmployeeID, salary);
	if (old_ACD_ptr->getNumberOfEmployees() == 0) {
		activeCompaniesTree.remove(activeCompaniesTree.getRoot(), old_ACD_ptr);
	}
	return SUCCESS;
}

StatusType SystemManager::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
	if (AcquirerID <= 0 || TargetID <= 0 || TargetID == AcquirerID || Factor < 1.00)
		return INVALID_INPUT;

	//updates in companyTreeByID
	CompanyData acquirerCD(AcquirerID,0);
	CompanyData* acquirerCD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), acquirerCD)->data;
	CompanyData targetCD(TargetID, 0);
	CompanyData* targetCD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), targetCD)->data;

	if (acquirerCD_ptr == nullptr || targetCD_ptr == nullptr)
		return FAILURE;

	int targetValue = targetCD_ptr->getValue();
	int acquirerValue = acquirerCD_ptr->getValue();

	if (acquirerValue < targetValue * 10) 
		return FAILURE;

	acquirerCD_ptr->setValue((acquirerValue + targetValue) * Factor);
	companiesTreeByID.remove(companiesTreeByID.getRoot(), targetCD_ptr);
	numberOfCompanies--;

	//updates at active companies tree
	ActiveCompaniesData targetACD(TargetID);
	ActiveCompaniesData acquirerACD(AcquirerID);

	if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), targetACD)) {
		ActiveCompaniesData* targetACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), targetACD)->data;

		if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), acquirerACD)) {
			activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &acquirerACD);

		}
		else {

		}
	}

	ActiveCompaniesData* acquirerACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), acquirerACD)->data;
	
	return SUCCESS;
}

StatusType SystemManager::GetHighestEarner(int CompanyID, int* EmployeeID)
{
	if (EmployeeID == nullptr || CompanyID == 0)
		return FAILURE;

	if (CompanyID < 0) {
		if (numberOfEmployees == 0) {
			return FAILURE;
		}
		*EmployeeID = highestSalaryAll->getEmployeeID();
	}
	else {
		ActiveCompaniesData ACD(CompanyID);
		if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD))
			return FAILURE;
		ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
		*EmployeeID = ACD_ptr->getHighestSalary()->getEmployeeID();
	}

	return SUCCESS;
}







