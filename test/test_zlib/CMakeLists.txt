set(DEMO_NAME "test_zlib")

aux_source_directory("${PROJECT_SOURCE_DIR}/src/log/" SRC_FILES)
aux_source_directory("${PROJECT_SOURCE_DIR}/test/${DEMO_NAME}/" DEMO_FILES)

add_executable(${DEMO_NAME} ${DEMO_FILES} ${SRC_FILES})

target_link_libraries(${DEMO_NAME} PUBLIC -lpthread -lz -lcrypto)

target_include_directories(${DEMO_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/3rd/openssl-1.1.0f/include"
    "${PROJECT_SOURCE_DIR}/3rd/zlib-1.2.11/include"
    # "${PROJECT_SOURCE_DIR}/3rd/libzip-1.10.1/include"
    "${PROJECT_SOURCE_DIR}/3rd/spdlog/include"
    )