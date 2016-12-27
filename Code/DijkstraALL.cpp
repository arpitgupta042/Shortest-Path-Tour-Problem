//Dijkstra function to calculate shortest distance from 'source' to all destinations in the graph
//returns the length of shortest path for a node if found else returns INF(+) for nodes which are unreachable
//assumes non-negative(>=0) edge costs.
//Assume nodes numbered from 1...N
//if numbering from 0...N-1, then change 'n+1' to 'n' in "fill(dist,dist+n+1,INF);"

void Dijkstra(int source,int n,vector<PI> graph[])
{
    fill(dist,dist+n+1,INF);
    fill(parent,parent+n+1,-1);
    dist[source]=0;
    parent[source]=source;
    set<PI> s;
    s.insert(PI(0,source));
    while(!s.empty())
    {
        PI top=*s.begin();
        s.erase(s.begin());
        EACH(it,graph[top.second])
        {
            if(dist[it->first]>(dist[top.second]+it->second))
            {
                if(dist[it->first]!=INF)s.erase(s.find(PI(dist[it->first],it->first)));
                dist[it->first]=dist[top.second]+it->second;
                s.insert(PI(dist[it->first],it->first));
                parent[it->first]=top.second;
            }
        }
    }
}
