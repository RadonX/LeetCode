//dynamic programming

// best way to (i,j), either from left or down
f[i][j] = 
max(f[i][j],
    max(
        //from down
        f[i+k][j], //not exactly
        //from left
        f[i][j-1], 
        g[i][j-1]
    ) + v[i][j]  
); 
//make v[i][j]: -1 -> -inf, 
// so that unreachable cell has v = -inf

// best way to (i,j), either from left or up
g[i][j] = max(
    g[i-1][j], 
    f[i][j-1], 
    g[i][j-1]
) + v[i][j]; 

// special case: 

f[n-1][j] = max(
    //from left
    f[n-1][j-1], 
    g[n-1][j-1],
    //teleport from top
    min(0, f[0][j])
);

g[0][j] = max(
    //from left
    f[0][j-1],
    g[0][j-1],
    //teleport from bottom
    min(0, g[n-1][j])
);


// init

// mark all cells as unreachable
f = -inf;
g = -inf;

// make an auxiliary column, column 0
f[i][0] = 0
g[i][0] = 0

// notice that within a column, there can be a loop,
// 1->...->n-1->0->1. how to update f, g?

for (k = 0; k < n; k++){
    //start from row k at current column j
    //i.e. (k,j-1)->(k,j)

    //down to up
    f1[k] = max(f[k][j-1],g[k][j-1])+v[k][j]; // temporary array
    if (f1[k] >= 0){ //reachable from (k,j-1)
        for(i = k - 1; i >= 0; i--){
            f1[i] = f1[i+1]+v[i][j];
        }
        f1[n-1] = min(0, f1[0]);
        for (i = n - 1; i > k; i--){ 
        // not really necessary to do this iterations for every k
        // just once 
            f1[i] = f1[i+1]+v[i][j];    
        }
        for (i = 0; i < n; i++){
            f[i][j] = max(f[i][j],f1[i]); // update f[i][j]
        }
    }

    g[k][j] = max(f[k][j-1],g[k][j-1])+v[k][j];
}

