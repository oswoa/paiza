/*
木の頂点・辺についての情報が与えられるので、この木の隣接リストを出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__adjacency_list_input
*/

#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {

    int N;
    cin >> N;

    vector<set<int>> table(N);

    // リストの作成
    for (size_t i = 0; i < N - 1; ++i) {
        int a_1;
        int b_1;
        cin >> a_1 >> b_1;

        // インデックスに修正する
        --a_1;
        --b_1;

        table[a_1].insert(b_1);
        table[b_1].insert(a_1);
    }

    // リストの中身を出力
    for (size_t i = 0; i < size(table); ++i) {
        for (auto itr = table[i].cbegin(); itr != table[i].cend(); ++itr) {
            cout << *itr + 1;
            if (next(itr) != table[i].cend())
                cout << " ";
        }

        cout << endl;
    }

    return 0;
}