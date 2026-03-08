#include <greeting.hpp>

#include <userver/utest/utest.hpp>

using bilol_abdilxayev::UserType;

UTEST(SayHelloTo, Basic) {
    EXPECT_EQ(bilol_abdilxayev::SayHelloTo("Developer", UserType::kFirstTime), "Hello, Developer!\n");
    EXPECT_EQ(bilol_abdilxayev::SayHelloTo({}, UserType::kFirstTime), "Hello, unknown user!\n");

    EXPECT_EQ(bilol_abdilxayev::SayHelloTo("Developer", UserType::kKnown), "Hi again, Developer!\n");
    EXPECT_EQ(bilol_abdilxayev::SayHelloTo({}, UserType::kKnown), "Hi again, unknown user!\n");
}