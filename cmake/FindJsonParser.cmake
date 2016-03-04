find_path(JSONPARSER_INCLUDE_DIRS
  NAMES json.h
  HINTS ${CMAKE_SOURCE_DIR}/third-party/json-parser
)

# We would normally use find_library here.
# But json-parser don't uses CMake.
# We build and assign it to JSONPARSER_LIBRARIES.
add_library(json-parser
  ${JSONPARSER_INCLUDE_DIRS}/json.c
)

target_link_libraries(json-parser
  PUBLIC m
)

set(JSONPARSER_LIBRARIES json-parser)

mark_as_advanced(
  JSONPARSER_INCLUDE_DIRS
  JSONPARSER_LIBRARIES
)
