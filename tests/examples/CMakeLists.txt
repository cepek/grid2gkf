set(TEXT2XML      ${CMAKE_BINARY_DIR}/gama-local-text2xml)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/examples)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/examples)

foreach(file 1-traverse_2d 5-resection)
  add_test(NAME examples/${file}
    COMMAND ${TEXT2XML} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
