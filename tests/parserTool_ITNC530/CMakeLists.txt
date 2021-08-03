set(BINARY libTest)

set(SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/runtest.cpp  
	${CMAKE_CURRENT_SOURCE_DIR}/parserTool_ITNC530_test.cpp
)

add_executable(${BINARY} ${SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC parserTool_ITNC530 gtest)