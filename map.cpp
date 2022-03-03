/* Map implementation in C/C++
Author - Abhishek Kumar */
#include <iostream>
#include <queue>
using namespace std;

class Map
{
public:
    static class Map *root;
    Map *left, *right, *par;
    int first, second, depth;

    int & operator[](int key){
        return insert(key)->second;
    }
    
    Map *create(int first)
    {
        Map *newnode = (Map *)malloc(sizeof(Map));
        newnode->first = first;
        newnode->second = 0;
        newnode->left = 0;
        newnode->right = 0;
        newnode->par = 0;
        newnode->depth = 1; //depth of a newnode shall be 1 and not zero to \
        differentiate between no child (which return 0) and having child
        return newnode;
    }

    void right_rotation(Map *x)
    {
        Map *y = x->left;
        x->left = y->right;
        if (y->right != 0)
        {
            y->right->par = x;
        }
        if (x->par != 0 && x->par->right == x)
        {
            x->par->right = y;
        }
        else if (x->par != 0 && x->par->left == x)
        {
            x->par->left = y;
        }
        y->par = x->par;
        y->right = x;
        x->par = y;
    }

    void left_rotation(Map *x)
    {
        Map *y = x->right;
        x->right = y->left;
        if (y->left != 0)
        {
            y->left->par = x;
        }
        if (x->par != 0 && x->par->left == x)
        {
            x->par->left = y;
        }
        else if (x->par != 0 && x->par->right == x)
        {
            x->par->right = y;
        }
        y->par = x->par;
        y->left = x;
        x->par = y;
    }

    int depthf(Map *node)
    {
        if (node == 0)
            return 0;
        return node->depth;
    }

    // draw the initial and final graph of each cases(take case where every node has two child)\
    and update the nodes depth before rotation
    void helper(Map *node)
    {
        if (depthf(node->left) - depthf(node->right) > 1)
        {
            if (depthf(node->left->left) > depthf(node->left->right))
            {
                node->depth = max(depthf(node->right) + 1, depthf(node->left->right) + 1);
                node->left->depth = max(depthf(node->left->left) + 1, depthf(node) + 1);
                right_rotation(node);
            }
            else
            {
                node->left->depth = max(depthf(node->left->left) + 1, depthf(node->left->right->left) + 1);
                node->depth = max(depthf(node->right) + 1, depthf(node->left->right->right) + 1);
                node->left->right->depth = max(depthf(node) + 1, depthf(node->left) + 1);
                left_rotation(node->left);
                right_rotation(node);
            }
        }
        else if (depthf(node->left) - depthf(node->right) < -1)
        {
            if (depthf(node->right->right) > depthf(node->right->left))
            {
                node->depth = max(depthf(node->left) + 1, depthf(node->right->left) + 1);
                node->right->depth = max(depthf(node->right->right) + 1, depthf(node) + 1);
                left_rotation(node);
            }
            else
            {
                node->right->depth = max(depthf(node->right->right) + 1, depthf(node->right->left->right) + 1);
                node->depth = max(depthf(node->left) + 1, depthf(node->right->left->left) + 1);
                node->right->left->depth = max(depthf(node) + 1, depthf(node->right) + 1);
                right_rotation(node->right);
                left_rotation(node);
            }
        }
    }

    void balance(Map *node)
    {
        while (node != root)
        {
            int d = node->depth;
            node = node->par;
            if (node->depth < d + 1)
            {
                node->depth = d + 1;
            }
            if (node == root && depthf(node->left) - depthf(node->right) > 1)
            {
                root = node->left->right;
                helper(node);
                break;
            }
            else if (node == root && depthf(node->left) - depthf(node->right) < -1)
            {
                root = node->right->left;
                helper(node);
                break;
            }
            helper(node);
        }
    }

    Map* insert(int first)
    {
        Map *newnode = create(first);
        if (root == 0)
        {
            root = newnode;
            return root;
        }
        Map *temp = root, *prev = 0;
        while (temp != 0)
        {
            prev = temp;
            if (first < temp->first)
            {
                temp = temp->left;
            }
            else if (first > temp->first)
            {
                temp = temp->right;
            }
            else
            {
                free(newnode);
                return temp;
            }
        }
        if (first < prev->first)
        {
            prev->left = newnode;
        }
        else
        {
            prev->right = newnode;
        }
        newnode->par = prev;
        balance(newnode);
        return newnode;
    }
    int search(int first)
    {
        Map *temp = root;
        while (temp != 0 && temp->first != first)
        {
            if (first < temp->first)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        if (temp != 0)
        {
            return temp->second;
        }
        return 0;
    }
};

Map *Map::root = 0;

int main()
{

    Map m;
    m[132] = 3;
    m[3334] = 5;
    m[42] = 7;
    m[-83] = 4;
    m[66] = 9;
    m[197] = 8;
    int arr[] = {132,3334,42,-83,66,197,83,56,1,0};
    for (int i=0;i<sizeof(arr)/sizeof(int);i++){
        cout<<arr[i]<<":"<<m.search(arr[i])<<' ';
    }
    cout<<endl;
    return 0;
}