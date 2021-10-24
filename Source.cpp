#include <Python.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main(){
	int userChoice = 0;  //Track the number of menu loops.
	int wordCount = 0; //Track the number of times a specific searched .
	int itemQuantity = 0; //Variable to contain an item quantity from.
	string itemName; //Variable to contain an item name from.
	string userSearch; //Collect user input for a search term.
	ifstream inFS;  //Open ifstream for file.

	while (userChoice != 4) {

		//Display for the user.
		cout << "============================================================" << endl;
		cout << "1. Check the number of times each individual item appears." << endl;
		cout << "2. Determine the frequency of specific item." << endl;
		cout << "3. Show Histogram of all items purchased in a given day." << endl;
		cout << "4. Exit program" << endl;
		cout << "============================================================" << endl;

		cout << endl;

		cout << "Enter your choice: "; //Prompt for user's input.

		cin >> userChoice; //Input from the User.

		cout << endl;

		switch (userChoice) { //Switch statement: Execute the proper command for user input

		//Case 1: Calculate the number of times each item appears, then print a list
		case 1:
			system("CLS"); //Clears Screen
			CallProcedure("ItemCount"); //Calls Python function

			cout << endl; //Space between printed list and menu.

			break;

		
		//Case 2: Calculate the number of times a specific item appears, then print the result.
		case 2:
			system("CLS"); //Clears Screen.
			cout << "What item would you like to search? "; //Prompt for user's input.

			cin >> userSearch; //Input from the User.

			cout << endl; //Line between user's input and display.

			wordCount = callIntFunc("WordSearch", userSearch); //Calls Python fuction.
			cout << userSearch << ": " << wordCount << endl; //Prints the statment to show user.
			cout << endl; //Space between printed list and menu.

			break;

		
		//Case 3: Print a histogram based on how many times each item appears. However asterisks will replace the numbers.
		case 3: 
			system("CLS"); //Clears Screen.

			CallProcedure("CollectData"); //Calls Python function.

			inFS.open("frequency.dat"); //Opens file.

			inFS >> itemName; // Collect first item on list.
			inFS >> itemQuantity; //Collect first quantity on list.

			 //For each line in the file, print a histogram. After every line has been parsed, break.
			while (!inFS.fail()) {
				
				cout << setw(14) << left << itemName << setw(6);  //Print the item name, then prepare for the histogram.

				//Print itemQuantity number of asterisks
				for (int i = 0; i < itemQuantity; i++) {
					cout << right << "*";
				}

				//Prepare for the next line.
				cout << endl;

				//Set the next item's name and quantity.
				inFS >> itemName;
				inFS >> itemQuantity;
			}

			inFS.close(); //Close file.

			break;

		//Case 4: Exits Program.
		case 4:
			return;
		

		//Default for invaild user input.
		default:
			cout << "Please input a vaild selection." << endl;

			cout << endl;
		}
	}
}