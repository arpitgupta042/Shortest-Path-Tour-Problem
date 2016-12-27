#include "Headers.cpp"

//Main code
#define MAXN 100001
#define INF INT_MAX

vector<PI> graph[MAXN];
vector<PIIVI> AUX_graph[MAXN];
int n,dist[MAXN],parent[MAXN];
vector<int> T[MAXN];
int FCOST[MAXN],SUCCESSOR[MAXN];
#include "DijkstraALL.cpp"
int main()
{
    int u,v,w,S;
    cin>>n;
    FORE(i,1,n)graph[i].clear();
    FORE(i,1,n)//INPUT GRAPH AS ADJACENCY LIST
    {
        cin>>u;
        scanf("%d,%d",&v,&w);
        while(v!=(-1))
        {
            graph[u].PB(PI(v,w));//u----->v with cost w
            scanf("%d,%d",&v,&w);
        }
    }
    /*Dijkstra(1);
    FORE(i,1,n)
    {
        cout<<i<<"->";
        EACH(it,graph[i])
        {
            cout<<"("<<it->first<<","<<it->second<<")->";
        }
        cout<<"\n";
    }
    //int destinations[10]={7,37,59,82,99,115,133,165,188,197};
    int destinations[7]={1,2,3,4,5,6,7};
    REP(i,7)
    {
        printf("\n distance = %d between 1 and %d",dist[destinations[i]],destinations[i]);
    }
    */

    //Assume s=1,d=n
    //input S=number of Stages
    cin>>S;
    //Now input T's
    FORE(i,1,S)
    {
        cin>>u;
        FORE(j,1,u)
        {
            cin>>v;
            T[i].PB(v);
        }
    }
    T[0].PB(1);
    T[S+1].PB(n);
    /*FORE(i,0,S+1)
    {
        cout<<i<<"->";
        EACH(it,T[i])
        {
            cout<<"("<<*it<<")->";
        }
        cout<<"\n";
    }*/
    FORE(i,0,S)
    {
        EACH(it1,T[i])
        {
            Dijkstra(*it1,n,graph);
            EACH(it2,T[i+1])
            {
                vector<int> v;
                int P=*it2;
                if(parent[P]==-1)v.PB(-1);
                else
                {
                    v.PB(P);
                    while(P!=(*it1))
                    {
                        v.PB(parent[P]);
                        P=parent[P];
                    }
                }
                reverse(ALL(v));
                AUX_graph[*it1].PB(PIIVI(PI(*it2,dist[*it2]),v));
            }
        }
    }
    /*FORE(i,1,n)
    {
        cout<<i<<"->";
        EACH(it,AUX_graph[i])
        {
            cout<<"("<<it->first<<","<<it->second<<")->";
        }
        cout<<"\n";
    }*/

    fill(FCOST,FCOST+n+1,INF);
    fill(SUCCESSOR,SUCCESSOR+n+1,-1);
    FCOST[n]=0;
    SUCCESSOR[n]=n;
    FORD(i,S,0)
    {
        EACH(it1,T[i])
        {
            EACH(it2,AUX_graph[*it1])
            {
                int tempcost;
                if((FCOST[it2->first.first]==INF)||((it2->first.second)==INF))tempcost=INF;
                else                      tempcost=FCOST[it2->first.first]+it2->first.second;
                //FCOST[*it1]=min(FCOST[*it1],tempcost);
                if(tempcost<FCOST[*it1])
                {
                    SUCCESSOR[*it1]=it2->first.first;
                    FCOST[*it1]=tempcost;
                }

            }
        }
    }
    cout<<FCOST[1]<<"\n";
    vector<int> PATH,FINALPATH;
    int succ=1;
    while(succ!=n)
    {
        PATH.PB(succ);
        succ=SUCCESSOR[succ];
    }
    PATH.PB(succ);//PATH now has multistage path
    //now blow up the path using Dijkstra Paths
    int source=1;
    FINALPATH.PB(source);
    IFOR(it,PATH.begin()+1,PATH.end())
    {
        EACH(it2,AUX_graph[source])
        {
            if(it2->first.first==(*it))
            {
                FINALPATH.insert(FINALPATH.end(),it2->second.begin()+1,it2->second.end());
                break;
            }
        }
        source=*it;
    }
    EACH(it,FINALPATH)cout<<*it<<"->";
    cout<<"<-";
    return 0;
}
