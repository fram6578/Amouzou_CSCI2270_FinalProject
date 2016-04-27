#include "Tree.h"
#include <iostream>
#include <string>
using namespace std;


Tree::Tree(string name, int pay){//initializes tree with boss node
	boss=new Employee(name,pay, nullptr);
}

Employee *Tree::addEmployee(string name, int salary, string senior, string uprank){
	Employee *head=search(senior,boss);
	Employee *rank=search(uprank,boss);
	Employee *add=new Employee(name,salary,head);
	add->next=rank;
	if(head==0){
		cout<<"Not real senior, try again"<<endl;
	}
	else{
		if(head->juniors==nullptr){
			head->juniors=add;
		}
		if(rank!=nullptr){
			add->previous=rank->previous;
			rank->previous=add;
		}
	}
	return add;
}

Employee *Tree::search(string name,Employee *root){
	Employee *temp=root;
	Employee *ans=nullptr;
	while(temp!=nullptr){
		if(temp->name.compare(name)==0){
			ans=temp;
			temp=nullptr;
		}
		else{
			if(temp->juniors!=nullptr){
				ans=search(name,temp->juniors);
			}
			temp=temp->next;
		}
	}
	return ans;
}
Tree::~Tree(){
	
}
