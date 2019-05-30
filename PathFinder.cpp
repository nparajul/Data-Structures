#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<list>

#define COUNT 10 

using namespace std;

template<class T, class U>
struct node{
	T data;
	U freq;
	node* left;
	node* right;
};

template<class T, class U>
class Heap{
	node<T,U> *head;
	public:
	node<T,U> *createnode(T tdata,U freq );
	node<T,U> *push(node<T,U> *root, T tdata, U freq);
	void swap(node<T,U> *x, node<T,U> *y);
	void display(node<T,U> *root);
	void arrange_min(node<T,U> *root);
	void arrange_max(node<T,U> *root);
	void minTop(node<T,U> *root);
	void gethead(node<T,U>* root);
	void min_Sum(node<T,U> * &root, Heap<T,U> minHeap, list<pair<int,char>> &myList,Heap<T,U> &finalHeap, node<T,U>* root2,vector<node<T,U>*> &myvec);
	node<T,U>* FindMin(node<T,U> *root);
	void print2DUtil(node<T,U> *root, int space);
	void makeleaves(list<pair<int, char>> myList, vector<node<T,U>*> &myvec, Heap<T,U> Heap);
	void findNum(node<T,U>* root,string str);
	
};

template<class T,class U>
node<T,U> *Heap<T,U>:: createnode(T  tdata, U freq)
	{
	node<T,U> *mynode= new node<T,U>;
	mynode->data= tdata;
	mynode->freq= freq;
	mynode->left= NULL;
	mynode->right= NULL;

	return mynode;
}

template <class T,class U>
node<T,U> *Heap<T,U>:: push(node<T,U> *root, T tdata,U freq)
{
	if(root == NULL)
	{
		root= createnode(tdata, freq);
		return root;
	}
	
	else if(freq <= root->freq)
	{
		root->left= push(root->left, tdata, freq);
	}
	else
	{
		root->right= push(root->right, tdata,freq);
	}
	return root;
}

template <class T,class U>
void Heap<T,U> :: arrange_min(node<T,U>* root)
{
	if(root!= NULL)
	{
		arrange_min(root->left);
		arrange_min(root->right);
		minTop(root);
	}
}

template <class T,class U>
void Heap<T,U>:: minTop(node<T,U>* root)
{
	node<T,U> *min= root;
	node<T,U> *rootLeft= root->left;
	node<T,U> *rootRight= root->right;
		
	if(root->left!=NULL && rootLeft->freq < root->freq)
	{
		min =rootLeft;
	}

	if(root->right != NULL && rootRight->freq < root->freq)
	{
		min= rootRight;
	}

	if(root != min)
	{
		swap(min,root);
		minTop(min);
	}
}

template <class T,class U>
void Heap<T,U>:: print2DUtil(node<T,U> *root, int space) 
{ 
     
    if (root == NULL) 
        return; 
  
     
    space += COUNT; 
  
    
    print2DUtil(root->right, space); 
  
     
    printf("\n"); 
    for (int i = COUNT; i < space; i++) 
        printf(" "); 
    cout<<root->data<<" and "<<root->freq<<endl; 
  
    
    print2DUtil(root->left, space); 
} 

template <class T,class U>
void Heap<T,U>:: swap(node<T,U> *x, node<T,U> *y)
{
	int temp=x->freq;
	char temp2= x->data;
	x->freq= y->freq;
	x->data= y->data;
	y->freq= temp;
	y->data= temp2;
}

template<class T,class U>
node<T,U>* Heap<T,U>:: FindMin(node<T,U> *root)
{
	if(root!=NULL)
	{
		if(root->left==NULL)
		{
			return root;
		}
	
		else
		{
			return FindMin(root->left);
		}
	}		
}

template<class T, class U>
void Heap<T,U>::display(node<T,U> *root)
{
	if(root!=NULL)
	{
		display(root->left);
		cout<<root->data<<" "<<root->freq<<endl;
		display(root->right);
	}
}


string processTxt(string input)
{
	string text;
        for (int i = 0;i<input.length();i++)
        {
                if (input[i] >= 'a'&&input[i] <= 'z')
                {
                        text += input[i];
                }
        }
        return text;

}

void make_List(list<pair<int,char>> &myList, string dna)
{
	char curr= dna[0];
        int count=0;
        for(int i=0; i<dna.length();i++)
        {
                if(dna[i]== curr)
                {
                        count++;
                }
                else
                {
                        myList.push_back(make_pair(count,curr));
                        curr=dna[i];
                        count=1;
                }
        }
        myList.push_back(make_pair(count,curr));
}

template<class T, class U>
void Heap<T,U>::min_Sum(node<T,U> * &root, Heap<T,U> minHeap, list<pair<int,char>> &myList, Heap<T,U> &finalHeap, node<T,U>* root2,vector<node<T,U>*> &myvec)
{
	list<pair<int,char>>::iterator it = myList.begin();
	if(!myList.empty())
	{
		int a= (*it).first;
		node<T,U>* goleft=NULL;
				
		node<T,U>* min2nd= root->left;
		advance(it, 1);
		int b= (*it).first;
		node<T,U>* goright=NULL;
		
		myList.erase(myList.begin());
		myList.erase(it);
		myList.push_back(make_pair(a+b,'I'));
		myList.sort();
		
		root2= finalHeap.push(root2, 'I',a+b );
		root2->left= myvec[0];
		myvec.erase(myvec.begin());
		root2->right= myvec[0];
		myvec.erase(myvec.begin());
		myvec.push_back(root2);

		return;
			
	}
}

template<class T, class U>
void Heap<T,U>:: findNum(node<T,U>* root,string str)
{
	if(root!= NULL)
	{
		if(root->left==NULL && root->right==NULL)
		{
			cout<<root->data<<"'s code: "<<str<<endl;
		}
	
		findNum(root->left,str+"0");
		findNum(root->right, str+"1");
	}
}

template<class T, class U>
void Heap<T,U>:: makeleaves(list<pair<int, char>> myList, vector<node<T,U>*> &myvec, Heap<T,U> Heap)
{
	for(list<pair<int,char>>::iterator pq= myList.begin(); pq!= myList.end(); pq++)
	{
		node<T,U>* curr = Heap.createnode((*pq).second, (*pq).first);
		myvec.push_back(curr);
	}
}
	

	
int main()
{
	string input1;
	string input2;
	ifstream myfile;
	myfile.open("DNA.txt");
	vector<string> substr;
	list<pair<int,char>> myList;
	
	while (getline(myfile, input1))
	{
		input2 = input2 + input1;
	}
	
	string dna;
	
	dna = processTxt(input2);
	sort(dna.begin(), dna.end());
	make_List(myList, dna);

	myList.sort();
	
	node<char,int> *root =NULL;
	Heap<char,int> minHeap;
	Heap<char,int> finalHeap;
	Heap<char,int> Heap;
	node<char,int> *root2=NULL;
	vector<node<char,int>*> myvec;
	
	for(list<pair<int,char>>::iterator pq= myList.begin(); pq!= myList.end(); pq++)
	{
		root=minHeap.push(root,(*pq).second, (*pq).first);
	}
	
	finalHeap.makeleaves(myList,myvec,Heap);
	minHeap.arrange_min(root);
	myList.sort();
	
	while(myvec.size()>1)
	{
		minHeap.min_Sum(root, minHeap, myList,finalHeap,root2,myvec);
	}
	string code;

	node<char,int>* ans=NULL;
	ans= myvec[0];
	finalHeap.findNum(ans, code);
	
	return 0;
}

















