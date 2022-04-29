/*
整数 N が与えられるので、N が素数の場合は "YES" , そうでない場合は "NO" を出力してください。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_calculation_step3
*/
#include <iostream>
using namespace std;

int main() {

    int N;
    cin >> N;

    string ans = "YES";

    if (N == 1) {
        ans = "NO";
        cout << ans << endl;
        return 0;
    }

    // √N 以下で割り切れるものがあるか確認
    for (size_t i = 2; i * i < N; ++i) {
        if (N % i == 0) {
            ans = "NO";
            break;
        }
    }

    cout << ans << endl;

    return 0;
}