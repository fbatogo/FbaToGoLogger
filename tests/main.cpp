#include <gtest/gtest.h>

// Start running all of the unit tests.
int main(int argc, char **argv)
{
    // Init Google Test.
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
