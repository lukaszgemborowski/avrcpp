#ifndef AVRCPP_TESTING_HPP
#define AVRCPP_TESTING_HPP

#include <tuple>

namespace avrcpp
{

struct success {};
struct fail {
    const char *expression;
};

struct result {
    result (success)
        : expression {nullptr}
        , succeed {true}
    {}

    result (fail f)
        : expression {f.expression}
        , succeed {false}
    {}

    result (const char *e, bool s)
        : expression {e}
        , succeed {s}
    {}

    const char *expression;
    bool succeed;
};

template<class... TestCases>
struct tests {
    tests (TestCases... tcs)
        : cases {tcs...}
    {}

    template<std::size_t... I>
    void run_impl(std::index_sequence<I...>)
    {
        result r[] = {
            std::get<I>(cases).fun() ...
        };
    }

    void run()
    {
        run_impl(std::make_index_sequence<decltype(cases)::size::value>{});
    }

    std::tuple<TestCases...> cases;
};

template<class T>
struct tc {
    tc(const char *name, T lambda)
        : name {name}
        , fun {lambda}
    {
    }

    const char *name;
    T fun;
};

#define CHECK(exp) \
    if (!(exp)) { \
        return result {#exp, false}; \
    }

} // namespace avrcpp

#endif // AVRCPP_TESTING_HPP
