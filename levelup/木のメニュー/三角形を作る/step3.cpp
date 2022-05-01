/*
木の頂点・辺についての情報が与えられます。
続いて、K 個の頂点の組が与えられるので、それらをつなぐ辺が存在すれば "YES"、存在しなければ "NO" を出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__edge_search
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    int N, K;
    cin >> N >> K;

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

    // リストの中身を出力
    for (size_t i = 0; i < K; ++i) {
        int qa_1;
        int qb_1;
        cin >> qa_1 >> qb_1;

        // インデックスに修正する
        --qa_1;
        --qb_1;

        const auto *v = &table[qa_1];
        if (find(v->begin(), v->end(), qb_1) != v->end())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}