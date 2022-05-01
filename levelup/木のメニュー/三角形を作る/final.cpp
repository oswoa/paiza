/*
paiza 君と erik 君は、1 〜 N 番の頂点からなる、任意の連続する 3 頂点が一直線上に並んでいない木が書かれた紙を使って、次のような遊びを思いつきました。

木の中で連続して繋がっている 3 つの頂点の端の 2 つの頂点を結び、元々木に含まれる 2 辺と合わせて三角形を作る。
交互に三角形を作っていき、先に三角形を作れなくなった方の負け！

2 人は paiza 君が先攻、 erik 君が後攻でこのゲームを遊ぶことにしました。
用意した木についての情報が与えられるので、両者が最適な戦略を取ったときどちらが勝利するかを判定してください。
https://paiza.jp/works/mondai/tree_primer/tree_primer__make_triangles
*/

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

size_t nCr(const int &node, const int &num) {

    if (node < num)
        return 0;

    size_t nPr = 1;
    for (size_t i = node, limit = num; 0 < limit; --i, --limit)
        nPr *= i;

    size_t fac = 1;
    for (size_t i = 1; i <= num; ++i)
        fac *= i;

    return nPr / fac;
}

/*
    ◆全体方針
        1. それぞれ親が持つ子の数を取得
        2. 子の数から2個の組み合わせを取得する. 2個の組み合わせの数だけ三角形を作る事が出来るため
        3. 線を引く順番は固定のため、2で取得した数が奇数であればpaiza君の勝利

*/
int main() {

    int N;
    cin >> N;

    vector<vector<int>> table(N);

    // 木の作成
    makeTree(table);

    int ans = 0;
    for (const auto &parent : table) {
        // 頂点の数を取得
        int node = size(parent);

        // nodeから2個の組み合わせを取得。
        ans += nCr(node, 2);
    }

    // 辺を作れる数が奇数であれば先行のpaiza君の勝利
    string winner;
    if (ans % 2 != 0) winner = "paiza";
    else              winner = "erik";

    cout << winner << endl;

    return 0;
}