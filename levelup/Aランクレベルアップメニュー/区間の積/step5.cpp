/*
数列 A の要素数 N とクエリの数 M , 数列 A の要素 A_1, A_2 ... A_N が与えられます。
続けて、クエリに用いる数 l_i, u_i, a_i が与えられます。

各クエリについて次の処理を行ってください。

・ 要素番号が、l_i 以上、u_i 以下の全ての A の要素に、a_i を足す。

全てのクエリについて処理を終えた後の A の各要素を出力してください。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_twopointers_step5
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    ◆全体方針
        いもす法で実装する
    最大: 0.23 秒
*/
int main() {

    int N, M;
    cin >> N >> M;

    vector<int> valTable(N);
    for (size_t i = 0; i < size(valTable); ++i)
        cin >> valTable[i];

    vector<int> addTable(size(valTable));
    for (size_t i = 0; i < M; ++i) {
        int start, end, add;
        cin >> start >> end >> add;

        --start;
        if (0 <= start && start < size(addTable)) addTable[start] += add;
        if (0 <= end && end < size(addTable))     addTable[end]   -= add;
    }

    int tmp = 0;
    for (size_t i = 0; i < size(addTable); ++i) {
        tmp += addTable[i];
        valTable[i] += tmp;
    }

    for (const auto &v : valTable)
        cout << v << endl;

    return 0;
}

/*
// 速度比較用
int main() {

    int N, M;
    cin >> N >> M;

    vector<int> table(N);
    for (size_t i = 0; i < size(table); ++i)
        cin >> table[i];

    for (size_t i = 0; i < M; ++i) {
        int start, end, add;
        cin >> start >> end >> add;

        --start;
        --end;

        // 最大: 0.59 秒
        // for (auto j = table.begin() + start; j != table.begin() + end + 1; ++j)
        //      *j += add;
        //

        // 最大: 0.61 秒
        // transform(table.begin() + start, table.begin() + end + 1, table.begin() + start, [add](int x) {
        //      return x += add;
        // });


        // 最大: 1.30 秒
        // for (size_t j = start; j <= end; ++j)
        //      table[j] += add;

    }

    for (const auto &v : table)
        cout << v << endl;

    return 0;
}
*/