#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

struct division_result {
    string quotient;
    string remainder;
};

string add(string x, string y) {
    string ans = "";
    int m = x.size(), n = y.size(), carry = 0;
    for (int i = m - 1, j = n - 1; i >= 0 || j >= 0 || carry; i--, j--) {
        int a = i >= 0 ? x[i] - '0' : 0;
        int b = j >= 0 ? y[j] - '0' : 0;
        int sum = a ^ b ^ carry;
        carry = (a & b) | (a & carry) | (b & carry);
        ans = to_string(sum) + ans;
    }
    return ans;
}

string subtract(string x, string y) {
    int m = x.size(), n = y.size(), carry = 0, i, j;
    assert(m >= n && x.compare(y) >= 0);
    string ans = "";
    for (i = m - 1, j = n - 1; i >= 0 || j >= 0; i--, j--) {
        int a = x[i] - '0';
        int b = j >= 0 ? y[j] - '0' : 0;
        int sub = a - b - carry;
        if (sub < 0) {
            sub += 2;
            carry = 1;
        } else {
            carry = 0;
        }
        ans += to_string(sub);
    }
    reverse(ans.begin(), ans.end());
    ans.erase(0, min(ans.find_first_not_of('0'), ans.size() - 1));
    return ans;
}

string multiply_naive(string x, string y) {
    string ans = "0", shift = x;
    int n = y.size();
    for (int i = n - 1; i >= 0; i--) {
        if (y[i] - '0') {
            ans = add(ans, shift);
        }
        shift += "0";
    }
    return ans;
}

string multiply(string x, string y) {
    if (y.empty() || y == "0") {
        return "0";
    }
    int n = y.size();
    string z = multiply(x, y.substr(0, n - 1));
    if (y[n - 1] - '0') {
        return add(x, z + "0");
    }
    return z + "0";
}

division_result divide(string x, string y) {
    assert(y.compare("0") == 1);
    division_result ans;
    if (x.empty() || x == "0") {
        ans.quotient = "0";
        ans.remainder = "0";
    } else {
        int m = x.size(), n = y.size();
        division_result temp = divide(x.substr(0, m - 1), y);
        if (temp.quotient.compare("0") == 1) {
            temp.quotient += "0";
        }
        if (temp.remainder.compare("0") == 1) {
            temp.remainder += "0";
        }
        if (x[m - 1] - '0') {
            temp.remainder = add(temp.remainder, "1");
        }
        int rs = temp.remainder.size();
        if (rs >= n && temp.remainder.compare(y) >= 0) {
            temp.remainder = subtract(temp.remainder, y);
            temp.quotient = add(temp.quotient, "1");
        }
        ans.quotient = temp.quotient;
        ans.remainder = temp.remainder;
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    string x = "110101", y = "100011", ans;
    ans = add(x, y);
    cout << "Add: " << x << " + " << y << " = " << ans << endl;
    ans = subtract(x, y);
    cout << "Subtract: " << x << " - " << y << " = " << ans << endl;
    x = "1101";
    y = "1011";
    ans = multiply_naive(x, y);
    cout << "Naive multiply: " << x << " * " << y << " = " << ans << endl;
    ans = multiply(x, y);
    cout << "Multiply: " << x << " * " << y << " = " << ans << endl;
    x = "1111111";
    y = "101";
    division_result dr = divide(x, y);
    cout << "Divide: " << x << " / " << y << " = " << dr.quotient << " ... " << dr.remainder << endl;
    return 0;
}

// Add: 110101 + 100011 = 1011000
// Subtract: 110101 - 100011 = 10010
// Naive multiply: 1101 * 1011 = 10001111
// Multiply: 1101 * 1011 = 10001111
// Divide: 1111111 / 101 = 11001 ... 10
