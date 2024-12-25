#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10); // count = 1
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // count = 4

    std::weak_ptr<int> observer = shared; // weak ptr不增加计数, count = 4
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset(); // count--
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr; // count--
    ASSERT(observer.use_count() == 2, "");
    // 这里是复制一个新的10, 创建新的shared_ptr指向这个新的值
    // *解引用后，就是一个新的值了，而不是引用，因此原有计数减1
    ptrs[2] = std::make_shared<int>(*shared); // count--
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared; // ++
    ptrs[1] = shared; // ++
    ptrs[2] = std::move(shared); // 把shared的指针计数放到ptrs[2]里，shared变成nullptr, count = 3
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]); // 不变，可能是std::ignore的特殊作用

    ptrs[1] = std::move(ptrs[1]); // 不变
    ptrs[1] = std::move(ptrs[2]); // --

    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock(); // ++
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr; // --
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");
    // 计数为0后直接释放资源了

    shared = observer.lock(); // weak_ptr已经失效 = nullptr
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
