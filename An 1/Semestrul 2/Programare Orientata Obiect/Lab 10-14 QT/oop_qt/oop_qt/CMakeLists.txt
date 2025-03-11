cmake_minimum_required(VERSION 3.28)
project(oop_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED
)

add_executable(oop_qt main.cpp
        gui/locatarGUI.h
        validators/exception.h
        domain/locatar.cpp
        repository/locatar_repo.cpp
        service/locatar_service.cpp
        teste/teste.cpp
        teste/teste.h
        utils/undo.cpp
        validators/validator.cpp
        gui/notificariGUI.h
        utils/observer.h
        gui/CosReadOnlyGUI.h
        gui/LocatarTableModel.h
)

target_link_libraries(oop_qt
        Qt::Core
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    set(IMAGE_FORMATS_DIR "${QT_INSTALL_PATH}/plugins/imageformats")
    if (EXISTS "${IMAGE_FORMATS_DIR}")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/")
        file(GLOB IMAGE_FORMAT_FILES "${IMAGE_FORMATS_DIR}/*")
        foreach (IMAGE_FORMAT_FILE ${IMAGE_FORMAT_FILES})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${IMAGE_FORMAT_FILE}"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/")
        endforeach()
    endif ()
endif ()