find_package(Python COMPONENTS Interpreter)


if ("${CAVANSITE_ADD_BREEZE}" STREQUAL "all")
    set(CAVANSITE_ADD_BREEZE "red,yellow,orange,green,cyan,blue,purple,pink,mono")
endif()
message(STATUS "Using themes: ${CAVANSITE_ADD_BREEZE}")

# define used vars + transform for adding
string(REPLACE "," ";" BREEZE_THEME_LIST "${CAVANSITE_ADD_BREEZE}")
set(BREEZE_MACROS "")
set(BREEZE_SCRIPT_THEMES_LIST "")
foreach(BREEZE_THEME ${BREEZE_THEME_LIST})
    string(REPLACE "-" "_" BREEZE_THEME_TEMP ${BREEZE_THEME})

    string(TOUPPER "${BREEZE_THEME_TEMP}" BREEZE_THEME_UPPER_SNAKE)

    list(APPEND BREEZE_MACROS "CAVANSITE_BREEZE_THEME_${BREEZE_THEME_UPPER_SNAKE}")
    list(APPEND BREEZE_SCRIPT_THEMES_LIST
        "light-${BREEZE_THEME}" "dark-${BREEZE_THEME}"
        "light-${BREEZE_THEME}-alt" "dark-${BREEZE_THEME}-alt"
    )
endforeach()
target_compile_definitions(${PROJECT_NAME} PUBLIC ${BREEZE_MACROS})

list(JOIN BREEZE_SCRIPT_THEMES_LIST "," BREEZE_SCRIPT_THEMES)


message(STATUS "Setting up Breeze themes")

set(BREEZE_OUT_DIR "${CMAKE_BINARY_DIR}/breeze-generated-themes/dist")
set(BREEZE_QRC "${BREEZE_OUT_DIR}/breeze.qrc")
file(REMOVE_RECURSE ${BREEZE_OUT_DIR})

add_custom_command(
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${BREEZE_OUT_DIR}"
    COMMAND ${Python_EXECUTABLE} configure.py --extensions=all --styles=${BREEZE_SCRIPT_THEMES} --resource breeze.qrc --output-dir=${BREEZE_OUT_DIR}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/breeze"
    OUTPUT "${BREEZE_QRC}"
    VERBATIM
    COMMENT "Generating Breeze themes"
)
set_source_files_properties("${BREEZE_QRC}" PROPERTIES GENERATED TRUE)

qt_add_resources(BREEZE_SOURCES ${BREEZE_QRC})
add_library(breeze STATIC ${BREEZE_SOURCES})
# qt tries to build qrc during generation i think
set_target_properties(breeze PROPERTIES
    AUTOMOC OFF
    AUTORCC OFF
)

target_link_libraries(${PROJECT_NAME} PUBLIC breeze)
target_compile_definitions(${PROJECT_NAME} PUBLIC CAVANSITE_ADD_BREEZE)

# mode svgs
target_sources(${PROJECT_NAME} PUBLIC resources/breeze/qresource.qrc)