#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

template<class T,class U>
struct node
{
	T T_data;
	U U_data;
	node* next;
};

template< class T,class U>
class list
{
	node<T,U> *root;
	public:
	list():root(NULL){}
	node<T,U>* createnode(T tdata, U udata);
	void display();
	void insertnodetail(T tdata, U udata);
	void findMaxfrequency(int max);
	node<T,U>* getroot();
	~list();
};

template<class T,class U>
void list<T,U>:: display()
{
	//displays the content of each node in the linked list
	if(root!= NULL)
	{
		node<T,U> *temp= root;
		while(temp-> next!=NULL)
		{
			cout<<"Word= "<<temp->T_data<<"| Freq= "<<temp->U_data<<endl;
			temp=temp->next;
		}	
		cout<<"Word= "<<temp->T_data<<"| Freq= "<<temp->U_data<<endl;
	}
}

template<class T, class U>
node<T,U> *list<T,U>:: createnode(T tdata, U udata)
{
	//creates a new node
	node<T,U>* mynode= new node<T,U>;
	mynode-> T_data= tdata;
	mynode-> U_data= udata;
	mynode-> next= NULL;

	return mynode;
}

template<class T,class U>
void list<T,U>::insertnodetail(T tdata, U udata)
{
	//inserts a new node at the end of linked list
	if(root==NULL)
	{
		root= createnode(tdata, udata);
	}

	else
	{
		node<T,U> *temp =root;
		while(temp->next != NULL)
		{
			temp= temp->next;
		}
		temp->next= createnode(tdata, udata);
	}
}

template<class T, class U>
list<T,U>::~list()
{
	//destructor
	if(root!=NULL)
	{
		node<T,U>* temp= root;
		
		while(temp->next != NULL)
		{
			delete temp;
			root=root->next;	
			temp=root;
		}
	}
	
}

void processText(string text)
{
	//clears all characters except english alphabets and spaces
	ofstream outfile;
	outfile.open("processedText.txt");

	for(int i=0;i<text.length();i++)
	{
		if((text[i]<'a'||text[i]>'z')&&(text[i]<'A'||text[i]>'Z')&&text[i]!=' ')
		{
			text.erase(i,1);
			
		}
	}

	outfile<<text;
	outfile.close();
}

template<class T, class U>
void list<T,U>::findMaxfrequency(int count)
{
	//finds the word that has the max freq in the linkedlist
	node<string, int>* temp= root;

	while(temp->next!= NULL)
	{
		if(temp->U_data==count)
		{
			cout<<"The word '"<<temp->T_data<<"' has the highest number of occurences ("<<count<<" occurences)"<<endl;
		}
	
	temp=temp->next;
		
	}
}

int main()
{
	//read the text from input.txt
	string input1,input2;
	ifstream myfile;
	myfile.open("input.txt");

	while(getline(myfile,input1))
	{
		input2=input2+input1;	
	}
		
	myfile.close();

	//process the text in the string
	processText(input2);
	
	myfile.open("processedText.txt");
		
	//clear strings
	input1.erase(0, input1.length());
	input2.erase(0, input2.length());
	
	//read the processed text 
	while(getline(myfile,input1))
	{
		input2=input2+input1;
	}

	myfile.close();
	
	//create an object
	list<string,int> mylist;
	
	//copy each word into an array
	stringstream ss(input2);

	string words[input2.length()];
	int i=0;
	int max=0;
	
	do{
		//insert word in the node and same word in an array with all lowercases
		string lcase;
		string word;
		ss>>word;
		lcase=word;
	
		//insert word and its frequency in a node
		if(i==0)
		{
			mylist.insertnodetail(word,1);
			lcase[0]= (tolower(lcase[0]));
			words[i]=lcase;
			i++;
		}		
	
		else
		{
			int count=1;
			lcase[0]=tolower(lcase[0]);
			for(int j=0;j<i;j++)
			{

				if(words[j] == lcase)
				{
					count++;
				}
		
			}
			
			if(count>max)
			{
				max=count;
			}
			
			words[i]=lcase;
			i++;
			mylist.insertnodetail(word,count);
		}
	}while(ss);

	//find word with max freq
	mylist.findMaxfrequency(max);
	
	return 0;


}
