# C++20 Compile-Time String Concatenation

Generate std::string_view that concatenate string literals at compile-time

## Usage

```cpp
#include "concat.h"

int main()
{
    static constexpr auto sv = Concat<"Hello", ", ", "world!">();

    std::cout << sv; // Hello, world!
}
```

[Compiler Explorer](https://godbolt.org/z/GbsGMosP1)

## Reference

- [C++ Weekly - Ep 313 - The constexpr Problem That Took Me 5 Years To Fix!](https://www.youtube.com/watch?v=ABg4_EV5L3w)
- [++namedtuple - Python-style Named Tuples in C++20 - Kris Jusiak - CppCon 2021](https://www.youtube.com/watch?v=4PwNi0Zgmm0)
