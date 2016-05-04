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
		while(stepper!=climber->superior){//step climbers least senior uncle until it reaches climbers parent
			if(stepper->breath==0){//add the breath of the climber's uncles
				ans+=1;
			}
			else{
				ans+=(stepper->breath);
			}
			stepper=stepper->next;//step across
		}
		climber=climber->superior;//climb up
	}
	if(node->superior!=nullptr and node!=node->superior->juniors){//same as above but stepping through the nodes neighbors
		stepper=node->superior->juniors;
		while(stepper!=node){
			ans++;
			stepper=stepper->next;
		}
	}
	return ans;//return position
}

void Tree::makevector(Employee *root){
	Employee *temp=root;//initialize temporary
	while(temp!=nullptr){//until looped through all neighbors
		makevector(temp->juniors);//loop through node's children
		names[temp->depth].push_back(temp);//add node to 2D vector
		temp=temp->next;//iterate
	}
}

int Tree::maxBreath(Employee *node){
	int crawl=0;//intialize return value and temporary
	Employee *temp=node;
	
	if(node!=nullptr){//if node exists add its breath
		crawl=node->breath;
	}
	temp=node->juniors;//set temp to the nodes children
	while(temp!=nullptr){//until looped through all children
		if(maxBreath(temp)!=0){//add the maximum breath of the children
			crawl+=maxBreath(temp)-1;
		}
		temp=temp->next;//iterate
	}
	if(crawl<=0){//since print statements need some width to print, even nodes with no breath contribute
		crawl=1;
	}
	return crawl;
}

int Tree::maxDepth(Employee *root){
	int climb=0;//intialize temporary and return value
	Employee *temp=root;
	while(temp!=nullptr){//loop through children
		if(climb<maxDepth(temp->juniors)){
			climb=maxDepth(temp->juniors);
		}
		temp=temp->next;
	}
	if(root!=nullptr){//if not a null node increment return value
		climb++;
	}
	return climb;
}

void Tree::promoteEmployee(string name){
	Employee *worker=search(name,boss);
	Employee *temp=worker;
	Employee *add=worker;
	if(worker!=nullptr){//if found exception
		if(worker->superior==nullptr){//boss exception
			cout<<"Already highest position, can't be promoted"<<endl;
		}
		else{
			if(worker->superior->superior==nullptr){//another boss exception
				cout<<"Can't promote to highest position"<<endl;
			}
			else{
				if(worker->juniors==nullptr){//children exception
					//the next three if statements essentially delete the original node while maintaining its information
					if(worker->next!=nullptr){
						worker->next->previous=worker->previous;
					}
					if(worker->previous!=nullptr){
						worker->previous->next=worker->next;
					}
					if(worker==worker->superior->juniors){
						worker->superior->juniors=worker->next;
					}
					//now the node is added back in except underneath a new superior
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
	if(worker==nullptr or add==nullptr){//invalid input exception
		cout<<"Source or destination invalid"<<endl;
	}
	else{
		if(add==worker->superior or add->superior==worker){//direct subordinate/superior exception (since not excepted this would make nodes loop infinitely through themselves)
			cout<<"Can't shift employees from/to current superior"<<endl;
		}
		else{//add all of the intial nodes children to before the least senior of the new node childrens
			temp=worker;
			if(add->juniors!=nullptr){
				if(worker->juniors==nullptr){//if no children just copy over children
					worker->juniors=add->juniors;
				}
				else{
					temp=worker->juniors;
					while(temp!=nullptr and temp->next!=nullptr){//link the two list accordingly
						temp=temp->next;
					}
					temp->next=add->juniors;
					add->juniors->previous=temp;
				}
			}
			add->juniors=worker->juniors;
			add->breath+=worker->breath;
			temp=worker->juniors;
			while(temp!=nullptr){//delete intial nodes children now that they have been copied
				temp->superior=add;
				temp=temp->next;
			}
			depthAdd(add->juniors);//update depth for all children
			worker->juniors=nullptr;
			worker->breath=0;
		}
	}		
}
void Tree::depthAdd(Employee *root){
	Employee *temp=root;
	while(temp!=nullptr){//for all children underneath root node update the depth parameter
		temp->depth=temp->superior->depth+1;
		depthAdd(temp->juniors);
		temp=temp->next;
	}
}

void Tree::modifyEmployee(string name,string newname, string salary){//pay is a string parameter so that a blank string exception can be handled
	Employee *worker=search(name,boss);
	if(worker==nullptr){//found employee exception
		cout<<"Employee not found"<<endl;
	}
	else{
		if(!newname.empty()){//if empty leave alone otherwise update name
			worker->name=newname;
		}
		if(!salary.empty()){//if empty leave alone otherwise update price
			worker->pay=stoi(salary);
		}
	}
}

void Tree::deleteEmployee(std::string name){
	Employee *worker=search(name,boss);
	if(worker->juniors==nullptr){//having children exception handled
		if(worker->previous!=nullptr){//unlink forwards
			worker->previous->next=worker->next;
		}
		if(worker->next!=nullptr){//unlink backwards
			worker->next->previous=worker->previous;
		}
		if(worker==worker->superior->juniors){//remove from parent
			worker->superior->juniors=worker->next;
		}
		if(worker->superior!=nullptr){//update parent breath
			worker->superior->breath--;
		}
		delete worker;//delete node
	}
	else{
		cout<<"Employee has subordinates, please shift them"<<endl;
	}
}

void Tree::rankEmployees(string name, string senior){
	Employee *worker=search(name,boss);
	Employee *rank=search(senior,boss);
	Employee *temp=worker;
	if(worker==nullptr){//found employee exception
		cout<<"Employee not found"<<endl;
	}
	else{
		if(rank==worker){//self senior exception
			cout<<"Employee can't outrank themselves"<<endl;
		}
		else{
			if(rank==nullptr){//if senior is empty, place at end of linked list
				temp=worker;
				while(temp->next!=nullptr){//temp is last node in linked list
					temp=temp->next;
				}
				if(temp==worker){//no other subordinate exception
					cout<<"Can't change rank, only subordinate"<<endl;
				}
				else{//relink worker to end
					rank=temp;
					rank->next=worker;
					worker->previous=rank;	
				}
			}
			else{
				if(worker->superior==rank->superior){//same superior exception
					if(rank->previous!=nullptr){//unlink
						rank->previous->next=worker;
					}
					if(worker->previous!=nullptr){//unlink
						worker->previous->next=worker->next;
					}
					worker->previous=rank->previous;//relink
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
	names.clear();//reinitialize 2D vector
	names.resize(maxDepth(boss));
	makevector(boss);
	for(int i=names.size()-1;i>0;i--){//iterate through the 2D vector in reverse excluding the boss
		for(int n=names[i].size()-1;n>=0;n--){//deleting the children backwards
			temp=names[i][n];
			cout<<"Deleting: "<<temp->name<<endl;
			deleteEmployee(temp->name);
		}
	}
	if(boss!=nullptr){//then delete the boss
		cout<<"Deleting: "<<boss->name<<endl;
		delete boss;
	}
	names.clear();//delete the 2D vector
	cout<<"Done"<<endl;
}
