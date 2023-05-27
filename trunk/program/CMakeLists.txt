cmake_minimum_required(VERSION 3.4)

project(Program)

# Note that for MinGW users the order of libs is important!
find_package(wxWidgets COMPONENTS core base)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
endif()

#specify set of project's source files
set(SOURCE_FILES
        src/main.cpp ../library/src/Board.cpp ../library/include/Board.h ../library/src/SnakeWindow.cpp ../library/include/SnakeWindow.h)
#add following files to executable file 'Program'
add_executable(Program ${SOURCE_FILES})

#add libraries from 'Library' project
target_link_libraries(Program Library ${wxWidgets_LIBRARIES})

#add header files from 'include' directory of main project
target_include_directories(Program PUBLIC
        include
        ${wxWidgets_INCLUDE_DIRS})

