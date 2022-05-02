/*
根付き木の頂点・辺についての情報と K 個の頂点が与えられるので、与えられた各頂点の子の頂点番号を昇順で全て出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__rooted_tree_child
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

void dispChildList(const set<int> &childList) {

    // setは[]演算子をもっていないため、イテレータを使ってアクセスする
    auto itr = childList.begin();

    for (size_t i = 0; i < size(childList); ++i) {
        // インデックスを1から始まる番号に修正してから表示
        cout << *itr + 1;

        if (i != size(childList) - 1)
            cout << " ";
        else
            break;
            
        ++itr;
    }
    cout << endl;
}

int main() {

    int N, K, R;
    cin >> N >> K >> R;

    vector<set<int>> table(N);
    makeTree(table);

    for (size_t i = 0; i < K; ++i) {
        int parent;
        cin >> parent;

        // インデックスに修正
        --parent;

        // parentが持つ子供一覧を取得
        const auto &childList = table[parent];
        if (childList.empty()) {
            cout << endl;
            continue;
        }

        // 子供一覧を表示
        dispChildList(childList);
    }

    return 0;
}