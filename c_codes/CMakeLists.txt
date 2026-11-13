add_library(csv_tools INTERFACE)

target_include_directories(csv_tools INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(csv_tools INTERFACE cxx_std_17)
