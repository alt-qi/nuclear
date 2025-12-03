
# если нашли clang-format
if(CLANG_FORMAT_EXE)
    if(ALL_SOURCE_FILES)  # сделал этот if для случаев когда папка include пустая (лол)
        # добавляем тест, который запустит clang-format, разом провяеряющий файлы из ALL_SOURCE_FILES
        add_test(NAME check_formatting
            COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror --style=file:${CMAKE_CURRENT_SOURCE_DIR}/../.clang-format ${ALL_SOURCE_FILES}
        )
    endif()
else()
    # если не нашли clang-format, то бросаем ошибку
    message(FATAL_ERROR "clang-format not found! can't run formatting checks")
endif()

# дальше настройки для юнит-тестов

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  tests
  unittests/sem2/fenwick_tree/test_2d.cc
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
