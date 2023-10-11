#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <bits/stdc++.h>

using namespace std;

struct tnode {
	int data;          
	struct tnode *left; 
	struct tnode *right; 
	tnode() {}
    tnode(int data): data(data) {}
};

tnode* insertNode(tnode* root, int key)
{
    if (root == NULL){
        return new tnode(key);
    }
    if (key < root->data) {
        root->left = insertNode(root->left, key);
    }
    else{
        root->right = insertNode(root->right, key);
    }
    return root;
}

tnode* getMinimumKey(tnode* curr)
{
    while (curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}

void deleteNode(tnode* &root, int key);
void searchKey(tnode* &curr, int key, tnode* &parent);
void depthSearch(tnode* root);
void widthSearch(tnode* root);

int main(){
	setlocale(LC_ALL,"Russian");
	tnode* root;
	int tempNode, point;
	root = NULL;
	cout<<"Вводите узлы по очереди(1 узел - корень), для выхода введите 0\n";
	do{
		cout<<"Введите следующий узел: ";
		cin>>tempNode;
		if(tempNode != 0)
			root = insertNode(root, tempNode);
	}while(tempNode != 0);
	del:
	cout<<"\nОбход в глубину: ";
	depthSearch(root);
	cout<<endl;
	cout<<"Обход в ширину: ";
	widthSearch(root);
	cout<<endl;
	cout<<"Хотите ли удалить узел? (1-да,2-нет): ";
	cin>>point;
	if(point == 1){
		cout<<"Какой узел хотите удалить: ";
		cin>>tempNode;
		deleteNode(root, tempNode);	
		goto del;
	}
}

void deleteNode(tnode* &root, int key)
{
    tnode* parent = NULL;
    tnode* curr = root;
    searchKey(curr, key, parent);
    if (curr == NULL) {
        return;
    }
    if (curr->left == NULL && curr->right == NULL)
    {
        if (curr != root)
        {
            if (parent->left == curr) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
        }
        else {
            root = NULL;
        }
        free(curr); 
    }
    else if (curr->left && curr->right)
    {
        tnode* successor = getMinimumKey(curr->right);
        int val = successor->data;
        deleteNode(root, successor->data);
        curr->data = val;
    }
    else {
        tnode* child = (curr->left)? curr->left: curr->right;
        if (curr != root)
        {
            if (curr == parent->left) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
        else {
            root = child;
        }
        free(curr);
    }
}

void searchKey(tnode* &curr, int key, tnode* &parent)
{
    while (curr != NULL && curr->data != key)
    {
        parent = curr;
        if (key < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
}

void depthSearch(tnode* root){
    stack<tnode*> nodeStack;
    nodeStack.push(root);
    while (!nodeStack.empty()) {
        root = nodeStack.top();
        cout<<root->data<<' ';
        nodeStack.pop();
        if (root-> right)
          	nodeStack.push(root->right);
        if (root-> left) 
           	nodeStack.push(root->left);
    }
}

void widthSearch(tnode* root){
    queue<tnode* > nodeQueue;
    nodeQueue.push(root);
    while (!nodeQueue.empty()) {
        root = nodeQueue.front();
        cout<<root->data<<' ';
        nodeQueue.pop();
        if (root->left)
            nodeQueue.push (root->left); 
        if (root->right)
            nodeQueue.push (root->right); 
    }
}
