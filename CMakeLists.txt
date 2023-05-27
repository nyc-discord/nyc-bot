cmake_minimum_required(VERSION 3.25)
project(nyc_discord_bot)

set(CMAKE_CXX_STANDARD 23)
set(OPEN_SSL_HEADER_ROOT_DIR "/nix/store/6zyv2ff4f4bsa5vbn4ylimnzzisak8ga-openssl-3.0.7-dev/include/")
set(OPENSSL_ROOT_DIR "/nix/store/in8nxwr1sjnncxzrqnprxlaxvfpvd5aq-openssl-3.0.7")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib")
set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.dylib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_ROOT_DIR})
include_directories(${OPEN_SSL_HEADER_ROOT_DIR})

include(FetchContent)
FetchContent_Declare(
        dpp
        GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
        GIT_TAG master
        BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/lib/libext.so
)
FetchContent_MakeAvailable(dpp)

add_executable(nyc_discord_bot main.cpp)
target_link_libraries(nyc_discord_bot ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY} dpp)
