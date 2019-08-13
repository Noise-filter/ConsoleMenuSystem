set(INCLUDE_DIR include)
set(SRC_DIR src)

set(SOURCES
    ${SRC_DIR}/Timer.cpp 
    ${SRC_DIR}/main.cpp)

set(HEADERS
    ${INCLUDE_DIR}/Test.h 
    ${INCLUDE_DIR}/Timer.h)

add_executable(TestProject ${SOURCES} ${HEADERS})
target_compile_features(TestProject PUBLIC cxx_std_17)
target_include_directories(TestProject PRIVATE include src)
target_link_libraries(TestProject PUBLIC MenuSystem)

add_custom_command(
  TARGET TestProject POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/json 
    ${CMAKE_CURRENT_BINARY_DIR}/json)
	
add_custom_command(
  TARGET TestProject POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/json 
    $<TARGET_FILE_DIR:TestProject>/json)