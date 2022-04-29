/*
整数 N が与えられるので、2 の N 乗を 1000003 で割った余り を求めてください。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_calculation_step2

 */
#include <iostream>
using namespace std;

constexpr int MOD = 1000003;

size_t pow(size_t x, size_t n) {

    size_t ans = 1;
    while (0 < n) {
        if (n & 0x01) ans = ans * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }

    return ans;
}

/*
    ◆全体方針
        繰り返し二乗法で実装する
*/
int main() {

    size_t N;
    cin >> N;

    cout << pow(2, N)<< endl;

    return 0;
}