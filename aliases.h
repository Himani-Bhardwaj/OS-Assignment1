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
vector<pair<string,string>> createAliases(vector<string> tokens,vector<pair<string,string>> aliasesCreated);
long long checkAliases(vector<string> tokens,vector<pair<string,string>> aliasesCreated);
