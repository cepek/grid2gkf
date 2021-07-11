set(TEXT2XML       ${CMAKE_BINARY_DIR}/gama-local-text2xml)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/levelling)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/levelling)

foreach(file  mikhail-7.4)
  add_test(NAME levelling/${file}
    COMMAND ${TEXT2XML} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
