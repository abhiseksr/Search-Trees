#pragma once
#include <iostream>
#include <vector>
#include "map.h"
using namespace std;

int digitCount(int n)
{
    int cnt = 0;
    while (n)
    {
        cnt++;
        n /= 10;
    }
    return cnt;
}

template <typename T>
void printer(T *root)
{
    cout << "\n\n";
    Map dist, offset;
    vector<T *> mp[200];
    queue<T *> q;
    int maxdepth = 0;
    q.push(root);
    dist[root->data] = 0;
    mp[0].push_back(root);
    while (!q.empty())
    {
        T *curr = q.front();
        q.pop();
        if (curr->left != 0)
        {
            q.push(curr->left);
            dist[curr->left->data] = dist.search(curr->data) + 1;
            mp[dist.search(curr->left->data)].push_back(curr->left);
            maxdepth = max(maxdepth, dist.search(curr->left->data));
        }
        if (curr->right != 0)
        {
            q.push(curr->right);
            dist[curr->right->data] = dist.search(curr->data) + 1;
            mp[dist.search(curr->right->data)].push_back(curr->right);
            maxdepth = max(maxdepth, dist.search(curr->right->data));
        }
    }
    printf("%72d\n\n", root->data);
    offset[root->data] = 70;
    Map hashing;
    hashing[root->data] = 1;
    int k = maxdepth + 1;
    for (int i = 1; i <= maxdepth; i++)
    {
        int cnt = 0;
        for (auto z : mp[i])
        {
            if (hashing.search(z->data))
                continue;
            while (cnt < offset.search(z->par->data) - k * (maxdepth - i + 1))
            {
                cout << ' ';
                cnt++;
            }
            if (z->par->left != 0)
            {
                offset[z->data] = cnt;
                cout << (z->data);
                cnt += digitCount(z->data);
                hashing[z->data] = 1;
                while (cnt < offset.search(z->par->data))
                {
                    cnt++;
                    cout << '_';
                }
                cout << '|';
                cnt++;
            }
            if (z->par->right != 0)
            {
                if (z->par->left == 0)
                {
                    while (cnt < offset.search(z->par->data))
                    {
                        cnt++;
                        cout << ' ';
                    }
                    cout << '|';
                    cnt++;
                }
                offset[z->par->right->data] = offset.search(z->par->data) - 2 + k * (maxdepth - i + 1);
                while (cnt < offset.search(z->par->right->data))
                {
                    cnt++;
                    cout << '_';
                }
                cout << z->par->right->data;
                cnt += digitCount(z->par->right->data);
                hashing[z->par->right->data] = 1;
            }
        }
        cout << "\n\n";
        k--;
    }
    cout << "\n\n\n";
}
