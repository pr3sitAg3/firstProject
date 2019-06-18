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
5. delete node from bst   
6. Serializing and Deserializing of Tree
7. Insertion in AVL tree
8. Deletion in AVL tree
9. Calculate height and set diameter of a Tree
10. Find the diameter of a Tree
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
//Generate Balance Factor of the Tree
Node * generateBF(Node * root){
	if(root != NULL){		
		generateBF(root->left);
		generateBF(root->right);
		root->bf = heightOfBST(root->left) - heightOfBST(root->right);
	}
	return root;
}
//getBalance of a node
int getBalance(Node * root){
	if (root == NULL)
		return 0;
	return heightOfBST(root->left) - heightOfBST(root->right);

//create Node
Node * createNode(int key){
	Node * p = (Node *)malloc(sizeof(Node));
	p->data = key;
	p->bf = 0;
	p->left = NULL;
	p->right = NULL;
	return p;	
}
	
//create BST
Node * createBST(Node * root, int val){
	if(root == NULL){
		return createNode(val);
	}
	Node *q = root;
	while(q != NULL){
		if(val < q->data ){
			if(q->left == NULL){
				q->left = createNode(val);
				return root;
			}
			else{
				q = q->left;
			}
		}
		else{
			if(q->right == NULL){
				q->right = createNode(val);
				return root;
			}
			else{
				q = q->right;
			}
		}
	}
}

//Inorder Traversal of a BST
void displayBST(Node * root){
	if (root!=NULL){
		displayBST(root->left);
		cout<<"data="<<root->data<<",BF="<<root->bf<<" ";
		displayBST(root->right);
	}
	cout<<endl;
}
	
//Preorder Traversal of BST
void preorder(Node * root){
	if(root != NULL){
		cout<<"data="<<root->data<<",BF="<<root->bf<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}

//Check if BST is heightBalanced i.e. |bf| < 1
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
	if(root == NULL){
		return root;
	}
	
	if(root->data >  val){
		root->left = deleteNode(root->left, val);
		return root;
	}
	else if(root->data < val){
		root->right = deleteNode(root->right, val);
		return root;
	}
	if(root->left == NULL){
		Node * p = root->right;
		delete root;
		return p;
	}
	else if(root->right == NULL){
		Node * p = root->left;
		delete root;
		return p;
	}
	else{
		Node * succPar = root->right;
		Node * succ = root-> right;
		while(succ->left != NULL){
			cout<< succ->data <<" "<<succPar->data;
			succPar=succ;
			succ=succ->left;
		}
		cout<< succ->data <<" "<<succPar->data;
		root->data = succ->data;
		succPar->left = succ->right;
		//condition to handle segmentation fault
		if(root->right == succ)
			root->right =  succ->right;
		delete succ;
		return root;
	}
}
void serialize(Node * root, vector<int> &v){
	if(root == NULL){
		return;
	}
	queue<Node *> q;
	q.push(root);
	while(!q.empty()){
		Node * temp = q.front();
		q.pop();
		if(temp){
			v.push_back(temp->data);
			q.push(temp->left);
			q.push(temp->right);
		}
		else 
			v.push_back(-1);
	}
}
Node * deSerialize(vector<int> v){
	vector<int>::iterator  itr = v.begin(), itr2=v.end();
	Node * p=NULL;
	for(; itr<itr2; itr++){
		if(*itr != -1){
			p = createBST(p, *itr);
		}
	}
	return p;
}
	
//Rotation of tree
Node * leftRotate(Node * rptr ){
	if(rptr == NULL){
		return rptr;
	}
	Node * p = rptr->right;
	rptr->right = p->left;
	p->left = rptr;
	p->bf = (heightOfBST(p->left)- heightOfBST(p->right));
	rptr->bf = (heightOfBST(rptr->left)- heightOfBST(rptr->right));
	return p;	
}
Node * rightRotate(Node * rptr){
	if(rptr==NULL)
		return rptr;
	Node * p = rptr->left;
	rptr->left = p->right;
	p->right = rptr;
	p->bf = (heightOfBST(p->left)- heightOfBST(p->right));
	rptr->bf = (heightOfBST(rptr->left)- heightOfBST(rptr->right));
	return p;
}
	
//Insert in AVL tree
Node * insertAVL(Node * root, int key){
	if(root==NULL){
		return createNode(key) ;
	}
	if(key < root->data)	{
		root->left = insertAVL(root->left,key);
	}
	else if(key > root->data){
		root->right = insertAVL(root->right, key);
	}
	else{
		return root;
	}
	int balance = getBalance(root) ;
	if(balance > 1 && key < root->left->data){
		return rightRotate(root);
	}
	if(balance < -1 && key > root->right->data){
		return leftRotate(root);
	}
	if(balance > 1 && key > root->left->data){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance < -1 && key < root->right->data){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}
//deletion of node in AVL tree
Node * deleteAVL(Node * root, int key){
	if(root==NULL){
		return NULL;
	}
	Node * p;
	if(root->data > key){
		root->left = deleteAVL(root->left, key);
	}
	else if(root->data < key){
		root->right = deleteAVL(root->right, key);
	}
	else{
		if(!root->left && !root->right){
			delete root;
			root = NULL;
		}
		else if(root->left && !root->right){
			p = root->left;
			root->data = p->data;
			root->left = p->left;
			root->right = p->right;
			delete p;
		}
		else if (root->right && !root->left){
			p = root->right;
			root->data = p->data;
			root->left = p->left;
			root->right = p->right;
			delete p;
		}
		else{
			Node * par = root->left, *succ = root->left;
			while(succ->left){
				par = succ;
				succ = succ->left;
			}
			root->data = succ->data;
			par->left = succ->right;
			if(root->right == succ)
				root->right = succ->right;
			delete succ;
		}
	}
	////balancing now at the very first node in unwinding phase i.e.
	///ancestors of the deleted node
	if(root == NULL) return root;
	int balance = getBalance(root);
	if(balance > 1 && getBalance(root->left) >=0){
		//Node was deleted from left heavy subtree
		return rightRotate(root);
	}
	if(balance > 1 && getBalance(root->left) <0){
		//Node was deleted from left heavy subtree and right subtree of left of root
		root->left =  leftRotate(root->left);
		return rightRotate(root);
	}
	if(balance < -1 && getBalance(root->right) <=0){
		//Node was deleted from right heavy subtree
		return leftRotate(root);
	}
	if(balance < -1 && getBalance(root->right) >0){
		//Node was deleted from right heavy subtree and left subtree of root->right
		root->right =  rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}
//calculate diameter of tree
int _height(Node *root, int & dia){
	/*utility function to set the diameter
	 and return the height - O(n) solution
	*/
	if (root==NULL)	return -1;
	int lh = _height(root->left, dia);
	int rh = _height(root->right, dia);
	dia = max(dia, lh+rh+3);
	return 1+max(lh, rh);
}
int diameterBt(Node * root){
	//Return the value of diameter of a binary tree
	//O(n^2) solution
	if(root==NULL) 	return 0;
	int ld = diameterBt(root->left);
	int rd = diameterBt(root->right);
	int left_h = height(root->left);
	int right_h = height(root->right);
	return max(left_h+right_h+3, max(ld, rd));

}	
int main(){
	int n, val, height;
	cin >> n;
	Node * root=NULL, *avlroot=NULL;
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
	root = deleteNode(root, 2);
	displayBST(root) ;
	//serializing tree
	vector<int> vtree;
	cout<<"\nSerializing...\n";
	serialize(root, vtree);
	vector<int>::iterator itr;
	for(itr= vtree.begin(); itr!=vtree.end(); itr++){
		cout<< *itr << ",";
	}
	cout<<"\nS. End\n";
	cout<<"\nDeSerializing...\n";
	displayBST(deSerialize(vtree));
	
	 displayBST(root);
	 cout<<"\nAVL tree:"<<endl;
	 preorder(avlroot);

	int diam = 0;
	height = _height(root, diam);
	return 0;
}
