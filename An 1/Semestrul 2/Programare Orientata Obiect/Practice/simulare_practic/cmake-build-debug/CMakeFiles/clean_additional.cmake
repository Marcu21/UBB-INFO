# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\simulare_practic_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\simulare_practic_autogen.dir\\ParseCache.txt"
  "simulare_practic_autogen"
  )
endif()
