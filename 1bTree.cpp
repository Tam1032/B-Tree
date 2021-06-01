#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define M 5
struct Student{
  int ID;
  string name;
  int rank;
};
struct Node{
  Student keys[M];
  Node *children[M+1]={NULL};
  int nkeys, leaf;
};
typedef Node *Tree;
void createTree(Tree &root);
int insert(Student arr[],int &n,Student newSt);
Tree split(Tree &p, Tree q);
int binarySearch(Student arr[], int n, Student find);
void addNode(Tree &root, Tree q, Student x);
void printMin(Tree &root);
int main(){
  ifstream fi("input.txt");
  Tree root,q;
  createTree(root);
  createTree(q);
  int n;
  fi>>n;
  Student temp;
  for(int i=0;i<n;i++){
    fi.ignore();
    fi>>temp.ID;
    fi>>temp.name;
    fi>>temp.rank;
    addNode(root,q,temp);
  }
  printMin(root);
  fi.close();
  return 0;
}
void createTree(Tree &root){
  root=NULL;
}
int insert(Student arr[],int &n,Student newSt){
  if(n==0){
    arr[0]=newSt;
    n++;
    return 0;
  }
  int i;
  for (i=0;i<n;i++){
    if(arr[i].rank>newSt.rank){
      for(int j=n;j>i;j--) arr[j]=arr[j-1];
      arr[i]=newSt;
      n++;
      return i;
    }
  }
  arr[i]=newSt;
  n++;
  return i;
}
Tree split(Tree &p, Tree q){
  if(p->nkeys<M) return NULL;
  Tree pp = new Node;
  p->nkeys/=2;
  pp->nkeys=p->nkeys;
  pp->leaf=p->leaf;
  for(int i=0;i<p->nkeys;i++){
    pp->keys[i]=p->keys[p->nkeys+i+1];
    pp->children[i]=p->children[p->nkeys+i+1];
  }
  pp->children[pp->nkeys]=p->children[M];
  if(q==NULL){
    q=new Node;
    q->nkeys=0;
    q->leaf=0;
  }
  int i = insert(q->keys, q->nkeys, p->keys[p->nkeys]);
  q->children[i] = p;
  q->children[i+1] = pp;
  return q;
}
int binarySearch(Student arr[], int n, Student find){
  for(int i=0;i<n;i++){
    if(arr[i].rank>find.rank) return i;
  }
  return n;
}
void addNode(Tree &root, Tree q, Student x) {
  if (root == NULL) {
    root = new Node;
    root->leaf = 1;
    root->nkeys = 1;
    root->keys[0] = x;
    return;
  }
  if (root->leaf) {
    insert(root->keys, root->nkeys, x);
  }
  else {
    int i = binarySearch(root->keys, root->nkeys, x);
    if (i < root->nkeys) {
      if (root->keys[i].rank == x.rank)return;
    }
    addNode(root->children[i], root, x);
  }
  Tree p = split(root, q);
  if (p)
    if (q == NULL)
    root = p;
    return;
}
void printMin(Tree &root){
  int i;
  for(i=0;i<root->nkeys;i++){
    if(root->children[i]!=NULL)
      printMin(root->children[i]);
    cout<<root->keys[i].ID<<"\t";
    cout<<root->keys[i].name<<"\t";
    cout<<root->keys[i].rank<<endl;
  }
  if(root->children[i]!=NULL)
    printMin(root->children[i]);
}
