// C++ Program to implement Map class(using AVL tree)

// This is a header file map.h and doesnot contain main()

#include <iostream>
using namespace std;

class Map {
    // 1. this methods are not useful to users, therefore
    // they are kept hidden
private:
    //  2. the const property is used to keep the "search"
    //  method
    // compatible with the method "const int&[]operator(int)
    // const"

    // 3. since we are not allowed to change the class
    // attributes in the method "const int&[]operator(int)
    // const" we have to assure the compiler that method
    // called(i.e "search") inside it also doesn't change
    // the attributes of the class

    const int search(int first) const
    {
        // 4. a temporary variable created so that we do not
        // loose the "root" of the tree

        Map* temp = root;

        // 5. stop only when either the key is found or we
        // have gone further the leaf node

        while (temp != nullptr && temp->first != first) {
            // 6. go to left if key is less than the key of
            // the traversed node

            if (first < temp->first) {
                temp = temp->left;
            }

            // 7. go to right if key is greater than the key
            // of the traversed node

            else {
                temp = temp->right;
            }
        }

        // 8. if key is found

        if (temp != nullptr) {
            // 9. if the key is found return the value

            return temp->second;
        }

        // 10. if key is not found

        return 0;
    }

    // 11. a utiliity function to return the Map* object
    // with its members initilized to default values except
    // the key

    Map* create(int first)
    {
        Map* newnode = (Map*)malloc(sizeof(Map));
        newnode->first = first;
        newnode->second = 0;
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->par = nullptr;

        // 12. depth of a newnode shall be 1 and not zero to
        // differentiate between no child (which return
        // nullptr) and having child(which return 1)

        newnode->depth = 1;

        return newnode;
    }
    // 13. all the rotation operation are performed about
    // the node itself

    // 14. performs all the linking done when there is
    // clockwise rotation performed at node "x"

    void right_rotation(Map* x)
    {
        Map* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->par = x;
        }
        if (x->par != nullptr && x->par->right == x) {
            x->par->right = y;
        }
        else if (x->par != nullptr && x->par->left == x) {
            x->par->left = y;
        }
        y->par = x->par;
        y->right = x;
        x->par = y;
    }

    // 15. performs all the linking done when there is
    // anti-clockwise rotation performed at node "x"

    void left_rotation(Map* x)
    {
        Map* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->par = x;
        }
        if (x->par != nullptr && x->par->left == x) {
            x->par->left = y;
        }
        else if (x->par != nullptr && x->par->right == x) {
            x->par->right = y;
        }
        y->par = x->par;
        y->left = x;
        x->par = y;
    }

    // 16. draw the initial and final graph of each
    // case(take case where every node has two child) and
    // update the nodes depth before any rotation

    void helper(Map* node)
    {

        // 17. if left skewed
        if (depthf(node->left) - depthf(node->right) > 1) {
            // 18. if "depth" of left subtree of left child
            // of "node" is greater than that of right
            // subtree of left child of "node"

            if (depthf(node->left->left)
                > depthf(node->left->right)) {
                node->depth = max(depthf(node->right) + 1,
                          depthf(node->left->right) + 1);
                node->left->depth = max(depthf(node->left->left)
                                        + 1,depthf(node) + 1);
                right_rotation(node);
            }
            // 19. if "depth" of right subtree of left child
            // of "node" is greater than that of left
            // subtree of left child of "node"

            else {
                node->left->depth = max(
                    depthf(node->left->left) + 1,
                    depthf(node->left->right->left) + 1);
                node->depth = max(
                    depthf(node->right) + 1,
                    depthf(node->left->right->right) + 1);
                node->left->right->depth
                    = max(depthf(node) + 1,
                          depthf(node->left) + 1);
                left_rotation(node->left);
                right_rotation(node);
            }
        }

        // 20. if right skewed

        else if (depthf(node->left) - depthf(node->right)
                 < -1) {
            // 21. if "depth" of right subtree of right
            // child of "node" is greater than that of left
            // subtree of right child of "node"

            if (depthf(node->right->right)
                > depthf(node->right->left)) {
                node->depth
                    = max(depthf(node->left) + 1,
                          depthf(node->right->left) + 1);
                node->right->depth
                    = max(depthf(node->right->right) + 1,
                          depthf(node) + 1);
                left_rotation(node);
            }
            // 22. if "depth" of left subtree of right child
            // of "node" is greater than that of right
            // subtree of right child of "node"

            else {
                node->right->depth = max(
                    depthf(node->right->right) + 1,
                    depthf(node->right->left->right) + 1);
                node->depth = max(
                    depthf(node->left) + 1,
                    depthf(node->right->left->left) + 1);
                node->right->left->depth
                    = max(depthf(node) + 1,
                          depthf(node->right) + 1);
                right_rotation(node->right);
                left_rotation(node);
            }
        }
    }

    // 23. balancing the tree about the "node"

    void balance(Map* node)
    {
        while (node != root) {
            int d = node->depth;
            node = node->par;
            if (node->depth < d + 1) {
                node->depth = d + 1;
            }
            if (node == root
                && depthf(node->left) - depthf(node->right)
                       > 1) {
                if (depthf(node->left->left)
                    > depthf(node->left->right)) {
                    root = node->left;
                }
                else {
                    root = node->left->right;
                }
                helper(node);
                break;
            }
            else if (node == root
                     && depthf(node->left)
                                - depthf(node->right)
                            < -1) {
                if (depthf(node->right->right)
                    > depthf(node->right->left)) {
                    root = node->right;
                }
                else {
                    root = node->right->left;
                }
                helper(node);
                break;
            }
            helper(node);
        }
    }

    // 24. utility method to return the "depth" of the
    // subtree at the "node"

    int depthf(Map* node)
    {
        if (node == nullptr)

            // 25. if it is null node

            return 0;
        return node->depth;
    }

    Map* insert(int first)
    {
        Map* newnode = create(first);

        // 26. if empty tree simply create the "root"

        if (root == nullptr) {
            root = newnode;
            return root;
        }
        Map *temp = root, *prev = nullptr;
        while (temp != nullptr) {
            prev = temp;
            if (first < temp->first) {
                temp = temp->left;
            }
            else if (first > temp->first) {
                temp = temp->right;
            }
            else {
                free(newnode);

                // 27. if the key is found then it is
                // returned by reference so that it is
                // updatable

                return temp;
            }
        }
        if (first < prev->first) {
            prev->left = newnode;
        }
        else {
            prev->right = newnode;
        }
        newnode->par = prev;

        // 28. once we have inserted we need to check and
        // balance the tree at every node which is present
        // in the path from "newnode" to "root"

        balance(newnode);

        // 29. new object is inserted and returned by
        // reference to initialize in the main by
        // assignment(hashing)

        return newnode;
    }

public:
    // 30. "root" is kept static because it is a class
    // property and not an instance property

    // 31. if the "root" is not static we will take double
    // memory for the programme than required
    // static "root" is initialized to nullptr outside the
    // class

    static class Map* root;

    // 32. "first" is key and "second" is value

    Map *left, *right, *par;
    int first, second, depth;

    // 33. overloaded [] operator for assignment(hashing) or
    // inserting a key-value pairs in the map since it might
    // change the members of the class therefore this is
    // invoked when any assignment is done

    int& operator[](int key) { return insert(key)->second; }

    // 34. Since we have two methods with the same name
    // "[]operator(int)" and methods/functions cannot be
    // distinguished by their return types it is mandatory
    // to include a const qualifier at the end of any of the
    // methods

    // 35. compiler will call this by default when we are
    // interested in only peeking the value

    // 36. it will not be called for assignment because
    // it doesn't allow change member variables

    // 37. we cannot make it return by reference because the
    // variable "temp" returned by the "search" method is
    // statically allocated and therefore it's been
    // destroyed when it is called out(stack frame is popped
    // out)

    const int operator[](int key) const
    {
        // 38. search method is also qualified with const

        return search(key);
    }
};

Map* Map::root = nullptr;