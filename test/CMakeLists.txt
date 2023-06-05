add_subdirectory(test_base64)
add_subdirectory(test_json)
add_subdirectory(test_log)

if(${PLATFORM} MATCHES "x64")
    add_subdirectory(test_jemalloc)
endif()
# jemalloc只有x64的lib，等之后会用了再补上

if((${PLATFORM} MATCHES "x64") OR (${PLATFORM} MATCHES "armhf"))
    add_subdirectory(test_sqlite3)
endif()

if(${PLATFORM} MATCHES "x64")
    add_subdirectory(test_uuid)
endif()

if(${PLATFORM} MATCHES "x64" OR (${PLATFORM} MATCHES "armhf"))
    add_subdirectory(test_protobuf)
endif()