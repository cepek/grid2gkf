set(TEXT2XML       ${CMAKE_BINARY_DIR}/gama-local-text2xml)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/gama)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/gama)

foreach(file  mikhail-7.4 geodet-pc-218 geodet-pc-218-settings-demo)
  add_test(NAME gama/${file}
    COMMAND ${TEXT2XML} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
