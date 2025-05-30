cmake_minimum_required(VERSION 3.16)

project(GammaCorrector VERSION 1.4.2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS DataVisualization Graphs Widgets)

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src)
set(ICONS_ROOT icons)
file(GLOB SOURCES ${SRC_ROOT}/*.cpp ${SRC_ROOT}/*/*.cpp ${SRC_ROOT}/*/*/*.cpp ${SRC_ROOT}/*/*/*/*.cpp)
file(GLOB HEADERS ${SRC_ROOT}/*.h ${SRC_ROOT}/*/*.h ${SRC_ROOT}/*/*/*.h ${SRC_ROOT}/*/*/*/*.h)

set(RESOURCES ${PROJECT_SOURCE_DIR}/resources.rc)
qt_add_executable(${PROJECT_NAME}
  WIN32
  MANUAL_FINALIZATION
  ${SOURCES}
  ${HEADERS}
  ${RESOURCES}
)
qt_add_resources(${PROJECT_NAME} "icons"
  PREFIX "/"
  FILES
    ${ICONS_ROOT}/about.png
    ${ICONS_ROOT}/cascade.png
    ${ICONS_ROOT}/close_all_windows.png
    ${ICONS_ROOT}/close_table.png
    ${ICONS_ROOT}/exit.png
    ${ICONS_ROOT}/find_offset.png
    ${ICONS_ROOT}/github.png
    ${ICONS_ROOT}/main_icon.png
    ${ICONS_ROOT}/next_sub_window.png
    ${ICONS_ROOT}/open.png
    ${ICONS_ROOT}/previous_sub_window.png
    ${ICONS_ROOT}/Q.png
    ${ICONS_ROOT}/Qt.png
    ${ICONS_ROOT}/save.png
    ${ICONS_ROOT}/settings.png
    ${ICONS_ROOT}/substract_line.png
    ${ICONS_ROOT}/table.png
    ${ICONS_ROOT}/tile.png
)
string(TIMESTAMP DATE "%Y.%m.%d")
target_compile_definitions(${PROJECT_NAME} PRIVATE
  QT
  PROGRAMM_VERSION="${CMAKE_PROJECT_VERSION}"
  PROGRAMM_NAME="Gamma corrector"
  PROGRAMM_DATE="${DATE}"
)
target_include_directories(${PROJECT_NAME} PRIVATE
  ${SRC_ROOT}
  ${SRC_ROOT}/data
  ${SRC_ROOT}/ui
  ${SRC_ROOT}/widgets
  ${SRC_ROOT}/widgets/approximate_plot_window
  ${SRC_ROOT}/widgets/main_window
  ${SRC_ROOT}/widgets/main_window/mdi_area
  ${SRC_ROOT}/widgets/main_window/menu_bar
  ${SRC_ROOT}/widgets/main_window/status_bar
  ${SRC_ROOT}/widgets/plot
  ${SRC_ROOT}/widgets/plot_3d
  ${SRC_ROOT}/widgets/table_widget
  ${SRC_ROOT}/widgets/temperature_plot_window
)

set(QWT_LIBRARY_NAME qwt)
add_library(${QWT_LIBRARY_NAME} SHARED IMPORTED)
set(QWT_ROOT ${PROJECT_SOURCE_DIR}/lib/qwt-6.3.0)
set_property(TARGET ${QWT_LIBRARY_NAME} PROPERTY IMPORTED_LOCATION ${QWT_ROOT}/lib/qwt.dll)
set_property(TARGET ${QWT_LIBRARY_NAME} PROPERTY IMPORTED_IMPLIB ${QWT_ROOT}/lib/qwt.dll)
target_include_directories(${PROJECT_NAME} PRIVATE ${QWT_ROOT}/include)

add_subdirectory(lib/csv/)
add_subdirectory(lib/lsa/)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt6::DataVisualization
  Qt6::Graphs
  Qt6::Widgets
  csv
  lsa
  qwt
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(GammaTransformer)
endif()
