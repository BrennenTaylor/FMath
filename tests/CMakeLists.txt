enable_testing()

add_executable(FMathTests
    FMathTests.cpp
)
target_link_libraries(FMathTests
    gtest
    gtest_main
    FMath::FMath
)

add_test(
    NAME FMathTests
    COMMAND FMathTests
)