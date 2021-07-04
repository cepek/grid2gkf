set(GRID2GKF       ${CMAKE_BINARY_DIR}/grid2gkf)
set(INPUT_DIR     ${PROJECT_SOURCE_DIR}/tests/single-point)
set(RESULT_DIR    ${CMAKE_BINARY_DIR}/tests/single-point)

foreach(file trilateration angles intersection directions)
  add_test(NAME single-point/${file}
    COMMAND ${GRID2GKF} ${INPUT_DIR}/${file}.dat ${file}.gkf)
endforeach(file)
