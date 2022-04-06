/*
1 から N のプレイヤー番号が与えられた N 人でいびつなオセロの対戦をします。
盤面・ゲームをする人数・合計のターン数・各行動についての情報が与えられます。
盤面に穴の空いているマスは '#' , 何も置かれていないマスは '.' になっています。

プレイヤー達は、各行動ごとに次の操作をおこないます。

・ 盤面のマス(Y_i, X_i)に石を置く。既に相手の石が置かれている場合は相手の石を自分の石に置き換える。
・ 次に、縦横斜めに自分の石ではさんだ連続した穴の空いていないマスに自分の石を置きます。相手の石が置かれている場合は相手の石を自分の石に置き換えて、操作を終了する。

操作を終えた後の盤面を出力してください。
ただし、番号 i のプレイヤーの石のあるマスを i として出力してください。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。

例えば、図 1 の状態から赤いマスに B さんが石を置くと、図 2 の状態になります。
図 3 の状態から赤いマスに C さんが石を置くと、図 4 の状態になります。
図 5 の状態から赤いマスに A さんが石を置くと、図 6 の状態になります。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_pincerattack_boss
 */
#include <iostream>
#include <vector>
using namespace std;

class mapTable {
public:
    mapTable(const vector<string> &table) : mTable(table){};
    ~mapTable() = default;

    // 指定された座標にSTONEを設置し、挟まれた領域をstoneで埋める
    bool setPlayerStone(const int &y, const int &x, const char &stone);

    // 保存しているマップを表示する
    void dispMap();

private:
    const char HOLE = '#'; // 穴を示す文字

    vector<string> mTable; // 所有される書き換え可能なマップ

    // 指定された座標にstoneを設置する
    bool setStone(const int &y, const int &x, const char &stone);

    // 指定された座標が穴か確認する
    bool isHole(const int &y, const int &x);

    // 指定された座標にstoneが設置出来るか確認する
    bool isMyStone(const int &y, const int &x, const char &stone);

    // 水平方向にstoneで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneHorizontally(const int &y, const int &x, const char &stone);

    // 垂直方向にstoneで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneVertically(const int &y, const int &x, const char &stone);

    // 右斜め方向にstoneで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneInRightDiagonalLine(const int &y, const int &x, const char &stone);

    // 左斜め方向にstoneで挟まれた領域をSTONEで埋める
    void overwriteBlankWithStoneInLeftDiagonalLine(const int &y, const int &x, const char &stone);
};

bool mapTable::setPlayerStone(const int &y, const int &x, const char &stone) {

    setStone(y, x, stone);
    overwriteBlankWithStoneHorizontally(y, x, stone);
    overwriteBlankWithStoneVertically(y, x, stone);
    overwriteBlankWithStoneInRightDiagonalLine(y, x, stone);
    overwriteBlankWithStoneInLeftDiagonalLine(y, x, stone);

    return true;
}

void mapTable::dispMap() {
    for (const auto &row : mTable)
        cout << row << endl;
}

bool mapTable::setStone(const int &y, const int &x, const char &stone) {

    if (isHole(y, x))
        return false;

    if (isMyStone(y, x, stone))
        return false;
        
    mTable[y][x] = stone;

    return true;
}

bool mapTable::isHole(const int &y, const int &x) {
    return (mTable[y][x] == HOLE) ? true : false;
}

bool mapTable::isMyStone(const int &y, const int &x, const char &stone) {
    return (mTable[y][x] == stone) ? true : false;
}

void mapTable::overwriteBlankWithStoneHorizontally(const int &y, const int &x, const char &stone) {

    bool flgStopSearch = false;
    int numNeedStone = 0;

    // 現在のx座標から左端までの距離を取得する
    int len = x;

    // 現在のx座標より左にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = 1; i <= len; ++i) {
        if (isHole(y, x - i))
            break;

        if (isMyStone(y, x - i, stone)) {
            flgStopSearch = true;
            break;
        } else ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y, x - i, stone);
    }

    flgStopSearch = false;
    numNeedStone = 0;

    // 現在のx座標から右端までの距離を取得する
    len = size(mTable[0]) - (x + 1);

    // 現在のx座標より右にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (isHole(y, x + i))
            break;

        if (isMyStone(y, x + i, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y, x + i, stone);
    }
}

void mapTable::overwriteBlankWithStoneVertically(const int &y, const int &x, const char &stone) {

    bool flgStopSearch = false;
    int numNeedStone = 0;

    // 現在のy座標から上端までの距離を取得する
    int len = y;

    // 現在のy座標より上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = 1; i <= len; ++i) {
        if (isHole(y - i, x))
            break;

        if (isMyStone(y - i, x, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y - i, x, stone);
    }

    flgStopSearch = false;
    numNeedStone = 0;

    // 現在のy座標から下端までの距離を取得する
    len = size(mTable) - (y + 1);

    // 現在のy座標より下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (int i = 1; i <= len; ++i) {
        if (isHole(y + i, x))
            break;

        if (isMyStone(y + i, x, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y + i, x, stone);
    }
}

void mapTable::overwriteBlankWithStoneInRightDiagonalLine(const int &y, const int &x, const char &stone) {

    bool flgStopSearch = false;
    int numNeedStone = 0;

    // 現在のx座標から右端、y座標から上端までの距離のうち短い距離を取得する
    int len = min(size((mTable[0])) - (x + 1), static_cast<size_t>(y));

    // 現在のy座標より右斜め上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (isHole(y - i, x + i))
            break;

        if (isMyStone(y - i, x + i, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y - i, x + i, stone);
    }

    flgStopSearch = false;
    numNeedStone = 0;

    // 現在のx座標から左端、y座標から下端までの距離のうち短い距離を取得する
    len = min(static_cast<size_t>(x), size(mTable) - (y + 1));

    // 現在のy座標より左斜め下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (isHole(y + i, x - i))
            break;

        if (isMyStone(y + i, x - i, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y + i, x - i, stone);
    }
}

void mapTable::overwriteBlankWithStoneInLeftDiagonalLine(const int &y, const int &x, const char &stone) {

    bool flgStopSearch = false;
    int numNeedStone = 0;

    // 現在のx座標から左端、y座標から上端までの距離のうち短い距離を取得する
    int len = min(static_cast<size_t>(x), static_cast<size_t>(y));

    // 現在のy座標より左斜め上にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (isHole(y - i, x - i))
            break;

        if (isMyStone(y - i, x - i, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y - i, x - i, stone);
    }

    flgStopSearch = false;
    numNeedStone = 0;

    // 現在のx座標から右端、y座標から下端までの距離のうち短い距離を取得する
    len = min(size((mTable[0])) - (x + 1), size(mTable) - (y + 1));

    // 現在のy座標より右斜め下にSTONEがある場合、挟まれた領域をSTONEで埋める
    for (size_t i = 1; i <= len; ++i) {
        if (isHole(y + i, x + i))
            break;

        if (isMyStone(y + i, x + i, stone)) {
            flgStopSearch = true;
            break;
        } else
            ++numNeedStone;
    }
    if (flgStopSearch) {
        for (size_t i = 1; i <= numNeedStone; ++i)
            setStone(y + i, x + i, stone);
    }
}

class player {
public:
    // マップに配置出来るよう、stoneはASCIIへ変換
    player(const int &stone, mapTable &map) : mStone(stone + 0x30), mMap(map){};
    ~player() = default;

    // 指定された位置へmStoneを配置する
    bool setStone(const int &y, const int &x) {
        return mMap.setPlayerStone(y, x, mStone);
    }

private:
    char mStone;    // プレイヤー毎の石を示す文字
    mapTable &mMap; // ユーザが操作するマップへの参照
};

/*
    ◆全体方針
    1. 入力されるマップを所有するマップオブジェクトを作成
    2. 石の配置、置かれた石ともともと置かれている石に挟まれた領域に石を置く操作をマップオブジェクトに担当させる
    3. プレイヤークラスを作成し、マップオブジェクトを所有させる
    4. プレイヤーは所有しているマップに対しメッセージを投げてプレイヤーの石を置く
 */
int main() {
    int H, W, N, n;
    cin >> H >> W >> N >> n;

    vector<string> tmpTable(H);
    for (size_t i = 0; i < H; ++i)
        cin >> tmpTable[i];

    // マップオブジェクトの作成
    mapTable table(tmpTable);

    vector<player> user;
    user.reserve(N);

    // プレイヤーの作成
    for (size_t i = 1; i <= N; ++i)
        user.emplace_back(i, table);

    // 石の配置
    for (size_t i = 0; i < n; ++i) {
        int player, y, x;
        cin >> player >> y >> x;
        user[player - 1].setStone(y, x);
    }

    // マップ表示
    table.dispMap();

    return 0;
}
