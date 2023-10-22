#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) x.begin(), x.end()
#define forn(i,a,b) for(int i = a; i < b; i++)
#define N 8

vector<int> z_function(string const& s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        while (i + z[i] < n && s[z[i]] == s[i+z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int get_z(vector<int> const& z, int i) {
    if (0 <= i && i < (int)z.size())
        return z[i];
    else
        return 0;
}

vector<pair<int, int>> repetitions;

void print(vector<vector<char>>&matrix){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

}
bool find_repetitions(string s, int shift = 0) {
    int n = s.size();
    if (n == 1)
        return false;

    int nu = n / 2;
    int nv = n - nu;
    string u = s.substr(0, nu);
    string v = s.substr(nu);
    string ru(u.rbegin(), u.rend());
    string rv(v.rbegin(), v.rend());

    find_repetitions(u, shift);
    find_repetitions(v, shift + nu);

    vector<int> z1 = z_function(ru);
    vector<int> z2 = z_function(v + '#' + u);
    vector<int> z3 = z_function(ru + '#' + rv);
    vector<int> z4 = z_function(v);

    for (int cntr = 0; cntr < n; cntr++) {
        int l, k1, k2;
        if (cntr < nu) {
            l = nu - cntr;
            k1 = get_z(z1, nu - cntr);
            k2 = get_z(z2, nv + 1 + cntr);
        } else {
            l = cntr - nu + 1;
            k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
            k2 = get_z(z4, (cntr - nu) + 1);
        }
        if (k1 + k2 >= l)
            return true;
    }
    return false;
}

vector<char> letters={'a','b','c','d','e','f','g'};
int gcd(int a, int b){
    return __gcd(abs(a),abs(b));
}

bool valid(vector<vector<char>>&matrix,int l,int r){
    for(int i = 0; i <= l; i++){
        for(int j = 0; j < N; j++){
            if(i==l && j>=r)continue;
            if(gcd(l-i,r-j) == 1){
                int mx=l-i;
                int my=r-j;
                int i1=l,j1=r;
                string s="";
                while(i1>=0 && i1<N && j1>=0 && j1<N){
                    s+=matrix[i1][j1];
                    i1-=mx;
                    j1-=my;
                }
                if(find_repetitions(s)) return 0;
            }
        }
    }
    return 1;
}

bool fill_matrix(vector<vector<char>>&matrix,int i,int j){
    if(i==N && j==0)return true;
    bool fl=false;
    for(auto x:letters){
        matrix[i][j]=x;
        // cout<<valid(matrix,i,j)<<endl;
        if(!valid(matrix,i,j)){
            continue;
        }
        int i1=i,j1=j+1;
        if(j1>=N){
            i1++;
            j1=0;
        }
        print(matrix);
        fl = fl|fill_matrix(matrix,i1,j1);
        if(fl) return fl;
    }
    return fl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<char>>matrix(N,vector<char>(N,'+'));
    cout<<fill_matrix(matrix,0,0);
}