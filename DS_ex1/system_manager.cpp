#include "system_manager.h"
#include "library1.h"


void SystemManager::updateEmployerIDByIDInCompany(Node<EmployeeIdData>* root, int companyID)
{
	if (!root) return;

	updateEmployerIDByIDInCompany(root->left, companyID);
	root->data->setEmployerID(companyID);
	*(root->data->getEmployerIDPtr()) = companyID;
	updateEmployerIDByIDInCompany(root->right, companyID);
}

void SystemManager::updateEmployerIDBySalaryInCompany(Node<EmployeeSalaryData>* root, int companyID)
{
	if (!root) return;

	updateEmployerIDBySalaryInCompany(root->left, companyID);
	root->data->setEmployerID(companyID);
	*(root->data->getEmployeeIDPtr()) = companyID;
	updateEmployerIDBySalaryInCompany(root->right, companyID);
}


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

/*
SystemManager::~SystemManager() {}
*/
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
	return SUCCESS;
}

StatusType SystemManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
	if (EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0) {
		return INVALID_INPUT;
	}

	//int* companyID_ptr = new int(CompanyID);

	EmployeeIdData EID(EmployeeID, CompanyID, Salary, Grade);
	CompanyData CD(CompanyID, 0); 
	EmployeeSalaryData ESD(EmployeeID, CompanyID, Salary, Grade);

	// if employee is existed in the id and salary trees
	if (employeesTreeByID.find(employeesTreeByID.getRoot(), EID) ||
		!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		//delete companyID_ptr;
		return FAILURE;
	}

	// if companyID not in active tree, insert it
	ActiveCompaniesData ACD(CompanyID);
	if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
		if (!activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &ACD)) {
			return FAILURE;
		}
	}

	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	if (employeesTreeByID.insert(employeesTreeByID.getRoot(), &EID) &&
		employeesTreeBySalary.insert(employeesTreeBySalary.getRoot(), &ESD) &&
		ACD_ptr->getActiveCompanyEmployeesByID().insert(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), &EID) &&
		ACD_ptr->getActiveCompanyEmployeesBySalary().insert(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), &ESD)) {
				
		EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
		EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD)->data;
		EmployeeIdData* EID_active_ptr = ACD_ptr->getActiveCompanyEmployeesByID().
			find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID)->data;
		EmployeeSalaryData* ESD_active_ptr = ACD_ptr->getActiveCompanyEmployeesBySalary().
			find(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD)->data;

		EID_active_ptr->setEmployerIDPtr(&(EID_ptr->getEmployerID()));
		ESD_active_ptr->setEmployerIDPtr(&(ESD_ptr->getEmployerID()));

		numberOfEmployees++;
		ACD_ptr->incNumberOfEmployees(); //for specific company
		highestSalaryAll = employeesTreeBySalary.getMax(employeesTreeBySalary.getRoot())->data;
		
		ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().
			getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
	
		return SUCCESS;
	}

	return FAILURE;
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

	//check if the employee exist
	EmployeeIdData EID(EmployeeID, 0, 0, 0);
	if (!employeesTreeByID.find(employeesTreeByID.getRoot(), EID)) {
		return FAILURE;
	}

	Node<EmployeeIdData>* EIN_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID);
	EmployeeSalaryData ESD(EmployeeID, 0, EIN_ptr->data->getSalary(), 0);
	Node<EmployeeSalaryData>* ESN_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD);
	ActiveCompaniesData ACD(EIN_ptr->data->getEmployerIDInteger());
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	int salary = ESN_ptr->data->getSalary();

	// remove employee from the active company
	if (!ACD_ptr->removeEmployee(EmployeeID, salary)) {
		return FAILURE;
	}

	int temp_employerID = 0;
	int temp_employeeID = 0;
	int temp2_employerID = 0;
	int temp2_employeeID = 0;
	int temp2_salary = 0;

	if ((EIN_ptr->left == nullptr) || (EIN_ptr->right == nullptr)) {
		Node<EmployeeIdData>* temp = EIN_ptr->left ? EIN_ptr->left : EIN_ptr->right;
		if (temp) {
			temp_employerID = temp->data->getEmployerIDInteger();
			temp_employeeID = temp->data->getEmployeeID();
		}
	}

	if ((ESN_ptr->left == nullptr) || (ESN_ptr->right == nullptr)) {
		Node<EmployeeSalaryData>* temp2 = ESN_ptr->left ? ESN_ptr->left : ESN_ptr->right;
		if (temp2) {
			temp2_employerID = temp2->data->getEmployerIDInteger();
			temp2_employeeID = temp2->data->getEmployeeID();
			temp2_salary = temp2->data->getSalary();
			
		}
	}
	// remove from the big trees
	/*if (!employeesTreeByID.remove(employeesTreeByID.getRoot(), EIN_ptr->data) &&
		!employeesTreeBySalary.remove(employeesTreeBySalary.getRoot(), ESN_ptr->data)) {
		return FAILURE;
	}*/
	employeesTreeByID.remove(employeesTreeByID.getRoot(), EIN_ptr->data);
	employeesTreeBySalary.remove(employeesTreeBySalary.getRoot(), ESN_ptr->data);
	
	if (temp_employeeID && temp_employerID) {
		EmployeeIdData new_tempEID(temp_employeeID, temp_employerID, 0, 0);
		EmployeeIdData* new_tempEID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), new_tempEID)->data;
		ActiveCompaniesData temp_ACD(temp_employerID);
		ActiveCompaniesData* temp_ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), temp_ACD)->data;
		EmployeeIdData* temp_AEID_ptr = temp_ACD_ptr->getActiveCompanyEmployeesByID().
			find(temp_ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), new_tempEID)->data;
		temp_AEID_ptr->setEmployerIDPtr(&(new_tempEID_ptr->getEmployerID()));
	}

	if (temp2_employeeID && temp2_employerID) {
		EmployeeSalaryData new_tempESD(temp2_employeeID, temp2_employerID, temp2_salary, 0);
		EmployeeSalaryData* new_tempESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), new_tempESD)->data;
		ActiveCompaniesData temp2_ACD(temp2_employerID);
		ActiveCompaniesData* temp2_ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), temp2_ACD)->data;
		EmployeeSalaryData* temp_AESD_ptr = temp2_ACD_ptr->getActiveCompanyEmployeesBySalary().
			find(temp2_ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), new_tempESD)->data;
		temp_AESD_ptr->setEmployerIDPtr(&(new_tempESD_ptr->getEmployerID()));
	}

	//employeesTreeByID.remove(employeesTreeByID.getRoot(), EID_ptr);
	//employeesTreeBySalary.remove(employeesTreeBySalary.getRoot(), ESD_ptr);
	
	//check if the company has no employees
	if (ACD_ptr->getNumberOfEmployees() == 0) {
		ActiveCompaniesData* newRootData = activeCompaniesTree.remove(activeCompaniesTree.getRoot(), ACD_ptr)->data;
		if (!newRootData) {
			return FAILURE;
		}
		newRootData->setHighestSalary(newRootData->getActiveCompanyEmployeesBySalary().
			getMax(newRootData->getActiveCompanyEmployeesBySalary().getRoot())->data);
	}

	else {
		ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().
			getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
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
	*EmployerID = EID_ptr->getEmployerIDInteger();
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
	int old_salary = EID_ptr->getSalary();
	int employerID = EID_ptr->getEmployerIDInteger();
	int grade = EID_ptr->getGrade();
	int new_salary = old_salary + SalaryIncrease;

	if (BumpGrade > 0) {
		grade += 1;
	}

	ActiveCompaniesData ACD(employerID);
	ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	int companyEmployeesNumber = ACD_ptr->getNumberOfEmployees();
	
	if (RemoveEmployee(EmployeeID) == SUCCESS) {
		//int* employerID_ptr = new int(employerID);
		EmployeeIdData new_EID(EmployeeID, employerID, new_salary, grade);
		EmployeeSalaryData new_ESD(EmployeeID, employerID, new_salary, grade);
		//ActiveCompaniesData ACD(employerID);
		//ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;

		if (companyEmployeesNumber == 1) {
			if (!activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &ACD)) {
				return FAILURE;
			}
			ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
		}

		if (employeesTreeByID.insert(employeesTreeByID.getRoot(), &new_EID) &&
			employeesTreeBySalary.insert(employeesTreeBySalary.getRoot(), &new_ESD) &&
			ACD_ptr->getActiveCompanyEmployeesByID().insert(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), &new_EID) &&
			ACD_ptr->getActiveCompanyEmployeesBySalary().insert(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), &new_ESD)) {

			numberOfEmployees++;
			ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().
				getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
			highestSalaryAll = employeesTreeBySalary.getMax(employeesTreeBySalary.getRoot())->data;
			ACD_ptr->incNumberOfEmployees();


			EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), new_EID)->data;
			EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), new_ESD)->data;
			EmployeeIdData* EID_active_ptr = ACD_ptr->getActiveCompanyEmployeesByID().
				find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), new_EID)->data;
			EmployeeSalaryData* ESD_active_ptr = ACD_ptr->getActiveCompanyEmployeesBySalary().
				find(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), new_ESD)->data;

			EID_active_ptr->setEmployerIDPtr(&(EID_ptr->getEmployerID()));
			ESD_active_ptr->setEmployerIDPtr(&(ESD_ptr->getEmployerID()));

			return SUCCESS;
		}
	}
	return FAILURE;
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

	ActiveCompaniesData* ACD_ptr;
	if (activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD) != nullptr) {
		ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
		if (ACD_ptr->getActiveCompanyEmployeesByID().find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID))
			return FAILURE;
	}

	EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	StatusType remove_res = RemoveEmployee(EmployeeID);
	StatusType add_res = AddEmployee(EmployeeID, NewCompanyID, EID_ptr->getSalary(), EID_ptr->getGrade());

	return (remove_res == SUCCESS && add_res == SUCCESS) ? SUCCESS : FAILURE;
	//EmployeeIdData EID(EmployeeID, 0, 0, 0);
	//CompanyData CD(NewCompanyID, 0);
	//ActiveCompaniesData ACD(NewCompanyID);

	//if (!employeesTreeByID.find(employeesTreeByID.getRoot(), EID) ||
	//	!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
	//	return FAILURE;
	//}

	//ActiveCompaniesData* ACD_ptr;
	//if (activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD) != nullptr) {
	//	ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	//	if (ACD_ptr->getActiveCompanyEmployeesByID().find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID))
	//		return FAILURE;
	//}
	//// if newCompany is not in the active we insert the company
	//else {
	//	if (!activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &ACD)) return FAILURE;
	//	ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	//}

	////update the employees big trees
	//EmployeeIdData* EID_ptr = employeesTreeByID.find(employeesTreeByID.getRoot(), EID)->data;
	//EmployeeSalaryData ESD(EmployeeID, 0, EID_ptr->getSalary(), 0);
	//EmployeeSalaryData* ESD_ptr = employeesTreeBySalary.find(employeesTreeBySalary.getRoot(), ESD)->data;
	//int oldEmployerID = EID_ptr->getEmployerID();
	////int* newCompany_ptr = new int(NewCompanyID);
	//EID_ptr->setEmployerID(NewCompanyID);
	//ESD_ptr->setEmployerID(NewCompanyID);

	////update employees trees in comapny
	//if (ACD_ptr->getActiveCompanyEmployeesByID().insert(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID_ptr) &&
	//	ACD_ptr->getActiveCompanyEmployeesBySalary().insert(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD_ptr)) {

	//	/*
	//	ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().
	//		getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
	//	ACD_ptr->incNumberOfEmployees();

	//	EmployeeIdData* EID_active_ptr = ACD_ptr->getActiveCompanyEmployeesByID().
	//		find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID)->data;
	//	EmployeeSalaryData* ESD_active_ptr = ACD_ptr->getActiveCompanyEmployeesBySalary().
	//		find(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD)->data;

	//	EID_active_ptr->setEmployerID(NewCompanyID);
	//	ESD_active_ptr->setEmployerID(NewCompanyID);
	//	EID_active_ptr->setEmployerIDPtr(&(EID_ptr->getEmployerID()));
	//	ESD_active_ptr->setEmployerIDPtr(&(ESD_ptr->getEmployerID()));
	//	*/

	//	//remove the employee from the old company
	//	ActiveCompaniesData old_ACD(oldEmployerID);
	//	ActiveCompaniesData* old_ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), old_ACD)->data;
	//	int salary = EID_ptr->getSalary();
	//	old_ACD_ptr->removeEmployee(EmployeeID, salary);
	//	if (old_ACD_ptr->getNumberOfEmployees() == 0) {
	//		if (!activeCompaniesTree.remove(activeCompaniesTree.getRoot(), old_ACD_ptr)) return FAILURE;
	//	}

	//	//ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
	//	ACD_ptr->setHighestSalary(ACD_ptr->getActiveCompanyEmployeesBySalary().
	//		getMax(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
	//	ACD_ptr->incNumberOfEmployees();

	//	EmployeeIdData* EID_active_ptr = ACD_ptr->getActiveCompanyEmployeesByID().
	//		find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID)->data;
	//	EmployeeSalaryData* ESD_active_ptr = ACD_ptr->getActiveCompanyEmployeesBySalary().
	//		find(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD)->data;

	//	EID_active_ptr->setEmployerID(NewCompanyID);
	//	ESD_active_ptr->setEmployerID(NewCompanyID);
	//	EID_active_ptr->setEmployerIDPtr(&(EID_ptr->getEmployerID()));
	//	ESD_active_ptr->setEmployerIDPtr(&(ESD_ptr->getEmployerID()));

	//	EID_ptr->setEmployerID(NewCompanyID);
	//	ESD_ptr->setEmployerID(NewCompanyID);
	//	
	//	/*EmployeeIdData* EID_active_ptr = ACD_ptr->getActiveCompanyEmployeesByID().
	//		find(ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), EID)->data;
	//	EmployeeSalaryData* ESD_active_ptr = ACD_ptr->getActiveCompanyEmployeesBySalary().
	//		find(ACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), ESD)->data;

	//	EID_active_ptr->setEmployerIDPtr(&(EID_ptr->getEmployerID()));
	//	ESD_active_ptr->setEmployerIDPtr(&(ESD_ptr->getEmployerID()));*/

	//	return SUCCESS;
	//}
	//return FAILURE;
}
// problem here
StatusType SystemManager::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
	if (AcquirerID <= 0 || TargetID <= 0 || TargetID == AcquirerID || Factor < 1.00)
		return INVALID_INPUT;
	
	//updates in companyTreeByID
	CompanyData acquirerCD(AcquirerID,0);	
	CompanyData targetCD(TargetID, 0);
	if (!companiesTreeByID.find(companiesTreeByID.getRoot(), acquirerCD) ||
		!companiesTreeByID.find(companiesTreeByID.getRoot(), targetCD))	{
		return FAILURE;
	}
	
	CompanyData* acquirerCD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), acquirerCD)->data;
	CompanyData* targetCD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), targetCD)->data;

	if (acquirerCD_ptr == nullptr || targetCD_ptr == nullptr)
		return FAILURE;

	int targetValue = targetCD_ptr->getValue();
	int acquirerValue = acquirerCD_ptr->getValue();

	if (acquirerValue < targetValue * 10) 
		return FAILURE;

	if (!companiesTreeByID.remove(companiesTreeByID.getRoot(), targetCD_ptr)) {
		return FAILURE;
	}
	numberOfCompanies--;
	acquirerCD_ptr = companiesTreeByID.find(companiesTreeByID.getRoot(), acquirerCD)->data;
	acquirerCD_ptr->setValue((int)((acquirerValue + targetValue) * Factor));

	//updates at active companies tree
	ActiveCompaniesData targetACD(TargetID);
	ActiveCompaniesData acquirerACD(AcquirerID);

	// if target company is active, else we do nothing
	if (activeCompaniesTree.find(activeCompaniesTree.getRoot(), targetACD)) {
		
		ActiveCompaniesData* targetACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), targetACD)->data;

		if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), acquirerACD)) {
			if (!activeCompaniesTree.insert(activeCompaniesTree.getRoot(), &acquirerACD)) return FAILURE;
			//insert the target company employees to the acquirer company
			ActiveCompaniesData* acquirerACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), acquirerACD)->data;
			acquirerACD_ptr->setActiveCompanyEmployeesByID(targetACD_ptr->getActiveCompanyEmployeesByID());
			acquirerACD_ptr->setActiveCompanyEmployeesBySalary(targetACD_ptr->getActiveCompanyEmployeesBySalary());
			acquirerACD_ptr->setNumberOfEmployees(targetACD_ptr->getNumberOfEmployees());
			acquirerACD_ptr->setHighestSalary(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getMax
				(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
			updateEmployerIDByIDInCompany(acquirerACD_ptr->getActiveCompanyEmployeesByID().getRoot(), AcquirerID);
			updateEmployerIDBySalaryInCompany(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), AcquirerID);
			
			if (!activeCompaniesTree.remove(activeCompaniesTree.getRoot(), targetACD_ptr)) return FAILURE;
		}
		// merge two companies(target and acqure), and remove the target company
		else {
			ActiveCompaniesData* targetACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), targetACD)->data;
			ActiveCompaniesData* acquirerACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), acquirerACD)->data;
			
			int target_employees_num = targetACD_ptr->getNumberOfEmployees();
			EmployeeSalaryData** targetEmployeesSalary = new EmployeeSalaryData * [target_employees_num];
			int acquirer_employees_num = acquirerACD_ptr->getNumberOfEmployees();
			EmployeeSalaryData** acquirerEmployeesSalary = new EmployeeSalaryData * [acquirer_employees_num];
			
			targetACD_ptr->getActiveCompanyEmployeesBySalary().fillArray(targetEmployeesSalary);
			acquirerACD_ptr->getActiveCompanyEmployeesBySalary().fillArray(acquirerEmployeesSalary);
			
			int total_employees = target_employees_num + acquirer_employees_num;
			EmployeeSalaryData** targetAndAcquirerEmployees = new EmployeeSalaryData * [total_employees];
			/*
			acquirerACD_ptr->getActiveCompanyEmployeesBySalary().mergeTree(targetEmployeesSalary, target_employees_num,
				acquirerEmployeesSalary, acquirer_employees_num, targetAndAcquirerEmployees);
			
			acquirerACD_ptr->setNumberOfEmployees(total_employees);
			acquirerACD_ptr->setHighestSalary(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getMax(
				acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
				*/
			EmployeeIdData** targetEmployeesID = new EmployeeIdData * [target_employees_num];
			EmployeeIdData** acquirerEmployeesID = new EmployeeIdData * [acquirer_employees_num];
			
			targetACD_ptr->getActiveCompanyEmployeesByID().fillArray(targetEmployeesID);
			acquirerACD_ptr->getActiveCompanyEmployeesByID().fillArray(acquirerEmployeesID);
			
				
			EmployeeIdData** target_fill_array_EID = new EmployeeIdData * [target_employees_num];
			EmployeeIdData**  acquire_fill_array_EID = new EmployeeIdData * [acquirer_employees_num];
			EmployeeSalaryData** acquirer_fill_array_ESD = new EmployeeSalaryData * [acquirer_employees_num];
			EmployeeSalaryData** target_fill_array_ESD = new EmployeeSalaryData * [target_employees_num];

			
			for (int i = 0; i < target_employees_num; i++) {
				target_fill_array_ESD[i] = new EmployeeSalaryData(*(targetEmployeesSalary[i]));
				target_fill_array_EID[i] = new EmployeeIdData(*(targetEmployeesID[i]));
			}

			for (int i = 0; i < acquirer_employees_num; i++) {
				acquire_fill_array_EID[i] = new EmployeeIdData(*(acquirerEmployeesID[i]));
				acquirer_fill_array_ESD[i] = new EmployeeSalaryData(*(acquirerEmployeesSalary[i]));
			}
			
			EmployeeIdData** totalEmployeesID = new EmployeeIdData * [total_employees];
			
			acquirerACD_ptr->getActiveCompanyEmployeesByID().mergeTree(target_fill_array_EID, target_employees_num,
				acquire_fill_array_EID, acquirer_employees_num, totalEmployeesID);

			acquirerACD_ptr->getActiveCompanyEmployeesBySalary().mergeTree(target_fill_array_ESD, target_employees_num,
				acquirer_fill_array_ESD, acquirer_employees_num, targetAndAcquirerEmployees);

			//updateEmployerIDByIDInCompany(acquirerACD_ptr->getActiveCompanyEmployeesByID().getRoot(), AcquirerID);
			//updateEmployerIDBySalaryInCompany(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), AcquirerID);
			
			if (!activeCompaniesTree.remove(activeCompaniesTree.getRoot(), targetACD_ptr)) return FAILURE;

			acquirerACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), acquirerACD)->data;
			acquirerACD_ptr->setNumberOfEmployees(total_employees);
			acquirerACD_ptr->setHighestSalary(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getMax(
				acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getRoot())->data);
			updateEmployerIDByIDInCompany(acquirerACD_ptr->getActiveCompanyEmployeesByID().getRoot(), AcquirerID);
			updateEmployerIDBySalaryInCompany(acquirerACD_ptr->getActiveCompanyEmployeesBySalary().getRoot(), AcquirerID);

			/*
			for (int i = 0; i < target_employees_num; i++) {
				delete targetEmployeesSalary[i];
			}

			for (int i = 0; i < acquirer_employees_num; i++) {
				delete acquirerEmployeesSalary[i];
			}

			for (int i = 0; i < targetACD_ptr->getNumberOfEmployees(); i++) {
				delete targetEmployeesID[i];
			}

			for (int i = 0; i < acquirerACD_ptr->getNumberOfEmployees(); i++) {
				delete acquirerEmployeesID[i];
			}

			for (int i = 0; i < total_employees; i++) {
				delete targetAndAcquirerEmployees[i];
				delete totalEmployeesID[i];
			}
			*/


			for (int i = 0; i < target_employees_num; i++) {
				delete target_fill_array_ESD[i];
				delete target_fill_array_EID[i]; 
			}

			for (int i = 0; i < acquirer_employees_num; i++) {
				delete acquire_fill_array_EID[i];
				delete acquirer_fill_array_ESD[i];
			}

			delete[] target_fill_array_ESD;
			delete[] target_fill_array_EID;
			delete[] acquire_fill_array_EID;
			delete[] acquirer_fill_array_ESD;


			delete[] targetEmployeesSalary;
			delete[] acquirerEmployeesSalary;
			delete[] targetEmployeesID;
			delete[] acquirerEmployeesID;
			delete[] targetAndAcquirerEmployees;
			delete[] totalEmployeesID;
		}
	}
	
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

StatusType SystemManager::GetAllEmployeesBySalary(int CompanyID, int** Employees, int* NumOfEmployees)
{
	if (!Employees || !NumOfEmployees || CompanyID == 0) {
		return INVALID_INPUT;
	}
	CompanyData CD(CompanyID, 0);
	if (!companiesTreeByID.find(companiesTreeByID.getRoot(), CD)) {
		return FAILURE;
	}

	if (CompanyID > 0) {
		ActiveCompaniesData ACD(CompanyID);
		
		//if company doesnt contain in active companies then there is no employeers
		if (!activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
			return FAILURE;
		}
		ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
		*NumOfEmployees = ACD_ptr->getNumberOfEmployees();
		
		EmployeeSalaryData** EmployeesInCompany = new EmployeeSalaryData * [ACD_ptr->getNumberOfEmployees()];
		//O(logk)
		ACD_ptr->getActiveCompanyEmployeesBySalary().fillArray(EmployeesInCompany);
		*Employees = (int*)malloc(ACD_ptr->getNumberOfEmployees() * (sizeof(int)));
		//O(NcompaniesID)
		
		
		for (int i = 0; i <  ACD_ptr->getNumberOfEmployees(); i++) {
			(*Employees)[i] = EmployeesInCompany[ACD_ptr->getNumberOfEmployees() - i - 1]->getEmployeeID();
		}
		/*
		for (int i = ACD_ptr->getNumberOfEmployees() - 1; i >= 0; i--) {
			(*Employees)[numberOfEmployees - 1 - i] = EmployeesInCompany[i]->getEmployeeID();
		}
		*/
		delete[] EmployeesInCompany;
		return SUCCESS;
	}

	if (CompanyID < 0) {
		if (numberOfEmployees == 0) {
			return FAILURE;
		}
		*NumOfEmployees = numberOfEmployees;
		
		EmployeeSalaryData** all_employees = new EmployeeSalaryData * [numberOfEmployees];
		employeesTreeBySalary.fillArray(all_employees);
		
		*Employees = (int*)malloc(numberOfEmployees * (sizeof(int)));
		for (int i = numberOfEmployees - 1 ; i >= 0; i--) {
			(*Employees)[numberOfEmployees - 1 - i] = all_employees[i]->getEmployeeID();
		}

		delete[] all_employees;
		return SUCCESS;
	}
	return FAILURE;
}

StatusType SystemManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int** Employees)
{
	if (Employees == nullptr || NumOfCompanies < 1)
		return INVALID_INPUT;

	//need to check for failure
	if (activeCompaniesTree.getNodesNumber() < NumOfCompanies) {
		return FAILURE;
	}

	ActiveCompaniesData** companiesArray = new ActiveCompaniesData * [NumOfCompanies];
	*Employees = (int*)malloc(NumOfCompanies * (sizeof(int)));
	if (companiesArray == nullptr)
		return ALLOCATION_ERROR;

	activeCompaniesTree.inorderK(activeCompaniesTree.getRoot(), NumOfCompanies, companiesArray);
	for (int i = 0; i < NumOfCompanies; i++) {
		(*Employees)[i] = companiesArray[i]->getHighestSalary()->getEmployeeID();
	}

	delete[] companiesArray;
	return SUCCESS;
}

StatusType SystemManager::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
	int MinSalary, int MinGrade, int* TotalNumOfEmployees, int* NumOfEmployees)
{
	if (!TotalNumOfEmployees || !NumOfEmployees || CompanyID == 0 || MinEmployeeID < 0 || MaxEmployeeId < 0 ||
		MinSalary < 0 || MinGrade < 0 || MinEmployeeID > MaxEmployeeId) {
		return INVALID_INPUT;
	}

	CompanyData CD(CompanyID, 0);
	ActiveCompaniesData ACD(CompanyID);

	if (CompanyID > 0) {
		if (!companiesTreeByID.find(companiesTreeByID.getRoot(), CD) || 
			!activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)) {
			return FAILURE;
		}
		else {
			ActiveCompaniesData ACD(CompanyID);
			ActiveCompaniesData* ACD_ptr = activeCompaniesTree.find(activeCompaniesTree.getRoot(), ACD)->data;
			EmployeeIdData minID(MinEmployeeID, 0, 0, 0);
			EmployeeIdData maxID(MaxEmployeeId, 0, 0, 0);
			*TotalNumOfEmployees = ACD_ptr->getActiveCompanyEmployeesByID().getNodesNumberBetweenMinMax(
				ACD_ptr->getActiveCompanyEmployeesByID().getRoot(), &minID, &maxID);

			*NumOfEmployees = 0;
			if (*TotalNumOfEmployees) {
				EmployeeIdData** employeesID_arr = new EmployeeIdData * [ACD_ptr->getNumberOfEmployees()];
				ACD_ptr->getActiveCompanyEmployeesByID().InorderMinMax(employeesID_arr, &minID, &maxID);

				for (int i = 0; i < *TotalNumOfEmployees; i++) {
					if ((employeesID_arr[i]->getSalary() >= MinSalary) && (employeesID_arr[i]->getGrade() >= MinGrade)) {
						(*NumOfEmployees)++;
					}
				}
				
				for (int i = 0; i < *TotalNumOfEmployees; i++) {
					//delete employeesID_arr[i];
				}
				delete[] employeesID_arr;
			}
		}
	}
	else if (CompanyID < 0 && numberOfEmployees == 0) {
		return FAILURE;
	}
	else {
		EmployeeIdData minID(MinEmployeeID, 0, 0, 0);
		EmployeeIdData maxID(MaxEmployeeId, 0, 0, 0);

		*TotalNumOfEmployees = employeesTreeByID.getNodesNumberBetweenMinMax(employeesTreeByID.getRoot(), &minID, &maxID);
		EmployeeIdData** employeesID_arr = new EmployeeIdData * [*TotalNumOfEmployees];
		employeesTreeByID.InorderMinMax(employeesID_arr, &minID, &maxID);

		*NumOfEmployees = 0;
		for (int i = 0; i < *TotalNumOfEmployees; i++) {
			if ((employeesID_arr[i]->getSalary() > MinSalary) && (employeesID_arr[i]->getGrade() > MinGrade)) {
				(*NumOfEmployees)++;
				//delete employeesID_arr[i];
			}
		}
		delete[] employeesID_arr;
	}

	return SUCCESS;
}







