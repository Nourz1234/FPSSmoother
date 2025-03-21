cmake_minimum_required(VERSION 3.26)

project(FPSSmoother VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# use Win SDK headers instead of MinGW headers
set(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.19041.0\\shared;C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.19041.0\\um")
if($ENV{PLATFORM} STREQUAL "x64")
    set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64")
elseif($ENV{PLATFORM} STREQUAL "x86")
    set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x86")
endif()


add_compile_definitions(_WIN32_WINNT=0x0601) # target windows version
add_compile_definitions(WIN32_LEAN_AND_MEAN) # for a minimal build
add_compile_definitions(UNICODE _UNICODE) # for unicode builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG _DEBUG)
endif()

add_link_options(-static)
add_link_options(-Wl,--enable-stdcall-fixup)

file(GLOB SOURCES
    ${PROJECT_NAME}/*.cpp
    ${PROJECT_NAME}/*.h
)

# PatchJmp lib
add_library(PatchJmp STATIC
    ../PatchJmp/PatchJmp/PatchJmp.h
    ../PatchJmp/PatchJmp/PatchJmp.cpp)


# main lib
add_library(${PROJECT_NAME} STATIC ${SOURCES})



# FakeDxgi
add_library(FakeDxgi SHARED
    FakeDxgi/main.h
    FakeDxgi/main.cpp
    FakeDxgi/dxgi.def
)
target_include_directories(FakeDxgi PRIVATE
    ./
    ../PatchJmp
)
target_link_libraries(FakeDxgi
    ${PROJECT_NAME}
    d3d11
    Pathcch
    PatchJmp
)
set_target_properties(FakeDxgi PROPERTIES PREFIX "") # remove "lib" prefix
set_target_properties(FakeDxgi PROPERTIES OUTPUT_NAME dxgi)
target_link_options(FakeDxgi PRIVATE -Wl,--kill-at)


# FakeD3d11
add_library(FakeD3d11 SHARED
    FakeD3d11/main.h
    FakeD3d11/main.cpp
    FakeD3d11/d3d11.def
)
target_include_directories(FakeD3d11 PRIVATE
    ./
    ../PatchJmp
)
target_link_libraries(FakeD3d11
    ${PROJECT_NAME}
    dxgi
    d3d11
    Shlwapi
    PatchJmp
)
set_target_properties(FakeD3d11 PROPERTIES PREFIX "") # remove "lib" prefix
set_target_properties(FakeD3d11 PROPERTIES OUTPUT_NAME d3d11)
target_link_options(FakeD3d11 PRIVATE -Wl,--kill-at)

