#include "gtest/gtest.h"
#include "testsuite.h"

TEST(example, add)
{
    double res;
    res = do_Test1(1) + 2.0;// add_numbers(1.0, 2.0);
    ASSERT_NEAR(res, 3.0, 1.0e-11);
}
