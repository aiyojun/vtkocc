# Learn CMake


## 基础概念

cmake宏macro: 类似于调用函数


## 内置变量

- CMAKE_BINARY_DIR: 编译目录
- CMAKE_SOURCE_DIR: 源码目录
- CMAKE_CURRENT_SOURCE_DIR: 当前CMakeLists.txt所在路径
- CMAKE_CURRENT_LIST_FILE: 输出调用这个变量的CMakeLists.txt的完整路径
- CMAKE_MODULE_PATH: cmake模块搜索路径

```cmake
include(xxx.cmake)  # 对应xxx.cmake文件本身
find_package(xxx)   # 对应Findxxx.cmake文件,xxx大小写保持一致
```

## 隐式变量

由project和enable_language定义

```cmake
project(<PROJECT-NAME> [languageName1 languageName2 ... ] )
# PROJECT-NAME大小写在隐式变量中保持一致
#<PROJECT-NAME>_BINARY_DIR
#<PROJECT-NAME>_DESCRIPTION
#<PROJECT-NAME>_HOMEPAGE_URL
#<PROJECT-NAME>_SOURCE_DIR
#<PROJECT-NAME>_VERSION
#<PROJECT-NAME>_VERSION_MAJOR
#<PROJECT-NAME>_VERSION_MINOR
#<PROJECT-NAME>_VERSION_PATCH
#<PROJECT-NAME>_VERSION_TWEAK
enable_language(<lang> [OPTIONAL] )
#CMAKE_<LANG>_COMPILER
#CMAKE_<LANG>_CPPCHECK
#CMAKE_<LANG>_CPPLINT
#CMAKE_<LANG>_CREATE_SHARED_LIBRARY
#CMAKE_<LANG>_CREATE_SHARED_MODULE
#CMAKE_<LANG>_CREATE_STATIC_LIBRARY
#CMAKE_<LANG>_FLAGS_DEBUG
#CMAKE_<LANG>_FLAGS_RELEASE
#CMAKE_<LANG>_COMPILER_AR

set(CMAKE_C_COMPILER ${XxxPrefix}/gcc)
set(CMAKE_ASM_COMPILER ${XxxPrefix}/gcc)
set(CMAKE_CXX_COMPILER ${XxxPrefix}/g++)
```

## NORMAL变量

```cmake
# 定义
set(<variable> <value>... [PARENT_SCOPE])
# 多个value，variable变量以list形式进行保存
# PARENT_SCOPE: 提升变量作用域到父级
```

## CACHE变量


```cmake
set(<variable> <value>... CACHE <type> <docstring> [FORCE])  
#	<type> <docstring>为必选项
#    <type> 可以被 CMake GUI 用来选择一个窗口。
#    FILEPATH  = 文件选择对话框。
#    PATH        = 路径选择对话框。
#    STRING    = 任意的字符串。
#    BOOL       = 布尔值选择复选框。
#    INTERNAL = 不需要 GUI 输入端。 (适用于永久保存的变量)  
#	<docstring>常用于该变量解释说明一段文字。
#	[FORCE]可选项将覆盖 cache 值，常用于修改cache变量。

#Cache变量作用相当于全局变量，即同一个CMake工程中所有CMakeLists.txt 都可以访问。
#所有的 Cache 变量都会出现在 CMakeCache.txt 文件中。
#option、find_file命令同样可以创建cache变量。
```

## 环境变量

- 读取环境变量：$ENV{NAME}
- 设置环境变量：SET(ENV{变量名} 值)

## 程序访问cmake变量的方法

通过configure_file指令和config.h.in文件实现

```c
// main.c
#include <stdio.h>
int main(int argc, char* argv[]) {
#ifdef ENABLE_HELLO
    printf("%s\n", ENABLE_HELLO);
#endif
    return 0;
}
```

```cmake
# CMakeLists.txt
set(ENABLE_HELLO "Hello World")
configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)
```

```c
// config.h.in
#define ENABLE_HELLO @ENABLE_HELLO@
#cmakedefine USE_MYMATH
```

```c
#define ENABLE_HELLO hello
#define USE_MYMATH
```


## 常用指令

```cmake
#find_系列
list(APPEND VAR_XXX YYY)
add_dependencies(target-name depend-target1 depend-target2 ...) # 声明依赖关系，按依赖关系先后构建项目模块
aux_source_directory(dir VARIABLE) # 用法如下
# ---
aux_source_directory(. SRC_LIST)
add_executable(main ${SRC_LIST})
#file指令
#cmake_path
add_definitions(-DENABLE_DEBUG -DABC) # 用法如下
# ---
##ifdef ENABLE_DEBUG 
#// ...
##endif
```



