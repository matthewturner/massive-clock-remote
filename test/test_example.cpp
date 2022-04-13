#include <unity.h>
#include <stdio.h>

void test_something(void)
{
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_something);
    UNITY_END();

    return 0;
}
