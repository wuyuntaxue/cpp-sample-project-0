set(DEMO_NAME "test_jemalloc")

aux_source_directory("${PROJECT_SOURCE_DIR}/test/${DEMO_NAME}/" DEMO_FILES)

add_executable(${DEMO_NAME} ${DEMO_FILES})

#链接库
target_link_libraries(${DEMO_NAME} PUBLIC -ljemalloc)

target_include_directories(${DEMO_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/3rd/jemalloc/include")