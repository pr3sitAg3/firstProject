#include<iostream>
#include<cstdlib>

using namespace std;
/*
This file implements following properties 
of binary search tree.
1. Create bst
2. Check if given bst is height balanced or not
3. Calculate Height of Tree
4. Generate balance factor of bst
5. delete node from bst --pending
*/
typedef struct node{
	int data, bf;//data and balance factor of the node
	struct node * left, *right;
}Node;
int maxNum(int a, int b){
	return a>b?a:b;
}
int heightOfBST(Node * root){
	if (root == NULL)
		return -1;
	return maxNum(heightOfBST(root->left), heightOfBST(root->right))+1;
}
Node * generateBF(Node * root){
	if(root != NULL){		
		generateBF(root->left);
		generateBF(root->right);
		root->bf = heightOfBST(root->left) - heightOfBST(root->right);
	}
	return root;
}
Node * createBST(Node * root, int val){
	if(root == NULL){
		root = (Node *)malloc(sizeof(Node));
		root->data = val;
		root->bf=0;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	Node *q = root;
	while(q != NULL){
		if(val < q->data ){
			if(q->left == NULL){
				q->left = (Node *)malloc(sizeof(Node));
				q->left->data = val;
				q->left->bf=0;
				q->left->left = NULL;
				q->left->right = NULL;
				return root;
			}
			else{
				q = q->left;
			}
		}
		else{
			if(q->right == NULL){
				q->right = (Node *)malloc(sizeof(Node));
				q->right->data = val;
				q->right->bf=0;
				q->right->left = NULL;
				q->right->right = NULL;
				return root;
			}
			else{
				q = q->right;
			}
		}
	}
}
void displayBST(Node * root){
	if (root!=NULL){
		displayBST(root->left);
		cout<<"data="<<root->data<<",BF="<<root->bf<<" ";
		displayBST(root->right);
	}
	cout<<endl;
}
int isHeightBalanceTree(Node * root){
	if(root!=NULL){
		if(root->bf > 1 || root->bf <-1) 
			return 0;
		return (isHeightBalanceTree(root->left) && isHeightBalanceTree(root->right));
	}
	return -1;
}
//check if a tree is height balanced and
//calculate height(using backTracking)
int isBalanced(Node *root, int * height){
	int lh=0, rh=0;
	int lb=0, rb=0;
	if(root==NULL){
		*height=-1;
		return 1;
	}
	lb = isBalanced(root->left, &lh);
	rb = isBalanced(root->right, &rh) ;
	*height = (lh>rh?lh:rh)+1;
	if((lh-rh<-1)||(lh-rh>1))
		return 0;
	else
		return lb&&rb;
}
//end-----------
Node * deleteNode(Node *root, int val){
	if(root != NULL){
		cout << "\nNot Null\n" ;
		return root;
	}
	
}
int main(){
	int n, val, height;
	cin >> n;
	Node * root=NULL;
	cout<<"Sizeof Node ="<<sizeof(Node)<<endl;
	for(int i=0; i<n; i++){
		cin >> val; 
		root = createBST(root, val);
	}
	displayBST(root);
	//root = generateBF(root);
	int x = isBalanced(root, &height) ;
	displayBST(root);
	cout << "Height Of Tree="<< height <<endl;
	cout << "isHeight Balanced="<< x <<endl;
	//delete a node
	cout << deleteNode(NULL, val) << endl;
	return 0;
}
