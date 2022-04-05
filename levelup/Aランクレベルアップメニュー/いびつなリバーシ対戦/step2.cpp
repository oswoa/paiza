/*
盤面の行数 H , 列数 W と盤面の情報 S_i , 石を置くマスの座標 Y , X が与えられます。
現在プレイヤーの石が置かれているマスは '*' になっており、何も置かれていないマスは '.' になっています。

プレイヤーは次の操作を 1 回だけおこないます。

・ 盤面の ( Y , X ) に石を置き、縦横に自分の石ではさんだマスの間に自分の石をおく。
・ 新たに置いた石によってさらに石が置けるようになった場合でもその時点で操作を終える。

この操作を終えた後の盤面を出力してください。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。

例として、図 1 のような盤面のとき赤いマスに石を置くと図 2 のようになります。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_pincerattack_step2
 */
#include <iostream>
#include <vector>
using namespace std;

class mapTable {
public:
    mapTable(const vector<string> &table) : mTable(table){};
    ~mapTable() = default;

    // 指定された座標にSTONEを設置し、挟まれた領域をSTONEで埋める
    bool setPlayerStone(const int &y, const int &x);

    // 保存しているマップを表示する
    void dispMap();

private:
    const char STONE = '*';
    vector<string> mTable;

    // 指定された座標にSTONEを設置する
    bool setStone(const int &y, const int &x);

    // 水平方向にSTONEで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneHorizontally(const int &y, const int &x);

    // 垂直方向にSTONEで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneVertically(const int &y, const int &x);
};

bool mapTable::setPlayerStone(const int &y, const int &x) {

    if (mTable[y][x] == STONE)
        return false;
    mTable[y][x] = STONE;

    overwriteBlankWithStoneHorizontally(y, x);
    overwriteBlankWithStoneVertically(y, x);

    return true;
}

void mapTable::dispMap() {
    for (const auto &row : mTable)
        cout << row << endl;
}

bool mapTable::setStone(const int &y, const int &x) {

    if (mTable[y][x] == STONE)
        return false;
    mTable[y][x] = STONE;

    return true;
}

void mapTable::overwriteBlankWithStoneHorizontally(const int &y, const int &x) {

    bool flgFindStone = false;
    int numNeedStone = 0;

    // 現在のx座標より左にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = x - 1; 0 <= i; --i) {
        if (mTable[y][i] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y, x - i);
    }

    flgFindStone = false;
    numNeedStone = 0;
    // 現在のx座標より右にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = x + 1; i < size(mTable[0]); ++i) {
        if (mTable[y][i] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y, x + i);
    }
}

void mapTable::overwriteBlankWithStoneVertically(const int &y, const int &x) {

    bool flgFindStone = false;
    int numNeedStone = 0;

    // 現在のy座標より上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = y - 1; 0 <= i; --i) {
        if (mTable[i][x] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y - i, x);
    }

    flgFindStone = false;
    numNeedStone = 0;
    // 現在のy座標より下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = y + 1; i < size(mTable); ++i) {
        if (mTable[i][x] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y + i, x);
    }
}

/*
    ◆全体方針
    1. 入力されるマップを所有するマップオブジェクトを作成
    2. 石の配置、置かれた石ともともと置かれている石に挟まれた領域に石を置く操作をマップオブジェクトに担当させる
 */
int main() {
    int H, W, Y, X;
    cin >> H >> W >> Y >> X;

    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    mapTable table(tmpTable);
    if (!table.setPlayerStone(Y, X))
        return 0;

    table.dispMap();

    return 0;
}