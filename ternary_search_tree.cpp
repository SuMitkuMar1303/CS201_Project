#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node 
{
    char data;
    int End;
    struct Node* left;
    struct Node* equal;
     struct Node* right;
};
 

Node* createNode(char newData)
{
    struct Node* newNode = new Node();
    newNode->data = newData;
    newNode->End = 0;
    newNode->left = NULL;
    newNode->equal = NULL;
    newNode->right = NULL;
    return newNode;
}
 


void Insert(Node** root,string word,int pos = 0)
{
    if (!(*root))
    *root = createNode(word[pos]);
 
    if ((*root)->data > word[pos])
    Insert(&((*root)->left), word,pos);
 
 
    else if ((*root)->data < word[pos])
    Insert(&((*root)->right), word,pos);
 
 
    else
    {
        if (pos + 1 == word.size())
        (*root)->End = 1;

        else
        Insert(&((*root)->equal), word, pos + 1);
    }
}
 

void Traverse(Node* root,vector<string>& ret,char* buff,int depth = 0)
{
    
    if (!root)
    return;
    
    Traverse(root->left, ret, buff, depth);
 

    buff[depth] = root->data;
 
 
    if (root->End) 
    {
        buff[depth + 1] = '\0';
        ret.push_back(string(buff));
    }
 
    
    Traverse(root->equal, ret, buff, depth + 1);
 
    
    Traverse(root->right, ret, buff, depth);
}

vector<string> Help(Node* root,   string pattern)
{
    
    char buffer[1001];
 
    vector<string> ret;

    Traverse(root, ret, buffer);
 
    if (root->End == 1)
    ret.push_back(pattern);
    return ret;
}
 

vector<string> autocomplete(Node* root,  string pattern)
{
    vector<string> Words;
    int pos = 0;
 

    if (pattern.empty())
    return Words;
 

 
    while (root && pos < pattern.length()) {
 
        if (root->data > pattern[pos])
           
        root = root->left; // then,search the left subTree
 
        
        else if (root->data < pattern[pos])
           
        root = root->right; // then,search right subTree
 
        
        else if (root->data == pattern[pos])
        {
            root = root->equal;
            pos++;
        }

        // If not found
        else
        return Words;
 
    }
 
   
    Words = Help(root, pattern);
 
    return Words;
}
 

 
void Print(vector<string> suggestion,string pat)
{
    
    int i;
    if ( suggestion.size()==3)
    {
        for ( i = 0; i <  suggestion.size()-1;i++)
        cout << pat <<  suggestion[i].c_str() << "\n";
    }
    else
    {
        for ( i = 0; i < suggestion.size();i++)
        cout << pat <<  suggestion[i].c_str() << "\n";
    }
}
bool searchTST(struct Node *root, string pattern)
{
    int pos = 0;
 
    
    if (pattern.empty())
    return false;
 
  
 
    while (root && pos < pattern.length()) {
 
      
        if (root->data > pattern[pos])
            
        return false;
        
        else if (root->data < pattern[pos])
            
        return false;
 
     
        else   
        {
           
            root = root->equal;
            pos++;
        }
 
}
if(root->End)
return true;
else
return false;
}
int main()
{
    vector<string> S= { "was",	"are","be"	,"have""had","were","	can","said","use","will","would","make","like","has",
"look","write","see","could",	"been","call","find","did", "get","come","made","may",
"take","know",	"live",	"give",	"think","say","help","tell","follow","came","indian",
"institute","technology","indiana", "ropar","data","structure","project","mumbai","delhi","bangalore","hyderabad",
"ahemdabad","chennai","kolkota","surat","pune","jaipur","lucknow","kanpur","nagpur",
"indore","thane","bhopal","visakhapatnam","patna","vadodara","ghaziabad","ludhiana"};
 
    Node* Tree = NULL;
 for (string str : S)
    Insert(&Tree, str);

    cout << "Enter prefix\n";
    string pat;
    cin>>pat;
 
    vector<string> suggestion= autocomplete(Tree, pat);

    if (suggestion.size()!=0)
    {  cout << "---Suggestions\n";
        Print(suggestion, pat);
      
    }
   else cout<< "Not Found\n";
    


 
    return 0;
}
