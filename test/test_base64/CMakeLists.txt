
aux_source_directory("${PROJECT_SOURCE_DIR}/test/test_base64/" DEMO_FILES)
aux_source_directory("${PROJECT_SOURCE_DIR}/3rd/base64/" BASE64_FILES)

add_executable(test_base64 ${DEMO_FILES} ${BASE64_FILES})

target_include_directories(test_base64 PUBLIC "${PROJECT_SOURCE_DIR}/3rd")