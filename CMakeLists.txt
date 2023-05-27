cmake_minimum_required(VERSION 3.25)
project(nyc_discord_bot)

set(CMAKE_CXX_STANDARD 23)
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

# Add the 'include' directory to the include file search path
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(nyc_discord_bot src/main.cpp src/command.cpp include/command.h include/command-ping.h src/bot-instance.cpp include/bot-instance.h include/command-about.h include/commands.h include/command-avatar.h)
target_link_libraries(nyc_discord_bot ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY} dpp)
