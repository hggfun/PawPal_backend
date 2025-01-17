cmake_minimum_required(VERSION 3.12)
project(UserverBackendTest CXX)

# Disable userver libraries that are not needed in this project
set(USERVER_FEATURE_MONGODB OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_REDIS OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_CLICKHOUSE OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_GRPC OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_RABBITMQ OFF CACHE BOOL "" FORCE)

# Compatibility mode: some systems don't support these features
set(USERVER_FEATURE_CRYPTOPP_BLAKE2 OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_GRPC_CHANNELZ OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_REDIS_HI_MALLOC ON CACHE BOOL "" FORCE)


# Adding userver dependency
include(third_party/userver/cmake/SetupEnvironment.cmake)
include(GNUInstallDirs)
add_subdirectory(third_party/userver)


# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
    src/hello.hpp
    src/hello.cpp
    src/views/test/test.hpp
    src/views/test/test.cpp
    src/views/profile/create_profile/post/view.hpp
    src/views/profile/create_profile/post/view.cpp
    src/views/profile/get_profile/post/view.hpp
    src/views/profile/get_profile/post/view.cpp
    src/views/profile/delete_profile/post/view.hpp
    src/views/profile/delete_profile/post/view.cpp
    src/controllers/profile_controllers/profile_controllers.hpp
    src/controllers/profile_controllers/profile_controllers.cpp
    src/views/advertisement/create_advertisement/post/view.hpp
    src/views/advertisement/create_advertisement/post/view.cpp
    src/views/advertisement/read_advertisement/post/view.hpp
    src/views/advertisement/read_advertisement/post/view.cpp
    src/views/advertisement/delete_advertisement/post/view.hpp
    src/views/advertisement/delete_advertisement/post/view.cpp
    src/controllers/adv_controllers/adv_controllers.hpp
    src/controllers/adv_controllers/adv_controllers.cpp
    src/views/post/create_post/post/view.hpp
    src/views/post/create_post/post/view.cpp
    src/views/post/read_post/post/view.hpp
    src/views/post/read_post/post/view.cpp
    src/views/post/read_list_of_posts/post/view.hpp
    src/views/post/read_list_of_posts/post/view.cpp
    src/views/post/delete_post/post/view.hpp
    src/views/post/delete_post/post/view.cpp
    src/controllers/post_controllers/post_controllers.hpp
    src/controllers/post_controllers/post_controllers.cpp
)
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver-postgresql)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
add_executable(${PROJECT_NAME}_unittest
    src/hello_test.cpp
)
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME}_objs userver-utest)
add_google_tests(${PROJECT_NAME}_unittest)


# Benchmarks
add_executable(${PROJECT_NAME}_benchmark
    src/hello_benchmark.cpp
)
target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME}_objs userver-ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)


# Functional Tests
include(UserverTestsuite)

userver_testsuite_add_simple()


# Install
if(DEFINED ENV{PREFIX})
  message(STATUS "Set install prefix: $ENV{PREFIX}")
  file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
  set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif()

file(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})
