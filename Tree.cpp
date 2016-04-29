#include "Tree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
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
		boss->depth=0;
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
	Employee *add=new Employee(name,salary,head);
	if(head==nullptr){
		cout<<"Not real senior, try again"<<endl;
	}
	else{
		head->breath++;
		add->depth=head->depth+1;
		Employee *rank=search(uprank,head);
		add->next=rank;
		if(head->juniors==nullptr){
			head->juniors=add;
		}
		else{
			if(rank==nullptr){
				rank=head->juniors;
				while(rank->next!=nullptr){
					rank=rank->next;
				}
				rank->next=add;
				add->previous=rank;
			}
			else{
				if(head->juniors==rank){
					head->juniors=add;
				}
				else{
					rank->previous->next=add;
				}
				add->previous=rank->previous;
				rank->previous=add;
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
			return temp;
		}
		else{
			if(temp->juniors!=nullptr){
				ans=search(name,temp->juniors);
				if(ans!=nullptr and ans->name.compare(name)==0){
					return ans;
				}
			}
			temp=temp->next;
		}
	}
	return ans;
}

void Tree::listEmployees(){
	list(boss);
}

void Tree::list(Employee *root){
	Employee *temp=root;
	while(temp!=nullptr){
		cout<<temp->name<<endl;
		if(temp->juniors!=nullptr){
			list(temp->juniors);
		}
		temp=temp->next;
	}
}

void Tree::printEmployees(){
	Employee *temp=boss;
	int delim=10;
	int offset=0;
	int start=0;
	int shift=0;
	string branches;
	names.clear();
	names.resize(maxDepth(boss));
	print(boss);
	for(int i=0;i<names.size();i++){
		branches="";
		for(int n=0;n<names[i].size();n++){
			temp=names[i][n];
			offset=maxBreath(temp);
			if(temp->senior != nullptr and temp==temp->senior->juniors and vectorIn(temp->senior)>n){
				start=vectorIn(temp->senior)-vectorIn(names[i][n-1]->senior)-1;
			}
			else{
				start=0;
			}
			cout<<setw(delim*start)<<left<<"";
			branches+=(string(delim*(start),' '));
			if(temp->next!=nullptr){
				cout<<setfill('-');
			}
			else{
				cout<<setfill(' ');
			}
			cout<<setw(delim*offset)<<left<<temp->name;
			shift=delim*offset;
			if(temp->juniors!=nullptr){
				branches+=("|");
				shift--;
			}
			branches+=string(shift,' ');
		}
		cout<<endl<<branches<<endl;
	}
}
int Tree::vectorIn(Employee *root){
	int ans=0;
	for(int i=0;i<names.size();i++){
		for(int n=0;n<names[i].size();n++){
			if(names[i][n]==root){
				ans=n;
			}
		}
	}
	return ans;
}
void Tree::print(Employee *root){
	Employee *temp=root;
	while(temp!=nullptr){
		print(temp->juniors);
		names[temp->depth].push_back(temp);
		temp=temp->next;
	}
}

int Tree::maxBreath(Employee *root){
	int crawl=0;
	Employee *temp=root;
	if(root!=nullptr){
		crawl=root->breath;
	}
	temp=root->juniors;
	while(temp!=nullptr){
		if(maxBreath(temp)!=0){
			crawl+=maxBreath(temp)-1;
		}
		temp=temp->next;
	}
	if(crawl==0){
		crawl=1;
	}
	return crawl;
}

int Tree::maxDepth(Employee *root){
	int climb=0;
	Employee *temp=root;
	while(temp!=nullptr){
		if(climb<maxDepth(temp->juniors)){
			climb=maxDepth(temp->juniors);
		}
		temp=temp->next;
	}
	if(root!=nullptr){
		climb++;
	}
	return climb;
}

Tree::~Tree(){
	
}
