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
    clock_t start_time,end_time,total_time=0;//CLOCK VARIABLES TO STORE TIME TAKEN IN ACTUAL SORTING OPERATION
    int u,v,w,S,m;
    cin>>n>>m;
    cin>>u>>v;
    cin>>S;
    S-=2;
    FORE(i,1,100)cin>>u;

    FORE(i,1,n)graph[i].clear();
    FORE(i,1,n)//INPUT GRAPH AS ADJACENCY LIST
    {
        FORE(j,1,n-1)
        {
            cin>>v>>w;
            graph[i].PB(PI(v,w));//u----->v with cost w
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
    cin>>u>>v;
    //Now input T's
    FORE(i,0,S+1)
    {
        cin>>u;
        FORE(j,1,u)
        {
            cin>>v;
            T[i].PB(v);
        }
    }
    cout<<"Processing\n";
    //T[0].PB(1);
    //T[S+1].PB(n);
    /*FORE(i,0,S+1)
    {
        cout<<i<<"->";
        EACH(it,T[i])
        {
            cout<<"("<<*it<<")->";
        }
        cout<<"\n";
    }*/
    start_time=clock();
    FORE(i,0,S)
    {
        EACH(it1,T[i])
        {
            Dijkstra(*it1,n,graph);
            EACH(it2,T[i+1])
            {
                vector<int> vi;
                int P=*it2;
                if(parent[P]==-1)vi.PB(-1);
                else
                {
                    vi.PB(P);
                    while(P!=(*it1))
                    {
                        vi.PB(parent[P]);
                        P=parent[P];
                    }
                }
                reverse(ALL(vi));
                AUX_graph[*it1].PB(PIIVI(PI(*it2,dist[*it2]),vi));
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
    end_time=clock();
    cout<<"cost="<<FCOST[1]<<"\n";
    total_time=total_time+(end_time-start_time);
    printf("\n\nTIME TAKEN =%f SECONDS\n\n\n\n",((float)(total_time))/CLOCKS_PER_SEC);
    EACH(it,FINALPATH)cout<<*it<<"->";
    cout<<"<-\n";
    EACH(it,PATH)cout<<*it<<"->";
    cout<<"<-\n";
    return 0;
}
