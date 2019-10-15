#include "std/cstddef.hpp"
#include "std/cstdint.hpp"
#include "std/new.hpp"
#include "std/tuple.hpp"
#include "std/type_traits.hpp"
#include "std/utility.hpp"
#include "avrcpp/testing.hpp"

using namespace avrcpp;

tests t1 {
    tc {"t1", []() -> result {
        int x = 0;
        int y = 1;

        CHECK(x == 1);
        CHECK(x == y);

        return success {};
    }},

    tc {"t2", []() -> result {
        return success {};
    }}
};

int main() {
    t1.run();
}
