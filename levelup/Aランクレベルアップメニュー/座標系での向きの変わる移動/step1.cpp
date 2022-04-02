/*
マップの行数 H と列数 W とマップを表す H 行 W 列の文字列 S_1 ...S_H が与えられます。
要素が '#' になっているマスが 1 つあるので、その y , x 座標 を答えてください。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_move_step1
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {

    constexpr const char MARK = '#';
    int H, W;
    cin >> H >> W;

    vector<string> table(H);
    for (size_t i = 0; i < H; ++i)
        cin >> table[i];

    pair<int, int> point;
    for (size_t i = 0; i < size(table); ++i) {
        if (int index = table[i].find(MARK); index != string::npos)
            point = {i, index};
    }

    cout << point.first << " " << point.second << endl;
    
    return 0;
}