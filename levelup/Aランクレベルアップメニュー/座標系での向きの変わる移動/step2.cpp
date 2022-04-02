/*
開始時点の y , x 座標 と移動の回数 N が与えられます。
続く N 行で移動の方角 d_1 ... d_N が与えられるので、与えられた順に移動をしたときの各移動後の y , x 座標 を答えてください。
ただし、図の通り、上側（ y 軸の負の向き）を北とします。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_move_step2
 */

#include <iostream>
#include <queue>
using namespace std;

void movePointer(pair<int, int> &point, const char &event) {

    constexpr const char NORTH = 'N';
    constexpr const char SOUTH = 'S';
    constexpr const char EAST = 'E';
    constexpr const char WEST = 'W';
    auto &[y, x] = point;

    switch (event) {
    case NORTH:
        --y;
        break;

    case SOUTH:
        ++y;
        break;

    case EAST:
        ++x;
        break;

    case WEST:
        --x;
        break;
    }
}

int main() {

    int Y, X, N;
    cin >> Y >> X >> N;

    pair<int, int> point{Y, X};
    queue<char> events;

    for (size_t i = 0; i < N; ++i) {
        char tmp;
        cin >> tmp;
        events.push(tmp);
    }

    while (!events.empty()) {
        auto event = events.front();
        events.pop();

        movePointer(point, event);
        cout << point.first << " " << point.second << endl;
    }

    return 0;
}