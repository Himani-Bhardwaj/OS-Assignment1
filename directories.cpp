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
#include"directories.h"
#define Max 4096
using namespace std;
void readDirectory(vector<string> tokens,char *temp[]){
	if(tokens.size() == 1 || tokens[1] == "~") chdir(getenv("HOME"));
	else chdir(temp[1]);
}
