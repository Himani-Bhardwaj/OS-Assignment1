#include<bits/stdc++.h>   
#define ALPHABET_SIZE (128) 
using namespace std; 

class node{
	public:
	bool isEndOfString;
	node *children[ALPHABET_SIZE];
};
class trie : public node{
	public:	
	node* createNode();
	bool searchNode(node *root, string value);
	void insert(node *root, string value);
	string autoComplete(node *root, string value);
	void getAllList(node *root,string value);
	void createTrieOnCurrentWorkingDirectory(node *root,char *value);
};
