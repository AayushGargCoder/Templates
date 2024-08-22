#include <iostream>
using namespace std;
class trieNode
{
public:
    char data;
    trieNode **children;
    bool isTerminal;
    trieNode(char data)
    {
        this->data = data;
        children = new trieNode *[26];
        isTerminal = false;
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
    }
};
class Node
{
    trieNode *root;
    void insert_inside(string word, trieNode *root)
    {
        if (word.length() == 0)
        {
            root->isTerminal = true;
            return;
        }
        int index = word[0] - 'a';
        trieNode *newNode;
        if (root->children[index] == NULL)
        {
            newNode = new trieNode(word[0]);
            root->children[index] = newNode;
        }
        else
        {
            newNode = root->children[index];
        }
        insert_inside(word.substr(1), newNode);
    }
    void remove_inside(string word, trieNode *root)
    {
        if (word.length() == 0)
        {
            root->isTerminal = false;
            return;
        }
        int index = word[0] - 'a';
        trieNode *newNode;
        if (root->children[index] == NULL)
        {
            return;
        }
        else
        {
            newNode = root->children[index];
        }
        remove_inside(word.substr(1), newNode);

        if (root->children[index]->isTerminal == false)
        {
            bool ans = false;
            for (int i = 0; i < 26; i++)
            {
                if (root->children[index]->children[i] != NULL)
                {
                    ans = true;
                }
            }
            if (!ans)
            {
                trieNode *node = root->children[index];
                root->children[index] = NULL;
                delete node;
            }
        }
    }
    bool search_inside(string word, trieNode *root)
    {
        if (word.length() == 0)
        {
            return root->isTerminal == true;
        }
        int index = word[0] - 'a';
        trieNode *newNode;
        if (root->children[index] == NULL)
        {
            return false;
        }
        else
        {
            newNode = root->children[index];
        }
        return search_inside(word.substr(1), newNode);
    }

public:
    Node()
    {
        root = new trieNode('\0');
    }
    void insert(string s)
    {
        insert_inside(s, root);
    }
    void remove(string s)
    {
        remove_inside(s, root);
    }
    bool search(string s)
    {
        return search_inside(s, root);
    }
};
