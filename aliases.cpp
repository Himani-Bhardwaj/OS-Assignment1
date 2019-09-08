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
#include "aliases.h"
#define Max 4096

using namespace std;

vector<pair<string,string>> createAliases(vector<string> tokens , vector<pair<string,string>> aliasesCreated){
	tokens[3].erase(remove( tokens[3].begin(), tokens[3].end(), '\"' ),tokens[3].end());					
	aliasesCreated.push_back(make_pair(tokens[1],tokens[3]));
	return aliasesCreated;
}

long long checkAliases(vector<string> tokens,vector<pair<string,string>> aliasesCreated){
	long long count = 0;
	for(int j=0;j< tokens.size();j++){
		for(int i=0;i< aliasesCreated.size();i++){
			if(tokens[j] == aliasesCreated[i].first){
				tokens[j] = aliasesCreated[i].second;
				count++;
			}
		}		
	}
	return count;
}	

