//也可以二分搜答案並用SPFA找負環(如果|V|太大存不下)。
/* minimum mean cycle O(VE) */
struct MMC{
#define SZ(c) ((int)(c).size())
#define E 101010
#define V 1021
#define inf 1e9 /可能不夠大
#define eps 1e-6
  struct Edge{
    int v, u;
    double c;
  };
  int n, m, prv[V][V], prve[V][V], vst[V];
  Edge e[E];
  vector<int> edgeID, cycle, rho;
  double d[V][V];
  void init(int _n){
    n = _n;
    m = 0;
  }
  // WARNING: TYPE matters
  void addEdge(int vi, int ui, double ci){
    e[m++] = {vi, ui, ci};
  }
  void bellman_ford(){
    for (int i = 0; i < n; i++)
      d[0][i] = 0;
    for (int i = 0; i < n; i++){
      fill(d[i + 1], d[i + 1] + n, inf);
      for (int j = 0; j < m; j++){
        int v = e[j].v, u = e[j].u;
        if (d[i][v]<inf && d[i+1][u]>d[i][v]+e[j].c){
          d[i + 1][u] = d[i][v] + e[j].c;
          prv[i + 1][u] = v;
          prve[i + 1][u] = j;
        }
      }
    }
  }
  double solve(){
    // returns inf if no cycle, mmc otherwise
    double mmc = inf;
    int st = -1;
    bellman_ford();
    for (int i = 0; i < n; i++){
      double avg = -inf;
      for (int k = 0; k < n; k++){
        if (d[n][i] < inf - eps)
          avg = max(avg, (d[n][i] - d[k][i]) / (n - k));
        else
          avg = max(avg, inf);
      }
      if (avg < mmc)
        tie(mmc, st) = tie(avg, i);
    }
    memset(vst, 0, sizeof(vst));
    edgeID.clear();
    cycle.clear();
    rho.clear();
    for (int i = n; !vst[st]; st = prv[i--][st]){
      vst[st]++;
      edgeID.push_back(prve[i][st]);
      rho.push_back(st);
    }
    while (vst[st] != 2){
      int v = rho.back();
      rho.pop_back();
      cycle.push_back(v);
      vst[v]++;
    }
    reverse(edgeID.begin(), edgeID.end());
    edgeID.resize(SZ(cycle));
    return mmc;
  }
} mmc;
