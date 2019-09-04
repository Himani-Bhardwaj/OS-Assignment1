#include<iostream> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<fcntl.h>
#include<vector>
#include<bits/stdc++.h>

#define Max 4096

using namespace std;
void displayPrompt(){
	cout<<"Prompt$ ";
}
void readDirectory(vector<string> tokens,char *temp[]){
	if(tokens.size() == 1 || tokens[1] == "~") chdir("/home");
	else chdir(temp[1]);
}
bool checkRedirectCrietria(vector<string> tokens)
{
	if(tokens.size() >= 3 && (tokens[tokens.size()-2] == ">>" ||	tokens[tokens.size()-2] == ">")) return true;
		else return false;
}
void executeCommand(char *temp[]){
	if(execvp(temp[0],temp) < 0)
		printf("unknown command\n");
	else execvp(temp[0],temp);
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
using namespace std;
int main(){
	int pId,x;
	while(1){
		
		pId = fork();
		
		if( pId == 0 ){
		displayPrompt();
		string readChar; 
		vector<string> tokens;
		char *temp[Max];
		int i=0;
		getline(cin, readChar);
		stringstream s(readChar); 
  	  	string word; 
	          while (s >> word) 
        	  tokens.push_back(word);
		 for (auto it = tokens.begin(); it != tokens.end(); ++it)
    				temp[i++] = const_cast<char*>(it->c_str());
  				temp[i] = NULL;
				if(checkRedirectCrietria(tokens)){
					redirectIOToFile(tokens,temp);
				} 
				else if(tokens[0]=="cd") readDirectory(tokens,temp);
				else executeCommand(temp);
		}
		else{
			wait(0);		
		}			 
	}
	return 0;
}
