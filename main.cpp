#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

struct NodeTu{
	string tu;
	string nghia;
	int height;
	NodeTu* left;
	NodeTu* right;
};

NodeTu* dict = NULL;

int max(int a, int b)
{
    return (a > b)? a : b;
}

int height(struct NodeTu *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

struct NodeTu* newNode(string tu, string nghia)
{
    struct NodeTu* node = new NodeTu;
   
	node->tu = tu;
	node->nghia = nghia;
	node->height = 1;
	node->left = node->right = NULL;
    return(node);
}

int getBalance(struct NodeTu *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct NodeTu *rightRotate(struct NodeTu *y)
{
    struct NodeTu *x = y->left;
    struct NodeTu *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct NodeTu *leftRotate(struct NodeTu *x)
{
    struct NodeTu *y = x->right;
    struct NodeTu *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}

struct NodeTu* insert(struct NodeTu* dict, string tu, string nghia)
{
    /* 1.  Perform the normal BST rotation */
    
    if (dict == NULL)
        return(newNode(tu, nghia));
 
    if (tu < dict->tu)
        dict->left  = insert(dict->left, tu, nghia);
    else
        dict->right = insert(dict->right, tu, nghia);
 
    /* 2. Update height of this ancestor node */
    dict->height = max(height(dict->left), height(dict->right)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(dict);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && tu < dict->left->tu)
        return rightRotate(dict);
 
    // Right Right Case
    if (balance < -1 && tu > dict->right->tu)
        return leftRotate(dict);
 
    // Left Right Case
    if (balance > 1 && tu > dict->left->tu)
    {
        dict->left =  leftRotate(dict->left);
        return rightRotate(dict);
    }
 
    // Right Left Case
    if (balance < -1 && tu < dict->right->tu)
    {
        dict->right = rightRotate(dict->right);
        return leftRotate(dict);
    }
 
    /* return the (unchanged) node pointer */
    return dict;
}

//int insertNodeTu(NodeTu* &dict, string tu, string nghia){
//	if (dict != NULL){
//		if (dict->tu == tu)
//			return 0; // da ton tai
//		if (tu > dict->tu)
//			return insertNodeTu(dict->right, tu, nghia);
//		else
//			return insertNodeTu(dict->left, tu, nghia);
//	}
//	
//	
//	
//	dict = new NodeTu;
//	if (dict == NULL)
//		return -1; // het bo nho
//	dict->tu = tu;
//	dict->nghia = nghia;
//	dict->height = 1;
//	dict->left = dict->right = NULL;
//	return 1; // thanh cong
//}

void readDictData(NodeTu* &dict, char* path){
	fstream f;
	f.open(path, ios::in);
	string tu;
	string nghia;
	while(!f.eof()){
		getline(f, tu);
		getline(f, nghia);
//		insertNodeTu(dict, tu, nghia);
		dict = insert(dict, tu, nghia);
	}
	f.close();
}

//NodeTu* searchTu(NodeTu* dict, string tu){
//	cout<<"searching.... "<<dict->tu<<" <<<<"<<endl;
//	if (dict != NULL){
//		if (dict->tu == tu){
//			cout<<"find out.... "<<dict->tu;
//			return dict;
//		}
//		if (tu > dict->tu){
//			return searchTu(dict->right, tu);
//		} else {
//			return searchTu(dict->left, tu);
//		}
//	}
//	return NULL;
//	
//}

NodeTu* search_node(NodeTu* dict, string tu){
   NodeTu* p = dict;
   while (p!=NULL){
	   	if(p->tu == tu)
			return p;
	    else if (tu < p->tu){
	      	p = p->left;
		} else {
			p = p->right;
		}	
   }
   return NULL;
}

void printDict(NodeTu* dict){
	
	if (dict != NULL){
		
		cout<<dict->tu<<": "<<dict->nghia<<endl;
		printDict(dict->left);
		printDict(dict->right);
	}
}

bool kiemTraDau(char x){
	int kt = (int) x;
	if ((x>=65 && x<=90) || (x>=97 && x<=122)){
		return true;
	} else
		return false;
}


void kiemTraTu(string tu){
	NodeTu* res = search_node(dict, tu);
	if (res == NULL){
		cout<<tu<<"\n";
	}
}

void readDocument(char* path){
	fstream f;
	f.open(path, ios::in);
	string tu;
	char x;
	tu.clear();
	
	while(!f.eof()){
		x = f.get();
		while (kiemTraDau(x)){
			tu += x;
			x = f.get();
		}
		if (tu != ""){
			kiemTraTu(tu);
		}
		tu.clear();
	}
}

void editTu(NodeTu* dict, string tu, string nghia){
	NodeTu* res = search_node(dict, tu);
	if (res != NULL){
		res->nghia = nghia;
	}
	return;
}

void searchStandFor(NodeTu* &p, NodeTu* &q){
	if (q->left != NULL){
		searchStandFor(p, q->left);
	} else {
//		cout<<q->tu<<": "<<q->nghia<<endl;
		p->tu = q->tu;
		p->nghia = q->nghia;
		p = q;
		q = q->right;
	}
}


int delNode(NodeTu* &dict, string tu){
	if (dict == NULL)
		return 0;
	if (tu < dict->tu)
		return delNode(dict->left, tu);
	if (tu > dict->tu)
		return delNode(dict->right, tu);
	else { // tu == dict->tu
		NodeTu* p = dict;
		if (dict->left == NULL){
			dict = dict->right;
			return 1;
		} else if (dict->right == NULL){
			dict = dict->left;
			return 1;
		} else { // dict co ca 2 nhanh
			NodeTu* q = dict->right;
			searchStandFor(p, q);
			delete p;
			return 1;
		}
		
	}
}

int main(int argc, char *argv[]){
	char* path = "E:\\dict.txt";
	readDictData(dict, path);
	cout<<"---------- Tu Dien --------------"<<endl;
	printDict(dict);
	cout<<"---------------------------------"<<endl;
		
	char* path2 = "E:\\doc.txt";
	readDocument(path2);
	
	cout<<"---------------------------------"<<endl;
	printDict(dict);
	cout<<"print done!!";
	
	
	
	getch();
	return 0;
}
