cmake_minimum_required(VERSION 3.16)
project(matrix_calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 在项目开始就设置编译选项
if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-fpermissive -Wall)
    # 为所有目标设置编译选项
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# 源文件
set(SOURCES
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
    src/ui/OperationWidget.cpp
    src/ui/OperationWidget.h
    src/ui/BoardWidget.cpp
    src/ui/BoardWidget.h
    src/core/Matrix.cpp
    src/core/Matrix.h
    src/core/Entry.cpp
    src/core/Entry.h
    src/core/EntryPolynomial.cpp
    src/core/EntryPolynomial.h
    src/main.cpp
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Windows特定设置
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
 