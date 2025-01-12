# Copyright (c) 2024-present, Qihoo, Inc.  All rights reserved.
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

INCLUDE(ExternalProject)

SET(SNAPPY_SOURCES_DIR ${THIRD_PARTY_PATH}/snappy)
SET(SNAPPY_INSTALL_DIR ${THIRD_PARTY_PATH}/install/snappy)
SET(SNAPPY_INCLUDE_DIR "${SNAPPY_INSTALL_DIR}/include" CACHE PATH "snappy include directory." FORCE)
SET(SNAPPY_LIBRARIES "${SNAPPY_INSTALL_DIR}/lib/libsnappy.a" CACHE FILEPATH "snappy library." FORCE)

SET(prefix_path "${CMAKE_CURRENT_BINARY_DIR}/_deps/gflags-build")

ExternalProject_Add(
        extern_snappy
        ${EXTERNAL_PROJECT_LOG_ARGS}
        DEPENDS gflags
        GIT_REPOSITORY "https://github.com/google/snappy.git"
        GIT_TAG "1.2.1"
        PREFIX ${SNAPPY_SOURCES_DIR}
        UPDATE_COMMAND ""
        CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
        -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}
        -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
        -DCMAKE_INSTALL_PREFIX=${SNAPPY_INSTALL_DIR}
        -DCMAKE_INSTALL_LIBDIR=${SNAPPY_INSTALL_DIR}/lib
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
        -DSNAPPY_BUILD_TESTS=OFF
        -DCMAKE_BUILD_TYPE=${THIRD_PARTY_BUILD_TYPE}
        -DCMAKE_PREFIX_PATH=${prefix_path}
        ${EXTERNAL_OPTIONAL_ARGS}
        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${SNAPPY_INSTALL_DIR}
        -DCMAKE_INSTALL_LIBDIR:PATH=${SNAPPY_INSTALL_DIR}/lib
        -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
        -DCMAKE_BUILD_TYPE:STRING=${THIRD_PARTY_BUILD_TYPE}
)

ADD_DEPENDENCIES(extern_snappy gflags)
ADD_LIBRARY(snappy STATIC IMPORTED GLOBAL)
SET_PROPERTY(TARGET snappy PROPERTY IMPORTED_LOCATION ${SNAPPY_LIBRARIES})
ADD_DEPENDENCIES(snappy extern_snappy)