#include <iostream>
#include <fstream>
using namespace std;

struct node
{
        struct node *prev;
        struct node *next;
        int data;
};

class list
{
public:
        list();
        int pop();
        void push(int data);
        struct node *first;//made public to determine if list is empty. (Done this way to reduce function count at no cost of readablitiy)
        struct node *last;//Same as above.
};

class vipq
{
public:
        vipq();
        int pop();
        void push(int data, int pri);
        void printtopprio();
private:
        list queue[10];
};

list::list()
{
        first = NULL;
        last = NULL;
}

void list::push(int data)
{
        node *g;
        g = new node;
        g->data = data;
        g->prev = NULL;
        if(first == NULL)
        {
                g->next = NULL;
                first = g;
                last = g;
                return;
        }
        else
        {
                g->next = first;
                first->prev = g;
                first = g;
        }
}


int list::pop()
{
        int x;
        node *tmp;
        tmp = last;
        if (tmp!=NULL)
                x = tmp->data;
        if(first==last)
        {
                last = NULL;
                first = NULL;
        }
        else
        {
                last = last->prev;
                last->next = NULL;
        }
        delete tmp;
        return x;
}
vipq::vipq()
{
}

void vipq::push(int data, int pri)
{
        queue[pri-1].push(data);
}

int vipq::pop()
{
        for(int x=9;x>=0;x--)//index 9 is prio 10, index 0 is prio 1
                if (queue[x].first!=NULL)
                {
                        cout << "Priority level: " << x+1 << " Data value: ";
                        return queue[x].pop();
                }
        cout << "ERROR! Removing from empty queue! ";
        return 0;
}

void vipq::printtopprio()
{
        for(int x=9;x>=0;x--)
                if (queue[x].last!=NULL)
                {
                        cout << "Highest Prio: " << queue[x].last->data << endl;
                        return;
                }
        cout << "ERROR! Searching in empty queue! ";
        return;
}

int main(int argc, char *argv[])
{
        int input, pri, key, x;
        vipq q;
    fstream reader;
    reader.open(argv[1],ios_base::in);
        while(reader>>input)
        {
                switch(input)
                {
                        case -1:
                                cout << q.pop() << endl;
                                break;
                        case 1:
                                reader>>pri;
                                reader>>key;
                                q.push(key, pri);
                                break;
                        case 3:
                                q.printtopprio();
                                break;
                }
        }
        return 1;//ERROR!
}
