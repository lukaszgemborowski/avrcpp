#ifndef AVRCPP_TESTING_HPP
#define AVRCPP_TESTING_HPP

#include <tuple>
#include <stdio.h>

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

    result (const char *tc, const char *e, bool s)
        : test {tc}
        , expression {e}
        , succeed {s}
    {}

    const char *test;
    const char *expression;
    bool succeed;
};

struct tests_base
{
    tests_base();
};

template<class... TestCases>
struct tests : tests_base {
    tests (TestCases... tcs)
        : cases {tcs...}
    {
    }

    void run()
    {
        run_impl(std::make_index_sequence<decltype(cases)::size::value>{});
    }

private:
    template<std::size_t I>
    result run_one ()
    {
        auto r = std::get<I>(cases).fun();
        return result {
            std::get<I>(cases).name,
            r.expression,
            r.succeed
        };
    }

    template<std::size_t... I>
    void run_impl(std::index_sequence<I...>)
    {
        result r[] = {run_one<I>() ...};

        for (const auto &e : r) {
            printf("TC: %s %s %s\n",
                e.test,
                (e.succeed ? "OK" : "FAIL"),
                (e.succeed ? "" : e.expression));
        }
    }

private:
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
        return fail {#exp}; \
    }

} // namespace avrcpp

#endif // AVRCPP_TESTING_HPP
