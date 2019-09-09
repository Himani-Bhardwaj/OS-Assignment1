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
#include "history.h"
#define Max 4096

using namespace std;

void displayHistory(vector<string> commands){
	if(commands.size() == 0) cout<<"no commands ececuted yet"<<endl;
	else{
		for(int i=0;i< commands.size();i++){
			if(commands[i] != "history")
				cout<<commands[i]<<endl;
		}
	}
}
void displayCommand(vector<string> tokens){
	if(tokens.size() == 0) cout<<" "<<endl;
	else{
		for(int i=1;i< tokens.size();i++){
			tokens[i].erase(remove( tokens[i].begin(), tokens[i].end(), '\"' ),tokens[i].end());			
			cout<<tokens[i]<<" ";
		}
		cout<<endl;
	}
}
