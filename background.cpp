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
#include "background.h"
#include "commonFunctionalities.h"
#define Max 4096
using namespace std;
bool checkBackground(vector<string> tokens){	
	if(tokens[tokens.size() - 1] == "&") return true;
	else return false;
}

vector<int> handleChildBackground(vector<string> tokens,char *temp[Max],vector<int> bgProcessId,int pId){
	//cout<<"closing file descriprors"<<endl;						
	bgProcessId.push_back(pId);
	//bg = setsid();					
	string fileName = "/dev/null";
	int fd = open(fileName.c_str(),O_RDONLY | O_CREAT|O_APPEND|O_WRONLY);
	//dup2(fd,STDIN_FILENO);
	dup2(fd,STDOUT_FILENO);
	temp[tokens.size()-1] = NULL;	
	executeCommand(temp);
	close(fd);
	return bgProcessId;
	//setpgid(pId, pId);
  	//tcsetpgrp(0, pId);
	//signal(SIGTTOU, childSignalHandler);
}

void handleParentBackground(int pId){
	cout<<"starting background job"<<pId<<endl;
	//setpgid(0, 0); // Put in its own process group
  	//tcsetpgrp(0, getpgrp());
	/*childpids [nChildren] = pId;
	nChildren++;*/
	//executeCommand(temp);
	//continue;
}
