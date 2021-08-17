#include <parserTool_ITNC530/parserTool_ITNC530.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>
#include <numeric>

#include <stdexcept>

namespace readData {
	
	std::pair<int, int> toolNumberFromString(std::string str) {
		std::pair<int, int> toolNumber = std::make_pair(-1, -1);
		std::string::size_type sz;
		// read major value
		try {
			std::get<0>(toolNumber) = std::stoi(str, &sz);
		} catch(std::invalid_argument &ex) { }
		// read minor value
		if (str[sz] == '.') {
			str.substr(sz + 1).swap(str);
			try {
				std::get<1>(toolNumber) = std::stoi(str, &sz);
			} catch(std::invalid_argument &ex) { }
		} else {
			std::get<1>(toolNumber) = 0;
		}
		return toolNumber;
	}
	
	ToolTableData::ToolTableData(const std::string &readFile)
		: mFileName(readFile) {
		mColumnNameWidth.reserve(40);
		mToolDataList.reserve(100);
	}
	
	parserTool_ITNC530::Filler_ToolTableData::Filler_ToolTableData(const std::string &parseFile) 
		: ToolTableData(parseFile) { 
	}

	void parserTool_ITNC530::Filler_ToolTableData::setNewFile(const std::string &newFile) {
		mFileName = newFile;
	}
	
	parserTool_ITNC530::parserTool_ITNC530(const std::string &mFileName) 
		: mToolData(std::make_shared<Filler_ToolTableData>(mFileName)) { 
	}
	
	void parserTool_ITNC530::Filler_ToolTableData::clear() {
		std::vector<pairNameWidth>().swap(mColumnNameWidth);
		toolDataContainer().swap(mToolDataList);
	}
	
	bool parserTool_ITNC530::Filler_ToolTableData::readStartHeaderLine(const std::string &startLine) {
		if (startLine.empty()) {
			return false;
		}
		std::istringstream iss(startLine);
		std::string sWord;
		bool bReadStatus = false;
		if ((iss >> sWord) && (sWord == "BEGIN"))
			if ((iss >> sWord) && (sWord == "TOOL"))
				if ((iss >> sWord) && (sWord == ".T"))
					if ((iss >> sWord) && (sWord == "MM" || sWord == "INCH"))
						bReadStatus = true;
		if (!iss) {
			std::cout << "Error istringstream\n";
			iss.clear();
		}	
		return bReadStatus;
	}
		
	int parserTool_ITNC530::Filler_ToolTableData::readAllColumnHeaderNameWidth(const std::string &lineOfColumnHeader) {
		if (lineOfColumnHeader.empty())
			return 0;
		if (isdigit(lineOfColumnHeader[0])){
			std::cout << "Error file structure! Read names of column\n";
			return -1;
		} 
		auto beginLexem = lineOfColumnHeader.begin();
		auto endLexem = beginLexem;
		// main loop for determinate every name of column header
		int counterNames = 0;
		while (beginLexem != lineOfColumnHeader.end()) {
			Filler_ToolTableData::pairNameWidth pNameWidth;
			// find name of column
			endLexem = std::find_if(beginLexem, lineOfColumnHeader.end(),
									[](char c) { return c == ' '; } );
			std::get<0>(pNameWidth) = std::string(beginLexem, endLexem);

			// find whidth of column
			endLexem = std::find_if_not(endLexem, lineOfColumnHeader.end(),
										[](char c) { return c == ' '; } );
			std::get<1>(pNameWidth) = endLexem - beginLexem;

			// add new column name in tool data structure
			mColumnNameWidth.push_back(pNameWidth);
			beginLexem = endLexem;
			++counterNames;
		}
		return counterNames;
	}
	
	int parserTool_ITNC530::Filler_ToolTableData::readLineToolData(const std::string &toolDataLine) {
		if (toolDataLine.empty())
			return 0;
		int totalWidthColumns = 0;
		totalWidthColumns = std::accumulate(mColumnNameWidth.begin(), mColumnNameWidth.end(), 
			totalWidthColumns, [](int total, pairNameWidth widthColumn) {
				return total + std::get<1>(widthColumn);
			}	);
		if (toolDataLine.size() < totalWidthColumns) {
			std::cout << "Size of tool data line less then length header\n";
			return -1;
		}
		// Read each column data from ToolTable line
		Filler_ToolTableData::dataTool toolLine;
		auto beginLexem = toolDataLine.begin();
		auto endLexem = beginLexem;
		int countData = 0;
		for(int i = 0; i < mColumnNameWidth.size(); ++i) {
			if (i == (mColumnNameWidth.size() - 1))
				endLexem = toolDataLine.end();
			else
				endLexem = beginLexem + std::get<1>(mColumnNameWidth[i]);
			toolLine.listOfValues.push_back(std::string(beginLexem, endLexem));
			++countData;
			beginLexem = endLexem;
		}
		toolLine.numMajorMinor = toolNumberFromString(toolLine.listOfValues[0]);
		mToolDataList.push_back(toolLine);
		return countData;
	}

	void parserTool_ITNC530::setNewFile(const std::string &newFile) {
		mToolData->setNewFile(newFile);
	}
	
	int parserTool_ITNC530::parse() {
		
		// Clear all old data
		// ============================
		mToolData->clear();
		
		std::ifstream fin(mToolData->getFileName());
		if (!fin) {
			std::cout << "Can't open file: " << mToolData->getFileName() << std::endl;
			return 0;
		}
		
		std::cout << "<= Start parsing file: " << mToolData->getFileName() << std::endl;
		
		// CHECK START LINE TOOLTABLE FILE THAT MUST BE CONTAIN
		// ====================================================
		std::string sLine;
		sLine.reserve(400);
		std::getline(fin, sLine);
		if (!mToolData->readStartHeaderLine(sLine)) {
			std::cout << "Undefined start line of file: " << mToolData->getFileName() << std::endl;
			return 0;
		}
		
		// READ NAME OF HEADER COLUMN AND WHIDTH
		// =====================================
		sLine.clear();
		if (!fin) {
			std::cout << "Error! I/O error!\n";
			fin.clear();
			return 0;
		}
		std::getline(fin, sLine);
		if (mToolData->readAllColumnHeaderNameWidth(sLine) <= 0) {
			std::cout << "Error! Error structure tool data!\n";
			return 0;
		}
		
		// READ ALL TOOL DATA 
		// ==================
		while (fin) {
			sLine.clear();
			std::getline(fin, sLine);
			if (std::string::npos != sLine.find(std::string("[END]"))) {
				return 1;
			}
			if (mToolData->readLineToolData(sLine) <= 0) {
				std::cout << "Error! Error structure tool data line!\n";
				return 0;
			}
		}

		// CHECK WHAT'S THE ERROR CLOSED READ PROCESS
		// ==========================================
			if (fin.eof()) {
				std::cout << "EOF is occured :" << mToolData->getFileName() << std::endl;
				fin.clear();
			} else if (fin.bad()) {
				std::cout << "I/O bad error is occured!\n";
				fin.clear();
			}
			return 0;
		}

}
