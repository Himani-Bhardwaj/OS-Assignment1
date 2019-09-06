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
extern char **environ;
char *env[100];
vector<int> bgProcessId;
vector<pair<string,string>> aliasesCreated;
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
void createBashrc(string readFile){
	uid_t uid = getuid();
	int fd1, fd2;
	vector<string> userLine; 
	int j=0;
	char buffer;
	char path[4096];
	string readLine="";
	long int n1;
	string outFile = "bashrc.txt";
	fd1 = open(readFile.c_str(), O_RDONLY | O_CREAT);
	if(readFile == "/etc/passwd"){
		fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		while ( (n1 = read(fd1, &buffer, 1)) > 0){
		       	if(buffer != '\n') {readLine += buffer;}
			else {
				stringstream s(readLine);
				string word;
				while(getline(s, word, ':')) userLine.push_back(word);
				if(userLine[2] == to_string(uid)){
					string toFile = "HOME = "+ userLine[5] +"\n"+"USER = "+ userLine[0] +"\n";
					if(write(fd2, toFile.c_str(), toFile.size()) != toFile.size()){
						write(2, "There was an error writing to testfile.txt\n", 43);			
					}
					close(fd2);
					break;
				}
				readLine="";
				userLine.clear();	
			}	
    		}
	}
	else if(readFile == "/etc/hostname"){
		fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		while ( (n1 = read(fd1, &buffer, 1)) > 0){
		       	if(buffer != '\n') {readLine += buffer;}
			else{
				string toFile = "HOSTNAME = "+ readLine +"\n";
				if(write(fd2, toFile.c_str(), toFile.size()) != toFile.size()){
					write(2, "There was an error writing to testfile.txt\n", 43);			
				}
				close(fd2);
				break;	
			}
		}
	}
	else{
	fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		while ( (n1 = read(fd1, path, 4096)) > 0){
		       	if(write(fd2, path, n1) != n1){
           		 write(2, "There was an error writing to testfile.txt\n", 43);	
            		exit(3);
        		}
		}
	}

}
void readBashRc(){
	string readFile="bashrc.txt";	
	int fd1 = open(readFile.c_str(), O_RDONLY);
	vector<string> userLine; 
	char buffer;
	string readLine="";
	long int n1;
	while ( (n1 = read(fd1, &buffer, 1)) > 0){
		       	if(buffer != '\n') {readLine += buffer;}
			else {
				stringstream s(readLine);
				string word;
				while(getline(s, word, '=')) userLine.push_back(word);
				if(userLine[0] == "PATH") setenv("PATH",userLine[1].c_str(),1);
				else if(userLine[0] == "HOME") setenv("HOME",userLine[1].c_str(),1);
				else if(userLine[0] == "HOSTNAME") setenv("HOSTNAME",userLine[1].c_str(),1);
				else if(userLine[0] == "USER") setenv("USER",userLine[1].c_str(),1);			
				readLine="";
				userLine.clear();	
			}	
    		}
}
int main(){
	environ  = env;
	int background =0,status,pId;
	signal(SIGINT, childSignalHandler);
	signal(SIGTTOU, childSignalHandler);
	signal(SIGCONT, childSignalHandler);
	string readFile = "bashrc.txt";
	string outFile = "history.txt";
	int fd1 = open(readFile.c_str(), O_RDONLY);
	if(fd1 == -1){
		createBashrc("/etc/passwd");
		createBashrc("/etc/hostname");
		createBashrc("/etc/environment");
	}
	close(fd1);
	readBashRc();
	//open file and set variables
	while(1){
		background = 0; 
		pid_t fg = tcgetpgrp(STDIN_FILENO),bg;
		vector<string> tokens;
		vector<string> commandForPipes;
		char *temp[Max];
		int count = 0,fd;
		string readChar;
		displayPrompt();
		getline(cin, readChar);
		string fileLine = readChar+"\n";
		int fd2 = open(outFile.c_str(),O_CREAT|O_APPEND|O_WRONLY, 0700);
		if(write(fd2, fileLine.c_str(), readChar.size()) != readChar.size()){
           		 write(2, "There was an error writing to testfile.txt\n", 43);	
            		exit(3);
        	}
		close(fd2);
		commandForPipes = parseCommandForPipes(readChar);
		if(commandForPipes.size() > 1){
			executePipe(commandForPipes);
		}
		else{
			tokens = parseInputViaSpaces(readChar,temp);
			if(checkBackground(tokens)) {
				background =1; 
			}
			else background = 0;
			pId = fork();
			if( pId == 0 ){
				for(int j=0;j< tokens.size();j++){
					for(int i=0;i< aliasesCreated.size();i++){
						if(tokens[j] == aliasesCreated[i].first){
							tokens[j] = aliasesCreated[i].second;
							count++;
						}
					}		
				}	
				if(count > 1){
					cout<<"Unknown Command"<<endl;
				}
				else{						
					if(background == 1){
						//cout<<"closing file descriprors"<<endl;						
						bgProcessId.push_back(pId);
						bg = setsid();					
						string fileName = "/dev/null";
						fd = open(fileName.c_str(),O_RDONLY | O_CREAT|O_APPEND|O_WRONLY);
						//dup2(fd,STDIN_FILENO);
						dup2(fd,STDOUT_FILENO);
						temp[tokens.size()-1] = NULL;	
						executeCommand(temp);
						close(fd);
						continue;
						//setpgid(pId, pId); // Either setpgid call will succeed, depending on how the processes 							are scheduled.
  						//tcsetpgrp(0, pId);
						//signal(SIGTTOU, childSignalHandler);
					}
					else if(tokens[0]=="cd") readDirectory(tokens,temp);
					else if(tokens[0] == "alias"){
						tokens[3].erase(remove( tokens[3].begin(), tokens[3].end(), 							'\"' ),tokens[3].end());					
						aliasesCreated.push_back(make_pair(tokens[1],tokens[3]));
					}
					else if(checkRedirectCrietria(tokens)){
						redirectIOToFile(tokens,temp);
						} 	
					else if(tokens[0] == "fg"){			
						//foregroundHandler(tokens);		
						}
					else executeCommand(temp);
				}
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
