#include "gtest/gtest.h"
#include <parserTool_ITNC530/parserTool_ITNC530.hpp>

#include <vector>
#include <utility>

TEST(parserTool_ITNC530, parse) {
	readData::parserTool_ITNC530 parser(std::string("../../../resources/TOOL_TEST.h"));
	EXPECT_EQ(parser.parse(), 1) << "TOOL_TEST\n";
	parser.setNewFile(std::string("../../../resources/TOOL_TEST_1.h"));
	EXPECT_EQ(parser.parse(), 1) << "TOOL_TEST_1\n";

	// std::vector<std::pair<std::string, int> > columnNameWhidth {
		// std::make_pair(std::string("T"), 8),
		// std::make_pair(std::string("NAME"), 17),
		// std::make_pair(std::string("DOC"), 17),
		// std::make_pair(std::string("NMAX"), 7),
		// std::make_pair(std::string("L"), 12),
		// std::make_pair(std::string("R"), 12),
		// std::make_pair(std::string("R2"), 12),
		// std::make_pair(std::string("DL"), 9),
		// std::make_pair(std::string("DR"), 9),
		// std::make_pair(std::string("DR2"), 9),
		// std::make_pair(std::string("TL"), 3),
		// std::make_pair(std::string("RT"), 6),
		// std::make_pair(std::string("TIME2"), 6),
		// std::make_pair(std::string("CUR.TIME"), 9),
		// std::make_pair(std::string("CUT."), 5),
		// std::make_pair(std::string("LTOL"), 8),
		// std::make_pair(std::string("RTOL"), 8),
		// std::make_pair(std::string("R2TOL"), 8),
		// std::make_pair(std::string("DIRECT."), 8),
		// std::make_pair(std::string("TT:L-OFFS"), 12),
		// std::make_pair(std::string("TT:R-OFFS"), 12),
		// std::make_pair(std::string("LBREAK"), 8),
		// std::make_pair(std::string("RBREAK"), 8),
		// std::make_pair(std::string("LCUTS"), 11),
		// std::make_pair(std::string("ANGLE"), 8),
		// std::make_pair(std::string("T-ANGLE"), 10),
		// std::make_pair(std::string("TYP"), 11),
		// std::make_pair(std::string("TMAT"), 17),
		// std::make_pair(std::string("CDT"), 17),
		// std::make_pair(std::string("PLC"), 10),
		// std::make_pair(std::string("LIFTOFF"), 8),
		// std::make_pair(std::string("KINEMATIC"), 17),
		// std::make_pair(std::string("AFC"), 11),
		// std::make_pair(std::string("LAST_USE"), 8)
	// };
	
	// is count of column is equal to vectorColumnWidth
	// EXPECT_EQ(parser.mToolData->mColumnNameWidth.size(), columnNameWhidth.size());
	
	// is the name and width of each column is equal name_width vector
	// for(int i = 0; i < parser.mToolData->mColumnNameWidth.size(); i++) {
		// EXPECT_EQ(parser.mToolData->mColumnNameWidth[i], columnNameWhidth[i]);
	// }
	
	// is number of line in tool table
	// EXPECT_EQ(parser.mToolData->mToolDataList.size(), 11);
	
	// test tool number major and minor
	// std::vector<std::pair<int, int> > toolNumber {
		// std::make_pair(154, 2),
		// std::make_pair(1, 0),
		// std::make_pair(2, 0),
		// std::make_pair(3, 0),
		// std::make_pair(4, 0),
		// std::make_pair(5, 0),
		// std::make_pair(6, 0),
		// std::make_pair(7, 0),
		// std::make_pair(27, 0),
		// std::make_pair(27, 1),
		// std::make_pair(28, 0)
	// };
	// int i = 0;
	// for(auto &a : parser.mToolData->mToolDataList) {
		// EXPECT_EQ(a.numMajorMinor, toolNumber[i]);
		// ++i;
	// }
}