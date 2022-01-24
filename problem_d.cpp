/*
 
QUESTION: 
    Given an n * m matrix filled with 0s (plots) and 1s(houses), find number of plots that are at maximum distance of k from each houses.
    (Distance here means Manhattan distance -> |x1 - x2| + |y1 - y2|)
 
CONSTRAINTS: 
    n -> 400, m -> 400, k -> 800
 
BRUTE FORCE:
    Traverse the grid and store coordinates of all 1s in the grid. Now for each 0 (plot), find max distance from any 1 (house). 
    If this distance is <= k, then add it to answer, else don't.
    Complexity -> O((n * m) ^ 2) 
    Hence TLE.
 
OPTIMIZED SOLUTION:
    Let's look at what the bottleneck is in the above approach. The bottleneck is calculation of the distance of the house that is farthest away 
    from the current plot. So we need a way to optimize this.
    To do this, let's have a closer look at the manhattan distance function.
    Let's say p1 = {x1, y1} and p2 = {x2, y2}
    Manhattan Distance(p1, p2) = |x1 - x2| + |y1 - y2|
    Now there's a simple lemma that states -> 
        |a| + |b| = max(|a + b|, |a - b|)
    You can prove it for yourself by doing casework and comparing LHS, RHS
    
    Substituting a = x1 - x2, and b = y1 - y2, we get
    Manhattan Distance(p1, p2) = 
    |x1 - x2| + |y1 - y2| = max(|x1 - x2 + y1 - y2|, |x1 - x2 - y1 + y2|) = max(|(x1 + y1) - (x2 + y2)|, |(x1 - y1) - (x2 - y2)|)
 
    Therefore, this means if we substitute the coordinates of p1 with -> {x1 + y1, x1 - y1} = {X1, Y1}, p2 with -> {x2 + y2, x2 - y2} = {X2, Y2};
 
    Now Manhattan Distance(p1, p2) = max(|X1 - Y1|, |X2 - Y2|) !!!!
    So to get Manhattan Distance between two points, we can just substitute {x, y} -> {x + y, x - y} and use the above formula instead.
    
    This is the crux of the solution. Now that we know how to calculate Manhattan Distance using this alternate formula, let's see how this helps us.
 
    Since for every 0 (plot) we need farthest house, we make the aforementioned transformation on every house and store New_x and New_y 
    coordinates in two array say X and Y.
    X -> contains (x + y) for all x, y such that grid[x][y] = 1
    y -> contains (x - y) for all x, y such that grid[x][y] = 1
 
    Now, for every plot at index i, j we need max Manhattan Distance i.e we want to maximize the value -> max(|i + j - x|, |i - j - y|)
    where x belongs to X and y belongs to Y. Notice that the two parts are sort of independent of each other and we can just calculate the max of all |i + j - x| 
    and max of all |i - j - y| and then finally take their maximum.
    Notice that now this is very easy to get. We can just sort the X and Y arrays. Now for the first part, the max absolute value will either be using x = X[0] or using
    x = X[X.size() - 1] as they are the extreme ends (Convince yourself of this, it's obvious). Similarly for y. Finally we can take the max of these both.
 
    Finally if the value you get is <= k, you can add it to the answer. Else don't.
 
    Time Complexity -> 
        Store all 1s -> O(n * m)
        Sort X -> O((n * m) * log(n * m))
        Sort Y -> O((n * m) * log(n * m))
        Iterate over each 0 -> O(n * m)
        Get max distance to 1 -> O(1)
 
        Therefore final time complexity -> O((n * m) * log(n * m))
*/
 
 
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define M (ll)1e9 + 7
 
ll n, m, k;
vector<ll> X;  // to store transformed x for all ones
vector<ll> Y;  // to store transformed y for all ones
vector<pair<ll, ll>> ones;  // to store {i, j} for all ones for brute force
 
ll grid[400][400];  // to take input
 
 
// Uses brute force method to solve, implemented to check correctness of optimized method
pair<vector<vector<ll>>, ll> brute(){
    ll ans = 0;
    vector<vector<ll>> res(n, vector<ll> (m, 0));
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            res[i][j] = grid[i][j];
            if(grid[i][j] == 0){
                ll mx = 0;
                for(auto p: ones){
                    mx = max(mx, abs(i - p.first) + abs(j - p.second));
                }
                if(mx <= k){
                    // making all 0s that are answers 2 to help visualize and verify just in case
                    res[i][j] = 2;
                    ans++;
                }
            }
        }
    }
 
    return {res, ans};
}
 
pair<vector<vector<ll>>, ll> optimized(){
    ll ans = 0;
    vector<vector<ll>> res(n, vector<ll> (m, 0));
 
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
 
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            res[i][j] = grid[i][j];
            if(grid[i][j] == 0){
                ll x = i + j;
                ll y = i - j;
                ll temp = max({abs(x - X[0]), abs(x - X.back()), abs(y - Y[0]), abs(y - Y.back())});
                if(temp <= k) {
                    // making all 0s that are answers 2 to help visualize and verify just in case
                    res[i][j] = 2;
                    ans++;
                }
            }
        }
    }
 
    return {res, ans};
}
 
void solve(){
    cin >> n >> m >> k;
    X.clear();
    Y.clear();
    ones.clear();
    for(ll i =0 ;i < n; i++){
        for(ll j = 0; j < m; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 1){
                ones.push_back({i, j});
 
                // storing transformed coordinates for 1s in X and Y
                X.push_back(i + j);
                Y.push_back(i - j);
            }
        }
    }
 
    pair<vector<vector<ll>>, ll> t1;
    pair<vector<vector<ll>>, ll> t2;
 
    // answer from brute force method
    t1 = brute();
 
    // answer from optimized method
    t2 = optimized();
 
    if(t1.second != t2.second){
        cout << "WRONG ANSWER\n";
        return;
    }
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            if(t1.first[i][j] != t2.first[i][j]){
                cout << "WRONG ANSWER\n";
                return;
            }
        }
    }
 
    cout << "PASSED" << endl;
 
    // cout << t2.second << endl;
    // for(ll i =0 ; i < n; i++){
    //     for(ll j = 0;j < m; j++){
    //         cout << t2.first[i][j] << " ";
    //     }
    //     cout << endl;
    // }
 
}
 
int main(){
    fastio
    ll t;
    cin >> t;
    while(t--){
        solve();
    }
}