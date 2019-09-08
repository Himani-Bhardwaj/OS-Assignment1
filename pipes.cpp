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
#include"pipes.h"
#include"commonFunctionalities.h"
#define Max 4096
using namespace std;
vector<string> parseCommandForPipes(string readChar){
	int i=0;
	vector<string> commandForPipes;	
	stringstream s(readChar); 
  	  string word; 
	  while (getline(s, word, '|')) 
       		commandForPipes.push_back(word);
return commandForPipes;
}
void executePipe(vector<string> commandForPipes){
	pid_t pid;
	vector<string> tokens;
	char *temp[Max];
	int pipes[2];
	int fd =0;
	int i=0;
	while( i < commandForPipes.size() )
	{
		pipe(pipes);
		pid =fork();
		if(pid ==0)
		{
			dup2(fd,STDIN_FILENO);
			if(i+1 < commandForPipes.size() )
    				dup2(pipes[1],STDOUT_FILENO);
			close(pipes[0]);
   	         	close(pipes[1]);
			tokens = parseInputViaSpaces(commandForPipes[i],temp);
			executeCommand(temp);
		}
		else{
			wait(NULL);
			close(pipes[1]);
   			fd=pipes[0];
   			i++;
		}
	}
}
