#pragma once
#include <cmath>

// 匹配规则服务（无状态）
class MatchService {
public:
    static bool canMatch(int a, int b)
    {
        if (abs(a - b) == 1)
            return true;

        // A 和 K 相邻
        if ((a == 0 && b == 12) || (a == 12 && b == 0))
            return true;

        return false;
    }
};
