#include "gtest/gtest.h"
#include "testsuite.h"

TEST(example, subtract)
{
    double res;
    //res = subtract_numbers(1.0, 2.0);
    res = do_Test1(2) - 1.0;
    ASSERT_NEAR(res, 3.0, 1.0e-11);
    //ASSERT_NEAR(res, -1000.0, 1.0e-11);
}
