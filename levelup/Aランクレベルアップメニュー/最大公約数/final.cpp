/*
整数 A , B が与えられるので、 A と B の最大公約数を出力してください。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_calculation_boss
*/
#include <iostream>
using namespace std;

/*
    ◆全体方針
        ユークリッドの互除法を用いて実装する
*/

size_t gcd(size_t x, size_t y) {

    size_t mod = 1;

    while (mod != 0) {
        mod = x % y;
        x = y;
        y = mod;
    }

    return x;
}

int main() {

    size_t A, B;
    cin >> A >> B;

    cout << gcd(A, B) << endl;

    return 0;
}