cmake_minimum_required(VERSION 3.16)

project(GammaTransformer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    main.cpp
    mainwindow.h mainwindow.cpp
    tablewidget.h tablewidget.cpp
    mainwindow_ui.h mainwindow_ui.cpp
    utils.h utils.cpp
)

add_subdirectory(lib/Csv/)
add_subdirectory(lib/LeastSquaresApproximation/)
add_subdirectory(lib/Matrix/)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    csv
    lsa
    matrix
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
