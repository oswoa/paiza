/*
マップの行数 H と列数 W , 現在の座標 sy , sx , 移動の回数 N が与えられます。
続けて、障害物を '#' で、移動可能な場所を '.' で表した H 行 W 列 のマップ S_1 ... S_H と N 回の移動の向き d_1 ... d_N が与えられます。

移動者ははじめ北を向いています。移動者は、1 回の移動で次の行動を行います。

「移動の向きに方向転換したのち、1 マス進む。」

各移動が可能である場合、移動後の y , x 座標を出力してください。
移動が可能でない場合、移動後の座標を出力する代わりに "Stop" を出力して、以降の移動を打ち切ってください。

各移動が可能であるということは、以下の図の通り
「移動先が障害物でない　かつ　移動先がマップの範囲外でない」
ということを意味します。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_mapmove_step3
 */

#include <iostream>
#include <vector>
using namespace std;

class mapTable {
public:
    mapTable(const int &sy, const int &sx, const vector<string> &tmpTable) : mY(sy + 1), mX(sx + 1), mDirection(NORTH){
        mTable = addLayer(tmpTable);
    };
    ~mapTable() = default;

    // 指定された方角へ移動する
    bool move(const char &d);

    // WALL層を追加してるので、現在位置は-1して返す
    pair<int, int> getPosition() {
        return {mY - 1, mX - 1};
    }

private:
    int mY;
    int mX;
    int mDirection;
    vector<string> mTable;

    const char WALL = '#';
    const char LEFT = 'L';
    enum {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        END_OF_DIRECTION,
    };


    // 座標を設定する
    void setPosition(const int &y, const int &x) {
        mY = y;
        mX = x;
    }

    // 方向転換する
    void changeDirection(const char &d) {
        constexpr const int TURN_RIGHT = 1;
        constexpr const int TURN_LEFT = 3;
        int turn = (d == LEFT) ? TURN_LEFT : TURN_RIGHT;
        mDirection = (mDirection + turn) % END_OF_DIRECTION;
    }

    // 外側にWALLレイヤーを追加する
    vector<string> addLayer(const vector<string> &tmpTable);
};

vector<string> mapTable::addLayer(const vector<string> &tmpTable) {

    constexpr const int NUM_ADD_LAYER = 2;
    const int len = size(tmpTable[0]) + NUM_ADD_LAYER;
    const string outerLayer = string(len, WALL);
    vector<string> table;

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

bool mapTable::move(const char &d) {

    int diffY = 0;
    int diffX = 0;
    int speed = 1;

    if (d == LEFT)
        speed *= -1;

    // 現在の方角を基準に左右に移動
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

    bool flgMove = (mTable[mY + diffY][mX + diffX] == WALL) ? false : true;
    setPosition(mY + diffY, mX + diffX);
    changeDirection(d);

    return flgMove;
}

/*
◆全体方針
    1. 地図を表すマップオブジェクトを生成し、移動出来るかチェック、移動ロジックを担当させる
    (移動ロジックはユーザオブジェクトに担当させるべきだが今回は作成しない。追加する際はマップにユーザを所持させる)
    2. マップオブジェクトはWALLで囲んだ層を外側に追加し、障害物の判定、マップの範囲外判定を
    配列の場所に依らず同じロジックで出来るようにする
 */
int main() {

    int H, W, sy, sx, N;
    cin >> H >> W >> sy >> sx >> N;

    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    mapTable table(sy, sx, tmpTable);

    for (size_t i = 0; i < N; ++i) {
        char d;
        cin >> d;

        if (!table.move(d)) {
            cout << "Stop" << endl;
            break;
        }

        const auto &[y, x] = table.getPosition();
        cout << y << " " << x << endl;
    }

    return 0;
}