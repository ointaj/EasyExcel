#pragma once
#include "Streams.h"
#include <functional>
#include <memory>
class bData
{
public:
	bData() = default;
	virtual std::pair<uint16_t, uint16_t> DelData(const std::pair<uint16_t, uint16_t>& Info) = 0;
	virtual std::tuple<std::vector<std::size_t>,uint16_t,std::optional<uint16_t>> ColumnPos(const std::vector<std::size_t>& AllPos, const std::tuple<uint16_t, uint16_t, uint16_t>& ColRowData, const std::optional<uint16_t>& CollumnChooseFull = {}) = 0;
	virtual bool isDigit(const std::string& sData) = 0;
	virtual uint32_t chToUint(const std::string& sData) = 0;
	virtual ptrdiff_t Count(const std::string& _Data, const char& Del) = 0;
	~bData() = default;
};

class Data: public bData
{
private:
	uint16_t sameValue{};
public:
	Data() = default;
	Data(const uint16_t& sVal)
	{
		this->sameValue = sVal;
	}	
	virtual std::pair<uint16_t, uint16_t> DelData(const std::pair<uint16_t, uint16_t>& Info) override;
	virtual std::tuple<std::vector<std::size_t>, uint16_t,std::optional<uint16_t>> ColumnPos(const std::vector<std::size_t>& AllPos, const std::tuple<uint16_t, uint16_t, uint16_t>& ColRowData, const std::optional<uint16_t>& CollumnChooseFull = {}) override;
	virtual bool isDigit(const std::string& sData) override;
	virtual uint32_t chToUint(const std::string& sData) override;
	virtual ptrdiff_t Count(const std::string& _Data, const char& Del) override;
	~Data() = default;
};