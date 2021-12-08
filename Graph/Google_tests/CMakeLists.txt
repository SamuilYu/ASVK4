cmake_minimum_required(VERSION 3.10)

project(Gtests)

include(CheckCXXCompilerFlag)

find_package(GTest REQUIRED)


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(
    ${GTEST_INCLUDE_DIRS}
)
function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

enable_cxx_compiler_flag_if_supported("-Wno-error=deprecated-copy")

file(GLOB SOURCES *.cpp ../Graphs/*.cpp ../Arithmetic/*.cpp ../Graphs/*.h ../Arithmetic/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} gtest gtest_main)