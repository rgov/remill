
include_directories(${CMAKE_SOURCE_DIR})



set (SEMANTICS_SOURCES
      Instructions.cpp
      BasicBlock.cpp
)


macro (build_semantics width avx avx512)

  set(PREVIOUS_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -x c++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${CMAKE_SOURCE_DIR}/third_party/include")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g0 -fno-exceptions -fno-rtti -m${width} -mtune=generic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections -fno-asynchronous-unwind-tables")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-return-type-c-linkage -fno-builtin")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DADDRESS_SIZE_BITS=${width} -DHAS_FEATURES_AVX=${avx} -DHAS_FEATURE_AVX512=${avx512}")

  set (target Semantics${width})

  if (${avx} EQUAL "1")
    set (target ${target}_avx)
  endif()

  if (${avx512} EQUAL "1")
    set (target ${target}_avx512)
  endif()

  add_bitcode(${target} ${SEMANTICS_SOURCES})

  set (CMAKE_CXX_FLAGS ${PREVIOUS_CMAKE_CXX_FLAGS})
endmacro (build_semantics)


foreach (width 32 64)
  foreach (has_avx 0 1)
    foreach (has_avx_512 0 1)

      build_semantics ("${width}" "${has_avx}" "${has_avx_512}")

    endforeach ()
  endforeach ()
endforeach ()

