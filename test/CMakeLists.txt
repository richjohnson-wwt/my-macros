# Include Catch2
find_package(Catch2 REQUIRED)
find_package(fakeit REQUIRED)
find_package(cli11 REQUIRED)
find_package(spdlog REQUIRED)
find_package(SQLiteCpp REQUIRED)

# Get all test files
file(GLOB TEST_FILES "*.cpp")

# Get all src files
file(GLOB SRC_FILES "../src/view-model/*.cpp")

# Exclude main.cpp from the test source files
list(FILTER SRC_FILES EXCLUDE REGEX "main\\.cpp$")

# For each test file
foreach(TEST_FILE ${TEST_FILES})
    # Get the filename without extension
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Add executable
    add_executable(${TEST_NAME} ${TEST_FILE} ${SRC_FILES})

    # Link with Catch2
    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain SQLiteCpp spdlog::spdlog CLI11::CLI11 recipe-macros)

    # Add it to the test suite and include the build dir a working director
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endforeach()
