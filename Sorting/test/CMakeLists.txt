set(TEST_SOURCES test.cpp)

add_executable(${CMAKE_PROJECT_NAME}.test ${TEST_SOURCES})

add_test(NAME ${CMAKE_PROJECT_NAME}.test COMMAND ${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME}.test PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest_main gtest gmock pthread)