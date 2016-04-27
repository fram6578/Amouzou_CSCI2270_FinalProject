#include "Tree.h"
#include <iostream>
#include <string>
using namespace std;


Tree::Tree(string name, int pay){//initializes tree with boss node
	boss=new Employee(name,pay, nullptr);
}

/*Employee *Tree::addEmployee(string name, int salary, string senior, string uprank){
	Employee *head=search(senior);
	Employee *rank=search(uprank);
	Employee *add=new Employee(name,salary,head);
}

Employee *search(string name,Employee *root){
	
}*/
Tree::~Tree(){
	
}
