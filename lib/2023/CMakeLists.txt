add_library(aoc_2023 STATIC
        aoc_2023.cpp aoc_2023.h
        day01.cpp day01.h
)

target_link_libraries(aoc_2023 PUBLIC file_utils)