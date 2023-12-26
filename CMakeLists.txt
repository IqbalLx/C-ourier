cmake_minimum_required(VERSION 3.0)

project(C-ourier C)

# Include directories for header files
include_directories(includes)

# Set source
set(
    AUTH
    src/auth/auth.data.c 
    src/auth/auth.service.c
)

# Add the executable
add_executable(migrator src/migrator/migrator.c src/helper/helper.c)
add_executable(seeder src/migrator/seeder.c src/helper/helper.c)
add_executable(main ${AUTH} src/helper/helper.c src/main.c)
