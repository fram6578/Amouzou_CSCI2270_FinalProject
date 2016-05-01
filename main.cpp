#include "Tree.h"
#include <iostream>
using namespace std;

void PrintMenu(){
	cout<<"=====Main Menu====="<<endl;
	cout<<"0. Help"<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Add Employee"<<endl;
	cout<<"3. Find Employee"<<endl;
	cout<<"4. List Employees"<<endl;
	cout<<"5. Print Employees"<<endl;
	cout<<"6. Shift Employees"<<endl;
	cout<<"7. Modify Employees"<<endl;
}
void EmployeeMenu(){
	cout<<"=====Employee Menu====="<<endl;
	cout<<"7. Back"<<endl;
	cout<<"8. Change Information"<<endl;
	cout<<"9. Change Rank"<<endl;
	cout<<"10. Promote Employee"<<endl;
	cout<<"11. Fire Employee"<<endl;
}

void HelpMenu(int stop){
	int in=-1;
	string input="";
	while(in!=stop){
		cout<<"=====Help Menu====="<<endl;
		cout<<"0. Back"<<endl;
		cout<<"1. Quit"<<endl;
		cout<<"2. Add Employee"<<endl;
		cout<<"3. Find Employee"<<endl;
		cout<<"4. List Employees"<<endl;
		cout<<"5. Print Employees"<<endl;
		cout<<"6. Shift Employees"<<endl;
		cout<<"7. Modify Employees"<<endl;
		cout<<"8. Change Information"<<endl;
		cout<<"9. Change Rank"<<endl;
		cout<<"10. Promote Employee"<<endl;
		cout<<"11. Fire Employee"<<endl;
		cout<<"12. General Information"<<endl;
		getline(cin,input);
		in=stoi(input);
		if(in==1){
			cout<<endl;
			cout<<"Quit"<<endl;
			cout<<"Prints exit message and deconstructs employee tree, deleting each employee node."<<endl;
			cout<<"Exits program, no input required"<<endl;
			cout<<endl;
		}
		else{
			if(in==2){
				cout<<endl;
				cout<<"Add Employee"<<endl;
				cout<<"Adds employee with specified name and pay under specified superior and before specified senior"<<endl;
				cout<<"If superior is not found, prints error message"<<endl;
				cout<<"If senior is not found or no senior is entered, places new employee at most senior position"<<endl;
				cout<<endl;
			}
			else{
				if(in==3){
					cout<<endl;
					cout<<"Find Employee"<<endl;
					cout<<"Finds and displays information of employee with specified name"<<endl;
					cout<<"If the employee is not found, prints error message"<<endl;
					cout<<endl;
				}
				else{
					if(in==4){
						cout<<endl;
						cout<<"List Employees"<<endl;
						cout<<"Prints out all employee names in a column, no input required"<<endl;
						cout<<endl;
					}
					else{
						if(in==5){
							cout<<endl;
							cout<<"Print Employees"<<endl;
							cout<<"Prints out all employee names in a tree, with vertical lines indicating superiors and horizontal lines indicating seniority"<<endl;
							cout<<"No input required"<<endl;
							cout<<endl;
						}
						else{
							if(in==6){
								cout<<endl;
								cout<<"Shift Employees"<<endl;
								cout<<"Moves all employees under one specified employee to another specified employee"<<endl;
								cout<<"Both employees must exist in the tree, and cannot be direct superior/subordinate to each other"<<endl;
								cout<<endl;
							}
							else{
								if(in==7){
									cout<<endl;
									cout<<"Modify Employees"<<endl;
									cout<<"Enters into secondary menu for changing employee information/position"<<endl;
									cout<<endl;
								}
								else{
									if(in==8){
										cout<<endl;
										cout<<"Change Information"<<endl;
										cout<<"Changes specified employee's name and pay to specified inputs"<<endl;
										cout<<"If either inputs are blank the respective information remains unchanged"<<endl;
										cout<<endl;
									}
									else{
										if(in==9){
											cout<<endl;
											cout<<"Change Rank"<<endl;
											cout<<"Changes specified employee's rank to be before the specified senior"<<endl;
											cout<<"If the senior input is blank, the employee is moved to the most senior position"<<endl;
											cout<<"Otherwise the senior and employee must have the same superior"<<endl;
											cout<<endl;
										}
										else{
											if(in==10){
												cout<<endl;
												cout<<"Promote Employee"<<endl;
												cout<<"Moves specified employee up one hierarchical level"<<endl;
												cout<<"Specified employee must have no subordinates, so a preliminary shift is necessary"<<endl;
												cout<<"Promoted employee is automatically placed in the least senior position"<<endl;
												cout<<endl;
											}
											else{
												if(in==11){
													cout<<endl;
													cout<<"Fire Employee"<<endl;
													cout<<"Only employees with no subordinates can be fired"<<endl;
													cout<<endl;
												}
												else{
													if(in==12){
														cout<<endl;
														cout<<"Welcome to my employee tree program"<<endl;
														cout<<endl;
														cout<<"Each employee node on the tree has 3 types of neighbooring nodes"<<endl;
														cout<<"A superior: which is its parent\nTeam members, which are its next/previous nodes\nAnd subordinates, which are its children"<<endl;
														cout<<"The node's 'pay' is an int that reflects the employee's salary in grand";
														cout<<endl;
														cout<<"Navigate menus by typing in the number of the desired option"<<endl;
														cout<<"Numerical menu navigation is sensitive"<<endl;
														cout<<"Whenever a numerical value is expected entering letters or punction or leaving it blank causes an stoi() error"<<endl;
														cout<<"This includes entering pay values (except when changing employee information where the blank error is handled) and menu values"<<endl;
														cout<<endl;
														cout<<"The intial tree is built from a text file containing the employee names and information"<<endl;
														cout<<"The boss node can and should only be changed from the txt file on which it is the first line"<<endl;
														
													}
													else{
														if(in!=0){
															cout<<"Invalid input"<<endl;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}	
			}
		}	
	}
}
int main(int argc, char ** argv){
	string name="";
	string pay="";
	string senior="";
	string uprank="";
	string input="";
	int in=-1;
	Tree Business(argv[1]);
	
	while(in!=1){
		PrintMenu();
		getline(cin,input);
		in=stoi(input);
		if(in==0){
			HelpMenu(in);
		}
		else{
			if(in==1){
				cout<<"Goodbye!"<<endl;
			}
			else{
				if(in==2){
					cout<<"Enter name of senior: "<<endl;
					getline(cin,senior);
					cout<<"Enter name of employee: "<<endl;
					getline(cin,name);
					cout<<"Enter pay: "<<endl;
					getline(cin,pay);
					cout<<"Enter name of outranking co-worker: "<<endl;
					getline(cin,uprank);
					Business.addEmployee(name,stoi(pay),senior,uprank);	
				}
				else{
					if(in==3){
						cout<<"Enter name of employee: "<<endl;
						getline(cin,name);
						Business.findEmployee(name);
					}
					else{
						if(in==4){
							Business.listEmployees();
						}
						else{
							if(in==5){
								Business.printEmployees();
							}
							else{
								if(in==6){
									cout<<"Enter name of employee: "<<endl;
									getline(cin,name);
									cout<<"Enter name of target employee: "<<endl;
									getline(cin,senior);
									Business.shiftEmployees(name,senior);
								}
								else{
									if(in==7){
										in=-1;
										while(in!=7){
											EmployeeMenu();
											getline(cin,input);
											in=stoi(input);
											if(in==8){
												cout<<"Enter name of employee: "<<endl;
												getline(cin,name);
												cout<<"Enter desired name of employee: "<<endl;
												getline(cin,senior);
												cout<<"Enter pay: "<<endl;
												getline(cin,pay);
												Business.modifyEmployee(name,senior,pay);
											}
											else{
												if(in==9){
													cout<<"Enter name of employee: "<<endl;
													getline(cin,name);
													cout<<"Enter name of outranking employee: "<<endl;
													getline(cin,uprank);
													Business.rankEmployees(name,uprank);
												}
												else{
													if(in==10){
														cout<<"Enter name of employee: "<<endl;
														getline(cin,name);
														Business.promoteEmployee(name);
													}
													else{
														if(in==11){
															cout<<"Enter name of employee: "<<endl;
															getline(cin,name);
															Business.deleteEmployee(name);
														}
														else{
															cout<<"Invalid input"<<endl;
														}
													}
												}
											}
										}
									}
									else{
										cout<<"Invalid input"<<endl;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
