// Adarsh Jha
// lowest < current < greatest
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define endl "\n"
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
#define repn(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define rep(n) repn(i, 0, n)
#define pb push_back
#define ALL(v) v.begin(), v.end()
#define sz(x) ((int)(x).size())

ll mod_mul(ll a, ll b, ll MOD) {
    return (a % MOD * b % MOD) % MOD;
}

ll mod_sub(ll a, ll b, ll MOD) {
    return (a - b + MOD) % MOD;
}

ll binpow(ll a, ll b, ll MOD) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll mminvprime(ll a, ll MOD) {
    return binpow(a, MOD - 2, MOD);
}

struct Hashing {
    string s;
    int n;
    int primes;
    vector<ll> hashPrimes = {1000000009, 100000007};
    const ll base = 31;
    vector<vector<ll>> hashValues;
    vector<vector<ll>> powersOfBase;
    vector<vector<ll>> inversePowersOfBase;

    Hashing(string a) {
        primes = sz(hashPrimes);
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length(); 

        for (int i = 0; i < primes; i++) {
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            powersOfBase[i][0] = 1;
            for (int j = 1; j <= n; j++) {
                powersOfBase[i][j] = (base * powersOfBase[i][j - 1]) % hashPrimes[i];
            }
            inversePowersOfBase[i][n] = mminvprime(powersOfBase[i][n], hashPrimes[i]);
            for (int j = n - 1; j >= 0; j--) {
                inversePowersOfBase[i][j] = mod_mul(inversePowersOfBase[i][j + 1], base, hashPrimes[i]);
            }
        }

        for (int i = 0; i < primes; i++) {
            hashValues[i].resize(n);
            for (int j = 0; j < n; j++) {
                hashValues[i][j] = ((s[j] - 'a' + 1LL) * powersOfBase[i][j]) % hashPrimes[i];
                if (j > 0) hashValues[i][j] = (hashValues[i][j] + hashValues[i][j - 1]) % hashPrimes[i];
            }
        }
    }

    vector<ll> substringHash(int l, int r) {
        vector<ll> hash(primes);
        for (int i = 0; i < primes; i++) {
            ll val1 = hashValues[i][r];
            ll val2 = l > 0 ? hashValues[i][l - 1] : 0LL;
            hash[i] = mod_mul(mod_sub(val1, val2, hashPrimes[i]), inversePowersOfBase[i][l], hashPrimes[i]);
        }
        return hash;
    }
};

//MATH FUNCTIONS

// int modAdd(int a, int b, int mod) { return (a + b) % mod; } 
// int modSubtract(int a, int b, int mod) { return (a - b + mod) % mod; } 
// int modMultiply(int a, int b, int mod) { return (a * b) % mod; } 
// int modExponentiation(int a, int b, int mod) { int result = 1; a = a % mod; while (b > 0) { if (b % 2 == 1) result = (result * a) % mod; b = b / 2; a = (a * a) % mod; } return result; } 
// int modInverse(int a, int mod) { int m0 = mod, t, q, x0 = 0, x1 = 1; if (mod == 1) return 0; while (a > 1) { q = a / mod; t = mod; mod = a % mod; a = t; t = x0; x0 = x1 - q * x0; x1 = t; } if (x1 < 0) x1 += m0; return x1; } 
// int modDivide(int a, int b, int mod) { int inv_b = modInverse(b, mod); if (inv_b == -1) { cout << "Modular inverse doesn't exist!" << endl; return -1; } return modMultiply(a, inv_b, mod); } 

/*REMOVE LEADING ZEROES
size_t pos = result.find_first_not_of('0');
result = (pos == std::string::npos) ? "0" : result.substr(pos);
*/
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;  //you can use less/greater/less_equal/greater_equal instead of less<int> as per your requirement
#define fastio() ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
void __print(long long x) { cerr << x; }void __print(unsigned x) { cerr << x; }void __print(unsigned long x) { cerr << x; }void __print(unsigned long long x) { cerr << x; }void __print(float x) { cerr << x; }void __print(double x) { cerr << x; }void __print(long double x) { cerr << x; }void __print(char x) { cerr << '\'' << x << '\''; }void __print(const char *x) { cerr << '\"' << x << '\"'; }void __print(const string &x) { cerr << '\"' << x << '\"'; }void __print(bool x) { cerr << (x ? "true" : "false"); }
template <typename A>void __print(const A &x);template <typename A, typename B>void __print(const pair<A, B> &p);template <typename... A>void __print(const tuple<A...> &t);template <typename T>void __print(stack<T> s);template <typename T>void __print(queue<T> q);template <typename T, typename... U>void __print(priority_queue<T, U...> q);template <typename A>void __print(const A &x) {    bool first = true;    cerr << '{';    for (const auto &i : x) {        cerr << (first ? "" : ","), __print(i);        first = false;    }    cerr << '}';}template <typename A, typename B>void __print(const pair<A, B> &p) {   cerr << '(';   __print(p.first);   cerr << ',';   __print(p.second);   cerr << ')';}template <typename... A>void __print(const tuple<A...> &t) {  bool first = true;  cerr << '(';    apply([&first](const auto &...args) { ((cerr << (first ? "" : ","), __print(args), first = false), ...); }, t);   cerr << ')';}template <typename T>void __print(stack<T> s) {   vector<T> debugVector;   while (!s.empty()) {        T t = s.top();        debugVector.push_back(t);        s.pop();    }    reverse(debugVector.begin(), debugVector.end());    __print(debugVector);}template <typename T>void __print(queue<T> q) {   vector<T> debugVector;   while (!q.empty()) {       T t = q.front();       debugVector.push_back(t);       q.pop();   }    __print(debugVector);}template <typename T, typename... U>void __print(priority_queue<T, U...> q) {   vector<T> debugVector;   while (!q.empty()) {       T t = q.top();      debugVector.push_back(t);      q.pop();}__print(debugVector);}void _print() { cerr << "]\n"; }template <typename Head, typename... Tail>void _print(const Head &H, const Tail &...T) {__print(H);if (sizeof...(T))    cerr << ", ";_print(T...);}
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

/**************CODE_BEGINS_HERE************************************************/

void solve()
{   
    string s,t;
    cin >> s>>t;
    int n=s.size();
    int m=t.size();
    Hashing hs1(s), hs2(t);
    vector<ll> hash1;
    vector<ll> hash2= hs2.substringHash(0, m - 1);
    int count=0;
    for (int i = 0; i <= n - m; i++) {
        hash1 = hs1.substringHash(i, i + m - 1);
        if (hash1 == hash2) {
            count++;
        }
    }
    cout << count << endl;
}

/**************CODE_ENDS_ HERE************************************************/
signed main()
{
    fastio();
   int t=1;
//    cin>>t;
   while(t--){solve();}
}

//NOTE: Unordered Map don't have pair as a key directly, you need to define a custom function to use this
