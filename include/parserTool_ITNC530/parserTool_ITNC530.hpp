#ifndef PARSER_TOOL_ITNC530_H
#define PARSER_TOOL_ITNC530_H

#include <string>
#include <memory>
#include <vector>
#include <utility>

namespace readData {
	
	std::pair<int, int> toolNumberFromString(std::string str);

	class ToolTableData {
	protected:
		struct dataTool {
			std::pair<int, int> numMajorMinor;
			std::vector<std::string> listOfValues;
		};
		
		using pairNameWidth = std::pair<std::string, int>;
		using toolDataContainer = std::vector<dataTool>;

		std::string mFileName;
		std::vector<pairNameWidth> mColumnNameWidth;
		toolDataContainer mToolDataList;
	protected:
		explicit ToolTableData(const std::string &readFile);
	public:
		ToolTableData(const ToolTableData &) = delete;
		ToolTableData& operator==(const ToolTableData &) = delete;
	};
	
	class parserTool_ITNC530 {
	private:
		class Filler_ToolTableData : public ToolTableData {
		public:
			explicit Filler_ToolTableData(const std::string &parseFile);
		public:
			Filler_ToolTableData(const Filler_ToolTableData &) = delete;
			Filler_ToolTableData& operator==(const Filler_ToolTableData &) = delete;
		public:
			/* Clear all tool data structure*/
			void clear();
			/* Set new file for parsing */
			void setNewFile(const std::string &newFile);
			/*	Return name of parsing file */
			const std::string& getFileName() { return mFileName; }
			/* Read start header of tool file
			/		- input: expected start header string line 
					- return: true if header is exist another false
			*/
			bool readStartHeaderLine(const std::string &startLine);
			/* Define all names from column header line:
			/		- input: string contained line of column header
			/ 	- return: count of names from input line
			/							0 - if line is empty
			/						 -1 - if line has error sturcture of toolTableFile
			*/
			int readAllColumnHeaderNameWidth(const std::string &lineOfColumnHeader);
			/* Read all data for one tool from one line
			/		- input: line of tool data line
					- return: count read data parameters
										0 - if line is empty
									 -1 - if line has error structure
			*/
			int readLineToolData(const std::string &toolDataLine);
		};
	public:
		parserTool_ITNC530(const parserTool_ITNC530 &) = delete;
		parserTool_ITNC530& operator==(const parserTool_ITNC530 &) = delete;
	public:
		explicit parserTool_ITNC530(const std::string &mFileName);
	public:
		int parse();
		void setNewFile(const std::string &newFile);
	private:
		std::shared_ptr<Filler_ToolTableData> mToolData;
	};
	
}

#endif // PARSER_TOOL_ITNC530_H