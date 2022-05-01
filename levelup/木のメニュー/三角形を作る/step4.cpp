/*
頂点に 1 〜 N の番号がついた木の頂点・辺についての情報が与えられるので、葉である全ての頂点の番号を昇順に改行区切りで出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__find_leaf
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    int N;
    cin >> N;

    vector<vector<int>> table(N);

    // リストの作成
    for (size_t i = 0; i < N - 1; ++i) {
        int a_1;
        int b_1;
        cin >> a_1 >> b_1;

        // インデックスに修正する
        --a_1;
        --b_1;

        table[a_1].push_back(b_1);
        table[b_1].push_back(a_1);
    }

    // 葉のnodeを昇順に出力(格納する時点で親が昇順になっているためソートの必要はない)
    for (size_t i = 0; i < size(table); ++i) {
        // 子供のベクトルを持った親を取得
        const auto &parent = table[i];

        // 子供の数が1であれば葉
        if (size(parent) == 1)
            cout << i + 1 << endl;
    }

    return 0;
}