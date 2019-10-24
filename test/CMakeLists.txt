add_executable(
    build-test
    build-test.cxx
)

target_link_libraries(
    build-test
    avrcpp
)

add_executable(
    testing-framework
    testing-framework.cxx
)

target_link_libraries(
    testing-framework
    avrcpp
)
