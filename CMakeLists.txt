cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(FMath VERSION 1.0)

add_subdirectory(glm)

include(FetchContent)

# In this example we are picking a specific tag.
# You can also pick a specific commit, if you need to.
FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v3.1.0"
)

FetchContent_MakeAvailable(GSL)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set (Sources
    GeometryCalculator.cpp
    Ray.cpp
    Matrix2x2.cpp
    Matrix3x3.cpp
    Matrix4x4.cpp
    Plane.cpp
    Quaternion.cpp
    Vector2.cpp
    Vector3.cpp
    Vector4.cpp
)

set (Includes
    FMath/GeometryCalculator.h
    FMath/Ray.h
    FMath/FMath.h
    FMath/Matrix2x2.h
    FMath/Matrix3x3.h
    FMath/Matrix4x4.h
    FMath/Plane.h
    FMath/Quaternion.h
    FMath/Vector2.h
    FMath/Vector3.h
    FMath/Vector4.h
)

add_library(FMath
    ${Sources}
    ${Includes}
)

target_include_directories(FMath
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE ${GLM_INCLUDE_DIRS}
)

target_link_libraries(FMath
	PRIVATE glm
    PRIVATE GSL
)

# Set targets to have d at end for debug build
set_target_properties(FMath PROPERTIES DEBUG_POSTFIX "d")
# allows to generate proper symlinks for shared libs
set_target_properties(FMath PROPERTIES VERSION ${PROJECT_VERSION})

add_library(FMath::FMath ALIAS FMath)

add_subdirectory(tests)