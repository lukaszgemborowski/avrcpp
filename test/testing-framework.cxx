#include "avrcpp/testing.hpp"

using namespace avrcpp;

// declaration of test set
auto t1 = tests {
    // Each test case is "tc" class instance consisting
    // of name and lambda (test to execute).
    // Test results are reported by return value.
    // By returning instance of "result" class test
    // case will signal its status. There are two helper
    // classes: success and fail which makes intention
    // easier to understand.
    tc {"success test case", []() -> result {
        int x = 0;
        int y = 1;

        // CHECK macro is simple wrapper returning fail{}
        // when expression evaluates to false
        CHECK(x == 0);
        CHECK(x != y);

        // this is basically to what CHECK macro is expanded
        if (y != 1) {
            return fail {"y != 1"};
        }

        // you can either explicitly return success
        // or use TC_END() macro
        return success {};
    }},

    tc {"fail test case", []() -> result {
        int x = 0;
        int y = 1;
        CHECK(x == y);

        TC_END();
    }}
};

int main() {
    // run all the test cases from t1 test set
    t1.run();
}
