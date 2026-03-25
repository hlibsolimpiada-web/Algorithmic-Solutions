#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXNODES = 45000000;
struct Node {
    int left, right, cnt;
} pool[MAXNODES];

int pool_top = 1;

int seg_insert(int node, int lo, int hi, int pos) {
    int cur = pool_top++;
    pool[cur].cnt = (node ? pool[node].cnt : 0) + 1;
    if (hi - lo == 1) {
        pool[cur].left = pool[cur].right = 0;
        return cur;
    }
    int mid = lo + (hi - lo) / 2;
    int L = node ? pool[node].left : 0;
    int R = node ? pool[node].right : 0;
    if (pos < mid) {
        pool[cur].left = seg_insert(L, lo, mid, pos);
        pool[cur].right = R;
    } else {
        pool[cur].left = L;
        pool[cur].right = seg_insert(R, mid, hi, pos);
    }
    return cur;
}

int seg_merge(int a, int b, int lo, int hi) {
    if (!a) return b;
    if (!b) return a;
    int cur = pool_top++;
    pool[cur].cnt = pool[a].cnt + pool[b].cnt;
    if (hi - lo == 1) {
        pool[cur].left = pool[cur].right = 0;
        return cur;
    }
    int mid = lo + (hi - lo) / 2;
    pool[cur].left = seg_merge(pool[a].left, pool[b].left, lo, mid);
    pool[cur].right = seg_merge(pool[a].right, pool[b].right, mid, hi);
    return cur;
}

int seg_kth(int node, int lo, int hi, int k) {
    if (hi - lo == 1) return lo;
    int mid = lo + (hi - lo) / 2;
    int left_cnt = pool[node].left ? pool[pool[node].left].cnt : 0;
    if (k <= left_cnt)
        return seg_kth(pool[node].left, lo, mid, k);
    else
        return seg_kth(pool[node].right, mid, hi, k - left_cnt);
}

int par[500005], sz[500005];
int seg_root[500005];

int find(int v) {
    while (par[v] != v) v = par[v];
    return v;
}

struct HistEntry {
    int v, old_sz, root_u, old_root_u_seg;
};
vector<HistEntry> hist;

struct Query {
    int type, a, b;
};

Query queries[500005];
int ans[500005];
vector<int> children[500005]; 
int N;

void dfs(int u) {
    int old_pool = pool_top;
    bool united = false;
    
    if (queries[u].type == 1) {
        int v = queries[u].a;
        int k = queries[u].b;
        int root = find(v);
        if (k > sz[root]) {
            ans[u] = -1;
        } else {
            ans[u] = seg_kth(seg_root[root], 0, N, k) + 1;
        }
    } else if (queries[u].type == 2) {
        int ru = find(queries[u].a);
        int rv = find(queries[u].b);
        if (ru != rv) {
            if (sz[ru] < sz[rv]) swap(ru, rv);
            hist.push_back({rv, sz[ru], ru, seg_root[ru]});
            par[rv] = ru;
            sz[ru] += sz[rv];
            seg_root[ru] = seg_merge(seg_root[ru], seg_root[rv], 0, N);
            united = true;
        }
    }

    for (int v : children[u]) {
        dfs(v);
    }

    if (united) {
        auto h = hist.back();
        hist.pop_back();
        par[h.v] = h.v;
        sz[h.root_u] = h.old_sz;
        seg_root[h.root_u] = h.old_root_u_seg;
    }
    pool_top = old_pool; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q, G;
    if (!(cin >> N >> Q >> G)) return 0;

    for (int i = 0; i < N; i++) {
        par[i] = i;
        sz[i] = 1;
        seg_root[i] = seg_insert(0, 0, N, i);
    }

    queries[0] = {0, 0, 0};
    for (int i = 1; i <= Q; i++) {
        cin >> queries[i].type;
        if (queries[i].type == 1) {
            cin >> queries[i].a >> queries[i].b;
            queries[i].a--; 
            children[i - 1].push_back(i);
        } else if (queries[i].type == 2) {
            cin >> queries[i].a >> queries[i].b;
            queries[i].a--; queries[i].b--;
            children[i - 1].push_back(i);
        } else {
            cin >> queries[i].a;
            children[queries[i].a].push_back(i);
        }
    }

    dfs(0);

    for (int i = 1; i <= Q; i++) {
        if (queries[i].type == 1) {
            cout << ans[i] << "\n";
        }
    }

    return 0;
}