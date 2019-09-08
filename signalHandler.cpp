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
#include "signalHandler.h"
#define Max 4096

using namespace std;

void childSignalHandler(int signum) {
    /*int status;
    pid_t pid;
     
    pid = waitpid(-1, &status, WNOHANG);*/
	//cout<<signum<<endl;
	/*string readChar= "fg %1";
	vector<string> tokens;
		char *temp[Max];		
		int i=0;
		stringstream s(readChar); 
  	  	string word; 
	          while (s >> word) 
        	  tokens.push_back(word);
		for (auto it = tokens.begin(); it != tokens.end(); ++it)
    				temp[i++] = const_cast<char*>(it->c_str());
  				temp[i] = NULL;
		
 executeCommand(temp);*/
	//printf("\n Cannot be terminated using Ctrl+C \n"); 
//    fflush(stdout); 
	if(getpgrp() == tcgetpgrp(STDOUT_FILENO)){
		cout<<"yes"<<endl;	
	}
} 

void variousSignalsHandled(){
	signal(SIGINT, childSignalHandler);
	signal(SIGTTOU, childSignalHandler);
	signal(SIGCONT, childSignalHandler);
}
