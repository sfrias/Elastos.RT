
if("$ENV{XDK_TARGET_PLATFORM}" STREQUAL "ios")
    include(cmake/openssl.cmake)
    include(cmake/icu.cmake)
elseif("$ENV{XDK_TARGET_PLATFORM}" STREQUAL "android")
    include(cmake/ndk-toolchain.cmake)
    include(cmake/icu.cmake)
    include(cmake/openssl.cmake)
endif()

if(NOT ("$ENV{XDK_TARGET_PLATFORM}" STREQUAL "linux" AND "$ENV{XDK_TARGET_CPU_ARCH}" STREQUAL "32"))
    include(cmake/elacarrier.cmake)
endif()
