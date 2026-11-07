/*
    随机数生成器
    全局只用这一个随机数生成器 方便固定种子复现
    种子在 main() 里面修改 否则使用默认种子
*/
#pragma once
#include <random>
#include <cstdint>

namespace gen::core {

inline uint32_t seed = 0x3f77a690; // 默认种子
inline std::mt19937 rnd(0x3f77a690); // 随机数生成器 默认种子

inline void setSeed(uint32_t settingSeed) {
    seed = settingSeed;
    rnd.seed(seed);
}

inline int randomInt(int min, int max) {
    return rnd() % (max - min + 1) + min;
}

inline double random01() {
    return rnd() / double(rnd.max()); 
}

inline double randomDouble(double min, double max) {
    return random01() * (max - min) + min;
}

}