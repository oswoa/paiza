/*
数列 A の要素数 N と値 M , 数列 A の要素 A_1, A_2, ..., A_N が与えられます。

要素の和が M 以上となるような A の部分列の最短の長さを求めてください。
そのような部分列が存在しない場合は -1 を出力してください。

なお、数列の部分列とは、数列の連続した 1 つ以上の要素を取り出して作ることができる数列のことです。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_twopointers_step3
 */
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

/* 
    ◆全体方針
    累積和を用いてM以上となる値を見つける
 */
int main() {

    int N, M;
    cin >> N >> M;

    vector<int> sumTable(N);
    int s = 0;
    for (size_t i = 0; i < size(sumTable); ++i) {
        int tmp;
        cin >> tmp;
        s += tmp;
        sumTable[i] = s;
    }

    size_t ans = INT_MAX;
    for (size_t i = 0; i < size(sumTable); ++i) {
        int diffSum = 0;
        if (0 < i)
            diffSum = sumTable[i - 1];

        for (size_t j = i; j < size(sumTable); ++j) {
            if (M <= sumTable[j] - diffSum) {
                ans = min(ans, j - i + 1);
                break;
            }
        }
    }

    if (ans == INT_MAX)
        cout << "-1" << endl;
    else
        cout << ans << endl;

    return 0;
}