#include <iostream>
#include <fstream>
using namespace std;

// for linked
struct treenode
{
    int dat;
    treenode *lchild;
    treenode *rchild;
};


class bstree
{
 public:
        bstree();
        void in( );
        void pre( );
        void post( );
        void insert( int x );
        void remove( int x );
        bool search( int x );
        int numnodes();
        int height();
 private:
        void pre(treenode *r);
        void post(treenode *r);
        void in(treenode *r);
        void remove(int x, treenode *r);
        int numnodes(treenode *r);
        int height(treenode *r);
        treenode *findnode(int x);
        treenode *findnode(int x, treenode *r);
        treenode *findparent(int x);
        treenode *findparent(int x, treenode *r);
        treenode *findlmost(treenode*r);
        treenode *root;
        bool search (treenode *t, int x);
};
treenode *bstree::findlmost(treenode *t)
{
        if (t->lchild == NULL)
                return t;
        return findlmost(t->lchild);
}
treenode *bstree::findparent(int val)
{
        return findparent(val, root);
}
treenode *bstree::findparent(int val, treenode*t)
{
        if (t->lchild!=NULL)
        {
                if (t->lchild->dat == val)
                        return t;
        }
        if (t->rchild!=NULL)
        {
                if (t->rchild->dat == val)
                        return t;
        }
        if (t->dat > val)
                return findparent(val, t->lchild);
        else
                return findparent(val, t->rchild);

}

treenode *bstree::findnode(int val)
{
        return findnode(val, root);
}
treenode *bstree::findnode(int val, treenode*t)
{
        if (t->dat == val)
                return t;
        if (t->dat > val)
                return findnode(val, t->lchild);
        else
                return findnode(val, t->rchild);

}
bstree::bstree()
{
        root = NULL;
}
void bstree::remove(int x)
{
        if (!search(x))
                return;
        treenode *node = findnode(x);
        treenode *parent;
        if (node != root)
                parent = findparent(x);

        if (node->rchild==NULL && node->lchild==NULL)
        {
                if (node != root)
                {
                        if (parent->rchild == node)
                                parent->rchild = NULL;
                        else
                                parent->lchild = NULL;
                }
                else
                        root = NULL;
                delete node;
                return;
        }
        if (node->rchild != NULL && node->lchild != NULL)
        {
                treenode *end = findlmost(node->rchild);
                treenode *endparent = findparent(end->dat);
                node->dat = end->dat;
                if (endparent->rchild == end)//detaches the leftmost node on the right side from parent
                {
                        if (end->rchild == NULL)
                                endparent->rchild = NULL;
                        else
                                endparent->rchild = end->rchild;
                }
                else
                {
                        if (end->rchild == NULL)
                                endparent->lchild = NULL;
                        else
                                endparent->lchild = end->rchild;
                }
                delete end;
                return;
        }
        if (node->rchild == NULL) // has left child but not right
        {
                if (node != root)
                {
                        if (parent->rchild == node)
                                parent->rchild = node->lchild;
                        else
                                parent->lchild = node->lchild;
                }
                else
                        root = node->lchild;
                delete node;
                return;
        }
        if (node->lchild == NULL) // has right child but not left
        {
                if (node != root)
                {
                        if (parent->rchild == node)
                                parent->rchild = node->rchild;
                        else
                                parent->lchild = node->rchild;
                }
                else
                        root = node->rchild;
                delete node;
                return;
        }
}
void bstree::remove(int x, treenode *t)
{

}
int bstree::height()
{
        return height(root);
}
int bstree::height(treenode *t)
{
        if (t==NULL)
                return 0;
        if (height(t->lchild)>height(t->rchild))
                return height(t->lchild)+1;
        else
                return height(t->rchild)+1;
}
int bstree::numnodes()
{
        return numnodes(root);
}
int bstree::numnodes(treenode *t)
{
        int k = 0;
        if (t==NULL)
                return 0;
        k += numnodes(t->lchild);
        k += numnodes(t->rchild);
        k++;
        return k;
}
void bstree::in()
{
        cout << "Inorder: ";
        in(root);
        cout << endl;
}
void bstree::in(treenode *t)
{
        if (t==NULL)
                return;
        in(t->lchild);
        cout << t->dat << ' ';
        in(t->rchild);
}
void bstree::pre()
{
        cout << "Preorder: ";
        pre(root);
        cout << endl;
}
void bstree::pre(treenode *t)
{
        if (t==NULL)
                return;
        cout << t->dat << ' ';
        pre(t->lchild);
        pre(t->rchild);
}
void bstree::post()
{
        cout << "Postorder: ";
        post(root);
        cout << endl;

}
void bstree::post(treenode *t)
{
        if (t==NULL)
                return;
        post(t->lchild);
        post(t->rchild);
        cout << t->dat << ' ';
}

void bstree::insert( int val )
{
        treenode *tmp;
        treenode *nn;
        tmp = root;
        nn = new treenode;
        nn->dat = val;
        nn->lchild = NULL;
        nn->rchild = NULL;

        if (root==NULL)
        {
                root = nn;
                return;
        }
        while (true)
        {
        if (val == tmp->dat)
                return;
        if (val<tmp->dat)
        {
                if (tmp->lchild==NULL)
                {
                        tmp->lchild = nn;
                        return;
                }
                else
                        tmp = tmp->lchild;
        }
        else if (val>tmp->dat)
        {
                if (tmp->rchild==NULL)
                {
                        tmp->rchild = nn;
                        return;
                }
                else
                        tmp = tmp->rchild;
        }
        }

}

bool bstree::search( int val )
{
        return search(root, val);
}
bool bstree::search(treenode *t, int val)
{
        if (t==NULL)
                return false;
        if (t->dat == val)
                return true;
        if (t->dat > val)
                return search(t->lchild,val);
        else
                return search(t->rchild,val);
}

int main(int argc, char *argv[])
{
        fstream reader;
        reader.open(argv[1],ios_base::in);
        bstree t;
        int input;
        while (reader>>input)
        {
                switch (input)
                {
                        case -1:
                                reader >> input;
                                t.remove(input);
                                break;
                        case 0:
                                return 0;
                        case 1:
                                reader >> input;
                                t.insert(input);
                                break;
                        case 2:
                                reader >> input;
                                if (t.search(input))
                                        cout << "found " << input << endl;
                                else
                                        cout << "NOT found " << input << endl;
                                break;
                        case 3:
                                t.pre();
                                break;
                        case 4:
                                t.in();
                                break;
                        case 5:
                                t.post();
                                break;
                        case 7:
                                cout << "Number of nodes: " << t.numnodes() << endl;
                                break;
                        case 8:
                                cout << "Height of tree: " << t.height() << endl;
                                t.height();
                                break;
                }
        }
        return 1;
}
