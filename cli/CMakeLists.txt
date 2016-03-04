find_package(CURL REQUIRED)
find_package(Sqlite REQUIRED)
find_package(JsonParser REQUIRED)

add_executable(stream
  ./main.c
  ./config.c
  ./utils.c
)

include_directories(
  ${CURL_INCLUDE_DIRS}
  ${SQLITE_INCLUDE_DIR}
  ${JSONPARSER_INCLUDE_DIRS}
)

target_link_libraries(stream
  PUBLIC ${CURL_LIBRARIES}
  PUBLIC ${SQLITE_LIBRARIES}
  PUBLIC ${JSONPARSER_LIBRARIES}
)

add_custom_target(run
  COMMAND stream
  DEPENDS stream
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
