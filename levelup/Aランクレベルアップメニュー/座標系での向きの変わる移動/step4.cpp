/*
開始時点の x , y 座標と移動の歩数 N が与えられます。
以下の図のように時計回りに渦を巻くように移動を N 歩行った後の x , y 座標 を答えてください。

なお、マスの座標系は下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_move_step4
 */

#include <iostream>
#include <queue>
using namespace std;

class user {
public:
    user(int y, int x) : mY(y), mX(x), mCurrentDirection(EAST){};
    ~user() = default;

    // ユーザの現在位置を返す
    const pair<int, int> getPosition() {
        return {mY, mX};
    }

    // ユーザを指定された座標分移動させる
    void move(const int N);

private:
    int mY;
    int mX;
    int mCurrentDirection;
    enum {
        EAST,
        SOUTH,
        WEST,
        NORTH,
        END_OF_DIRECTION,
    };

    // ユーザの現在向いている方向を返す
    int getCurrentDirection() {
        return mCurrentDirection;
    }

    // ユーザの現在位置を設定する
    void setPosition(const int &y, const int &x) {
        mY = y;
        mX = x;
    }

    // ユーザの向いてる方向を変える
    // E -> S -> W -> N -> E ...と時計回りに変わる
    void changeDirection() {
        mCurrentDirection = (++mCurrentDirection) % END_OF_DIRECTION;
    }
};

void user::move(const int N) {

    auto [y, x] = getPosition();
    int n = N;
    int speed = 1;
    int counter = 0;

    while (n) {
        switch (getCurrentDirection()) {
        case EAST:
            x += speed;
            break;

        case SOUTH:
            y += speed;
            break;

        case WEST:
            x -= speed;
            break;

        case NORTH:
            y -= speed;
            break;
        }
        changeDirection();
        n -= speed;

        if (++counter % 2 == 0) {
            counter = 0;
            ++speed;
        }
        if (n <= speed)
            speed = n;
    }

    setPosition(y, x);
}

int main() {

    int X, Y, N;
    cin >> X >> Y >> N;

    user u(Y, X);
    u.move(N);

    const auto &[y, x] = u.getPosition();
    cout << x << " " << y << endl;

    return 0;
}