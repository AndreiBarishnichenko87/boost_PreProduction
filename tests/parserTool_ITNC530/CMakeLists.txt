set(BINARY test)

set(SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/runtest.cpp  
	${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp
)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC parserTool_ITNC530 gtest)