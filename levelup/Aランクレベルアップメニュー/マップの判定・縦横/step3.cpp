/*
行数 H , 列数 W の盤面があり、盤面の各マスには文字が 1 つだけ書かれています。
盤面が与えられるので、「左右のマスが "#" 」であるようなマスの座標を全て出力してください。
ただし、左端のマスの場合は「右のマスが "#" 」であれば、右端のマスの場合は「左のマスが "#" 」であれば条件を満たすものとします。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_map_step3
 */

#include <iostream>
#include <vector>
using namespace std;

constexpr const char MARK = '#';
constexpr const int numAddedLayer = 2; // 外側の層を追加するため +2分 余分に確保

/*
   外側にMARKレイヤーを追加する
 */
vector<string> addLayer(const int W, const vector<string> &tmpTable) {
    vector<string> table;
    table.push_back(string(W + numAddedLayer, MARK));

    for (const auto &row : tmpTable) {
        // 左端、右端に追加する事で外側の層を作成
        string tmp;
        tmp += MARK;
        tmp += row;
        tmp += MARK;
        table.push_back(tmp);
    }
    table.push_back(string(W + numAddedLayer, MARK));

    return table;
}

/*
◆全体方針
    与えられたマップを囲うよう外側の層にMARKで囲んだ層を追加し、
    左右がMARKと一致するかの判定を、配列の場所に依らず出来るようにする
 */
int main() {

    int H, W;
    cin >> H >> W;

    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    vector<string> table = addLayer(W, tmpTable);

    // 行/列はnumAddedLayerが追加されているので、本来マップが持つ範囲内で評価する
    for (size_t i = 1; i < H + numAddedLayer - 1; ++i) {
        for (size_t j = 1; j < W + numAddedLayer - 1; ++j) {
            if (table[i][j - 1] != MARK || table[i][j + 1] != MARK)
                continue;

            // 本来のインデックスにするため、それぞれを-1する
            cout << i - 1 << " " << j - 1 << endl;
        }
    }

    return 0;
}