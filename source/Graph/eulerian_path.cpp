/*
Usage:
- dfs(u, p): dfs, what the fuck
- Return the order of edge you enter (in reverse)
*/

vector<int> ans;
void find_eulerian_path(int u){
    while(graph[u].size()){
        pair<int, int> v = graph[u].back(); graph[u].pop_back();
        if (used[v.second]) continue;
        used[v.second] = true;
        find_eulerian_path(v.first);
        ans.push_back(v.first);
    }
}
 