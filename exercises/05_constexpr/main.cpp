#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……

    // fib(90)计算量太大，编译器无法在编译时计算出结果
    // 即便去掉constexpr，改为在运行时计算, 也可能无法计算出结果(运行时间过长or爆栈)
    // constexpr auto ANS_N = 90;
    // auto ANS = fibonacci(ANS_N);
    // std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
