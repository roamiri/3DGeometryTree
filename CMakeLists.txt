cmake_minimum_required(VERSION 2.8.3)
set(PRJ_NAME pytree)
project(${PRJ_NAME})
FIND_PACKAGE(PythonInterp)

if (PYTHONINTERP_FOUND)
  if (PYTHON_VERSION_MAJOR EQUAL 3)
        FIND_PACKAGE(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX})
        FIND_PACKAGE(PythonInterp 3)
        FIND_PACKAGE(PythonLibs 3 REQUIRED)
    else()
        FIND_PACKAGE(Boost COMPONENTS python)
        FIND_PACKAGE(PythonInterp)
        FIND_PACKAGE(PythonLibs REQUIRED)
    endif()
else()
    message("Python not found")
endif()

message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")

ENABLE_TESTING()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

include_directories("./core")
# set(CORE 
# ${CMAKE_SOURCE_DIR}/core/node.cpp
# ${CMAKE_SOURCE_DIR}/core/trx.cpp
# ${CMAKE_SOURCE_DIR}/core/container.cpp
# )

# PYTHON_ADD_MODULE(hello main.cpp)
add_library(${PRJ_NAME} SHARED pylib.cpp)
 
target_link_libraries(${PRJ_NAME} -lboost_python38 ${PYTHON_LIBRARIES})
 # Tweaks the name of the library to match what Python expects
  set_target_properties(${PRJ_NAME} PROPERTIES SUFFIX .so)
  set_target_properties(${PRJ_NAME} PROPERTIES PREFIX "")
