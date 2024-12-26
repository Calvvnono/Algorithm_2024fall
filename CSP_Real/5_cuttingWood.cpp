#include <bits/stdc++.h>
using namespace std;

int main () {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> colors(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> colors[i];
    }
    // 初始化木板列表
    vector<deque<int>> boards;
    boards.push_back(deque<int>());
    for(int i = 1; i <= n; ++i) {
        boards[0].push_back(i);
    }
    // 模拟切割操作
    for(int i = 0; i < k; ++i) {
        int xi, li, ri;
        cin >> xi >> li >> ri;
        xi -= 1; // 调整木板编号为从 0 开始
        deque<int>& board = boards[xi];
        deque<int> new_board;
        // 切割指定范围的段
        auto it = board.begin();
        while(it != board.end()) {
            if(*it >= li && *it <= ri) {
                // 切割下来的形成新的木板，编号保留不变，方便找color
                new_board.push_back(*it);
                it = board.erase(it);
            } else {
                ++it;
            }
        }
        boards.push_back(new_board);
        // 统计并输出结果
        if(new_board.empty()) {
            cout << 0 << " " << 0 << endl;
        } else {
            set<int> color_set;
            int color_blocks = 1;
            color_set.insert(colors[new_board[0]]);
            for(size_t j = 1; j < new_board.size(); ++j) {
                color_set.insert(colors[new_board[j]]); // 直接用set不用考虑重复
                if(colors[new_board[j]] != colors[new_board[j - 1]]) {
                    color_blocks++;
                }
            }
            cout << color_set.size() << " " << color_blocks << endl;
        }
    }
    return 0;
}