include(FindPkgConfig)

pkg_check_modules(BASE "base-types")
include_directories(${BASE_INCLUDE_DIRS})
link_directories(${BASE_LIBRARY_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${BASE_LIBRARIES})

pkg_check_modules(BASE_LIB "base-lib")
include_directories(${BASE_LIB_INCLUDE_DIRS})
link_directories(${BASE_LIB_LIBRARY_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${BASE_LIB_LIBRARIES})

pkg_check_modules(YAML "yaml-cpp")
include_directories(${YAML_INCLUDE_DIRS})
link_directories(${YAML_LIBRARY_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${YAML_LIBRARIES})

find_package(OpenSceneGraph REQUIRED osgManipulator osgViewer osgFX)
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
link_directories(${OPENSCENEGRAPH_LIBRARY_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${OPENSCENEGRAPH_LIBRARIES})

find_package(Qt4 4.5 REQUIRED QtOpenGL)
add_definitions(${QT_DEFINITIONS})
include_directories(${QT_INCLUDE_DIR})
include_directories(${QT_QTCORE_INCLUDE_DIR})
include_directories(${QT_QTGUI_INCLUDE_DIR})
set(QT_USE_OPENGL TRUE)
include(${QT_USE_FILE})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${QT_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${Boost_LIBRARIES})
