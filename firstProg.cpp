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
int main(){
	int pId,x;
	while(1){
		
		pId = fork();
		
		if( pId == 0 ){
			cout<<"Prompt$ ";
		string readChar;
		//const char * binaryPath = readChar.c_str();
		vector<string> argStrings; 
		vector<string> tokens;
		char *temp[Max];
		int i=0;
		//cout<<readChar;
		stringstream s(readChar); 
  	  	string word; 
		getline(cin, readChar);
	          while (s >> word) 
        	  {			
			/*cout<<"word "<<word<<endl;
			word += '\0';			
			temp[i] = const_cast<char*> (word.c_str());
			cout<<"inside loop"<<i<<" "<<temp[i]<<endl;
			i++;
			cout<<"temp[0]"<<temp[0]<<endl;*/
			/*argStrings.push_back(word);
			temp.push_back(const_cast<char *>(argStrings.back().c_str()));*/
			tokens.push_back(word);
		  }
			 for (auto it = tokens.begin(); it != tokens.end(); ++it)
    				temp[i++] = const_cast<char*>(it->c_str());
  				temp[i] = NULL;			
	 	  execvp(temp[0],temp);
		}
		else{
			wait(0);		
		}			 
	}
	return 0;
}
