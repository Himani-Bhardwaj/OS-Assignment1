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
#include "foreground.h"
#define Max 4096

using namespace std;
void foregroundHandler(vector<string> tokens){
	/*cout<<"inside fg";	
	pid_t pgid = tcgetpgrp(STDIN_FILENO);
	int pid = bgProcessId[0];
	setpgid(pid, pgid); // Either setpgid call will succeed, depending on how the processes are scheduled.
  	tcsetpgrp(0, pid);*/
	//executeCommand(temp);
}

