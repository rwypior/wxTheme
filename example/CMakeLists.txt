cmake_minimum_required (VERSION 3.26)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_definitions(-DUNICODE -D_UNICODE)

if("${WXT_PLATFORM}" STREQUAL "windows")
    message("Configuring for Windows platform")
    SET(OPTIONS WIN32)
endif()

project ("wxThemeExample")
add_executable(wxThemeExample ${OPTIONS} "main.cpp" "wxtexample.h" "wxtexample.cpp" "wxtexamplemainwindow.h" "wxtexamplemainwindow.cpp")

set_property(TARGET wxThemeExample PROPERTY CXX_STANDARD 17)

find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base html propgrid xml aui)
find_package(wxTheme CONFIG REQUIRED)

target_link_libraries(wxThemeExample PUBLIC wxTheme)
target_link_libraries(wxThemeExample PUBLIC wx::core wx::base wx::html wx::propgrid wx::xml wx::aui)

# Patch generated sources
execute_process(COMMAND ${CMAKE_COMMAND} -DTARGET_FILE=${CMAKE_CURRENT_SOURCE_DIR}/wxtexample.cpp -P${WXT_PATCH_FBP})

# Copy DLLs to exe directory
add_custom_command(TARGET wxThemeExample POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:wxThemeExample> $<TARGET_RUNTIME_DLLS:wxThemeExample>
  COMMAND_EXPAND_LISTS
)

# Copy resources
add_custom_command(
  TARGET wxThemeExample POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_SOURCE_DIR}/themes" "${PROJECT_BINARY_DIR}/themes"
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_SOURCE_DIR}/lang" "${PROJECT_BINARY_DIR}/lang"
)