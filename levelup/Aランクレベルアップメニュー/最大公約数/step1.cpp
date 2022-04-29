/*
整数 N ,K が与えられるので、規則的な無限数列 A = [1 , 0 , -1 , 1 , 0 , -1 , ... ] の N 要素目から K 要素目までの和を求めてください。　
https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_calculation_exchange_700/edit?language_uid=c-plus-plus
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {

    size_t N, K;
    cin >> N >> K;

    // インデックスに修正
    --N;
    --K;

    // 規則性のある 1, 0, -1 でベクトルを作成
    vector<int> list = {1, 0, -1};

    // N をlist上のインデックスに変換
    int currentPos = N % size(list);

    // N -> K 間の移動距離を N + diff で表現出来るよう、剰余を取得する
    int diff = (K - N) % size(list);

    cout << list[ (currentPos + diff) % size(list)] << endl;

    return 0;
}