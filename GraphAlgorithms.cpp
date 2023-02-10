#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct node
{
        node *next;
        node *prev;
        int data;
};

class stack
{
        public:
                stack();
                void push(int x);
                int pop();
                bool empty();
        private:
                node *first;
};
bool stack::empty()
{
        if (first==NULL)
                return 1;
        return 0;
}
stack::stack()
{
        first = NULL;
}
void stack::push(int x)
{
        node *tmp;
        tmp = new node;
        tmp->data = x;
        tmp->next = NULL;
        if (first!=NULL)
        {
                first->next = tmp;
                tmp->prev = first;
        }
        else
        {
                tmp->prev = NULL;
        }
        first = tmp;
}
int stack::pop()
{
        int x=0;
        if (first==NULL)
                return x;//ERROR!
        node *tmp;
        x = first->data;
        tmp = first;
        if (tmp->prev==NULL)
                first = NULL;
        else
        {
                first = first->prev;
                first->next = NULL;
        }
        delete tmp;
        return x;
}
class queue
{
        public:
                queue();
                int pop();
                bool empty();
                void push(int x);
        private:
        node *first;
        node *last;
};
bool queue::empty()
{
        if (first==NULL)
                return 1;
        return 0;
}
queue::queue()
{
        first = NULL;
        last = NULL;
}
int queue::pop()
{
        int x=0;
        if (last==NULL)
        {
                return x;//ERROR
        }
        node *tmp;
        tmp = last;
        if (last==first)
        {
                x = last->data;
                last = NULL;
                first = NULL;
                delete tmp;
                return x;
        }
        else
        {
                last = last->prev;
                last->next = NULL;
                x = tmp->data;
                delete tmp;
                return x;
        }
}
void queue::push(int x)
{
        node *tmp;
        tmp = new node;
        tmp->data = x;
        tmp->prev = NULL;
        if (first==NULL)
        {
                first = tmp;
                last = tmp;
                return;
        }
        else
        {
                first->prev = tmp;
                first = tmp;
        }
}
class graph
{
        public:
                graph( ifstream& file );   // constructor
                                   // fill graph from data file
                                   // file is already open
                void bfs( int x );         // breadth-first node order
                void bfssp( int x );       // breadth-first spanning tree
                void dfs( int x );         // depth-first node order
                void dfssp( int x );       // depth-first spanning tree
                void mprint();             // print representation
                void dijkstra(int x);
                void prim(int x);
        private:
        int nodes;
        int edges;
        int matrix[100][100] = {0};
};
void graph::prim(int x)
{
        int nodestree[nodes+1], totalnodes=1;
        nodestree[0] = x;
        bool isintree[nodes+1] = {0};
        isintree[x] = 1;
        int totalcost = 0, y, z, min, nextnode;
        for (totalnodes = 1; totalnodes<nodes;totalnodes++)
        {
                min = 1000000;
                for(z=0;z<totalnodes;z++)
                {
                        for(y=1;y<=nodes;y++)
                        {
                                if ( matrix[y][nodestree[z]]!=0 && !isintree[y])
                                {
                                        if (matrix[y][nodestree[z]]<min)
                                        {
                                                min = matrix[y][nodestree[z]];
                                                nextnode = y;
                                        }
                                }
                        }
                }
        isintree[nextnode] = 1;
        nodestree[totalnodes] = nextnode;
        totalcost += min;
        cout << "Current min: " << min << endl;
        }
        cout << "Total cost: " << totalcost << endl;
        for (int i=0;i<totalnodes;i++)
                cout << nodestree[i] << endl;
}
int min(int x[], int y, bool w[])
{
        int min = -1, z;
        for (z=1;w[z]==1;z++);
        min = z;
        for (;z<y;z++)
                if (x[z]<x[min]&&w[z]!=1)
                        min = z;
        return min;
}
void graph::dijkstra(int x)
{
        int distance[nodes+1];
        fill_n(distance,nodes+1,1000000);
        bool solved[nodes+1] = {0};
        int numsolved = 0;
        int y, current;
        distance[x] = 0;
        while (numsolved<nodes)
        {
                current = min(distance,nodes,solved);
                for (y=1;y<=nodes;y++)
                {
                        if ( matrix[current][y] + distance[current] < distance[y] && matrix[current][y]!=0 )
                                distance[y] = matrix[current][y]+distance[current];
                }
                solved[current] = 1;
                numsolved++;
                cout << "Current progress at node " << current << ':' << endl;
                for (int a=1;a<=nodes;a++)
                {
                        cout << a << ": " << distance[a] << "   ";
                }
                cout << endl;
        }
        cout << endl << "Final tree:" << endl;
        for (y=1;y<=nodes;y++)
                cout << y << ": " << distance[y] << endl;
}
void graph::bfs(int x)
{
        int y, z;
        bool mark[nodes+1] = {0};
        queue D;
        D.push(x);
        while (!D.empty())
        {
                y = D.pop();
                if (!mark[y])
                {
                        cout << y << " ";
                        mark[y] = 1;
                        for (z=0;z<=nodes;z++)//CHANGED!
                        {
                                if (matrix[z][y])//if tree[z][y]!=0. In other words, if an edge exists between these two nodes
                                {
                                        if (!mark[z])
                                        {
                                                D.push(z);
                                        }
                                }
                        }
                }
        }
}
void graph::bfssp(int x)
{
        int y, z, w;
        bool mark[nodes+1] = {0};
        queue E;
        queue D;
        D.push(x);
        E.push(x);
        while (!D.empty())
        {
                y = D.pop();
                w = E.pop();
                if (!mark[y])
                {
                        cout << w << "-" << y <<endl;
                        mark[y] = 1;
                        for (z=0;z<=nodes;z++)//CHANGED!
                        {
                                if (matrix[z][y])//if tree[z][y]!=0. In other words, if an edge exists between these two nodes
                                {
                                        if (!mark[z])
                                        {
                                                D.push(z);
                                                E.push(y);
                                        }
                                }
                        }
                }
        }
}
void graph::dfs(int x)
{
        int y, z;
        bool mark[nodes+1] = {0};
        stack D;
        D.push(x);
        while (!D.empty())
        {
                y = D.pop();
                if (!mark[y])
                {
                        cout << y << " ";
                        mark[y] = 1;
                        for (z=nodes;z>0;z--)//CHANGED!
                        {
                                if (matrix[z][y])//if tree[z][y]!=0. In other words, if an edge exists between these two nodes
                                {
                                        if (!mark[z])
                                        {
                                                D.push(z);
                                        }
                                }
                        }
                }
        }
}
void graph::dfssp(int x)
{
    int y, z, w;
    bool mark[nodes+1] = {0};
    stack D;
        stack E;
    D.push(x);
        E.push(x);
    while (!D.empty())
    {
        y = D.pop();
                w = E.pop();
        if (!mark[y])
        {
            cout << w << "-" << y << endl;
            mark[y] = 1;
            for (z=nodes;z>0;z--)//CHANGED!
            {
                if (matrix[z][y])//if tree[z][y]!=0. In other words, if an edge exi$
                {
                    if (!mark[z])
                    {
                        D.push(z);
                                                E.push(y);
                    }
                }
            }
        }
    }
}
graph::graph( ifstream& file )
{
        int source, destination, weight;
        file >> nodes;
        file >> edges;
        while(file>>source>>destination>>weight)
        {
                matrix[source][destination] = weight;
                matrix[destination][source] = weight;
        }
}

void graph::mprint()
{
        int x, y;
        cout << "   ";
        for (y=1;y<=nodes;y++)
        {
                cout << setw(6) << y;
        }
        cout << endl;
        cout << "     " << '#';
        for (y=1;y<=nodes;y++)
                cout << "=====#";
        cout << endl;
        for (x=1;x<=nodes;x++)
        {
                cout << setw(5) << x << '|';
                for (y=1;y<=nodes;y++)
                {
                        cout << setw(3) << matrix[x][y] << setw(3) << '|';
                }
                cout << endl;
                cout << "     " << '#';
                for (y=1;y<=nodes;y++)
                        cout << "=====#";
                cout << endl;
        }
}

int main( int argc, char *argv[] )
{
        ifstream ifp;

        //checking to see if file was entered on command line
        if ( argc != 2 )
        {
                cout << "File was not entered\n";
                return 2;
        }

        ifp.open( argv[1] );

        // checking to see if file was opened successfully
        if( ! ifp.is_open() )
        {
                cout << "File could not be opened\n";
                return 3;
        }

        //create graph based on graph description file
        graph g( ifp );

        //print the matrix
        g.mprint();
        cout << endl << endl;

        int location;
        //ask for starting location
        cout << "Enter the starting location: ";
        cin >> location;

        // calculate DFS
        cout << "DFS" << endl;
        g.dfs( location );
        cout << endl << endl;

        //calculate DFS-SP
        cout << "DFS ST" << endl;
        g.dfssp( location );
        cout << endl << endl;

        //calculate BFS
        cout << "BFS" << endl;
        g.bfs( location );
        cout << endl << endl;

        //calculate BFS-SP
        cout << "BFS ST" << endl;
        g.bfssp( location );
        cout << endl << endl;

        cout << "DIJKSTRA" << endl;
        g.dijkstra( location );
        cout << endl << endl;

        cout << "PRIM" << endl;
        g.prim( location );
        cout << endl << endl;

        return 0;
}
