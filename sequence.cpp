#include<iostream>
#include<vector>
#include<fstream>


using namespace std;

string processTxt(string input)
{
	//processes the input file
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

void subString(string text, vector<string> &substr)
{
	//records a substring in a vector
	string temp;
	for (int i=0; i< text.size();i++)
	{
		for (int k = i; k <= text.size(); k++)
		{
			temp += text[k];
		}
		substr.push_back(temp);
		temp.clear();

	}
	
}

string find_maxrep(string a, string b)
{
	//find repeated strings
	int i=0;
	int j=0;
	string rep;

	while(a[i]==b[i])
	{
		rep += a[i];
		i++;
	}

	return rep;
}

string find_longest_rep(vector<string> repeated)
{
	// finds the longest string among repeated strings
	int i=0;
	int max_size= repeated[i].size();
	string large;

	for(int j=i+1;j<repeated.size();j++)
	{
		if((repeated[j].size())>max_size)
		{
			max_size= repeated[j].size();
			large= repeated[j];
		}
		
		if((repeated[j].size())==max_size)
		{
			large= repeated[j];
		}
	}
	return large;
}
		
	

void find_rep(vector<string> substr, vector<string> &repeated)
{
	//adds only repeated strings in a new vector
	int i=0, j=1;
	string rep;
	for(int k=0;k<substr.size()-1;k++)
	{
		if((substr[i])[0]== (substr[j])[0])
		{
			rep=find_maxrep(substr[i],substr[j]);
			repeated.push_back(rep);
			rep.clear();
		}
		i++;
		j++;
	}
}

void swap(string *a, string *b) 
{ 
    string t = *a; 
    *a = *b; 
    *b = t; 
}

int partition (vector<string> &substr, int low, int high) 
{
	//for quick sort implementation 

    string pivot = substr[high];    
    int i = (low - 1);  
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (substr[j] <= pivot) 
        { 
            i++;     
            swap(&substr[i], &substr[j]); 
        } 
    } 
    swap(&substr[i + 1], &substr[high]); 
    return (i + 1); 
} 
  
void quickSort(vector<string> &substr, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(substr, low, high); 
        quickSort(substr, low, pi - 1); 
        quickSort(substr, pi + 1, high); 
    } 
}

int main()
{
		//driver

		string input1;
		string input2;
		ifstream myfile;
		myfile.open("DNA.txt");
		vector<string> substr;

		while (getline(myfile, input1))
		{
			input2 = input2 + input1;
		}

		string dna;

		dna = processTxt(input2);
		subString(dna, substr);
		
		int len= substr.size();
		quickSort(substr,0,len-1);

		vector<string> repeated;
		find_rep(substr, repeated);
		
		string large= find_longest_rep(repeated);
		cout<<"Largest string = "<<large<<endl;

		return 0;
	
}
