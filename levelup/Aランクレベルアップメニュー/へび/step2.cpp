/*
マップの行数 H と列数 W , 障害物を '#' , 移動可能な場所を '.' で表した H 行 W 列のマップ S_1 ... S_H が与えられます。
続けて現在の座標 sy , sx , 現在向いている方角 d , １マス移動する方向 m が与えられるので、移動が可能かどうかを判定してください。

移動が可能であるということは、以下の図の通り
「移動先が障害物でない　かつ　移動先がマップの範囲外でない」
ということを意味します。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_mapmove_step2
 */

#include <iostream>
#include <vector>
using namespace std;

class mapTable {
public:
    mapTable(const int &sy, const int &sx, const char &d, const vector<string> &tmpTable)
        : mY(sy + 1), mX(sx + 1), mDirection(d), mTable(addLayer(tmpTable)){};
    ~mapTable() = default;

    // 指定された方角へ移動出来るか確認する
    bool canMove(const char &d);

private:
    const char WALL = '#';
    int mY;
    int mX;
    char mDirection;
    vector<string> mTable;

    // 外側にWALLレイヤーを追加する
    vector<string> addLayer(const vector<string> &tmpTable);
};

vector<string> mapTable::addLayer(const vector<string> &tmpTable) {

    constexpr const int NUM_ADD_LAYER = 2;
    const int len = size(tmpTable[0]) + NUM_ADD_LAYER;
    const string outerLayer = string(len, WALL);
    vector<string> table;

    table.push_back(outerLayer);
    for (const auto &row : tmpTable) {
        // 左端、右端に追加する事で外側の層を作成
        string tmp;
        tmp += WALL;
        tmp += row;
        tmp += WALL;
        table.push_back(tmp);
    }
    table.push_back(outerLayer);

    return table;
}

bool mapTable::canMove(const char &m) {

    constexpr const char NORTH = 'N';
    constexpr const char SOUTH = 'S';
    constexpr const char EAST = 'E';
    constexpr const char WEST = 'W';
    constexpr const char LEFT = 'L';

    int diffY = 0;
    int diffX = 0;
    int speed = 1;

    if (m == LEFT)
        speed *= -1;

    switch (mDirection) {
    case NORTH:
        diffX += speed;
        break;

    case SOUTH:
        diffX -= speed;
        break;

    case EAST:
        diffY += speed;
        break;

    case WEST:
        diffY -= speed;
        break;
    }

    return (mTable[mY + diffY][mX + diffX] != WALL) ? true : false;
}

/*
◆全体方針
    与えられたマップをWALLで囲んだ層を追加し、
    障害物の判定、マップの範囲外判定を配列の場所に依らず同じロジックで出来るようにする
 */
int main() {

    int H, W, sy, sx;
    char d, m;
    cin >> H >> W >> sy >> sx >> d >> m;

    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    mapTable table(sy, sx, d, tmpTable);
    if (table.canMove(m))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}