#pragma once
#include "Streams.h"
class tValues
{
public:
	tValues() = default;

	const std::string InvalitInput = "You passed invalid value ! ";
	const std::string WrongCollumn = "That column doesnt exists ! ";

	const std::string NewLine = "\n";
	const std::string NewTab = "\t";

	const std::string FileError = "Cant open the file !";
	const std::string txtFileExt = ".txt";
	const std::string sDot = ".";
	const std::string sSlash = "/";
	const std::string sArrow = "-> ";
	const std::string failExt = "You didn't write File Extention ! ";
	const std::string badExt = "You wrote wrong File Extention, WE WORK ONLY WITH TXT FILES";
	const std::string notExFile = "File doesnt exists ! ";
	const std::string emptyFile = "File is empty ! ";
	const std::string saveFile = "Dou you want to save your changes in your file ?";
	const std::string workChoose = "Do you want to work with columns or one cell ?";
	const std::string sumValue = "Sum of the cells is: ";
	const std::string chOperation = "Choose the operation you want to work with:";
	const std::string chPrintData = "Do you want to print your changes to the console ?";
	const std::string chSameNewFile = "Do you want to save your changes in the same or new file ?";
	const std::string sNoDelimeter = "There wasnt find delimeter in the row ! ";
	const std::string sNoSameCount = "There is no same count of delimeters in the rows ! Every row has to have same count of columns ! ";
	const std::string sInputReFiVal = "Please enter replace/fill value: ";

	const std::string sEnd = "PRESS ESC IF YOU WANT TO END THE PROGRAM ! ";

	const std::string enterPath = "ENTER PATH TO YOUR FILE: ";
	const std::string enterDel = "ENTER DELIMTER FOR WORKING WITH FILE: ";

	const std::string PrintData = "[1] PRINT TO CONSOLE [2] DO NOT PRINT TO CONSOLE -> ";
	const std::string Oper = "[1] ERASE DATA [2] REPLACE DATA [3] SWAP DATA [4] SUM DATA  [5] FILL EMPTY COLLUMN -> ";

	const std::string newPath = "[1] SAME FILE [2] DIFERENT FILE -> ";

	const std::string selectRowCol = "[1] By row [2] By Column -> ";

	const std::string sSaveFileCh = "[1] SAVE FILE [2] DONT SAVE FILE -> ";

	const std::string ColorCell = "[1] Columns [2] Cell -> ";
	const std::string chColl = "CHOOSE COLLUMN -> ";
	const std::string chRow = "CHOOSE ROW -> ";

	const std::string diskName = "Disk: ";
	const std::string dirName = ". Directory: ";
	const std::string fileName = "File: ";
	const std::string fileExt = "File extention: ";
	const std::string del = "Delimeter -> ";

	const std::string collAllCh = "[1] SWAP FULL COLUMN [2] SWAP BY ROWS -> ";
	const std::string replaceAll = "[1] REPLACE/FILL DATA IN FULL COLUMN [2] REPLACE/FILL DATA BY ROWS -> ";

	~tValues() = default;

};

class nValues
{	
public:
	nValues() = default;

	static constexpr uint8_t NullValue = 0;
	static constexpr uint8_t fPos = 1;
	static constexpr uint8_t sPos = 2;
	static constexpr uint8_t tPos = 3;
	static constexpr uint8_t foPos = 4;
	static constexpr uint8_t fiPoa = 5;
	static constexpr uint8_t fCho = 1;
	static constexpr uint8_t sCho = 2;
	static constexpr uint8_t tCho = 3;
	static constexpr uint8_t foCho = 4;
	static constexpr uint8_t fiCho = 5;

	static constexpr uint16_t END = 27;
	static constexpr bool infLoop = true;

	~nValues() = default;
};
