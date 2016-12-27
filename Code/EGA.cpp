#include "Headers.cpp"

//Main code
#define MAXN 100001
#define INF INT_MAX

vector<PI> graph[MAXN];
vector<PI> AUX_graph[MAXN];
int n,dist[MAXN],parent[MAXN];
vector<int> T[MAXN];
int FCOST[MAXN],SUCCESSOR[MAXN];
#include "DijkstraSINGLE.cpp"
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
    //construct expanded Graph
    start_time=clock();
    int N=(S+2)*n;
    FORE(i,1,N)AUX_graph[i].clear();
    FORE(k,0,S)
    {
        FORE(j,1,n)
        {
            EACH(it,graph[j])
            {
                if(VFIND(T[k+1],it->first))
                {
                    AUX_graph[j+k*n].PB(PI((it->first)+(k+1)*n,it->second));
                }
                else
                {
                    AUX_graph[j+k*n].PB(PI((it->first)+(k)*n,it->second));
                }
            }
        }
    }
    int ans=Dijkstra(1,N,N,AUX_graph);
    vector<int> vi;
    int P=N;
    if(parent[P]==-1)vi.PB(-1);
    else
    {
        vi.PB(P);
        while(P!=(1))
        {
            vi.PB(parent[P]);
            P=parent[P];
        }
    }
    reverse(ALL(vi));
    EACH(it,vi)
    {
        *it=(*it)%n;
        if((*it)==0)*it=n;
    }
    end_time=clock();
    EACH(it,vi)cout<<*it<<"->";
    cout<<"<-\n";
    cout<<"cost="<<ans;
    total_time=total_time+(end_time-start_time);
    printf("\n\nTIME TAKEN =%f SECONDS\n\n\n\n",((float)(total_time))/CLOCKS_PER_SEC);
    return 0;
}
