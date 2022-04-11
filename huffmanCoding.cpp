#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    class Node *left, *right;
    double p;
    char c;
    bool operator()(Node *a, Node *b)
    {
        return (a->p) > (b->p);
    }
    Node *create(double pb, char ch = '#')
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->p = pb;
        newnode->c = ch;
        newnode->left = 0;
        newnode->right = 0;
        return newnode;
    }

    void code(map<char,string> &mp,Node *head=0,string strn = "")
    {
        if (head == 0)
            return;
        if (head->left != 0)
        {
            strn.push_back('0');
            code(mp,head->left,strn);
            strn.pop_back();
        }
        if (head->right != 0)
        {
            strn.push_back('1');
            code(mp,head->right,strn);
            strn.pop_back();
        }
        if (head->left==0 && head->right==0){
            mp[head->c] = strn;
        }
    }
};

string compress(string s,map<char,string> &mp){
    string strn = "";
    cout<<"\n\nOriginal string: ";
    for (char c: s){
        for (int i=7;i>-1;i--){
            if (c&(1<<i)) cout<<'1';
            else cout<<'0';
        }
        strn = strn + mp[c];
    }
    cout<<"\n\nCompressed string: ";
    cout<<strn<<endl;
    cout<<"\nOriginal size: "<<s.size()*8<<" bytes.";
    cout<<"\nCompressed size: "<<strn.size()<<" bytes.\n";
    cout<<"\nPercentage reduction = "<<100-1.0*100*strn.size()/(s.size()*8)<<endl;
    return strn;
}

string decode(string s,Node *root){
    string strn = "";
    int ptr = 0;
    while (ptr<s.size()){
        Node *temp = root;
        while (temp->c=='#'){
            if (s[ptr]=='0'){
                temp = temp->left;
            }
            else temp = temp->right;
            ptr++;
        }
        strn.push_back(temp->c);
    }
    return strn;
}

int main()
{

    map<char, double> probability = {{'a', 0.09}, {'b', 0.065}, {'c', 0.065}, {'d', 0.04}, {'e', 0.06}, 
    {'f', 0.01}, {'g', 0.02}, {'h', 0.01}, {'i', 0.09}, {'j', 0.01}, {'k', 0.02}, {'l', 0.009}, {'m', 0.01}, 
    {'n', 0.03}, {'o', 0.02}, {'p', 0.08}, {'q', 0.01}, {'r', 0.015}, {'s', 0.02}, {'t', 0.03}, {'u', 0.02}, 
    {'v', 0.01}, {'w', 0.001}, {'x', 0.001}, {'y', 0.002}, {'z', 0.0008}, {' ', 0.1612}, {'.', 0.03}, {',', 0.03},{'\n',0.04}};

    priority_queue<Node *, vector<Node *>, Node> pq;
    for (auto z : probability)
        pq.push((new Node())->create(z.second, z.first));
    while (pq.size() > 1)
    {
        Node *a = pq.top();
        pq.pop();
        Node *b = pq.top();
        pq.pop();
        Node *newnode = (new Node())->create(a->p + b->p);
        newnode->left = a;
        newnode->right = b;
        pq.push(newnode);
    }
    Node *root = pq.top();
    map<char,string> maptable;
    root->code(maptable,root);
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string input = "",s;
    while (!in.eof()){
        getline(in,s);
        input = input + s + "\n";
    }
    string zipped = compress(input,maptable);
    string unzipped = decode(zipped,root);
    out<<unzipped<<endl;
    in.close();
    out.close();

    return 0;
}
