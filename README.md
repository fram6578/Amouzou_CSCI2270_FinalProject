# Amouzou_CSCI2270_FinalProject

Project Summary:

This project will be an N-ary tree representation of a business hierarchy. 
It'll take the names of the employee and various employee data and organize them according to superiority and senority.
Each employee will be a node and their direct superior will be their parent.
The children of a node are subordinate employees listed according to rank.
Additionally, this project will visualize the business hierarchy and each employee by printing them out in a tree.
It'll also have methods for accessing and modifying employee data.
The end user will be able to utilize the tree through the linux terminal

Dependencies:

This only requires the standard C++11 library no third-party libraries required

How to run:

Download the Trees.h,Trees.cpp, main.cpp, and workers.txt files in one folder. Or just download the repository as a whole. In terminal, cd to the folder with the files and compile using the command "g++ -std=c++11 *.cpp". This should create an a.out file. Now run the a.out file using the command "./a.out filename" where 'filename' is the workers.txt or any file you'd like to test. This should run the program, to learn how to use the program type in 0 for help and then 12 for general directions.

System Requirements:

Must be linux, preferable ubuntu.

Open issues/bugs:

There are numerous bugs with using stoi() to convert strings into integars for the pay rate node property
Running any modifications on the boss will lead to crashing if it is not exception handled.
