#include "avrcpp/testing.hpp"

using namespace avrcpp;

tests t1 {
    tc {"success test case", []() -> result {
        int x = 0;
        int y = 1;

        CHECK(x == 0);
        CHECK(x != y);

        return success {};
    }},

    tc {"fail test case", []() -> result {
        int x = 0;
        int y = 1;
        CHECK(x == y);
        return success {};
    }}
};

int main() {
    t1.run();
}
