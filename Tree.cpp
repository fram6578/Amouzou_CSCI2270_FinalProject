#include "Tree.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

Tree::Tree(string filename){
	ifstream inFile;//open file
	inFile.open(filename);
	
	int comma=0; //used for finding comma delimiter on each line
	string line="";//string for storing each line
	
	string name="";//strings for storing the line data, i.e., one for each node parameter
	string pay="";
	string superior="";
	string senior="";
	
	if (inFile.good()){//if file opened
		getline(inFile,line);//take first line and pull boss data from it
		comma=line.find(",",0);
		name=line.substr(0,comma); 
		comma++;
		pay=line.substr(comma,line.length()-comma);
		boss=new Employee(name,stoi(pay), nullptr);//initialize boss node
		boss->depth=0;
		while(getline(inFile,line)){//for subsequent lines find and store each node parameter
			comma=line.find(",",0);
			superior=line.substr(0,comma);
			comma++;
			name=line.substr(comma,line.find(",",comma+1)-comma);
			comma=line.find(",",comma)+1;
			pay=line.substr(comma,line.find(",",comma+1)-comma);
			comma=line.find(",",comma)+1;
			senior=line.substr(comma,line.length()-comma);
			addEmployee(name,stoi(pay),superior,senior);//create and add new employee to tree
		}
	}
	else{
		cout<<"File can't be opened"<<endl;
	}
	
}

void Tree::findEmployee(string name){
	Employee *worker=search(name,boss);//find node with inputed name
	if(worker==nullptr){//if not found print message
		cout<<"Employee not found"<<endl;
	}
	else{//if found print out information
		cout<<"Employee info"<<endl;
		cout<<"============="<<endl;
		cout<<"Name: "<<worker->name<<endl;
		cout<<"Pay: $"<<worker->pay*1000<<endl;//pay is inputted and stored in grands
		cout<<"Superior: ";
		if(worker==boss){//exception for boss node since it can have no superior
			cout<<"none"<<endl;
		}
		else{//print name of superior
			cout<<worker->superior->name<<endl;
		}
		cout<<"Manages: ";
		Employee *temp=worker->juniors;
		if(temp==nullptr){//exception for node without subordinates
			cout<<"none"<<endl;
		}
		else{//loop through and print name of each subordinate employee
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

void Tree::addEmployee(string name, int salary, string superior, string senior){
	Employee *head=search(superior,boss);//find superior node
	Employee *add=new Employee(name,salary,head);//create node to be added to tree
	if(head==nullptr){//handle bad input for superior is nonexistant
		cout<<"Not real superior, try again"<<endl;
	}
	else{//add node to tree
		head->breath++;//the superior is getting one extra subordinate so breath increases by 1
		add->depth=head->depth+1;//the depth of the addition must be one greater than its parent node's
		Employee *rank=search(senior,head);//rank variable tracks the seniority position for the addition to be put
		add->next=rank;//the addition will always come before its inputted senior
		if(head->juniors==nullptr){//if its superior has no subordinates
			head->juniors=add;//place the addition as the singular subordinate
		}
		else{
			if(rank==nullptr){//if there is no senior, the addition is most senior so add it to the end of the linked list
				rank=head->juniors;
				while(rank->next!=nullptr){
					rank=rank->next;
				}
				rank->next=add; //linked forward
				add->previous=rank;// linked backwards
			}
			else{
				if(head->juniors==rank){//if being placed before the least senior, become the new least senior
					head->juniors=add;
				}
				else{
					rank->previous->next=add;//linked forwards
				}
				add->previous=rank->previous;//linked backwards
				rank->previous=add;
			}
		}
	}
}

Employee *Tree::search(string name,Employee *root){
	Employee *temp=root;//initialize temporary node
	Employee *ans=nullptr;//initialize return node
	while(temp!=nullptr){//until looped through the entire tree from root
		if(temp->name.compare(name)==0){//if found return node
			return temp;
		}
		else{
			if(temp->juniors!=nullptr){//if node has children check children
				ans=search(name,temp->juniors);
				if(ans!=nullptr and ans->name.compare(name)==0){
					return ans;
				}
			}
			temp=temp->next;//iterate to neighbor
		}
	}
	return ans;
}

void Tree::listEmployees(){
	list(boss);//use recursive function to print out full tree
}

void Tree::list(Employee *root){
	Employee *temp=root;//initialize temporary as root
	while(temp!=nullptr){//until looped thourgh all neighbors print names
		cout<<temp->name<<endl;
		if(temp->juniors!=nullptr){//if node has children list children
			list(temp->juniors);
		}
		temp=temp->next;//proceed to next neighbor in linked list
	}
}

void Tree::printEmployees(){
	Employee *temp=boss;//intialize temporary as boss for the heck of it
	int delim=10;//delim variable tracks witdh of each print statement
	int shift=0;//shift variable tracks distance between nodes (in nodes not absolute distance)
	string branches;//string variable for printing vertical bars underneath superiors
	
	names.clear();//initialize 2D vector after emptying it
	names.resize(maxDepth(boss));
	makevector(boss);
	
	for(int i=0;i<names.size();i++){//for each level of the tree
		branches="";
		for(int n=0;n<names[i].size();n++){//for each node in this level
			temp=names[i][n];
			shift=0;
			if(temp->superior!=nullptr and temp==temp->superior->juniors){//find the shift value of the node
				shift=position(temp);
				if(n>0){
					shift-=position(names[i][n-1]);
					shift--;
				}
				shift*=delim;
			}
			cout<<setw(shift)<<left<<"";//offset the print statements by shift
			branches+=(string(shift,' '));
			if(temp->next!=nullptr){//if node has neighbor, add '-' fill otherwise just leave blank
				cout<<setfill('-');
			}
			else{
				cout<<setfill(' ');
			}
			shift=delim*maxBreath(temp);//find space needed by the node (so that children node fit underneath)
			cout<<setw(shift)<<left<<temp->name;
			if(temp->juniors!=nullptr){//if node has children print out vertical line
				branches+=("|");
				shift--;
			}
			branches+=string(shift,' ');
		}
		cout<<endl<<branches<<endl;
		/*since the vertical lines are on their own line I used a string variable to track it so that its created 
		 * and positioned along the actual nodes but remain on their own line*/
	}
}

int Tree::position(Employee *node){
	int ans=0;//initilize return value
	Employee *climber=node;//this variables goes up the tree
	Employee *stepper=node;//this variables goes across the tree
	while(climber->superior!=nullptr and climber->superior->superior != nullptr){//until the climber variable reaches the top of the tree
		stepper=climber->superior->superior->juniors;
		while(stepper!=climber->superior){
			if(stepper->breath==0){
				ans+=1;
			}
			else{
				ans+=(stepper->breath);
			}
			stepper=stepper->next;
		}
		climber=climber->superior;
	}
	if(node->superior!=nullptr and node!=node->superior->juniors){
		stepper=node->superior->juniors;
		while(stepper!=node){
			ans++;
			stepper=stepper->next;
		}
	}
	return ans;
}

void Tree::makevector(Employee *root){
	Employee *temp=root;
	while(temp!=nullptr){
		makevector(temp->juniors);
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
	if(crawl<=0){
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

void Tree::promoteEmployee(string name){
	Employee *worker=search(name,boss);
	Employee *temp=worker;
	Employee *add=worker;
	if(worker!=nullptr){
		if(worker->superior==nullptr){
			cout<<"Already highest position, can't be promoted"<<endl;
		}
		else{
			if(worker->superior->superior==nullptr){
				cout<<"Can't promote to highest position"<<endl;
			}
			else{
				if(worker->juniors==nullptr){
					if(worker->next!=nullptr){
						worker->next->previous=worker->previous;
					}
					if(worker->previous!=nullptr){
						worker->previous->next=worker->next;
					}
					if(worker==worker->superior->juniors){
						worker->superior->juniors=worker->next;
					}
					worker->superior=worker->superior->superior;
					worker->next=worker->superior->juniors;
					if(worker->next!=nullptr){
						worker->next->previous=worker;
					}
					worker->superior->juniors=worker;
					worker->previous=nullptr;
					worker->depth--;
					worker->superior->breath++;
				}
				else{
					cout<<"Employee has subordinates, please shift them."<<endl;
				}
			}
		}
	}
}

void Tree::shiftEmployees(std::string name, std::string target){
	Employee *worker=search(name,boss);
	Employee *temp=worker;
	Employee *add=search(target,boss);
	Employee *climb=worker;
	if(worker==nullptr or add==nullptr){
		cout<<"Source or destination invalid"<<endl;
	}
	else{
		if(add==worker->superior or add->superior==worker){
			cout<<"Can't shift employees from/to current superior"<<endl;
		}
		else{
			temp=worker;
			if(add->juniors!=nullptr){
				if(worker->juniors==nullptr){
					worker->juniors=add->juniors;
				}
				else{
					temp=worker->juniors;
					while(temp!=nullptr and temp->next!=nullptr){
						temp=temp->next;
					}
					temp->next=add->juniors;
					add->juniors->previous=temp;
				}
			}
			add->juniors=worker->juniors;
			add->breath+=worker->breath;
			temp=worker->juniors;
			while(temp!=nullptr){
				temp->superior=add;
				temp=temp->next;
			}
			depthAdd(add->juniors);
			worker->juniors=nullptr;
			worker->breath=0;
		}
	}		
}
void Tree::depthAdd(Employee *root){
	Employee *temp=root;
	while(temp!=nullptr){
		temp->depth=temp->superior->depth+1;
		depthAdd(temp->juniors);
		temp=temp->next;
	}
}

void Tree::modifyEmployee(string name,string newname, string salary){
	Employee *worker=search(name,boss);
	if(worker==nullptr){
		cout<<"Employee not found"<<endl;
	}
	else{
		if(!newname.empty()){
			worker->name=newname;
		}
		if(!salary.empty()){
			worker->pay=stoi(salary);
		}
	}
}

void Tree::deleteEmployee(std::string name){
	Employee *worker=search(name,boss);
	if(worker->juniors==nullptr){
		if(worker->previous!=nullptr){
			worker->previous->next=worker->next;
		}
		if(worker->next!=nullptr){
			worker->next->previous=worker->previous;
		}
		if(worker==worker->superior->juniors){
			worker->superior->juniors=worker->next;
		}
		if(worker->superior!=nullptr){
			worker->superior->breath--;
		}
		delete worker;
	}
	else{
		cout<<"Employee has subordinates, please shift them"<<endl;
	}
}

void Tree::rankEmployees(string name, string senior){
	Employee *worker=search(name,boss);
	Employee *rank=search(senior,boss);
	Employee *temp=worker;
	if(worker==nullptr){
		cout<<"Employee not found"<<endl;
	}
	else{
		if(rank==worker){
			cout<<"Employee can't outrank themselves"<<endl;
		}
		else{
			if(rank==nullptr){
				temp=worker;
				while(temp->next!=nullptr){
					temp=temp->next;
				}
				if(temp==worker){
					cout<<"Can't change rank, only subordinate"<<endl;
				}
				else{
					rank=temp;
					rank->next=worker;
					worker->previous=rank;	
				}
			}
			else{
				if(worker->superior==rank->superior){
					if(rank->previous!=nullptr){
						rank->previous->next=worker;
					}
					if(worker->previous!=nullptr){
						worker->previous->next=worker->next;
					}
					worker->previous=rank->previous;
					worker->next=rank;
					rank->previous=worker;
					if(worker->superior->juniors==rank){
						worker->superior->juniors=worker;
					}
				}
				else{
					cout<<"Employees do not have same superior"<<endl;
				}
			}
		}
	}
}

Tree::~Tree(){
	cout<<"Deconstructing..."<<endl;
	Employee *temp;
	names.clear();
	names.resize(maxDepth(boss));
	makevector(boss);
	for(int i=names.size()-1;i>0;i--){
		for(int n=names[i].size()-1;n>=0;n--){
			temp=names[i][n];
			cout<<"Deleting: "<<temp->name<<endl;
			deleteEmployee(temp->name);
		}
	}
	if(boss!=nullptr){
		cout<<"Deleting: "<<boss->name<<endl;
		delete boss;
	}
	names.clear();
	cout<<"Done"<<endl;
}
