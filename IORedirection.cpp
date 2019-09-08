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
#include "IORedirection.h"
#include"commonFunctionalities.h"
#define Max 4096

using namespace std;
bool checkRedirectCrietria(vector<string> tokens)
{
	if(tokens.size() >= 3 && (tokens[tokens.size()-2] == ">>" ||	tokens[tokens.size()-2] == ">")) return true;
		else return false;
}

void redirectIOToFile(vector<string> tokens,char *temp[]){
	string fileName = tokens[tokens.size() -1 ];
	int fd;
	if(tokens[tokens.size()-2] == ">>")
		fd= open(fileName.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	else
		fd= open(fileName.c_str(), O_WRONLY | O_APPEND , S_IRUSR | S_IWUSR);
	if(fd < 0) fd = open(fileName.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	temp[tokens.size()-2] = NULL; temp[tokens.size()-1]=NULL;
	dup2(fd,STDOUT_FILENO);
	executeCommand(temp);
}
