file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp") 

add_library(GraphicsForUI ${SRCS})

target_include_directories(GraphicsForUI PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(GraphicsForUI PUBLIC SFML::Graphics)
target_compile_features(GraphicsForUI PRIVATE cxx_std_17)