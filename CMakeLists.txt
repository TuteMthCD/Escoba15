cmake_minimum_required (VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(ESCOBA15)

add_executable(main src/main.cpp)

#target_link_libraries(main m)

add_custom_target(ESCOBA15 ALL
    DEPENDS main
    COMMENT "VAMOOOOOOOOOOOOS PAPA COMPILO"
    COMMAND ./main
    COMMENT "EJECUTANAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANDO"
)
