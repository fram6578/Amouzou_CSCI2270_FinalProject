#ifndef TREE_H
#define TREE_H
#include <string>
#include <iostream>

struct Employee{ //basic employee struct, includes name senior and juniors
	std::string name="";
	int pay=0;
	
	Employee *senior=NULL;//points to senior
	Employee *juniors=NULL;//points to head of linked list of juniors
	
	Employee *previous=NULL;//points to downranking co-worker
	Employee *next=NULL;//points to upranking co-worker
	
	Employee(){};
	Employee(std::string in_name, int in_pay, Employee* in_senior){//intializes employee with name and senior
		name=in_name;
		senior=in_senior;
		pay=in_pay;
	}
};

class Tree
{
	public:
		Tree(std::string filename);
		~Tree();
		
		void findEmployee(std::string name);//finds and displays information of employee
		Employee * addEmployee(std::string name, int salary, std::string senior, std::string uprank);//adds employee to tree
		void replaceEmployee(std::string name, std::string replacement);//removes employee from tree and replaces them
		void promoteEmployee(std::string name);//moves employee up one step in tree
		void modifyEmployee(std::string name, int salary, std::string uprank);//changes employee's rank and/or salary
		void shiftEmployees(std::string name, std::string junior);//moves junior employees to another senior.
		
		void listEmployees();//prints out all employees in list
		void printEmployees();//prints out all employees in tree
		void countEmployees();//prints total number of employees and maybe other relevent data
		
		
	protected:
	private:
		Employee *boss;//root of employee tree
		Employee *search(std::string name,Employee *root);//find pointer to specific employee starting from root
};

#endif
