#include<iostream>
using namespace std;

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == NULL)
        return;

    showTrunks(p->prev);

    cout << p->str;
}


//create a structure of a node
class Node
{
public:
	int info;  //any data type
	Node *left,*right;

	//constructor
	Node(int val)
	{
		info = val;
		left = right = NULL;
	}

};


class bin_search_tree
{
public:
	void printTree(Node *root, Trunk *prev, bool isRight);
	void insert(Node* &root, int val);
	void del(Node* &root, int val);
	//Node* remove(int x, Node* t);
	Node* findMin(Node* t);
	Node* findMax(Node* t);

};

//print Tree
void bin_search_tree::printTree(Node *root, Trunk *prev, bool isRight)
{
    if (root == NULL)
        return;
    
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->info << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}


void bin_search_tree::insert(Node* &root, int val)  
{
	if (root == NULL)
	{
		root = new Node(val);
		return;
	}

	if (root->info == val)
	{
		cout << "\n" << val<<" is already present in Tree"<<endl;
		return;
	}
	
	if (val < root->info)
	{
		insert(root->left, val);
		return;
	}

	else //(val > root->info)
	{
		insert(root->right, val);
		return;
	}
	
}


void bin_search_tree::del(Node* &root, int val)
{
	 Node* temp=NULL;
	//case 1, leaf node delete
	if (root->left==NULL && root->right==NULL)
	{
		delete root;
		root = NULL;
		return;
		
	
	}

	if (val < root->info)
	{
		del(root->left, val);
		return;
	}

	if (val > root->info)
	{
		del(root->right, val);
		return;
	}


	//
	//case 3
	else if(root->left && root->right)
        {
            temp = findMin(root->right);
            root->info = temp->info;
            //delete temp;
            //temp = NULL;
            //return;
            del(root->right, temp->info);
        }

	// case 2	
	/*if (root->info==val)
	{
	
		if (root->right)
		{
			root->info = root->right->info;
			delete root->right;
			root->right = NULL;
			return;
		}
		if (root->left)
		{
			root->info = root->left->info;
			delete root->left;
			root->left = NULL;
			return;
		}*/
		else
        {
            temp = root;
            if(root->left == NULL)
                root = root->right;
            else if(root->right == NULL)
                root = root->left;
            delete temp;
        }

	//}

	

	
}


//
Node* bin_search_tree::findMin(Node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
/*
Node* bin_search_tree::findMax(Node* t) 
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

/*
Node* bin_search_tree::remove(int x, Node* t) 
    {
        Node* temp=NULL;
        if(t == NULL)
            return NULL;
        else if(x < t->info)
            t->left = remove(x, t->left);
        else if(x > t->info)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->info = temp->info;
            t->right = remove(t->info, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }*/



int main()
{
	bin_search_tree obj;  //bin_search_tree object

	Node* root = NULL;  
	obj.insert(root,10);
	obj.insert(root,5);
	obj.insert(root,15);
	obj.insert(root,4);
	obj.insert(root,6);
	obj.insert(root,11);
	obj.insert(root,9);
	obj.insert(root,8);
	obj.insert(root,10);  //not insert it b/c it already present
	obj.insert(root, 11);


	obj.printTree(root, NULL, false);
	
	cout<<"\n\ndelete operation"<<endl;
	cout<<"case 1"<<endl; 
	obj.del(root, 11);
	obj.del(root, 8);
	obj.printTree(root, NULL, false);
	
	cout<<"case 2"<<endl;
	obj.del(root, 6);
	obj.printTree(root, NULL, false);

	cout<<"case 3"<<endl;
	obj.del(root, 10);
	
	obj.printTree(root, NULL, false);
	//obj.del(root, 6);
	//obj.del(root, 5);
	//obj.del(root, 15);


	//obj.printTree(root, NULL, false);
	//obj.remove(10, root);
	//obj.printTree(root, NULL, false);
	return 0;
}