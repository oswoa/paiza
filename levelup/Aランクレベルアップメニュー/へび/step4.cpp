/*
マップの行数 H と列数 W , 障害物を '#' で移動可能な場所を '.' で表した H 行 W 列のマップ S_1 ... S_H , 現在の座標 sy, sx, 移動の回数 N が与えられます。
続けて、 N 回の移動の向き d_1 ... d_N と移動するマス数 l_1 ... l_N が与えられます。

プレイヤーははじめ北を向いています。

各移動が可能である場合、移動後の y , x 座標 を出力してください。
移動が可能でない場合(移動しきれない場合)、移動できるところまで移動した後の座標を出力した後に "Stop" を出力して、以降の移動を打ち切ってください。

各移動が可能であるということは、以下の図の通り
「今いるマスから移動先のマスまでに障害物がない　かつ　移動先がマップの範囲外でない」
ということを意味します。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_mapmove_step4
 */

#include <iostream>
#include <vector>
using namespace std;

class mapTable {
public:
    explicit mapTable(const vector<string> &tmpTable) : mTable(addLayer(tmpTable)){};
    ~mapTable() = default;
    static const char WALL = '#'; // 壁を示す文字

    // 作成したマップを返す
    const vector<string> &getTable() { return mTable; };

private:
    vector<string> mTable; // 作成したマップを保持する

    // 外側にWALLレイヤーを追加する
    vector<string> addLayer(const vector<string> &tmpTable); 
};

vector<string> mapTable::addLayer(const vector<string> &tmpTable) {

    constexpr const int    NUM_ADD_LAYER = 2;
    const           int    len           = size(tmpTable[0]) + NUM_ADD_LAYER;
    const           string outerLayer    = string(len, WALL);
    vector<string>         table;

    // 上端追加
    table.push_back(outerLayer);

    for (const auto &row : tmpTable) {
        // 左端、右端に追加する事で外側の層を作成
        string tmp;
        tmp += WALL;
        tmp += row;
        tmp += WALL;
        table.push_back(tmp);
    }

    // 下端追加
    table.push_back(outerLayer);

    return table;
}

class player {
public:
    player(const int &sy, const int &sx, mapTable table) : mY(sy + 1), mX(sx + 1), mDirection(NORTH), mTable(table) {};
    ~player() = default;

    // マップにWALL層を追加してるので、現在位置は-1して返す
    pair<int, int> getCurrentPosition() { return {mY - 1, mX - 1}; }

    // 指定された方角へ移動する
    bool move(const char &d, int distance);

private:
    int mY;          // 現在のy座標 マップにWALL層を追加してるので、現在位置は+1されている
    int mX;          // 現在のx座標 マップにWALL層を追加してるので、現在位置は+1されている
    int mDirection;  // プレイヤーが現在向いてる方角(デフォルトは北)
    mapTable mTable; // 作成したマップオブジェクト

    const char LEFT = 'L';
    enum {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        END_OF_DIRECTION,
    };

    // マップ上における実際の座標を設定する
    void setRealCurrentPosition(const int &y, const int &x) {
        mY = y;
        mX = x;
    }

    // マップ上における実際の座標を取得する
    pair<int, int> getRealCurrentPosition() {
        return {mY, mX};
    }

    // プレイヤーを方向転換する
    void changeDirection(const char &d) {
        constexpr const int TURN_RIGHT = 1;
        constexpr const int TURN_LEFT = 3;
        int turn = (d == LEFT) ? TURN_LEFT : TURN_RIGHT;

        // 方角を示すenum値を右+1, 右+3 することで右、左回転を表現
        mDirection = (mDirection + turn) % END_OF_DIRECTION;
    }
};

bool player::move(const char &d, int distance) {

    int diffY = 0;
    int diffX = 0;
    int speed = 1;

    if (d == LEFT)
        speed *= -1;

    // 現在の方角を基準に移動する方向を決定
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

    bool                 flgMove = true;
    auto                 [y, x]  = getRealCurrentPosition();
    const vector<string> &table  = mTable.getTable();

    // 指定された分だけ移動する
    for (size_t i = 0; i < distance; ++i) {
        // 移動後の位置がWALLでなければ移動可能を示すtrueを返す
        if (table[y + diffY][x + diffX] == mapTable::WALL) {
            flgMove = false;
            break;
        }

        y += diffY;
        x += diffX;
    }

    setRealCurrentPosition(y, x);
    changeDirection(d);

    return flgMove;
}

/*
◆全体方針
    1. 移動させるプレイヤーオブジェクト、地図を表すマップオブジェクトを生成し、プレイヤーにマップを所有させる。
    2. マップオブジェクトはWALLで囲んだ層を外側に追加し、障害物の判定、マップの範囲外判定を配列の場所に拘らず同じロジックを適用できるようにする
 */
int main() {

    int H, W, sy, sx, N;
    cin >> H >> W >> sy >> sx >> N;

    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    player p1(sy, sx, mapTable(tmpTable));

    for (size_t i = 0; i < N; ++i) {

        char d;
        int speed;
        cin >> d >> speed;

        bool flgMove = p1.move(d, speed);
        const auto &[y, x] = p1.getCurrentPosition();
        cout << y << " " << x << endl;

        if (!flgMove) {
            cout << "Stop" << endl;
            break;
        }
    }

    return 0;
}