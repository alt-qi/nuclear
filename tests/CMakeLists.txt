
unset(CLANG_FORMAT_EXE CACHE)
find_program(CLANG_FORMAT_EXE "clang-format")
find_program(CLANG_TIDY_EXE "clang-tidy")

# если нашли clang-format
if(CLANG_FORMAT_EXE)
    # ищем все файлы с исходным кодом и записываем в переменную ALL_SOURCE_FILES
    file(GLOB_RECURSE ALL_SOURCE_FILES 
        "../include/**/*.hpp"
    )

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

# если нашли clang-format
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
else()
    # если не нашли clang-format, то бросаем ошибку
    message(FATAL_ERROR "clang-tidy not found! can't run formatting checks")
endif()
