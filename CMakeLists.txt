cmake_minimum_required(VERSION 3.15)
project(nuclear)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

unset(ALL_SOURCE_FILES CACHE)
# ищем все файлы с исходным кодом и записываем в переменную ALL_SOURCE_FILES
file(GLOB_RECURSE ALL_SOURCE_FILES 
    "include/**/*.hpp"
)

unset(CLANG_FORMAT_EXE CACHE)
find_program(CLANG_FORMAT_EXE "clang-format")
# если нашли clang-format
if(CLANG_FORMAT_EXE)
    # добавляем таргет "make format", запускающий автоматическое форматирование всех файлов в include
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i --style=file:${CMAKE_CURRENT_SOURCE_DIR}/.clang-format ${ALL_SOURCE_FILES}
        COMMENT "Auto-formatting code..."
    )
else()
    message(WARNING "clang-format not found, can't add \"format\" target")
endif()

enable_testing()

add_subdirectory(tests)