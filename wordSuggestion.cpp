#include "bits/stdc++.h" 

using namespace std; 

#define max_n 100 
 
#define tolerance 4
 
#define LEN 10 



void read(vector<string>&word,vector<string>&freq,string path){
	ifstream ias(path);

  if(!ias.is_open()) std::cout << "Error" << '\n';

 
 
	string v;
	string f;
  while(ias.good()){

    getline(ias,v,',');
    getline(ias,f,'\n');
    transform(v.begin(), v.end(), v.begin(), ::tolower); 
	word.push_back(v);
	freq.push_back(f);

  }

  freq.erase(freq.begin()+freq.size());
 
  ias.close();
  
}


struct node 
{ 
	
	string word; 


	int next[2*LEN]; 


	node(string x):word(x) 
	{ 
		
		for(int i=0; i<2*LEN; i++) 
			next[i] = 0; 
	} 
	node() {} 
}; 

 
node RT; 


node tree[max_n]; 

 
int ptr; 

int min(int a, int b, int c) 
{ 
	return min(a, min(b, c)); 
} 

 
int editDistance(string& a,string& b) 
{ 
	int m = a.length(), n = b.length(); 
	int editdist[m+1][n+1]; 


	for (int i=0; i<=m; i++) 
		editdist[i][0] = i; 
	for (int j=0; j<=n; j++) 
		editdist[0][j] = j; 

 
	for (int i=1; i<=m; i++) 
	{ 
		for (int j=1; j<=n; j++) 
		{ 
			if (a[i-1] != b[j-1]) 
			{ 
				editdist[i][j] = min( 1 + editdist[i-1][j], // deletion 
								1 + editdist[i][j-1], // insertion 
								1 + editdist[i-1][j-1] // replacement 
							); 
			} 
			else
				editdist[i][j] = editdist[i-1][j-1]; 
		} 
	} 
	return editdist[m][n]; 
} 

 
void add(node& root,node& curr) 
{ 
	if (root.word == "" ) 
	{ 
	
		root = curr; 
		return; 
	} 

 
	int dist = editDistance(curr.word,root.word); 

	if (tree[root.next[dist]].word == "") 
	{ 
	 
		ptr++; 

	
		tree[ptr] = curr; 

		
		root.next[dist] = ptr; 
	} 
	else
	{ 
		
		add(tree[root.next[dist]],curr); 
	} 
} 

vector <string> getSimilarWords(node& root,string& s) 
{ 
	vector < string > ret; 
	if (root.word == "") 
	return ret; 

 
	int dist = editDistance(root.word,s); 

	if (dist <= tolerance) ret.push_back(root.word); 

	
	int start = dist - tolerance; 
	if (start < 0) 
	start = 1; 

	while (start < dist + tolerance) 
	{ 
		vector <string> tmp = 
			getSimilarWords(tree[root.next[start]],s); 
		for (auto i : tmp)
			ret.push_back(i); 
		start++; 
	} 
	return ret; 
} 

// driver program to run above functions 
int main(int argc, char const *argv[]) 
{ 
 vector<string>dict,freq;
 string path=argv[1];
   read(dict,freq,path);
 
 
	ptr = 0; 
	int sz = dict.size();

	for(int i=0; i<sz; i++) 
	{ 
		node tmp = node(dict[i]); 
		add(RT,tmp); 
	} 

	string w1 = argv[2]; 
 
	vector < string > match = getSimilarWords(RT,w1); 
    sort(match.begin(),match.end()); 
	if(match.size()>=5)
	for(int i=0;i<5;++i)cout<<match[i]<<" ";
	else
	for(auto i:match)cout<<i<<" ";
	

} 

