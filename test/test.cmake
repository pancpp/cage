# COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
# 
# @author Leyuan Pan
# @date Jun 01, 2018
# 
macro(add_cage_test TEST_TARGET TEST_SRCS)
    add_executable(${TEST_TARGET} ${TEST_SRCS})
    target_link_libraries(${TEST_TARGET} PUBLIC cage)
endmacro()

# Add testings
add_cage_test(test_cage_http "${CMAKE_CURRENT_LIST_DIR}/test_cage_http.cpp")
