#include <iostream>
#include <set>
using namespace std;

int main() {
    int n; 
    cin >> n;

    int a[1000005], pref[1000005], cnt[1000005];
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i-1];
        cnt[a[i]]++;
        if (cnt[a[i]] == 1)
            pref[i]++;
    }
    memset(cnt, 0, sizeof cnt);
    for (int i = n; i >= 1; i--) {
        cnt[a[i]]++;
        if (cnt[a[i]] == 2) {
            ans += pref[i-1];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i] >= 3)
            ans--;
    }
    cout << ans;
}