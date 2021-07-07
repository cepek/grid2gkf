set(TEXT2XML      ${CMAKE_BINARY_DIR}/gama-local-text2xml)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/traverse)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/traverse)

foreach(file square 1-traverse_2d)
  add_test(NAME traverse/${file}
    COMMAND ${TEXT2XML} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
