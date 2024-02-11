cmake_minimum_required (VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ESCOBA15)

add_executable(main src/main.cpp)

#target_link_libraries(main m)

add_custom_target(ESCOBA15 ALL
    DEPENDS main
    COMMAND ./main
    COMMENT "VAMOOOOOOOOOOOOS PAPA COMPILO"
    COMMENT "EJECUTANAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANDO"
)
