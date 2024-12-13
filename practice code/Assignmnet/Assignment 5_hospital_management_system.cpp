
#include <iostream>
using namespace std;
class patientTree;

class Patient
{
public:
	int pID;
	string Pname;
	Patient* Pleft;
	Patient* Pright;
	bool PleftThread, PrightThread;

	Patient(int id,string name)
	{
		pID = id;
		Pname = name;
		Pleft = nullptr;
		Pright = nullptr;
		PleftThread = false;
		PrightThread = false;
	}

};


class patientTree
{

	Patient* root;
public:
	patientTree()
	{
		root = nullptr;
	}

	void insertPatientData(int id, string name) // insertion is done in BST based on PID
	{
		Patient* newnode = new Patient(id, name);

		if (root == nullptr)
		{
			root = newnode;
			return;
		}
		Patient* current = root;
		Patient* parent = nullptr;

		while (current != nullptr)
		{
			parent = current;
			if (id<current->pID)
			{
				if (current->PleftThread)
				{
					break;
				}
				current = current->Pleft;

			}
			else
			{
				if (current->PrightThread)
				{
					break;
				}
				current = current->Pright;
			}
		}

		// insertion new record
		if (id < parent->pID)
		{
			parent->Pleft = newnode;
			parent->PleftThread = false; // this is because to make sure the left child as not thread
			newnode->Pright = parent;
			newnode->PrightThread = true;
		}
		else
		{
			parent->Pright = newnode;
			parent->PrightThread = false;
			newnode->Pleft = parent;
			newnode->PleftThread = true; // point to parent as thread not as child.
		}
	}

	void inOrderTravesal(Patient* root) {
		if (root == nullptr) {
			cout << "No patient records available." << endl;
			return;
		}
		Patient* current = root;
		while (current->Pleft != nullptr && !current->PleftThread)
		{
			current = current->Pleft;
		}
		while (current != nullptr) 
		{
			cout << "Patient ID: " << current->pID << ", Patient Name: " << current->Pname << endl;

			// If the right pointer is a thread
			if (current->PrightThread) {
				current = current->Pright;
			}
			else
			{
				// move to the leftmost node in the right subtree
				current = current->Pright;
				while (current != nullptr && !current->PleftThread) 
				{
					current = current->Pleft;
				}
			}
		}
	}

	void displayPatientData()
	{
		inOrderTravesal(root);
	}

	void deletePatientData(int id) {
		root = deleteNode(root, id);
	}

	Patient* deleteNode(Patient* root, int id)
	{
		if (root == nullptr) {
			cout << "Patient with ID " << id << " not found.\n";
			return nullptr;
		}

		if (id < root->pID) 
		{
			root->Pleft = deleteNode(root->Pleft, id);
		}
		else if (id > root->pID)
		{
			root->Pright = deleteNode(root->Pright, id);
		}
		else 
		{ 
			// 1 Node has no children
			if (root->Pleft == nullptr && root->Pright == nullptr) 
			{
				delete root;
				return nullptr;
			}
			//2 Node has one child (right child)
			else if (root->Pleft == nullptr) 
			{
				Patient* temp = root;
				root = root->Pright;
				delete temp;
			}
			// 3: Node has one child (left child)
			else if (root->Pright == nullptr) {
				Patient* temp = root;
				root = root->Pleft;
				delete temp;
			}
			// Case 4: Node has two children
			else 
			{
				// Find the smallest in the right subtree
				Patient* temp = minNode(root->Pright);
				root->pID = temp->pID;
				root->Pname = temp->Pname;

				// Delete the in-order successor
				root->Pright = deleteNode(root->Pright, temp->pID);
			}
		}

		return root;
	}

	Patient* minNode(Patient* node) // last leftnode
	{
		Patient* current = node;
		while (current != nullptr && !current->PleftThread) {
			current = current->Pleft;
		}
		return current;
	}

};

class Department
{
public:
	string DName;
	Department* Dleft;
	Department* Dright;
	patientTree patientData;

	Department(string name)
	{
		DName = name;
		Dleft = nullptr;
		Dright = nullptr;

	}
};

class DepartmentTree
{
public:
	Department* root;
	DepartmentTree()
	{
		root = nullptr;
	}
	// insert functions
	void insertDepartmentData(string name)
	{
		root = insert(root, name);

	}

	Department* insert(Department* root, string name)
	{
		Department* newnode = new Department(name);

		if (root == nullptr)
		{
			root = newnode;
			return root;
		}

		Department* current = root;
		Department* parent = nullptr;
		while (current != nullptr)
		{
			parent = current;
			if (name < current->DName)
			{
				current = current->Dleft;
			}
			else
			{
				current = current->Dright;
			}
		}

		if (name < parent->DName)
		{
			parent->Dleft = newnode;
		}
		else
		{
			parent->Dright = newnode;
		}
		return root;
	}


	void inorderTravesal(Department* root) // travesal for regualr travesal recursive approach
	{
		if (root == nullptr)
			return;

		inorderTravesal(root->Dleft);
		cout << root->DName << endl;
		inorderTravesal(root->Dright);

	}

	void displayDepartment()
	{
		inorderTravesal(root);
	}

	Department* findDepartment(string deptName) {
		return findDepartmentdta(root, deptName);
	}

	Department* findDepartmentdta(Department* root, string deptName) {
		if (root == nullptr)
			return nullptr;

		if (root->DName == deptName)
			return root;

		if (deptName < root->DName)
		{
			return findDepartmentdta(root->Dleft, deptName);

		}
		return findDepartmentdta(root->Dright, deptName);
	}

	void displayAllDepartmentsPatients()
	{
		displayAllDepartments(root);
	}

	void displayAllDepartments(Department* root)
	{
		if (root == nullptr)
			return;

		displayAllDepartments(root->Dleft);

		cout << "Department: " << root->DName << endl;

		root->patientData.displayPatientData();

		displayAllDepartments(root->Dright);
	}

};

class HospitalManagementSystem {
private:
	DepartmentTree deptobj;
	patientTree patientobj;

public:
	void displayMenu()
	{
		cout << "Hospital Management System" << endl;
		cout << "*****************************" << endl;
		cout << "1. Add Department" << endl;
		cout << "2. Display Department Hierarchy" << endl;
		cout << "3. Add Patient Record" << endl;
		cout << "4. Display Patient Records for specific department" << endl;
		cout << "5. Delete Patient Record" << endl;
		cout << "6. Display All Patients Across All Departments" << endl;
		cout << "7. Exit" << endl;
	}


	void addDepartment()
	{
		string newDept;
		cout << "Enter New Department: ";
		cin >> newDept;
		deptobj.insertDepartmentData(newDept);
	}

	void displayDepartmentHierarchy() 
	{
		deptobj.displayDepartment();
	}

	void addPatientRecord() 
	{
		cout << "department available:" << endl;
		displayDepartmentHierarchy();

		int patientId;
		string patientName,departName;
		Department* dept = nullptr;
		while (dept == nullptr) 
		{
			cout << "Enter Department Name: ";
			cin >> departName;

			dept = deptobj.findDepartment(departName); // Find the department

			if (dept == nullptr) {
				cout << "Department not found. Please add again." << endl;
			}
		}
		cout << "Enter Patient ID: ";
		cin >> patientId;
		cout << "Enter Patient Name: "<<endl;
		cin.ignore();
		cin >> patientName;

		dept->patientData.insertPatientData(patientId, patientName);
		cout << "Patient added to " << departName << " department." << endl;
	}

	void deletePatientRecord() {
		int patientId;
		string departName;
		cout << "Enter Department Name: ";
		cin >> departName;
		Department* dept = deptobj.findDepartment(departName);
		if (dept)
		{
			cout << "Enter Patient ID to delete: ";
			cin >> patientId;
			dept->patientData.deletePatientData(patientId);
		}
		else 
		{
			cout << "Department not found." << endl;
		}
	}

	void displayPatientRecords()
	{
		string departName;
		cout << "Enter Department Name: ";
		cin >> departName;
		Department* dept = deptobj.findDepartment(departName);
		if (dept) 
		{
			dept->patientData.displayPatientData();
		}
		else
		{
			cout << "Department not found." << endl;
		}
	}

	void displayAllPatients()
	{
		cout << "Displaying all patients across departments:\n";
		deptobj.displayAllDepartmentsPatients();
	}
};

int main() 
{
	HospitalManagementSystem hms;
	int choice;

	while (true)
	{
		hms.displayMenu();
		cout << "Choose one option: ";
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1:
			hms.addDepartment();
			break;
		case 2:
			hms.displayDepartmentHierarchy();
			break;
		case 3:
			hms.addPatientRecord();
			break;
		case 4:
			hms.displayPatientRecords();
			break;
		case 5:
			hms.deletePatientRecord();
			break;
		case 6:
			hms.displayAllPatients(); 
			break;
		case 7:
			cout << "Exiting system" << endl;
			return 0;
		default:
			cout << "Invalid choice, please try again" << endl;
		}

		
	}
	return 0;

}
