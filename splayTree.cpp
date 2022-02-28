/* Splay tree implementation in C/C++
Author - Abhishek Kumar */
#include<iostream>
using namespace std;

class Splay{
    public:
        static class Splay *root;
        class Splay *par, *left, *right;
        int data;

        Splay * create(int data){
            Splay *newnode = (Splay *)malloc(sizeof(Splay));
            newnode->data = data;
            newnode->left = 0;
            newnode->right = 0;
            newnode->par = 0;
            return newnode;
        }

        void dfs(Splay *head = root){
            if (root==0) return;
            if (head->left!=0){
                dfs(head->left);
            }
            cout<<head->data<<' ';
            if (head->right!=0){
                dfs(head->right);
            }
        }

        void rightRotation(Splay *x){
            Splay *y = x->left;
            x->left = y->right;
            if (y->right!=0){
                y->right->par = x;
            }
            if (x->par!=0 && x->par->right==x){
                x->par->right = y;
            }
            else if (x->par!=0 && x->par->left==x){
                x->par->left = y;
            }
            y->par = x->par;
            y->right = x;
            x->par = y;
        }

        void leftRotation(Splay *x){
            Splay *y = x->right;
            x->right = y->left;
            if (y->left!=0){
                y->left->par = x;
            }
            if (x->par!=0 && x->par->left==x){
                x->par->left = y;
            }
            else if (x->par!=0 && x->par->right==x){
                x->par->right = y;
            }
            y->par = x->par;
            y->left = x;
            x->par = y;
        }

        void splay(Splay *newnode){
            if (newnode->par==0){
                root = newnode;
                return;
            }
            Splay *p = newnode->par, *g = p->par;
            if (newnode->par==root){
                if (newnode->par->left==newnode){
                // cout<<"hi\n";
                    rightRotation((p));
                }
                else{
                // cout<<"hello\n";
                    leftRotation((p));
                }
            }
            else if (g->left==p && p->left==newnode){
                rightRotation((g));
                rightRotation((p));
            }
            else if (g->right==p && p->right==newnode){
                leftRotation((g));
                leftRotation((p));
            }
            else if (g->left==p){
                leftRotation((p));
                rightRotation((g));
            }
            else{
                rightRotation((p));
                leftRotation((g));
            }
            splay(newnode);
        }

        void insert(int data){
            Splay *newnode = create(data);
            if (root==0){
                root = newnode;
                return;
            }
            Splay *temp = root, *prev = 0;
            while (temp!=0){
                prev = temp;
                if (data<temp->data){
                    temp = temp->left;
                }
                else if (data>temp->data){
                    temp = temp->right;
                }
                else{
                    return;
                }
            }
            if (data<prev->data){
                prev->left = newnode;
            }
            else{
                prev->right = newnode;
            }
            newnode->par = prev;
            splay(newnode);
        }

        Splay *inorderPredecessor(Splay *head){
            if (head==0) return head;
            while (head->right!=0){
                head = head->right;
            }
            return head;
        }

        Splay *inorderSuccessor(Splay *head){
            if (head==0) return head;
            while (head->left!=0){
                head = head->left;
            }
            return head;
        }

        void remove(int data,Splay *temp = root){
            Splay *prev = 0;
            while (temp!=0 && temp->data!=data){
                prev = temp;
                if (data<temp->data){
                    temp = temp->left;
                }
                else if (data>temp->data){
                    temp = temp->right;
                }
            }
            if (temp->data!=data){
                if (prev!=0)
                splay(prev);
                return;
            }
            Splay *l = inorderPredecessor(temp->left);
            Splay *r = inorderSuccessor(temp->right);
            if (l==0 && r==0){
                if (prev==0){
                    root = 0;
                }
                else{
                    if (prev->left==temp){
                        prev->left = 0;
                    }
                    else{
                        prev->right = 0;
                    }
                    free(temp);
                    splay(prev);
                }
                return;
            }
            if (l!=0){
                if (l==temp->left){
                    l->right = temp->right;
                    if (l->right!=0){
                        l->right->par = l;
                    }
                }
                else{
                    if (l->left!=0){
                        l->left->par = l->par;
                    }
                    l->par->right = l->left;
                    l->right = temp->right;
                    l->par = 0;
                    if (l->right!=0){
                        l->right->par = l;
                    }
                    l->left = temp->left;
                    temp->left->par  = l;
                }
                if (prev==0){
                    root = l;
                }
                else{
                    if (prev->left==temp){
                        prev->left = l;
                        l->par = prev;
                    }
                    else{
                        prev->right = l;
                        l->par = prev;
                    }
                    free(temp);
                    splay(prev);
                }
                return;
            }
            else{
                if (r==temp->right){
                    r->left = temp->left;
                    if (r->left!=0){
                        r->left->par = r;
                    }
                }
                else{
                    if (r->right!=0){
                        r->right->par = r->par;
                    }
                    r->par->left = r->right;
                    r->left = temp->left;
                    r->par = 0;
                    if (r->left!=0){
                        r->left->par = r;
                    }
                    r->right = temp->right;
                    temp->right->par  = r;
                }
                if (prev==0){
                    root = r;
                }
                else{
                    if (prev->right==temp){
                        prev->right = r;
                        r->par = prev;
                    }
                    else{
                        prev->left = r;
                        r->par = prev;
                    }
                    free(temp);
                    splay(prev);
                }
                return;
            }
        }
        bool search(int data){
            Splay *temp = root;
            while (temp!=0 && temp->data!=data){
                if (data<temp->data){
                    temp = temp->left;
                }
                else{
                    temp = temp->right;
                }
            }
            if (temp!=0){
                splay(temp);
                return 1;
            }
            return 0;
        }
};

Splay * Splay:: root = 0; 

int main(){

    Splay s;
    s.insert(15);
    s.insert(10);
    s.insert(17);
    s.insert(7);
    s.insert(13);
    s.insert(16);
    s.insert(-2);
    s.insert(50);
    s.insert(-9);
    cout<<s.search(12)<<endl;
    s.remove(16);
    cout<<s.search(16)<<endl;
    cout<<s.search(15)<<endl;
    s.remove(15);
    s.dfs();
    return 0;
}