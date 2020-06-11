cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(FMath VERSION 1.0)

find_package( glm REQUIRED )

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
)

target_link_libraries(FMath
    PRIVATE glm)

# Set targets to have d at end for debug build
set_target_properties(FMath PROPERTIES DEBUG_POSTFIX "d")
# allows to generate proper symlinks for shared libs
set_target_properties(FMath PROPERTIES VERSION ${PROJECT_VERSION})

# Installing
include(GNUInstallDirs)

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS FMath
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

install(
    DIRECTORY "FMath"
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.h"
)

# # Export headers:
# None for this project
# #   * ${CMAKE_CURRENT_BINARY_DIR}/fooer_export.h -> <prefix>/include/fooer_export.h
# install(
#     FILES
#         "${CMAKE_CURRENT_BINARY_DIR}/fooer_export.h"
#     DESTINATION "${include_install_dir}"
# )

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

add_library(FMath::FMath ALIAS FMath)