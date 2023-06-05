set(DEMO_NAME "test_protobuf")

aux_source_directory("${PROJECT_SOURCE_DIR}/src/log/" SRC_FILES)
aux_source_directory("${PROJECT_SOURCE_DIR}/test/${DEMO_NAME}/" DEMO_FILES)
aux_source_directory("${PROJECT_SOURCE_DIR}/test/${DEMO_NAME}/hello/" DEMO_FILES)

add_executable(${DEMO_NAME} ${DEMO_FILES} ${SRC_FILES})

target_link_libraries(${DEMO_NAME} PUBLIC -lpthread -lprotobuf)

target_include_directories(${DEMO_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/3rd/protobuf-v3.20.2/${PLATFORM}/include"
    "${PROJECT_SOURCE_DIR}/3rd/spdlog/include"
    )