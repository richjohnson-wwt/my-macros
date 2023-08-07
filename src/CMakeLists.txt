
set (WxSRCS "WxApp.cpp" "MyFrame.cpp" "MyMacroApp.cpp")
file (GLOB SOURCES "model/*.cpp" "model/db/*.cpp" "model/food/*.cpp" "model/fatsecret/*.cpp" "model/recipe/*.cpp" "view/*.cpp" "presenter/*.cpp")

find_package(wxWidgets COMPONENTS aui adv core base REQUIRED)
find_package(cli11 REQUIRED)
find_package(spdlog REQUIRED)
find_package(SQLiteCpp REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(my-macros ${WxSRCS} ${SOURCES})

target_link_libraries(my-macros ${wxWidgets_LIBRARIES} spdlog::spdlog CLI11::CLI11 SQLiteCpp nlohmann_json::nlohmann_json )
