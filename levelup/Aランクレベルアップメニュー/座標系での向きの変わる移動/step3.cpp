/*
開始時点の y , x 座標 と向いている方角 D が与えられます。
続く 1 行で移動の向き d が与えられるので、その向きに移動した後の y , x 座標 を答えてください。
移動前に向いている方角によって同じ移動の向きでも座標の変化が違うことに気をつけてください。

なお、マスの座標系は左上端のマスの座標を ( y , x ) = ( 0 , 0 ) とし、
下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
以下の図を参考にしてみてください。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_move_step3
 */

#include <iostream>
#include <queue>
using namespace std;

class user {
public:
    user(int y, int x, char d) : mY(y), mX(x), mDirection(d){};
    ~user() = default;

    pair<int, int> getPosition() { return {mY, mX}; }
    char getDirection() { return mDirection; }

    void setPosition(const int &y, const int &x) {
        mY = y;
        mX = x;
    }

    void setDirection(const char &d) {
        mDirection = d;
    }

private:
    int mY;
    int mX;
    char mDirection;
};

void movePointer(user &u, const char &event) {

    constexpr const char NORTH = 'N';
    constexpr const char SOUTH = 'S';
    constexpr const char EAST = 'E';
    constexpr const char WEST = 'W';
    constexpr const char LEFT = 'L';
    constexpr const char RIGHT = 'R';

    auto [y, x] = u.getPosition();
    auto direction = u.getDirection();

    switch (direction) {
    case NORTH:
        if (event == LEFT) --x;
        else if (event == RIGHT) ++x;
        break;

    case SOUTH:
        if (event == LEFT) ++x;
        else if (event == RIGHT) --x;
        break;

    case EAST:
        if (event == LEFT) --y;
        else if (event == RIGHT) ++y;
        break;

    case WEST:
        if (event == LEFT) ++y;
        else if (event == RIGHT) --y;
        break;
    }

    u.setPosition(y, x);
}

int main() {

    int Y, X, N = 1;
    char D;
    cin >> Y >> X >> D;

    user u(Y, X, D);
    queue<char> events;

    for (size_t i = 0; i < N; ++i) {
        char tmp;
        cin >> tmp;
        events.push(tmp);
    }

    while (!events.empty()) {
        auto event = events.front();
        events.pop();

        movePointer(u, event);
        auto [y, x] = u.getPosition();
        cout << y << " " << x << endl;
    }

    return 0;
}