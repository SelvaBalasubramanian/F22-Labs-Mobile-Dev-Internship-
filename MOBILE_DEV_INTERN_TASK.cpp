#include<iostream>
#include<map>
#include<utility>
#include <fstream>
#include<algorithm>
#include<string>
using namespace std;


struct tnode{
	map<char , tnode *> t;
	bool eos;
};

string str; // global string for input without space

/*

	Insert & Search Fuctions for Trie Datastructure.
	Search is not used for given problem.

*/

void insertInTrie(string s, tnode *current , int index){
	int len = s.length();
	cout<<s[index];
	if(index == len){
		cout<<endl;
		current->eos = true;
		return;
	}
	char c = s[index];
	if(current->t.find(c) == current->t.end()){
		tnode *n ;
		n = new tnode();
		current->t.insert(make_pair(c,n));		
	}
	insertInTrie(s, current->t[c] , index+1);
}

bool searchInTrie(string s, tnode *current , int index){
	if(s.length() == index){
		return current->eos;
	}
	char c = s[index];
	if(current->t.find(c) == current->t.end()){
		return false;
	}
	return searchInTrie(s, current->t[c] , index+1);
}


bool seprateString(tnode *root, tnode *current , int index){
	if(str.length() == index){
		return current->eos;
	}
	char c = str[index];
	if((current->t.find(c) != current->t.end()) && seprateString(root,current->t[c],index+1)){
			// cout<<index<<" "<<str[index]<<endl;
		if(current->eos){ 
			// cout<<index<<endl; // index at space to be inserted
			str.insert(index," ");
		}
		return true;
	}
	else if(current->eos && seprateString(root,root,index)){
			// cout<<index<<" "<<str[index]<<endl;
		if(current->eos){ 
			// cout<<index<<endl; // index at space to be inserted
			str.insert(index," ");
		}
		return true;
	}
	return false;
}

int main(){
	str = "Packmyboxwithfivedozenliquorjugs"; // Input String // modify here
	tnode *root ;
	root = new tnode();
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	ifstream file("DB.rtf");//reading DB file
	if(file.is_open()){
		string l;
		while(getline(file,l,',')){
			remove(l.begin(),l.end(),' ');
			remove(l.begin(),l.end(),'\n');
			cout<<l<<l.length()<<endl; //print each string certain diffculty in trimming string
			insertInTrie(l,root,0);  //inserting each string in Trie data structure
			getline(file,l,' '); 
		}
	}


	if(seprateString(root,root,0)){
		cout<<"Output : "<<str<<endl;
	}
	else{
		cout<<"Output : Invalid Input"<<endl;
	}
	return 0;
}




















