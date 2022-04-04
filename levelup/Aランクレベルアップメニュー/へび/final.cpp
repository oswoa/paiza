/*
マップの行数 H と列数 W , 障害物を '#' で移動可能な場所を '.' で表した H 行 W 列のマップ S_1 ... S_H , 現在の座標 sy , sx , 移動の回数 N が与えられます。
続けて N 回の移動の向き d_1 ... d_N と移動するマス数 l_1...l_N が与えられます。

はじめは北を向いています。

各移動が可能である場合、スタート位置を含む移動の際に通ったマップのマスを '*' に変更してください。
移動が可能でない場合、障害物やマップの端までできる限り移動をして通ったマップのマスを '*' に変更したのち、以降の移動を打ち切ってください。

移動が終了した時のマップを出力してください。

移動可能であるということは、以下の図の通り
「今いるマスから移動先のマスまでに障害物がない かつ 移動先がマップの範囲外でない」
ということを意味します。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_mapmove_step5
 */

#include <iostream>
#include <vector>
using namespace std;

class mapTable {
public:
    explicit mapTable(const vector<string> &tmpTable) : mTable(addLayer(tmpTable)){};
    ~mapTable() { delete mTable; }
    static constexpr const int  NUM_ADD_LAYER = 2; // 追加するレイヤーの数
    static           const char WALL = '#';        // 壁を示す文字
    static           const char MARK = '*';        // プレイヤーの奇跡を示す文字
    

    // 作成したマップを返す
    const vector<string> &getTable() { return *mTable; };

    // レイヤーを追加した絶対座標にMARKを置く
    void setMark(const int &y, const int &x) { mTable->at(y).at(x) = MARK; }

private:
    vector<string> *mTable; // 作成したマップを保持する

    // 外側にWALLレイヤーを追加する
    vector<string>* addLayer(const vector<string> &tmpTable); 
};

vector<string>* mapTable::addLayer(const vector<string> &tmpTable) {

    const          int    len        = size(tmpTable[0]) + NUM_ADD_LAYER;
    const          string outerLayer = string(len, WALL);
    vector<string>        *table = new vector<string>();

    // 上端追加
    table->push_back(outerLayer);

    for (const auto &row : tmpTable) {
        // 左端、右端に追加する事で外側の層を作成
        string tmp;
        tmp += WALL;
        tmp += row;
        tmp += WALL;
        table->push_back(tmp);
    }

    // 下端追加
    table->push_back(outerLayer);

    return table;
}


class player {
public:
    player(const int &sy, const int &sx, mapTable *table) : mY(sy + 1), mX(sx + 1), mDirection(NORTH), mTable(table) {};
    ~player() { delete mTable; };

    // マップにWALL層を追加してるので、現在位置は-1して返す
    pair<int, int> getCurrentPosition() { return {mY - 1, mX - 1}; }

    // 指定された方角へ移動する
    bool move(const char &d, int distance);

    // 外側のレイヤーを除外した、本来のマップを表示する
    void dispMap();

private:
    int mY;          // 現在のy座標 マップにWALL層を追加してるので、現在位置は+1されている
    int mX;          // 現在のx座標 マップにWALL層を追加してるので、現在位置は+1されている
    int mDirection;  // プレイヤーが現在向いてる方角(デフォルトは北)
    mapTable *mTable; // 作成したマップオブジェクト

    const char LEFT = 'L';
    enum {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        END_OF_DIRECTION,
    };

    // レイヤーを考慮したマップの絶対座標を設定する
    void setRealCurrentPosition(const int &y, const int &x) {
        mY = y;
        mX = x;
    }

    // レイヤーを考慮したマップの絶対座標を取得する
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

void player::dispMap() {

    const vector<string> &table = mTable->getTable();    

    int height = size(table);
    int width = size(table[0]) - mapTable::NUM_ADD_LAYER;

    // 外側のレイヤーを除外したマップを表示する
    for (size_t i = 1; i < height - 1; ++i)
        cout << table[i].substr(1, width) << endl;
}

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
    const vector<string> &table  = mTable->getTable();

    // 現在位置にMARKを置く
    mTable->setMark(y, x);

    // 指定された分だけ移動する
    for (size_t i = 0; i < distance; ++i) {
        // 移動後の位置がWALLでなければ移動可能を示すtrueを返す
        if (table[y + diffY][x + diffX] == mapTable::WALL) {
            flgMove = false;
            break;
        }

        y += diffY;
        x += diffX;

        // 現在位置にMARKを置く
        mTable->setMark(y, x);
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

    player p1(sy, sx, new mapTable(tmpTable));

    for (size_t i = 0; i < N; ++i) {
        char d;
        int speed;
        cin >> d >> speed;

        if (!p1.move(d, speed))
            break;
    }

    p1.dispMap();

    return 0;
}