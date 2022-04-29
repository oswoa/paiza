/*
木の頂点・辺についての情報が与えられるので、この木の隣接行列を出力してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__adjacency_matrix_input
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {

    int N;
    cin >> N;

    vector<vector<int>> list(N, vector<int>(N, 0));

    // データの入力
    for (size_t i = 0; i < N - 1; ++i) {
        int parent, child;
        cin >> parent >> child;

        // インデックスに修正
        --parent;
        --child;

        list[parent][child] = 1;
        list[child][parent] = 1;
    }

    // データの出力
    for (const auto row : list) {
        for (size_t i = 0; i < size(row); ++i) {
            cout << row[i];
            if (i != size(row) - 1)
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}