/*
頂点に 1 〜 N の番号がついた木の頂点・辺についての情報が与えられるので、木の中心である頂点の番号を昇順に改行区切りで出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__center_of_tree
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void makeTree(vector<vector<int>> &table) {

    // リストの作成
    for (size_t i = 0; i < size(table) - 1; ++i) {
        int a_1;
        int b_1;
        cin >> a_1 >> b_1;

        // インデックスに修正する
        --a_1;
        --b_1;

        table[a_1].push_back(b_1);
        table[b_1].push_back(a_1);
    }
}

bool delLeaves(vector<vector<int>> &table) {

    bool flgDelete = false;

    for (auto itr = table.begin(); itr != table.end(); ++itr) {

        // 接続してる数が1つなら葉
        if (size(*itr) != 1) continue;

        // 子のnodeを取得
        int node = (*itr)[0];

        // 木全体を対象に、取得したnodeを子に持つ場合、そのnodeを削除する
        for (size_t i = 0; i < size(table); ++i) {
            auto tmp = find(table[i].begin(), table[i].end(), node);
            if (tmp != table[i].end())
                table[i].erase(tmp);
        }

        // 葉のnodeを削除する
        (*itr).clear();
        if (!flgDelete) flgDelete = true;
    }

    return flgDelete;
}

int main() {

    int N;
    cin >> N;

    vector<vector<int>> table(N);

    // 木の作成
    makeTree(table);

    // 葉の削除
    while (!delLeaves(table));

    // 木の中心を出力
    for (size_t i = 0; i < size(table); ++i) {
        if (size(table[i]) != 0) cout << i + 1 << endl;
    }

    return 0;
}