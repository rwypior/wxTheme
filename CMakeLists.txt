cmake_minimum_required (VERSION 3.26)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_definitions(-DUNICODE -D_UNICODE)

project ("wxTheme")
add_library(wxTheme)
add_library(wxTheme::wxTheme ALIAS wxTheme)

if(WXT_PLATFORM STREQUAL "windows")
    set(WXT_WINDOWS 1)
elseif(WXT_PLATFORM STREQUAL "linux")
    set(WXT_LINUX 1)
endif()
set_property(TARGET wxTheme PROPERTY CXX_STANDARD 17)

configure_file("cmake/wxt.h.in" "include/wxt/wxt.h" @ONLY)

target_include_directories (wxTheme PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_subdirectory("include/wxt")
add_subdirectory("src")
add_subdirectory("example")

find_package(wxWidgets CONFIG REQUIRED COMPONENTS core base html)

target_link_libraries(wxTheme PUBLIC wx::core wx::base)

if("${WXT_PLATFORM}" STREQUAL "windows")
    target_link_libraries(wxTheme PRIVATE "dwmapi.lib")
endif()

# Install

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(ConfigPackageLocation lib/cmake/wxTheme)

configure_package_config_file(
        cmake/wxThemeConfig.cmake.in
	    "${CMAKE_CURRENT_BINARY_DIR}/wxTheme/wxThemeConfig.cmake"
	    INSTALL_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/wxTheme"
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/wxTheme/wxThemeConfigVersion.cmake"
        VERSION 1.0.0
        COMPATIBILITY AnyNewerVersion
)

install(
        TARGETS wxTheme EXPORT wxThemeTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
        DIRECTORY "include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(EXPORT wxThemeTargets
        FILE wxThemeTargets.cmake
        NAMESPACE wxTheme::
        DESTINATION ${ConfigPackageLocation}
)

install(FILES 
            "${CMAKE_CURRENT_BINARY_DIR}/wxTheme/wxThemeConfig.cmake" 
            "${CMAKE_CURRENT_BINARY_DIR}/wxTheme/wxThemeConfigVersion.cmake"
        DESTINATION ${ConfigPackageLocation}
)

export(PACKAGE wxTheme)