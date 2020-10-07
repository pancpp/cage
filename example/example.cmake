# COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
# 
# @author Leyuan Pan
# @date Jun 01, 2018
# 
macro(add_cage_example TEST_TARGET TEST_SRCS)
    add_executable(${TEST_TARGET} ${TEST_SRCS})
    target_link_libraries(${TEST_TARGET} PUBLIC cage)
endmacro()

# Add testings
add_cage_example(rest_api_server "${CMAKE_CURRENT_LIST_DIR}/rest_api_server.cpp")
