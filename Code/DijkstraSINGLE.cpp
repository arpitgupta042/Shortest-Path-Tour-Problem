int Dijkstra(int source,int destination,int n,vector<PI> graph[])
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
        if(top.second==destination)return dist[destination];
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
    return INF;
}
