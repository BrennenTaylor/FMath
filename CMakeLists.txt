cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(FMath VERSION 1.0)

# C++ language configuration boilerplate
if (NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET AND
    NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
endif ()

# Let SomeLib_SHARED_LIBS override BUILD_SHARED_LIBS
if (DEFINED FMath_SHARED_LIBS)
    set(BUILD_SHARED_LIBS "${FMath_SHARED_LIBS}")
endif ()

include(FetchContent)

FetchContent_Declare(GLM
    GIT_REPOSITORY "https://github.com/g-truc/glm"
)

FetchContent_MakeAvailable(GLM)

# In this example we are picking a specific tag.
# You can also pick a specific commit, if you need to.
FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v3.1.0"
)

FetchContent_MakeAvailable(GSL)

add_library(FMath    
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

add_library(FMath::FMath ALIAS FMath)

set_target_properties(FMath PROPERTIES
    VERSION ${FMath_VERSION}
    SOVERSION ${FMath_VERSION_MAJOR}
)

target_include_directories(FMath
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE ${GLM_INCLUDE_DIRS}
)

target_link_libraries(FMath
	PRIVATE glm
    PRIVATE GSL
)

target_compile_features(FMath PUBLIC cxx_std_17)

# Set targets to have d at end for debug build
set_target_properties(FMath PROPERTIES DEBUG_POSTFIX "d")
# allows to generate proper symlinks for shared libs
set_target_properties(FMath PROPERTIES VERSION ${PROJECT_VERSION})

# Generate the export header for FMath and attach it to the target
include(GenerateExportHeader)
generate_export_header(FMath EXPORT_FILE_NAME FMath/export.h)
target_compile_definitions(
    FMath PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:FMath_STATIC_DEFINE>")
target_include_directories(
    FMath PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/>"
)

enable_testing()
add_subdirectory(tests)