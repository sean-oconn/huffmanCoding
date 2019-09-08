//Sean O'Connor and Jeffrey Martin
#include <bits/stdc++.h>
using namespace std;
string final;
class Huffman{
  struct Node{
    char data;
    int freq;
    Node* left;
    Node* right;
    Node(char data, int freq):data(data), freq(freq),left(nullptr),right(nullptr){}

  ~Node(){
    delete left;
    delete right;
  }
};
struct compare{
  bool operator()(Node* l, Node* r){
    return (l->freq > r->freq);
  }
};
Node* top;
void PrintCode(Node* root, string str){
  if (root==nullptr) return;
  if(root->data != '$')
{
  cout << root->data << " : " << str << "\n";
}
PrintCode(root->left, str + "0");
PrintCode(root->right, str + "1");


}
void encode(Node* root, string str, unordered_map<char,string> &Codes){
  if (root==nullptr) return;
  if(!root->left and !root->right){
    Codes[root->data]=str;
  }
  encode(root->left, str+"0", Codes);
  encode(root->right, str+"1", Codes);
}

public:
  Huffman(){};
  ~Huffman(){
    delete top;
  }
  void decode(Node*root, int&index, string str){
    ofstream output;
    output.open("decoded.txt",std::ios_base::app);
    if(root==nullptr) return;
    if(!root->left and !root->right){
      output<<root->data;
      return;
    }
    cout<<final;
    index++;
    if(str[index]=='0'){
      decode(root->left, index, str);
    }
    else{
      decode(root->right,index,str);
    }
  }
  void GetCode(vector<char>& data, vector<int> &freq, int size, string input){
    Node* left;
    Node* right;
    priority_queue<Node*,vector<Node*>,compare >minHeap;
    for (int i=0;i<size; i++){
      minHeap.push(new Node(data[i], freq[i]));
    }
    while(minHeap.size()!=1){
      left=minHeap.top();
      minHeap.pop();
      right=minHeap.top();
      minHeap.pop();
      top=new Node('$', left->freq+right->freq);
      top->left=left;
      top->right=right;
      minHeap.push(top);
    }
    Node* root=minHeap.top();
    unordered_map<char,string> Codes;
    encode(root,"",Codes);

    PrintCode(minHeap.top(),"");
    string str="";
    for (char ch: input){
      str+=Codes[ch];
    }
    //cout<<str<<endl;
    ofstream enc;
    enc.open("encoded.txt");
    enc<<str<<endl;
    enc.close();
    int index=-1;
    while(index<(int)str.size()-2){
      decode(root,index,str);
    }
  }
};
int main(){
  unordered_map<char,int> freq;
  int value;
  char ch;
  fstream inFile;
  Huffman test;
  vector<char> keys;
  vector<int> vals;
  vector<pair<char,int>> combine;
  inFile.open("frequency.txt");
  while(inFile>>ch){

    inFile>>value;
    freq[ch]=value;
  }
  for(auto i : freq) {
    keys.push_back(i.first);
    vals.push_back(i.second);
}
fstream enter;
string words;
enter.open("input.txt");
enter>>words;
int size=keys.size();
test.GetCode(keys,vals,size,words);
}
