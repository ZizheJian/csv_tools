add_library(libcsv INTERFACE)

target_include_directories(libcsv INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS libcsv DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    DESTINATION include 
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.tpp"
)