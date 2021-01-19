#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef long long ll;
typedef long double ld;
std::vector <ll> a;
using namespace std;

bool comp(ll a, ll b){
    return a > b;
}

int main(){
    int n;
    cin >> n;
    ld max = -1;
    ld sum = 0;
    for (int i = 0; i < n; ++i){
        ll num;
        cin >> num;
        if (num > max) max = num;
        sum += num;
        a.push_back(num);
    }
    sum /= 2;
    if (sum < max){
        cout << "no\n";
        return 0;
    }
    sort(a.begin(), a.end(), comp);
    vector<ll> c;
    vector<vector<ll>> ans;
    ll s = 0;
    for (int i = 0; i < n; ++i){
        if (s + a[i] < sum){
            c.push_back(a[i]);
            s += a[i];
        } else{
            if (c.size() == 0){
                cout << "no\n";
                cout << a[i];
                return 0;
            }
            cout << c.size() << endl;
            ans.push_back(c);
            c = {a[i]};
            s = a[i];
        }
    }
    cout << ans.size() << "\n";
    // Идем с конца и кладем максимальное количество чисел в отдельный массив, сумма которых меньше sum. Можно изначально взять префикс суммы или почитать условие про порядок чисел
    return 0;
}
