#include<iostream>
#include<list>
#include<queue>
using namespace std;

class Graph
{
private:
    int V;
    list<int>* l;
public:
    Graph(int vertices)
    {
        V=vertices+1;
        l=new list<int>[V];
    }
    ~Graph()
    {
        delete [] l;
    }
    void AddEdge(int fmV, int toV, bool bidir=true)
    {
        l[fmV].push_back(toV);
        if(bidir)
            l[toV].push_back(fmV);
        return;
    }

    void PrintAdjList()
    {
        for(int i=0;i<V;i++)
        {
            cout<<i<<"->";
            for(list<int>::iterator it=l[i].begin();it!=l[i].end();it++)
                cout<<*it<<", ";
            cout<<endl;
        }
    }

    void BFS(int s)
    {
        queue<int> q;
        bool* visited=new bool[V];
        for(int i=0;i<V;i++)
            visited[i]=false;
        q.push(s);
        visited[s]=true;
        while(!q.empty())
        {
            int f=q.front();
            cout<<f<<" ";
            q.pop();
            for(list<int>::iterator it=l[f].begin();it!=l[f].end();it++)
                if(visited[*it]==false)
                {
                    q.push(*it);
                    visited[*it]=true;
                }
        }
        cout<<endl;
    }

    void BFSpath(int s, int x)
    {
        int *distance=new int[V];
        int *parent=new int [V];
        for(int i=0;i<V;i++)
        {
            distance[i]=-1;
            parent[i]=-1;
        }
        queue<int> q;
        q.push(s);
        distance[s]=0;
        while(!q.empty())
        {
            int f=q.front();
            cout<<f<<" "<<distance[f]<<endl;
            q.pop();
            for(list<int>::iterator it=l[f].begin();it!=l[f].end();it++)
                if(distance[*it]==-1)
                {
                    q.push(*it);
                    distance[*it]=distance[f]+1;
                    parent[*it]=f;
                }
        }
        int ind=x;
        cout<<"Min Distance of "<<x<<" :"<<distance[x]<<endl;
        cout<<"Path is:"<<x<<"<-";
        while(parent[ind]!=-1)
        {
            cout<<parent[ind]<<"<-";
            ind=parent[ind];
        }
        cout<<endl;
    }

    void DFSrecursive(int node, bool* visited)
    {
        cout<<node<<" ";
        visited[node]=true;
        for(list<int>::iterator it=l[node].begin();it!=l[node].end();it++)
            if(visited[*it]==false)
                DFSrecursive(*it,visited);

    }
    void DFS(int s)
    {
        bool* visited=new bool[V];
        for(int i=0;i<V;i++)
            visited[i]=false;
        DFSrecursive(s,visited);
        cout<<endl;
    }

    void DFSallcomponents()
    {
        bool* visited=new bool[V];
        for(int i=0;i<V;i++)
            visited[i]=false;
        int component=0;
        for(int i=0;i<V;i++)
        {
            if(visited[i]==false)
            {
                component++;
                cout<<"DFS of component-"<<component<<":";
                DFSrecursive(i,visited);
                cout<<endl;
            }
        }
    }
};

int main()
{
    int n=36;
    Graph g(36);
    int *Board=new int[n+1];
    for(int i=1;i<=n;i++)
        Board[i]=i;
    Board[2]=15;
    Board[5]=7;
    Board[9]=27;
    Board[17]=4;
    Board[18]=29;
    Board[20]=6;
    Board[24]=16;
    Board[25]=35;
    Board[32]=30;
    Board[34]=12;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6;j++)
            if(i+j<=n)
                g.AddEdge(i,Board[i+j],false);
    }
    g.BFSpath(1,36);
    g.PrintAdjList();
}

