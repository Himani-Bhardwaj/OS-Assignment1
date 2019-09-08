#include<iostream> 
using namespace std;
class bashrc
{
	string readFile;
	string outFile;
	public:
		void readBashRc(string readFile);
		void createBashrc(string readFile,string outFile);
};
