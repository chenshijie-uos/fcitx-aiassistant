find_package(Qt5 COMPONENTS Core DBus REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (
    ${PROJECT_BINARY_DIR}
    ${FCITX4_FCITX_UTILS_INCLUDE_DIRS}
    ${FCITX4_FCITX_CONFIG_INCLUDE_DIRS}
    ${FCITX4_FCITX_INCLUDE_DIRS}
    ${LIBINTL_INCLUDE_DIR}
    )

set( fcitx_aiassistant_sources
    eim.cpp
    config.cpp
    bus.cpp
    )

add_definitions( -DLOCALEDIR=\"${CMAKE_INSTALL_PREFIX}/share/locale\" )

fcitx_add_addon_full(aiassistant DESC
SOURCES ${fcitx_aiassistant_sources}
IM_CONFIG aiassistant.conf
LINK_LIBS PkgConfig::DBus ${LIBINTL_LIBRARIES} X11 Xtst
)
