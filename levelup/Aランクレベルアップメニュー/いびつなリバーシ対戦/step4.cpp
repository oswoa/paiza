/*
盤面についての情報と、石を置くマスについての情報が与えられます。
現在プレイヤーの石が置かれているマスは '*' になっており、何も置かれていないマスは '.' になっています。

プレイヤーは次の操作を 1 回だけおこないます。

・ 盤面の ( Y , X ) に石を置き、斜めに自分の石ではさんだマスの間に自分の石をおきます。
・ 新たに置いた石によってさらに石が置けるようになった場合でもその時点で操作を終える。

この操作を終えた後の盤面を出力してください。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。

例として、図 1 のような盤面のとき赤いマスに石を置くと図 2 のようになります。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_pincerattack_step4
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

    // 右斜め方向にSTONEで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneInRightDiagonalLine(const int &y, const int &x);

    // 左斜め方向にSTONEで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneInLeftDiagonalLine(const int &y, const int &x);
};

bool mapTable::setPlayerStone(const int &y, const int &x) {

    if (mTable[y][x] == STONE)
        return false;
    mTable[y][x] = STONE;

    // overwriteBlankWithStoneHorizontally(y, x);
    // overwriteBlankWithStoneVertically(y, x);
    overwriteBlankWithStoneInRightDiagonalLine(y, x);
    overwriteBlankWithStoneInLeftDiagonalLine(y, x);

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

    // 現在のx座標から左端までの距離を取得する
    int len = x;

    // 現在のx座標より左にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = 1; i <= len; ++i) {
        if (mTable[y][x - i] == STONE) {
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

    // 現在のx座標から右端までの距離を取得する
    len = size(mTable[0]) - (x + 1);

    // 現在のx座標より右にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (mTable[y][x + i] == STONE) {
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

    // 現在のy座標から上端までの距離を取得する
    int len = y;

    // 現在のy座標より上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = 1; i <= len; ++i) {
        if (mTable[y - i][x] == STONE) {
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

    // 現在のy座標から下端までの距離を取得する
    len = size(mTable) - (y + 1);

    // 現在のy座標より下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = 1; i <= len; ++i) {
        if (mTable[y + i][x] == STONE) {
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

void mapTable::overwriteBlankWithStoneInRightDiagonalLine(const int &y, const int &x) {

    bool flgFindStone = false;
    int numNeedStone = 0;

    // 現在のx座標から右端、y座標から上端までの距離のうち短い距離を取得する
    int len = min(size((mTable[0])) - (x + 1), static_cast<size_t>(y));

    // 現在のy座標より右斜め上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (mTable[y - i][x + i] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y - i, x + i);
    }

    flgFindStone = false;
    numNeedStone = 0;

    // 現在のx座標から左端、y座標から下端までの距離のうち短い距離を取得する
    len = min(static_cast<size_t>(x), size(mTable) - (y + 1));

    // 現在のy座標より左斜め下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (mTable[y + i][x - i] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y + i, x - i);
    }
}

void mapTable::overwriteBlankWithStoneInLeftDiagonalLine(const int &y, const int &x) {

    bool flgFindStone = false;
    int numNeedStone = 0;

    // 現在のx座標から左端、y座標から上端までの距離のうち短い距離を取得する
    int len = min(static_cast<size_t>(x), static_cast<size_t>(y));

    // 現在のy座標より左斜め上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (mTable[y - i][x - i] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y - i, x - i);
    }

    flgFindStone = false;
    numNeedStone = 0;

    // 現在のx座標から右端、y座標から下端までの距離のうち短い距離を取得する
    len = min(size((mTable[0])) - (x + 1), size(mTable) - (y + 1));

    // 現在のy座標より右斜め下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (mTable[y + i][x + i] == STONE) {
            flgFindStone = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgFindStone) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y + i, x + i);
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