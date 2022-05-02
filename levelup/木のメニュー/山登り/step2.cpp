/*
根付き木の頂点・辺についての情報と K 個の頂点が与えられるので、与えられた各頂点の親の頂点番号を全て昇順で出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__rooted_tree_parent
*/
#include <iostream>
#include <set>
#include <vector>
using namespace std;

void makeTree(vector<set<int>> &table) {

    // リストの作成
    for (size_t i = 0; i < size(table) - 1; ++i) {
        int a_1;
        int b_1;
        cin >> a_1 >> b_1;

        // インデックスに修正する
        --a_1;
        --b_1;

        // 親に子供を持たせる
        table[a_1].insert(b_1);
    }
}

bool searchParent(const vector<set<int>> &table, const int &i, const int &child) {

    // 指定した親の子供一覧を取得し、指定した子供を持っているか確認
    const auto &parent = table[i];
    return parent.find(child) != parent.end();
}

int main() {

    int N, K, R;
    cin >> N >> K >> R;

    vector<set<int>> table(N);
    makeTree(table);

    for (size_t i = 0; i < K; ++i) {
        int child;
        cin >> child;

        // インデックスに修正
        --child;

        // 空白を表示するかを決定するフラグ
        bool flgSpace = false;

        for (size_t i = 0; i < size(table); ++i) {
            // インデックスiが指すコンテナの中にchildがいるか確認
            if (searchParent(table, i, child)) {
                if (!flgSpace) flgSpace = true;
                else           cout << " ";
                cout << i + 1;
            }
        }
        cout << endl;
    }

    return 0;
}