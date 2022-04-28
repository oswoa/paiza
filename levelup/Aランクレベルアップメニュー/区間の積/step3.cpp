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

/*
    ◆全体方針
    しゃくとり法を用いてM以上となる値を見つける

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    uint32_t N, M;
    cin >> N >> M;

    vector<uint32_t> v(N, 0);
    for (size_t i = 0; i < N; ++i)
        cin >> v[i];

    int ans = size(v) + 1; // 取り得ない値を格納しておく
    size_t sum = 0;        // 合計値格納用
    size_t right = 0;      // 右端制御用

    for (size_t left = 0; left < size(v); ++left) {

        // M を超えるまで加算する
        while (right < size(v) && sum < M) {
            sum += v[right];
            ++right;
        }

        // M以上になったところで長さを取得
        if (M <= sum)
            ans = min(static_cast<size_t>(ans), right - left);

        // 現在の合計からleftの値を引き、加算する範囲をずらす
        sum -= v[left];
    }

    if (ans == size(v) + 1)
        ans = -1;

    // 答えを出力
    cout << ans << endl;

    return 0;
}
*/