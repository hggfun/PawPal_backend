#include "hello.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  using UserverBackendTest::SayHelloTo;
  using UserverBackendTest::UserType;

  EXPECT_EQ(SayHelloTo("Developer", UserType::kNewbie),
            "Hello, Developer!\n");
  EXPECT_EQ(SayHelloTo({}, UserType::kNewbie), "Hello, unknown user!\n");

  EXPECT_EQ(SayHelloTo("Developer", UserType::kKnown),
            "Hi again, Developer!\n");
}
