# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\melodii2qt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\melodii2qt_autogen.dir\\ParseCache.txt"
  "melodii2qt_autogen"
  )
endif()
