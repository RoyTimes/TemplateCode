#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
struct node
{
    int size;
    struct node *next[26];
    void node()
    {
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
        size = 0;
    }
};
void insert(node *root, char *s)
{
    if (root == NULL || *s == '\0') return;
    node *p = root;
    while (*s != '\0')
    {
        if (p->next[*s - 'a'] == NULL)
            p->next[*s - 'a'] = new node();
        p = p->next[*s - 'a'];
        s++;
    }
    p->size++;
}
int search(node *root, char *s)
{
    node *p = root;
    while (p != NULL && *s != '\0')
    {
        p = p->next[*s - 'a'];
        s++;
    }
    if (p != NULL)
        return p->size;
    return 0;
}
void remove(node *root)
{
    for (int i = 0; i < 26; i++)
        if (root->next[i] != NULL)
            remove(root->next[i]);
    delete(root);
}
int main()
{
    int m, n;
    node *root;
    root = new node();
    remove(root);
    return 0;
}

