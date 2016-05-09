#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

struct NodeTu{
	string tu;
	string nghia;
	NodeTu* left;
	NodeTu* right;
};

NodeTu* dict = NULL;

int insertNodeTu(NodeTu* &dict, string tu, string nghia){
	if (dict != NULL){
		if (dict->tu == tu)
			return 0; // da ton tai
		if (tu > dict->tu)
			return insertNodeTu(dict->right, tu, nghia);
		else
			return insertNodeTu(dict->left, tu, nghia);
	}
	dict = new NodeTu;
	if (dict == NULL)
		return -1; // het bo nho
	dict->tu = tu;
	dict->nghia = nghia;
	dict->left = dict->right = NULL;
	return 1; // thanh cong
}

void readDictData(char* path){
	fstream f;
	f.open(path, ios::in);
	string tu;
	string nghia;
	while(!f.eof()){
		getline(f, tu);
		getline(f, nghia);
		insertNodeTu(dict, tu, nghia);
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
		printDict(dict->left);
		cout<<dict->tu<<": "<<dict->nghia<<endl;
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
	readDictData(path);
	cout<<"---------- Tu Dien --------------"<<endl;
	printDict(dict);
	cout<<"---------------------------------"<<endl;
		
//	char* path2 = "E:\\doc.txt";
//	readDocument(path2);
	
	delNode(dict, "what");
	cout<<"---------------------------------"<<endl;
	printDict(dict);
	
	getch();
	return 0;
}
