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
#define Max 4096
using namespace std;

bool checkBackground(vector<string> tokens);
vector<int> handleChildBackground(vector<string> tokens,char *temp[Max],vector<int> bgProcessId,int Pid);
void handleParentBackground(int pId);
