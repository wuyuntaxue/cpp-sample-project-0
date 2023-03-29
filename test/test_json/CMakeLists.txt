set(DEMO_NAME "test_json")

aux_source_directory("${PROJECT_SOURCE_DIR}/test/${DEMO_NAME}/" DEMO_FILES)

add_executable(${DEMO_NAME} ${DEMO_FILES})

target_include_directories(${DEMO_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/3rd")