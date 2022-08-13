//Nome: Matheus Oliveira Ribeiro da Silva

#include <iostream>
#include <iomanip>
#include <climits>
#include <sstream>
#include <cstring>
using namespace std;

#ifndef BSTREETEMPLATE_H
#define BSTREETEMPLATE_H

template< class TreeEntry >
class BinarySearchTree
{ public:
    BinarySearchTree();
    ~BinarySearchTree();
    bool empty();
    bool full();
    void clear();
    bool search(TreeEntry x);
    void insert(TreeEntry x);
    bool remove(TreeEntry x);
    void print();
    string toString();
    int nodes();
    int leaves();
    int height();
    TreeEntry minimum();
    TreeEntry maximum();
    TreeEntry secondMinimum();
    
  private:
    // definicao de estruturas
    struct TreeNode; 

    typedef TreeNode *TreePointer; 

    struct TreeNode
    { TreeEntry entry;             
      TreePointer leftNode, rightNode; 
    };

    // campos
    TreePointer root;
    
    // metodos
    void clear(TreePointer &t);
    bool iSearch(TreeEntry x);
    bool rSearch(TreeEntry x, TreePointer &t);
    bool remove(TreeEntry x, TreePointer &p);
    void removeMin(TreePointer &q,  TreePointer &r);
    void preOrder(TreePointer &t);
    void inOrder(TreePointer &t);
    void postOrder(TreePointer &t);
    void print(TreePointer &t, int s);
    string toString(TreePointer &t);
    int  nodes(TreePointer &t);
    int  leaves(TreePointer &t);
    int  height(TreePointer &t);
}; 

//------------------------------------------------------------
template< class TreeEntry >
BinarySearchTree<TreeEntry>::BinarySearchTree()
{  
  root = NULL;
}
//------------------------------------------------------------
template< class TreeEntry >
BinarySearchTree<TreeEntry>::~BinarySearchTree()
{  
  clear();
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::empty()
{
  return (root == NULL);
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::full()
{
  return false;
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::clear()
{
  clear(root);
  root = NULL;
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::clear(TreePointer &t)
{
  if( t != NULL )
  { clear( t->leftNode );
    clear( t->rightNode );
    delete t;
  }
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::search(TreeEntry x)
{ // basta escolher uma unica implementacao do metodo de busca
  // return iSearch(x);
  return rSearch(x, root);
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::iSearch(TreeEntry x)
{ TreePointer t=root;

  while (t != NULL && t->entry != x) 
    if(x < t->entry)
      t = t->leftNode; // procurar subarvore esquerda
    else
      t = t->rightNode; // procurar subarvore direita
 
  return (t != NULL);
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::rSearch(TreeEntry x, TreePointer &t)
{
  if(t == NULL)
    return false; // x nao encontrado
  
  if(x < t->entry)
      return rSearch(x,t->leftNode);
  else
    if(x > t->entry)
      return rSearch(x,t->rightNode);
   else     // x == t->entry
      return true;
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::insert(TreeEntry x)
{ TreePointer p=NULL, q=root, r;

  while (q != NULL) 
  { p = q; 
    if(x < q->entry)
      q = q->leftNode;
    else
      q = q->rightNode;
  }
  
  r = new TreeNode;
  r->entry = x;
  r->leftNode = NULL;
  r->rightNode = NULL;

  if(p == NULL)
    root = r;  // arvore vazia
  else
    if(x < p->entry)
      p->leftNode = r;
    else
      p->rightNode = r;
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::remove(TreeEntry x)
{
  return remove(x,root);
}
//------------------------------------------------------------
template< class TreeEntry >
bool BinarySearchTree<TreeEntry>::remove(TreeEntry x, TreePointer &p)
{ TreePointer q;
   
   if(p == NULL)
     return false; // elemento inexistente

   if(x < p->entry)
      return remove(x,p->leftNode);
   else
    if(x > p->entry)
       return remove(x,p->rightNode);
    else // remover p->
    { q = p;
      if(q->rightNode == NULL)
         p = q->leftNode;
      else
        if(q->leftNode == NULL)
          p = q->rightNode;
        else
          removeMin(q,q->rightNode);
      delete q;
      return true;
    }
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::removeMin(TreePointer &q,  TreePointer &r)
{
  if(r->leftNode != NULL)
    removeMin(q,r->leftNode);
  else
  { q->entry = r->entry;
    q = r;
    r = r->rightNode;
  }
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::print(TreePointer &t, int s)
{ int i;

  if(t != NULL) 
  { print(t->rightNode, s+3);
    for(i=1; i<= s; i++)
      cout << " ";
    cout << setw(6) << t->entry << endl;
    print(t->leftNode, s+3);
  }
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::print()
{
  print(root,0);     
  cout << endl << "Pre-ordem" << endl;
  preOrder(root);
  cout << endl << "Em-ordem" << endl;
  inOrder(root);
  cout << endl << "Pos-ordem" << endl;
  postOrder(root);
  cout << endl;
}


//------------------------------------------------------------
template< class TreeEntry >
string BinarySearchTree<TreeEntry>::toString()
{ 
  return toString( root );
}
//------------------------------------------------------------
template< class TreeEntry >
string BinarySearchTree<TreeEntry>::toString(TreePointer &t)
{ 
  if(t != NULL) 
    return toString(t->leftNode) + 
	       static_cast<ostringstream*>(&(ostringstream() << t->entry))->str() + " " +
		   toString(t->rightNode);
  else
    return "";  // subarvore vazia, nada a fazer
}


//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::preOrder(TreePointer &t)
{
  if(t != NULL)
  { cout << t->entry << ",";
    preOrder(t->leftNode);
    preOrder(t->rightNode);
  }
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::inOrder(TreePointer &t)
{
  if(t != NULL)
  { inOrder(t->leftNode);
    cout << t->entry << ",";
    inOrder(t->rightNode);
  }
}
//------------------------------------------------------------
template< class TreeEntry >
void BinarySearchTree<TreeEntry>::postOrder(TreePointer &t)
{
  if(t != NULL)
  { postOrder(t->leftNode);
    postOrder(t->rightNode);
    cout << t->entry << ",";
  }
}
//------------------------------------------------------------
template< class TreeEntry >
int BinarySearchTree<TreeEntry>::nodes()
{  return nodes(root);
}
//------------------------------------------------------------
template< class TreeEntry >
int BinarySearchTree<TreeEntry>::nodes(TreePointer &t)
{ 
  if(t == NULL)
     return 0;
  else
    return 1 + nodes(t->leftNode) + nodes(t->rightNode);
}
//------------------------------------------------------------
template< class TreeEntry >
int BinarySearchTree<TreeEntry>::leaves()
{  return leaves(root);
}
//------------------------------------------------------------
template< class TreeEntry >
int BinarySearchTree<TreeEntry>::leaves(TreePointer &t)
{  if(t == NULL)
     return 0;
   else
     if(t->leftNode == NULL && t->rightNode == NULL)
        return 1;
     else
        return leaves(t->leftNode) + leaves(t->rightNode);
}
//------------------------------------------------------------
template< class TreeEntry >
int BinarySearchTree<TreeEntry>::height()
{  return height(root);
}
//------------------------------------------------------------
template< class TreeEntry >
int BinarySearchTree<TreeEntry>::height(TreePointer &t)
{ if(t == NULL)
     return -1;
  else
  {   int L,R;
      L = height(t->leftNode);
      R = height(t->rightNode);
      if(L>R) return L+1; else return R+1;
  }
}
//------------------------------------------------------------
template< class TreeEntry >
TreeEntry BinarySearchTree<TreeEntry>::minimum()
{ TreePointer t=root;

  if(t == NULL)
  { cout << "Arvore vazia" << endl;
    return INT_MIN;
  }
  while (t->leftNode != NULL) 
    t = t->leftNode; // procurar subarvore esquerda
  
  return t->entry;
}
//------------------------------------------------------------
template< class TreeEntry >
TreeEntry BinarySearchTree<TreeEntry>::maximum()
{ TreePointer t=root;

  if(t == NULL)
  { cout << "Arvore vazia" << endl;
    return INT_MAX;
  }
  while (t->rightNode != NULL) 
    t = t->rightNode; // procurar subarvore direita
  
  return t->entry;
}
//------------------------------------------------------------
template< class TreeEntry >
TreeEntry BinarySearchTree<TreeEntry>::secondMinimum()
{ TreePointer t=root; //Ponteiro t percorrera a arvore uma posicao a frente do ponteiro p 
  TreePointer p=root; 
  int min2; //Armazena o 2o valor minimo

  if(t == NULL)
  { cout << "Arvore vazia" << endl;
    return INT_MAX;
  }
  
  //Se a arvore nao for vazia a esquerda, o ponteiro t atingira a extremidade esquerda, ou seja, o valor minimo da arvore.
  //O ponteiro p, que estara uma posicao atras do t, sera o 2o menor valor se nao tiver vertice a sua direita.
  if (t->leftNode != NULL) {
    t = t->leftNode;
      while (t->leftNode != NULL) {
      t = t->leftNode;
      p = p->leftNode;
      }
      min2 = p->entry;
  //Se houver vertice a direita do vertice apontado por p, o ponteiro p o percorrera e, havendo no(s) a esquerda deste, tambem.
  //Parada: ate atingir o fim desta subarvore. 
    if (p->rightNode == NULL)
      return min2;
      else {        
        p = p->rightNode;
        while (p->leftNode != NULL) {
        p = p->leftNode;
      }
//Eh feita uma comparacao adicional. Se o valor deste vertice (fim da subarvore) for menor que o 2o minimo anterior, min2 eh atualizado.
      if (p->entry < min2) {
        min2 = p->entry; 
      }
    }
  }

//Caso a arvore cresca apenas para a direita, o 2o minimo sera o vertice logo abaixo da raiz caso este nao possua vertice a sua esquerda.
  if (p->leftNode == NULL && p->rightNode != NULL) {
    p = p->rightNode;
    min2 = p->entry;
    if (p->leftNode == NULL)
      return min2;
//Se houver, o ponteiro p percorrera sua subarvore ate o final.
      else {
        while (p->leftNode != NULL) {
        p = p->leftNode;
      }
//Fara uma comparacao adicional, atualizando o valor de min2 se a condicao for satisfeita.
      if (p->entry < min2) {
        min2 = p->entry;
      }
    }
  }    
  return min2;
}
//------------------------------------------------------------

//Analise de complexidade para o pior caso (O.)

//O pior caso para este algoritmo sera ao percorrer a altura da arvore binaria de busca (O (h)), 
//O maior nº de operacoes ocorrera ao percorrer o seu lado esquerdo, dados os dois ponteiros, nos casos de...   
//...a comparacao (p->rightNode == NULL) ser falsa e a comparacao (p->entry < min2) verdadeira.

/*
  if (t->leftNode != NULL) {                [2]
    t = t->leftNode;                        [1]
      while (t->leftNode != NULL) {         [2 + 1 + 1] -> 4n (neste loop)
      t = t->leftNode;                      
      p = p->leftNode;                      
      }
      min2 = p->entry;                      [1]

  if (p->rightNode == NULL)                 [2] (comp. falsa nao executa a proxima linha)
      return min2;                          
      else {                                
        p = p->rightNode;                   [1]
        while (p->leftNode != NULL) {       [2 + 1] -> 3k (neste loop)
        p = p->leftNode;                    
      }
        if (p->entry < min2) {              [2]
          min2 = p->entry;                  [1] (comp. verdadeira executa esta atribuicao)
      }
    }
  }

No de operacoes = 10 + 4n + 3k.

n: nº de vértices percorridos dentro das operações no 1º if;
k: nº de vértices percorridos dentro das operações no 2º if;
no pior caso, a altura da árvore será percorrida. n + k vértices (O (h)). [linear] 
para este algoritmo,
ressalta-se que n + k = h apenas podera ser verdade se altura da arvore implicar no percorrer de subarvore especifica ao no apontado pelo ponteiro p.

exemplo:
          [10]
        [5]   [15]
      [4]         [20]
    [2]   [6]
        [3]  

no caso, h = 4.
o ponteiro t eh inicializado na raiz (aponta para 10).
como t->leftNode != NULL, avança e aponta para 5.
(inicia-se o 1º if)
percorre-se 4, depois 2 (n = 2).
como o no 4 tem subarvore a direita, o ponteiro p aponta para a direita [6], depois percorre [3] (p=2).
assim, n + p = 4 = h.
 
*/

#endif /* BSTREETEMPLATE_H */
