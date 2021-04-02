#pragma once
#include "Streams.h"
#include "Start.h"

enum class eControl: uint8_t
{
	NOTOK = 0,
	OK
};

enum class eFileSave : uint8_t
{
	DONTSAVE = 0,
	SAVE
};

enum class ePrintData : uint8_t
{
	DONTPRINT = 0,
	PRINT
};

class bPosFilesystem
{
public:
	bPosFilesystem() = default;
	virtual void inputPathDel() = 0;
	virtual eControl ControlPath() = 0;
	virtual eControl ControlDelimeter() = 0;
	virtual std::pair<eFileSave,std::string> SaveFileCh() = 0;
	virtual ePrintData PrintDataCh() = 0;

	virtual void CollALl(const uint16_t& Collumns) = 0;
	virtual void replaceAll() = 0;
	virtual std::string newPath() = 0;
	virtual void pPath() = 0;

	virtual void SaveChanges(const std::string& Data, const std::string& Path) = 0;
	virtual std::tuple<std::vector<std::size_t>, uint16_t, uint16_t> DelPos() = 0;
	virtual void ReadData(const uint16_t& Input, const uint16_t& Columns, const std::vector<std::size_t>& posOfdels, const uint16_t& ColumnsChoose, void(bPosFilesystem::*FuncData)(std::string&, const std::size_t&, const std::size_t&, const std::optional<uint16_t>&), const std::optional<uint16_t>& Row, const std::pair<eFileSave,std::string>& saveChoose, const ePrintData& printChoose) = 0;
	virtual void Fill(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) = 0;
	virtual void Erase(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) = 0;
	virtual void Replace(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) = 0;
	virtual void Choose(const uint16_t& Columns, const std::vector<std::size_t>& posOfdels, const uint16_t& ColumnsChoose, const std::optional<uint16_t>& Rows) = 0;
	virtual void tRead() = 0;
	virtual void Swap(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) = 0;
	virtual void Sum(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) = 0;
	~bPosFilesystem() = default;
};

class PosFileSystem : public bPosFilesystem
{
private:	
	std::string Path;
	char Delimeter;
	uint32_t sum{};
	uint16_t AllColl{};
	std::string AllReplaceVals;
	std::ifstream readMyfile;
	std::ofstream writeInFile;
	std::string _Data;
public:
	PosFileSystem() = default;
	virtual void inputPathDel() override;
	virtual eControl ControlPath() override;
	virtual eControl ControlDelimeter() override;
	virtual std::pair<eFileSave, std::string> SaveFileCh() override;
	virtual ePrintData PrintDataCh() override;

	virtual void CollALl(const uint16_t& Collumns) override;
	virtual void replaceAll() override;
	virtual std::string newPath() override;
	virtual void pPath() override;

	virtual void SaveChanges(const std::string& Data, const std::string& Path) override;
	virtual std::tuple<std::vector<std::size_t>, uint16_t, uint16_t> DelPos() override;

	virtual void Fill(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) override;
	virtual void ReadData(const uint16_t& Input, const uint16_t& Columns, const std::vector<std::size_t>& posOfdels, const uint16_t& ColumnsChoose, void(bPosFilesystem::*FuncData)(std::string&, const std::size_t&, const std::size_t&, const std::optional<uint16_t>&), const std::optional<uint16_t>& Row, const std::pair<eFileSave, std::string>& saveChoose, const ePrintData& printChoose) override;
	virtual void Erase(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) override;
	virtual void Replace(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) override;
	virtual void Choose(const uint16_t& Columns, const std::vector<std::size_t>& posOfdels, const uint16_t& ColumnsChoose, const std::optional<uint16_t>& Rows) override;
	virtual void tRead() override;
	virtual void Swap(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) override;
	virtual void Sum(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue) override;
	~PosFileSystem() = default;
};	

