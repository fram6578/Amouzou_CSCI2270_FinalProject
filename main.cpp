#include "Tree.h"
#include <iostream>
using namespace std;

void PrintMenu(){
	cout<<"=====Main Menu====="<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Add Employee"<<endl;
}

int main(int argc, char ** argv){
	string name="";
	string pay="";
	string senior="";
	string uprank="";
	string input="";
	int in=-1;
	
	cout<<"Building new business \n\n\nEnter name of boss: "<<endl;
	getline(cin,name);
	cout<<"Enter pay: "<<endl;
	getline(cin,pay);
	Tree Business(name,stoi(pay));
	
	while(in!=1){
		PrintMenu();
		getline(cin,input);
		in=stoi(input);
		if(in==1){
			cout<<"Goodbye!"<<endl;
		}
		else{
			if(in==2){
				cout<<"Enter name of employee: "<<endl;
				getline(cin,name);
				cout<<"Enter pay: "<<endl;
				getline(cin,pay);
				cout<<"Enter name of senior: "<<endl;
				getline(cin,senior);
				cout<<"Enter name of outranked co-worker"<<endl;
				getline(cin,uprank);
				Business.addEmployee(name,stoi(pay),senior,uprank);	
			}
			else{
				if(in==3){
				
				}
			}
		}
	}
	return 0;
}
