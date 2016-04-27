#include "Tree.h"
#include <iostream>
using namespace std;

int main(int argc, char ** argv){
	string root="";string pay="";
	cout<<"Enter name of boss: "<<endl;
	getline(cin,root);
	cout<<"Enter pay: "<<endl;
	getline(cin,pay);
	Tree Business(root,stoi(pay));
	return 0;
}
