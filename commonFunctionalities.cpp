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
#include "commonFunctionalities.h"
#include<termios.h>
#define Max 4096
using namespace std;
void enableRawInputMode(){
	struct termios oldIO;
	struct termios newIO;
	tcgetattr(STDIN_FILENO,&oldIO);
	newIO = oldIO;
	newIO.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO,TCSANOW,&newIO);
}
void displayPrompt(){
	uid_t uid = getuid();
	if(to_string(uid) == "0")
		cout<<getenv("PS1")<<"# ";
	else cout<<getenv("PS1")<<"$ ";
}
void executeCommand(char *temp[]){
	if(execvp(temp[0],temp) < 0)
		exit(127);
	else execvp(temp[0],temp);
}
vector<string> parseInputViaSpaces(string readChar,char *temp[Max]){
	int i=0;
	vector<string> tokens;	
	stringstream s(readChar); 
  	  string word; 
	  while (s >> word) 
       		tokens.push_back(word);
		for (auto it = tokens.begin(); it != tokens.end(); ++it)
    				temp[i++] = const_cast<char*>(it->c_str());
  				temp[i] = NULL;
return tokens;
}
