cmake_minimum_required(VERSION 3.0)
project(Atividade_Multithread VERSION 1.0 LANGUAGES CXX)

# Add the executable target
add_executable(run_library main.cpp includes/classes.hpp includes/constantes.hpp includes/funcoes.hpp)

# Set the include directories for the target
target_include_directories(run_library PRIVATE includes)

# Find the pthread library (required for std::thread)
find_package(Threads REQUIRED)
target_link_libraries(run_library PRIVATE Threads::Threads)

# Copy the txtFiles directory to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/txtFiles DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Install the program and txtFiles directory
install(TARGETS run_library DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/txtFiles DESTINATION share/Atividade_Multithread)

