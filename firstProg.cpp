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
#include<termios.h>
#include "bashrc.h"
#include "commonFunctionalities.h"
#include "pipes.h"
#include "directories.h"
#include "aliases.h"
#include "background.h"
#include "IORedirection.h"
#include "foreground.h"
#include "signalHandler.h"
#include "history.h"
#include "trie.h"
#define Max 4096
int exitStatus;
using namespace std;
extern char **environ;
char *env[100];
vector<int> bgProcessId;
vector<pair<string,string>> aliasesCreated;
char *dirName;
int main(){
	trie trie;
	node *root = trie.createNode();
	trie.createTrieOnCurrentWorkingDirectory(root,getcwd(dirName,Max));
   	int parentPid = getpid();
	enableRawInputMode();	
	environ  = env;
	int background =0,status,pId;
	bashrc bash;
	string readFile = "bashrc.txt";
	string outFile = "history.txt";
	vector<string> commands;
	int fd1 = open(readFile.c_str(), O_RDONLY);
	if(fd1 == -1){
		bash.createBashrc("/etc/passwd","bashrc.txt");
		bash.createBashrc("/etc/hostname","bashrc.txt");
		bash.createBashrc("/etc/environment","bashrc.txt");
	}
	close(fd1);
	bash.readBashRc("bashrc.txt");
	variousSignalsHandled();
	while(1){
		background = 0; 
		vector<string> tokens;
		vector<string> commandForPipes;
		char *temp[Max];
		int count = 0,fd,i=0;
		displayPrompt();	
		string readChar="";
		string file="";
		char buffer;
		long long n1;
		while ( (buffer = getchar()) != '\n'){
			readChar += buffer;
			if(buffer == ' '){
				file="";
			}
			else if(buffer == '\t'){
				trie.autoComplete(root,file);
			}
			else if((int)buffer == 127){
				 cout<<"backspace";
				readChar.pop_back();
			}
			else{	
		       		
				file += buffer;
			}
		}
		commands.push_back(readChar);
		commandForPipes = parseCommandForPipes(readChar);
		if(commandForPipes.size() > 1){
			executePipe(commandForPipes);
		}
		else{
			tokens = parseInputViaSpaces(readChar,temp);
			if(tokens[0] == "exit"){
				_Exit(10);
			}
			else if(checkBackground(tokens)) {
				background =1; 
			}
			else background = 0;
			pId = fork();
			if( pId == 0 ){
				tokens=checkAliases(tokens,aliasesCreated,&count);
				if(count > 1){
					cout<<"alias can't be processed"<<endl;
				}
				else{	
					changeArray(tokens,temp);					
					if(background == 1){
						bgProcessId = handleChildBackground(tokens,temp,bgProcessId,pId);
					}
					else if(tokens[0]=="cd") {
						readDirectory(tokens,temp);
						root = trie.createNode();
						trie.createTrieOnCurrentWorkingDirectory(root,getcwd(dirName,Max));
					}
					else if(tokens[0] == "alias"){
						aliasesCreated = createAliases(tokens,aliasesCreated);
						
					}
					else if(checkRedirectCrietria(tokens)){
						redirectIOToFile(tokens,temp);
						} 	
					else if(tokens[0] == "fg"){			
						//foregroundHandler(tokens);		
						}
					else if(tokens[0] == "history"){
							displayHistory(commands);	
						}
					else if(tokens[0] == "echo"){
							if(tokens[1] == "$$")
								cout<<parentPid<<endl;
							else if(tokens[1] == "$?")
								cout<<exitStatus<<endl;
							else displayCommand(tokens);	
						}
					
					else executeCommand(temp);
				}
			}
			else {
				if (background) {
					handleParentBackground(pId);
				} else { 
					waitpid(pId, &status, 0);
					if(WIFEXITED(status)){
						exitStatus=WEXITSTATUS(status);
					}
				} 		
			}
		}
		
	}
	return 0;
}
