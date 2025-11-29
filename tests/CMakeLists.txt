
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
