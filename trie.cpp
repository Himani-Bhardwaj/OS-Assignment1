#include<bits/stdc++.h>  
#include"trie.h" 
#include <dirent.h>
#define ALPHABET_SIZE (128) 
using namespace std;

node* trie :: createNode(){	
	node *newNode = (node*) malloc(sizeof(node)); 
        newNode->isEndOfString = false; 
  	for (int i = 0; i < ALPHABET_SIZE; i++) 
        	newNode->children[i] = NULL; 
  return newNode; 
}
void trie :: insert(node *root, string value){
	for(int i=0;i< value.size();i++){
		int index = value[i] - ' ';
		if(root->children[index] == NULL){
			root->children[index] = createNode();
		}
		root = root->children[index];
	}
	root->isEndOfString = true;
}
bool trie :: searchNode(node *root, string value){
	for(int i=0;i< value.size();i++){
		int index = value[i] -  ' ';
		if(root->children[index] == NULL){
			return false;
		}
		root = root->children[index];
	}
	return (root != NULL && root->isEndOfString);
}
string trie :: autoComplete(node *root, string value){
	for(int i=0;i< value.size();i++){		
	int index = (int)value[i] - (int)' ';
		if(root->children[index] == NULL){
			return "No string Found";
		}
		else root = root->children[index];
	}
	 getAllList(root,value);
}
void trie :: getAllList(node *root,string value){
	if(root == NULL) return; 	
	if(root->isEndOfString == 0){
		for(int i=0;i< ALPHABET_SIZE;i++)
		{		
			if(root->children[i] != NULL){
				value += i + ' ';
				getAllList(root->children[i],value);
				value.pop_back();
			}	
		}
	}
	else {
		cout << value <<endl;
		}
}
void trie :: createTrieOnCurrentWorkingDirectory(node *root,char *value){
	DIR *sourcedr = opendir(value);
	struct dirent *de;
	if (sourcedr != NULL) {		
	while((de = readdir(sourcedr)) != NULL){
    			insert(root,de->d_name);
 		 }
  		closedir (sourcedr);
	}
}
