#ifndef TREE_H
#define TREE_H
#include <string>
struct Employee{
	std::string name="";
	Employee *senior=NULL;
	Employee *juniors=NULL;
	Employee(){};
	Employee(std::string in_name, Employee* in_senior){
		name=in_name;
		senior=in_senior;
	}
};

class Tree
{
	public:
		Tree();
		~Tree();
	protected:
	private:
};

#endif
