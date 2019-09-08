#include<iostream> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<fcntl.h>
#include<vector>
#include<bits/stdc++.h>
#include<signal.h>
#include"bashrc.h"
using namespace std;
void bashrc :: createBashrc(string readFile,string outFile){
	uid_t uid = getuid();
	int fd1, fd2;
	vector<string> userLine; 
	int j=0;
	char buffer;
	char path[4096];
	string readLine="";
	long int n1;
	//string outFile = "bashrc.txt";
	fd1 = open(readFile.c_str(), O_RDONLY | O_CREAT);
	if(readFile == "/etc/passwd"){
		fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		while ( (n1 = read(fd1, &buffer, 1)) > 0){
		       	if(buffer != '\n') {readLine += buffer;}
			else {
				stringstream s(readLine);
				string word;
				while(getline(s, word, ':')) userLine.push_back(word);
				if(userLine[2] == to_string(uid)){
					string toFile = "HOME = "+ userLine[5] +"\n"+"USER = "+ userLine[0] +"\n";
					if(write(fd2, toFile.c_str(), toFile.size()) != toFile.size()){
						write(2, "There was an error writing to testfile.txt\n", 43);			
					}
					close(fd2);
					break;
				}
				readLine="";
				userLine.clear();	
			}	
    		}
	}
	else if(readFile == "/etc/hostname"){
		fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		while ( (n1 = read(fd1, &buffer, 1)) > 0){
		       	if(buffer != '\n') {readLine += buffer;}
			else{
				string toFile = "HOSTNAME = "+ readLine +"\n";
				if(write(fd2, toFile.c_str(), toFile.size()) != toFile.size()){
					write(2, "There was an error writing to testfile.txt\n", 43);			
				}
				close(fd2);
				break;	
			}
		}
	}
	else{
	fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		while ( (n1 = read(fd1, path, 4096)) > 0){
		       	if(write(fd2, path, n1) != n1){
           		 write(2, "There was an error writing to testfile.txt\n", 43);	
            		exit(3);
        		}
		}
	}

}
void bashrc :: readBashRc(string readFile){
	//string readFile="bashrc.txt";	
	int fd1 = open(readFile.c_str(), O_RDONLY);
	vector<string> userLine; 
	char buffer;
	string readLine="";
	long int n1;
	while ( (n1 = read(fd1, &buffer, 1)) > 0){
		       	if(buffer != '\n') {readLine += buffer;}
			else {
				stringstream s(readLine);
				string word;
				while(getline(s, word, '=')) userLine.push_back(word);
				if(userLine[0] == "PATH") setenv("PATH",userLine[1].c_str(),1);
				else if(userLine[0] == "HOME") setenv("HOME",userLine[1].c_str(),1);
				else if(userLine[0] == "HOSTNAME") setenv("HOSTNAME",userLine[1].c_str(),1);
				else if(userLine[0] == "USER") setenv("USER",userLine[1].c_str(),1);			
				readLine="";
				userLine.clear();	
			}	
    		}
}
