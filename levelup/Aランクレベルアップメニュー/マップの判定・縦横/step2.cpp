/*
行数 H , 列数 W の盤面があり、各マスには文字が 1 つだけ書かれています。
盤面と N 個 の y , x 座標 が与えられるので、盤面の与えられた座標の文字を "#" に書き換えた後の盤面を出力してください。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_map_step2
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {

    constexpr const char MARK = '#';
    int H, W, N;
    cin >> H >> W >> N;

    vector<string> table(H);
    for (size_t i = 0; i < H; ++i)
        cin >> table[i];

    vector<pair<int, int>> points(N);
    for (size_t i = 0; i < N; ++i) {
        int y, x;
        cin >> y >> x;
        table[y][x] = MARK;
    }

    for (const auto &row: table)
        cout << row << endl;

    return 0;
}