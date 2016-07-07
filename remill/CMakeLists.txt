
## set (REMILL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/include")
## 
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
## 
## # Disable specific warnings.
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-nested-anon-types")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-extended-offsetof")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-anonymous-struct")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-variadic-macros")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-gnu-zero-variadic-macro-arguments")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-command-line-argument")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-override-module")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type-c-linkage")
## 
## # Features.
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
## 
## # Macros.
## add_definitions(-DREMILL_DIR=${CMAKE_SOURCE_DIR})
## add_definitions(-DREMILL_OS=${CMAKE_SYSTEM_NAME})
## add_definitions(-D__STDC_LIMIT_MACROS)
## add_definitions(-D__STDC_CONSTANT_MACROS)
## add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
## 
## # Includes.
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${REMILL_INCLUDE_DIR}")
## 
## # Output info.
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpie")
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
## 
## set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_SYSTEM_NAME}")


add_subdirectory(Arch)
add_subdirectory(CFG)
