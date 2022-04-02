/*
開始時点の x , y 座標、移動の回数 N が与えられます。
続くN行で移動の向き d1 ... dN が与えられるので、与えられた順に移動をしたときの各移動後の x , y 座標 を答えてください。
移動者ははじめ北を向いています。

なお、マスの座標系は下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。

・ 移動をするごとに向く方角が変わること
・ 移動前に向いている方角によって同じ移動の向きでも座標の変化が違うこと
の 2 点に気をつけてください。
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_snake_move_boss
 */

#include <iostream>
#include <vector>
using namespace std;

class user {
public:
    user(int y, int x) : mY(y), mX(x), mCurrentDirection(NORTH), mSpeed(1){};
    ~user() = default;

    // ユーザの現在位置を返す
    pair<int, int> getPosition() {
        return {mY, mX};
    }

    // ユーザを指定された方角に移動させる
    pair<int, int> move(const char &d);

private:
    int mY;
    int mX;
    int mCurrentDirection;
    int mSpeed;
    const char LEFT = 'L';
    const char RIGHT = 'R';

    enum {
        NORTH,
        EAST,
        SOUTH,
        WEST,
        END_OF_DIRECTION,
    };

    // ユーザの現在向いている方向を返す
    int getCurrentDirection() {
        return mCurrentDirection;
    }

    // 現在のスピードを返す
    int getSpeed() {
        return mSpeed;
    }

    // ユーザの現在位置を設定する
    void setPosition(const int &y, const int &x) {
        mY = y;
        mX = x;
    }

    /* 
        ユーザの向いてる方向を変える
        N -> E -> S -> W とenumで定義されているので回転する方向に合わせて定数を足し、剰余を出す事で回転後の方向を出す
     */
    void changeDirection(const char &d) {
        constexpr const int TURN_RIGHT = 1;
        constexpr const int TURN_LEFT = 3;
        int turn = (d == LEFT) ? TURN_LEFT : TURN_RIGHT;
        mCurrentDirection = (getCurrentDirection() + turn) % END_OF_DIRECTION;
    }
};

pair<int, int> user::move(const char &d) {

    auto [y, x] = getPosition();
    int speed = getSpeed();

    if (d == LEFT)
        speed *= -1;

    switch (getCurrentDirection()) {
    case NORTH:
        x += speed;
        break;

    case EAST:
        y += speed;
        break;

    case SOUTH:
        x -= speed;
        break;

    case WEST:
        y -= speed;
        break;
    }
    changeDirection(d);
    setPosition(y, x);

    return getPosition();
}

int main() {

    int X, Y, N;
    cin >> X >> Y >> N;

    vector<char> directionList(N);
    for (size_t i = 0; i < N; ++i)
        cin >> directionList[i];

    user u(Y, X);
    for (const auto &d : directionList) {
        const auto &[y, x] = u.move(d);
        cout << x << " " << y << endl;
    }

    return 0;
}