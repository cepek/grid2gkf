set(TEXT2XML       ${CMAKE_BINARY_DIR}/gama-local-text2xml)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/single-point)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/single-point)

foreach(file  angles-at-from-to  angles-from-at-to
              trilateration intersection directions)
  add_test(NAME single-point/${file}
    COMMAND ${TEXT2XML} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
