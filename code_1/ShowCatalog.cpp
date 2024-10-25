#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}

/* TODO */

ShowItem* findParent(ShowItem* root, ShowItem* node) {
    if ((node==root)||(root==nullptr)) {
        return nullptr;
    }
    if ((root->left==node)||(root->right==node)) {
        return root;
    }
    if (node->title>root->title) {
        return findParent(root->right, node);
    }    
    return findParent(root->left, node);
}

ShowItem* removeShowHelper(ShowItem *current, ShowItem*& parent, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title) {
        return current;
    }
    parent=current;
    if (current->title > title) {
        return removeShowHelper(current->left, parent, title);
    }
    return removeShowHelper(current->right, parent, title);
}

void ShowCatalog::removeShow(std::string title)
{
    ShowItem* parent = nullptr;
    ShowItem* node = removeShowHelper(root, parent, title);

    if (node==nullptr) {
        return;
    }
    if ((node->left==nullptr)&&(node->right==nullptr)) {
        if (node==root) {
            delete root;
            root=nullptr;
        } else if (parent->left==node) {
            parent->left=nullptr;
            delete node;
            node=nullptr;
        } else {
            parent->right=nullptr;
            delete node;
            node=nullptr;
        }
    } else if (node->right==nullptr) {
        if (node==root) {
            ShowItem* temp = node->left;
            delete root;
            root=temp;
        } else if (parent->left==node) {
            parent->left=node->left;
            delete node;
            node=nullptr;
        } else {
            parent->right=node->left;
            delete node;
            node=nullptr;
        }
    } else if (node->left==nullptr) {
        if (node==root) {
            ShowItem* temp = node->right;
            delete root;
            root=temp;
        } else if (parent->left==node) {
            parent->left=node->right;
            delete node;
            node=nullptr;
        } else {
            parent->left=node->right;
            delete node;
            node=nullptr;
        }
    } else {
        ShowItem* temp = node->right;
        ShowItem* tempParent = node;
        while (temp->left!=nullptr) {
            tempParent=temp;
            temp=temp->left;
        }
        node->title=temp->title;
        node->year=temp->year;
        node->userRating=temp->userRating;
        node->showRating=temp->showRating;
        if (tempParent->left==temp) {
            tempParent->left=nullptr;
        } else {
            tempParent->right=nullptr;
        }
        delete temp;
        temp=nullptr;
    }
}

/* TODO */

void ShowCatalog::rightRotate(std::string title)
{
    ShowItem* y = getShowHelper(root, title);
    if (y==nullptr) {
        return;
    }
    ShowItem* x=y->left;
    if (x==nullptr) {
        return;
    }

    y->left=x->right;
    x->right=y;

    ShowItem* yParent;
    yParent=findParent(root, y);

    if (yParent==nullptr) {
        root=x;
    } else if (yParent->right==y) {
        yParent->right=x;
    } else {
        yParent->left=x;
    }
}

/* TODO */
void ShowCatalog::leftRotate(std::string title)
{
    ShowItem* x = getShowHelper(root, title);
    if (x==nullptr) {
        return;
    }
    ShowItem* y=x->right;
    if (y==nullptr) {
        return;
    }

    x->right=y->left;
    y->left=x;

    ShowItem* xParent;
    xParent=findParent(root, x);

    if (xParent==nullptr) {
        root=y;
    } else if (xParent->left==x) {
        xParent->left=y;
    } else {
        xParent->right=y;
    }
}
