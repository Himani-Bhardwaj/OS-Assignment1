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
#define Max 4096
using namespace std;
string getInput(){
	string readChar;	
	getline(cin, readChar);
	/*string fileLine = readChar+"\n";
	int fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
	if(write(fd2, fileLine.c_str(), readChar.size()) != readChar.size()){
      		 write(2, "There was an error writing to testfile.txt\n", 43);	
       		exit(3);
        }
	close(fd2);*/
	return readChar;
}
void displayPrompt(){
	uid_t uid = getuid();
	if(to_string(uid) == "0")
		cout<<"Prompt/ ";
	else cout<<"Prompt# ";
}
void executeCommand(char *temp[]){
	if(execvp(temp[0],temp) < 0)
		printf("unknown command\n");
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
