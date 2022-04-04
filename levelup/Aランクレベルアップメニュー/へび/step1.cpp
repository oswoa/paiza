/*
マップの行数 H と列数 W , 障害物を '#' で、移動可能な場所を '.' で表した H 行 W 列のマップ S_1 ... S_H が与えられます。
続けて現在の座標 sy , sx ,１マス移動する方角 m が与えられるので、移動が可能かどうかを判定してください。

移動が可能であるということは、以下の図の通り
「移動先が障害物でない　かつ　移動先がマップの範囲外でない」
ということを意味します。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_mapmove_step1
 */

#include <iostream>
#include <vector>
using namespace std;

constexpr const char WALL = '#';

/*
   外側にWALLレイヤーを追加する
 */
vector<string> addLayer(const int &W, const vector<string> &tmpTable) {

    constexpr const int NUM_ADD_LAYER = 2;
    vector<string> table;

    table.push_back(string(W + NUM_ADD_LAYER, WALL));
    for (const auto &row : tmpTable) {
        // 左端、右端に追加する事で外側の層を作成
        string tmp;
        tmp += WALL;
        tmp += row;
        tmp += WALL;
        table.push_back(tmp);
    }
    table.push_back(string(W + NUM_ADD_LAYER, WALL));

    return table;
}

bool canMove(const vector<string> &table, const pair<int, int> &point, const char &d) {

    constexpr const char NORTH = 'N';
    constexpr const char SOUTH = 'S';
    constexpr const char EAST = 'E';
    constexpr const char WEST = 'W';

    const auto &[y, x] = point;
    int diffY = 0;
    int diffX = 0;

    if (d == NORTH) --diffY;
    else if (d == SOUTH) ++diffY;
    else if (d == EAST) ++diffX;
    else if (d == WEST) --diffX;

    return (table[y + diffY][x + diffX] == WALL) ? false : true;
}

/*
◆全体方針
    与えられたマップを囲うよう外側の層にWALLで囲んだ層を追加し、
    障害物の判定、マップの範囲外判定を配列の場所に依らず同じロジックで出来るようにする
 */
int main() {

    int H, W, sy, sx;
    char m;
    cin >> H >> W >> sy >> sx >> m;

    
    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    vector<string> table = addLayer(W, tmpTable);
    // 層を追加したのでy, xそれぞれをインクリメントしておく
    pair<int, int> point{++sy, ++sx};

    if (canMove(table, point, m))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}