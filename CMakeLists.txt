cmake_minimum_required(VERSION 3.24)

project(NakedNPCFixF4 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force static triplet to avoid spdlog.dll / fmt.dll dependency errors
if(NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "x64-windows-static-md" CACHE STRING "")
endif()

include(FetchContent)

# Fetch CommonLibF4 — SOURCE_SUBDIR ile sadece CommonLibF4 alt dizinini ekle,
# AddressLibGen ve diğer araçlar atlanır (srell gerektirmez)
FetchContent_Declare(
    CommonLibF4
    GIT_REPOSITORY https://github.com/Ryan-rsm-McKenzie/CommonLibF4.git
    SOURCE_SUBDIR CommonLibF4
)
FetchContent_MakeAvailable(CommonLibF4)

find_package(spdlog REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} 
    PRIVATE 
        src/main.cpp
        src/VisibilityFixer.cpp
        src/VisibilityFixer.h
        src/Settings.h
        src/PCH.h
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        CommonLibF4::CommonLibF4
        spdlog::spdlog
        fmt::fmt
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        PROJECT_NAME="${PROJECT_NAME}"
)

set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP /Zm200)
endif()
