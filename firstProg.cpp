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
vector<int> bgProcessId;
void displayPrompt(){
	cout<<"Prompt$ ";
}
void readDirectory(vector<string> tokens,char *temp[]){
	if(tokens.size() == 1 || tokens[1] == "~") chdir("/home");
	else chdir(temp[1]);
}
bool checkBackground(vector<string> tokens){	
	if(tokens[tokens.size() - 1] == "&") return true;
	else return false;
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
void childSignalHandler(int signum) {
    /*int status;
    pid_t pid;
     
    pid = waitpid(-1, &status, WNOHANG);*/
	//cout<<signum<<endl;
	/*string readChar= "fg %1";
	vector<string> tokens;
		char *temp[Max];		
		int i=0;
		stringstream s(readChar); 
  	  	string word; 
	          while (s >> word) 
        	  tokens.push_back(word);
		for (auto it = tokens.begin(); it != tokens.end(); ++it)
    				temp[i++] = const_cast<char*>(it->c_str());
  				temp[i] = NULL;
		
 executeCommand(temp);*/
	//printf("\n Cannot be terminated using Ctrl+C \n"); 
//    fflush(stdout); 
	if(getpgrp() == tcgetpgrp(STDOUT_FILENO)){
		cout<<"yes"<<endl;	
	}
} 
void foregroundHandler(vector<string> tokens){
	cout<<"inside fg";	
	pid_t pgid = tcgetpgrp(STDIN_FILENO);
	int pid = bgProcessId[0];
	setpgid(pid, pgid); // Either setpgid call will succeed, depending on how the processes are scheduled.
  	tcsetpgrp(0, pid);
	//executeCommand(temp);
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
vector<string> parseCommandForPipes(string readChar){
	int i=0;
	vector<string> commandForPipes;	
	stringstream s(readChar); 
  	  string word; 
	  while (getline(s, word, '|')) 
       		commandForPipes.push_back(word);
return commandForPipes;
}
void executePipe(vector<string> commandForPipes){
	pid_t pid;
	vector<string> tokens;
	char *temp[Max];
	int pipes[2];
	int fd =0;
	int i=0;
	while( i < commandForPipes.size() )
	{
		pipe(pipes);
		pid =fork();
		if(pid ==0)
		{
			dup2(fd,STDIN_FILENO);
			if(i+1 < commandForPipes.size() )
    				dup2(pipes[1],STDOUT_FILENO);
			close(pipes[0]);
   	         	close(pipes[1]);
			tokens = parseInputViaSpaces(commandForPipes[i],temp);
			executeCommand(temp);
		}
		else{
			wait(NULL);
			close(pipes[1]);
   			fd=pipes[0];
   			i++;
		}
	}
}
using namespace std;
int main(){
	int background =0,status,pId;
	signal(SIGINT, childSignalHandler);
	signal(SIGTTOU, childSignalHandler);
	signal(SIGCONT, childSignalHandler);
	while(1){
		background = 0; 
		vector<string> tokens;
		vector<string> commandForPipes;
		char *temp[Max];
		string readChar;
		displayPrompt();
		getline(cin, readChar);
		commandForPipes = parseCommandForPipes(readChar);
		if(commandForPipes.size() > 1){
			executePipe(commandForPipes);
		}
		else{
			tokens = parseInputViaSpaces(readChar,temp);
			if(checkBackground(tokens)) {
				background =1; 
			}
				pId = fork();
			if( pId == 0 ){
				if(background == 1){
					//cout<<"closing file descriprors"<<endl;			
					//temp[tokens.size()-1] = NULL;			
					//string fileName = "/dev/null";
					//int fd = open(fileName.c_str(),O_RDONLY);
					//dup2(fd,STDIN_FILENO);
					//dup2(fd,STDOUT_FILENO);
					//bgProcessId.push_back(pId);
					//setpgid(pId, pId); // Either setpgid call will succeed, depending on how the processes are 						scheduled.
  					//tcsetpgrp(0, pId);
					//signal(SIGTTOU, childSignalHandler);
				}
				else if(checkRedirectCrietria(tokens)){
					redirectIOToFile(tokens,temp);
					} 	
				else if(tokens[0] == "fg"){
					cout<<"hi";			
					//foregroundHandler(tokens);		
					}
				else if(tokens[0]=="cd") readDirectory(tokens,temp);
				else executeCommand(temp);
			}
			else {
				if (background) {
					cout<<"starting background job"<<pId<<endl;
					//setpgid(0, 0); // Put in its own process group
  					//tcsetpgrp(0, getpgrp());
					/*childpids [nChildren] = pId;
					nChildren++;*/
					//executeCommand(temp);
					//continue;
				} else { 
					wait(0);
				} 		
			}
		}
		
	}
	return 0;
}
