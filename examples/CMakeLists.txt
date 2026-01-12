function(add_tinylog_example_executable name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} PRIVATE tinylog)
  set_target_properties(${name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/examples"
  )

  if(MSVC)
    target_compile_options(${name} PRIVATE /W4)
  else()
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endfunction()

add_tinylog_example_executable(console_logging)
add_tinylog_example_executable(file_logging)
