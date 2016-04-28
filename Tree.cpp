#include "Tree.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


Tree::Tree(string filename){//initializes tree with boss node
	ifstream inFile;
	inFile.open(filename);
	
	int comma=0;
	string line="";
	string name="";
	string pay="";
	string senior="";
	string uprank="";
	
	if (inFile.good()){
		getline(inFile,line);
		comma=line.find(",",0);
		name=line.substr(0,comma); 
		comma++;
		pay=line.substr(comma,line.length()-comma);
		boss=new Employee(name,stoi(pay), nullptr);
		while(getline(inFile,line)){
			comma=line.find(",",0);
			name=line.substr(0,comma);
			comma++;
			pay=line.substr(comma,line.find(",",comma+1)-comma);
			comma=line.find(",",comma)+1;
			senior=line.substr(comma,line.find(",",comma+1)-comma);
			comma=line.find(",",comma)+1;
			uprank=line.substr(comma,line.length()-comma);
			addEmployee(name,stoi(pay),senior,uprank);
		}
	}
	
}

void Tree::findEmployee(string name){
	Employee *worker=search(name,boss);
	if(worker==nullptr){
		cout<<"Employee not found"<<endl;
	}
	else{
		cout<<"Employee info"<<endl;
		cout<<"============="<<endl;
		cout<<"Name: "<<worker->name<<endl;
		cout<<"Pay: $"<<worker->pay*1000<<endl;
		cout<<"Senior: ";
		if(worker==boss){
			cout<<"none"<<endl;
		}
		else{
			cout<<worker->senior->name<<endl;
		}
		cout<<"Manages: ";
		Employee *temp=worker->juniors;
		if(temp==nullptr){
			cout<<"none"<<endl;
		}
		else{
			cout<<temp->name;
			temp=temp->next;
			while(temp!=nullptr){
				cout<<", "<<temp->name;
				temp=temp->next;
			}
			cout<<endl;
		}
	}
}

Employee *Tree::addEmployee(string name, int salary, string senior, string uprank){
	Employee *head=search(senior,boss);
	Employee *rank=search(uprank,boss);
	Employee *add=new Employee(name,salary,head);
	add->next=rank;
	if(head==nullptr){
		cout<<"Not real senior, try again"<<endl;
	}
	else{
		if(head->juniors==nullptr){
			head->juniors=add;
		}
		if(rank!=nullptr){
			add->previous=rank->previous;
			rank->previous=add;
			if(head->juniors==rank){
				head->juniors=add;
			}
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

void Tree::listEmployees(){
	
}

Tree::~Tree(){
	
}
