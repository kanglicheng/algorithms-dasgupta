#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int fib1(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    vector<int> ans(n + 1, 0);
    ans[1] = 1;
    for (int i = 2; i <= n; i++) {
        ans[i] = ans[i - 1] + ans[i - 2];
    }
    return ans[n];
}

int main(int argc, const char * argv[]) {
    clock_t start, end;
    int n = 40, ans;
    start = clock();
    ans = fib1(n);
    end = clock();
    cout << "fib1(" << n << ") = " << ans << ", time to compute: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    start = clock();
    ans = fib2(n);
    end = clock();
    cout << "fib2(" << n << ") = " << ans << ", time to compute: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

// fib1(40) = 102334155, time to compute: 0.701892s
// fib2(40) = 102334155, time to compute: 3e-06s

