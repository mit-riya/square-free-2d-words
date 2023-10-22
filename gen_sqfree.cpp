## GENERATES SQUARE FREE WORDS OF GIVEN LENGTH WITH THE LETTERS IN THE VECTOR 'letters'

#include<bits/stdc++.h>
#include<chrono>
using namespace std;
typedef long long ll;
#define take(a)  int a; cin>>a;
#define all(x) x.begin(), x.end()
#define forn(i,a,b) for(int i = a; i < b; i++)
#define sz(c) int((c).size())
#define vi vector <int>
#define vll vector <long long>
#define pi pair <int,int>

vector<char>letters={'i','j','f'};
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

    // find_repetitions(u, shift);
    // find_repetitions(v, shift + nu);

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
vector<vector<string>>dp(100);
vector<string> generate(int len){
    if(len==1){
        vector<string>tem;
        for(auto x:letters){
            string s="";
            s+=x;
            tem.push_back(s);
        }
        return tem;
    }
    if(dp[len].size())return dp[len];
    vector<string>a,b;
    if(len%2){
        a=generate(len/2);
        b=generate((len+1)/2);
    }
    else{
        a=generate(len/2);
        b=generate((len)/2);
    }
    for(auto x:a){
        for(auto y:b){
            string s=x+y;
            if(!find_repetitions(s)){
                dp[len].push_back(s);
            }
        }
    }
    return dp[len];
}

int main(){
    auto start = std::chrono::system_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string>v=generate(10);

    auto end = std::chrono::system_clock::now();
    auto elapsed =chrono::duration_cast<std::chrono::seconds>(end - start);
    freopen("store_ijf.txt","w",stdout);
    for(auto x:v){
        for(int i=0;i<=x.length();i++){
            if(i == x.length()){
                cout<<x<<endl;
            }
            else if(x[i]=='f' && i%2==0) break;
        }
    }
    return 0;
}
