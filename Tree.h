#ifndef TREE_H
#define TREE_H
#include <string>
#include <vector>
#include <iostream>

struct Employee{ //Employee node, stores neighboring nodes as well as parent and children
	std::string name=""; //Employee personal information
	int pay=-1;//Pay is in grands
	int breath=0;//Tracks the number of children a node has
	int depth=-1;//Tracks the hierarchical levels deep a node is
	
	Employee *superior=NULL;//points to parent
	Employee *juniors=NULL;//points to head of linked list of children, which is the least senior subordinate, I refer to subordinates as juniors
	
	Employee *previous=NULL;//points to downranking co-worker
	Employee *next=NULL;//points to upranking co-worker
	
	Employee(){};
	Employee(std::string in_name, int in_pay, Employee* in_superior){//intializes employee with name and superior and pay rate
		name=in_name;
		superior=in_superior;
		pay=in_pay;
	}
};

class Tree
{
	public:
		Tree(std::string filename);//intializes and builds tree according to input file, look at readme for information on how this file should be formatted
		~Tree();//deconstructs and deletes each tree node
		
		void findEmployee(std::string name);//finds and displays information of employee
		void addEmployee(std::string name, int salary, std::string superior, std::string senior);//adds employee to tree
		void deleteEmployee(std::string name);//employee from tree only if employee node has no children
		void promoteEmployee(std::string name);//moves employee node up one step in tree if it has no children
		void modifyEmployee(std::string name, std::string newname, std::string salary);//changes employee's rank and/or salary
		void shiftEmployees(std::string name, std::string target);//moves subordinate employees to another superior.
		void rankEmployees(std::string name, std::string senior);//moves employee to new rank
		void makevector(Employee *root);//function creates 2D vector housing each node according to depth in tree and recursive access
		void listEmployees();//prints out all employees in list
		void printEmployees();//prints out all employees in tree (left justified)
		
		
	protected:
	private:
		Employee *boss;//root of employee tree
		Employee *search(std::string name,Employee *root);//find pointer to employee with name 'name' starting search from inputed root
		void list(Employee *root);//function for recursive employee listing
		int maxDepth(Employee *root);//function finds max depth of tree and returns it
		int maxBreath(Employee *node);//finds total breath of node and all nodes below it and returns it
		int position(Employee *node);//finds how distanced children nodes should be when printed
		void depthAdd(Employee *node);//recursively updates depth for all nodes under 'node'
		std::vector < std::vector < Employee* > > names;//2D vector variable used for printing in tree format
};

#endif
