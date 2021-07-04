set(GRID2GKF       ${CMAKE_BINARY_DIR}/grid2gkf)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/traverse)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/traverse)

foreach(file square)
  add_test(NAME traverse/${file}
    COMMAND ${GRID2GKF} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
