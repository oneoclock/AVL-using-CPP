#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

class node
{
public:
	char keyword[20];
	char meaning[20];
	node *left, *right;
	int ht;
	node()
	{
		left=NULL;
		right=NULL;
		ht=0;
		strcpy(meaning, "");
		strcpy(keyword, "");
	}
};

class avl
{
	node *root;
	int bf (node *);
	int height (node *);
	node * insert (node *, char word[20], char mean[20]);
	node * rotate_left (node *);
	node * rotate_right (node *);
	void inorder (node *);
	void preorder (node *);
	void postorder (node *);
	void display();
public:
	avl()
		{
			root=NULL;
		}
	void flow();
};

node * avl :: insert (node *T, char word[20], char mean[20])
{
	if(T==NULL)
	{
		T= new node;
	}
	if(strcmp(T->keyword, "")==0)
	{
		strcpy(T->keyword, word);
		strcpy(T->meaning, mean);
		T->left=NULL;
		T->right=NULL;
	}
	else
	{
		if(strcmp(word,T->keyword)>0)
		{
			T->right=insert(T->right, word, mean);
			if(bf(T)==-2)
			{
				if(strcmp(word, T->right->keyword)>0)
				{
					T=rotate_left(T);
				}
				else
				{
					T->right=rotate_right(T->right);
					T=rotate_left(T);
				}
			}
		}
		else
		{
			if (strcmp(word, T->keyword)<0)
			{
				T->left=insert(T->left, word, mean);
				if(bf(T)==2)
				{
					if(strcmp(word, T->left->keyword)<0)
					{
						T=rotate_right(T);
					}
					else
					{
						T->left=rotate_left(T->left);
						T=rotate_right(T);
					}
				}
			}
		}
	}
	T->ht=height(T);
	return T;
}

int avl :: bf(node *T)	//check bracket
{
	int lh, rh;
	if(T==NULL)
	{
		return 0;
	}
	else
	{
		if(T->left==NULL)
		{
			lh=0;
		}
		else
		{
			lh=1+T->left->ht;
		}
		if(T->right==NULL)
		{
			rh=0;
		}
		else
		{
			rh=1+T->right->ht;
		}
		return (lh-rh);
	}
}

int avl :: height(node *T)
{
	int left_height, right_height;
	if(T==NULL)
	{
		return 0;
	}
	if(T->left==NULL)
	{
		left_height=0;
	}
	else
	{
		left_height=1+(T->left->ht);
	}
	if(T->right==NULL)
	{
		right_height=0;
	}
	else
	{
		right_height=1+(T->right->ht);
	}
	if(left_height>right_height)
	{
		return (left_height);
	}
	else
	{
		return (right_height);
	}
}

node * avl :: rotate_left(node *T)
{
	node *temp;
	temp=T->right;
	T->right=temp->left;
	temp->left=T;
	T->ht=height(T);
	temp->ht=height(temp);
	return temp;
}

node * avl :: rotate_right(node *T)
{
	node *temp;
	temp=T->left;
	T->left=temp->right;
	temp->right=T;
	T->ht=height(T);
	temp->ht=height(temp);
	return temp;
}

void avl :: inorder(node *root)
{
	if(root!=NULL)
		{
			inorder(root->left);
			cout<<endl<<root->keyword<<" "<<root->meaning<<" "<<endl;
			inorder(root->right);
		}
}

void avl :: preorder(node *root)
{
	if(root!=NULL)
	{
	cout<<endl<<root->keyword<<" "<<root->meaning;
	preorder(root->left);
	preorder(root->right);
	}
}

void avl :: postorder(node *root)
{
	if(root!=NULL)
	{
	postorder(root->left);
	postorder(root->right);
	cout<<root->keyword<<" "<<root->meaning<<" ";
	}
}

void avl :: display()
{
	int ch;
	do
	{
		cout<<"Display AVL tree through:\n1. Inorder"<<endl<<"2. Preorder"<<endl<<"3. Postorder"<<endl<<"4. Exit"<<endl;
		cout<<"Enter your choice: ";
		cin>>ch;
		switch(ch)
		{
		case 1: inorder(root);
		break;
		case 2: preorder(root);
		break;
		case 3: postorder(root);
		break;
		case 4: exit(0);
		default:cout<<"Invalid choice";
		break;
		}
	}while(ch!=4);
}

void avl :: flow()
{
	char key[20], mean[20];
	FILE *fp;
	fp=fopen("input.dat", "r");
	if(fp==NULL)
	{
		cout<<"File opening error..";
	}
	else
	{
		while(!feof(fp))
		{
			fscanf(fp, "%s%s", key, mean);
			root=insert(root, key, mean);
			//fflush(fp);
		}
	}
	display();
	fclose(fp);
}

int main() {
	avl obj;
	obj.flow();
	return 0;
}
