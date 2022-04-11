/*
数列 A についての情報と、整数 K が与えられます。
次の条件を満たす A の部分列の最短の長さを答えてください。

・ 数列に含まれる全ての要素の積が K 以上である。

なお、数列の部分列とは、数列の連続した 1 つ以上の要素を取り出して作ることができる数列のことです。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_twopointers_boss
 */
#include <iostream>
#include <vector>
using namespace std;

/*
    ◆全体方針
        しゃくとり法で実装する
*/
int main() {

    size_t N, K;
    cin >> N >> K;

    // データを入力
    vector<size_t> table(N);
    for (size_t i = 0; i < size(table); i++)
        cin >> table[i];

    size_t ans = size(table) + 1; // 最短長を入れる変数。要素数を超える値で初期化しておく
    size_t sum = 1;               // 累積
    size_t right = 0;             // 現在の右端を示す

    // しゃくとり法で積がK以上となる最短の長さを取得する
    for (size_t left = 0; left < size(table); ++left) {

        // Kが要素数を超えない、かつK未満であれば積を計算する
        while (right < size(table) && sum < K) {
            if (table[right] == 0) break;
            sum *= table[right];
            ++right;
        }

        // leftとrightが同じ要素を指していて、かつK以上が確定しているので長さ1にする
        if (left == right)
            ++right;

        // 累積がK以上なら[left, right)の長さを答えとして保存
        if (K <= sum)
            ans = min(ans, right - left);

        // 現在の累積を左端で割り、累積から除外する
        if (table[left] != 0)
            sum /= table[left];
    }

    cout << ans << endl;

    return 0;
}