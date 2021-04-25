add_executable(SHA-256_Hash main.cpp)

target_link_libraries(SHA-256_Hash SHA-256_Lib)

target_include_directories(SHA-256_Hash PUBLIC ${CMAKE_SOURCE_DIR}/lib)
