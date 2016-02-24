// from: https://leetcode.com/discuss/75139/clean-beats-submissions-using-union-rank-path-compression
// problem: https://leetcode.com/problems/number-of-islands-ii

class Node{
    public:
        int rank;
        int x;
        int y;
        Node* parent;
        Node(int x, int y):rank(1),x(x),y(y),parent(this){}
};

Node* f(Node* n){
    if(n == n->parent) return n;
    n->parent = f(n->parent);
    return n->parent;
}

Node* u(Node* m, Node* n, int& res){
    Node* p_m = f(m);
    Node* p_n = f(n);
    if(p_m == p_n) return p_m;
    if(p_m->rank<p_n->rank){
        p_m->parent = p_n;
        res--;
        return p_n;
    }
    else{
        p_n->parent = p_m;
        if(p_m->rank == p_n->rank) p_m->rank++;
        res--;
        return p_m;
    }
}

vector<int> numIslands2(int m, int n, vector<pair<int, int> >& positions) {
    int sz = positions.size();
    vector<int> res;
    if(sz==0) return res;
    int x = 0;
    vector<vector<Node*> > nodes(m, vector<Node*>(n, NULL));
    int move[4][2] = {
        {0, -1},
        {-1, 0},
        {0, 1},
        {1, 0}
    };
    for(pair<int,int> p : positions){
        Node* temp = new Node(p.first,p.second);
        nodes[p.first][p.second] = temp;
        x++;
        for(int i=0; i<4; i++){
            int new_x = p.first+move[i][0];
            int new_y = p.second+move[i][1];
            if(new_x<0 || new_x>=m || new_y<0 || new_y>=n) continue;
            if(nodes[new_x][new_y] == NULL) continue;
            temp = u(temp, nodes[new_x][new_y], x);
        }
        res.push_back(x);
    }
    return res;
}
