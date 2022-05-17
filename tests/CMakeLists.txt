include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(FMathTests
    FMathTests.cpp
)
target_link_libraries(FMathTests
    gtest
    gtest_main
    FMath::FMath
)

if (BUILD_SHARED_LIBS)
add_custom_command(TARGET FMathTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    "${PROJECT_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>/"
   "${CMAKE_CURRENT_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>/" 
)

add_custom_command(TARGET FMathTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory  
    "${PROJECT_BINARY_DIR}/bin/$<IF:$<CONFIG:Debug>,Debug,Release>/"
    "${CMAKE_CURRENT_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>/"
)
endif()

add_test(
    NAME FMathTests
    COMMAND FMathTests
)