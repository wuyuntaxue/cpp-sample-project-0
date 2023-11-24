#include "log/log.hpp"

int main() {
    LOG_WARN("start test");
#if _OPENMP
    LOG_WARN("find openmp");
#else
    LOG_WARN("not find openmp");
#endif

    // #pragma omp 指令 子句 子句 ...
    int numThreads = 100;

#pragma omp parallel num_threads(numThreads)
    {
        static int count = 0;
        count++;
        LOG_INFO("test");
        LOG_INFO("count={}", count);
    }

#pragma omp parallel for num_threads(100)
    for (int i = 0; i < 10; i++) {
        LOG_INFO("i={}", i);
    }

    // #pragma omp parallel for num_threads(2)
    //     for (int i = 0; i < 10; i++) {
    //         LOG_INFO("i={}", i);
    //     }

    return 0;
}