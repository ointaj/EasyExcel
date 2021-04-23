#include "Data.h"

std::pair<uint16_t, uint16_t> Data::DelData(const std::pair<uint16_t, uint16_t>& Info)
{
	nValues _nVal;
	uint16_t DelInRow = Info.second / Info.first;
	uint16_t Collumns = DelInRow + _nVal.fPos;
	return std::make_pair(DelInRow, Collumns);
}

std::tuple<std::vector<std::size_t>, uint16_t, std::optional<uint16_t>> Data::ColumnPos(const std::vector<std::size_t>& AllPos, const std::tuple<uint16_t, uint16_t, uint16_t>& ColRowData, const std::optional<uint16_t>& CollumnChooseFull) //col f, row s, del in row
{
	//tuple - > Col,Rows,DelInRow
	inputStream _inputStream;
	outputStream _outputStream;
	nValues _nVal;

	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	std::vector<std::size_t> columnsValues;
	uint16_t count{};
	uint16_t RowChoose{};
	uint16_t mainCoulmsChoose{};
	uint16_t workchooseInput{};
	const auto oNullVal = std::nullopt;
	do
	{
		if (this->sameValue == _nVal.NullValue)
		{
			if (CollumnChooseFull || CollumnChooseFull == _nVal.NullValue)
			{
				_outputStream.Print(_tValues->chColl);
				mainCoulmsChoose = _inputStream.uiInput();
				workchooseInput = _nVal.fPos;
			}
			if (!CollumnChooseFull)
			{
				_outputStream.Print(_tValues->workChoose, _tValues->NewLine, _tValues->ColorCell);
				workchooseInput = _inputStream.uiInput();
				if (workchooseInput == _nVal.fCho)
				{
					_outputStream.Print(_tValues->chColl);
					mainCoulmsChoose = _inputStream.uiInput();
				}
				if (workchooseInput == _nVal.sCho)
				{
					_outputStream.Print(_tValues->chColl);
					mainCoulmsChoose = _inputStream.uiInput();
					_outputStream.Print(_tValues->NewLine, _tValues->chRow);
					RowChoose = _inputStream.uiInput();
				}
			}
		}
		else if (this->sameValue != _nVal.NullValue)
		{
			mainCoulmsChoose = this->sameValue;
		}
		if(RowChoose > _nVal.NullValue && RowChoose <= std::get<1>(ColRowData) && workchooseInput == _nVal.sCho || workchooseInput == _nVal.fCho || CollumnChooseFull == _nVal.NullValue)
		{
			if (mainCoulmsChoose == _nVal.fCho || mainCoulmsChoose == std::get<0>(ColRowData))
			{
				uint16_t value{};
				uint16_t pos{};
				if (mainCoulmsChoose == _nVal.fCho)
					pos = _nVal.NullValue;
				if (mainCoulmsChoose == std::get<0>(ColRowData))
					pos = std::get<2>(ColRowData) - _nVal.fPos;
				if(workchooseInput == _nVal.fCho || CollumnChooseFull == _nVal.NullValue)
					value = std::get<1>(ColRowData) * std::get<2>(ColRowData);
				if (workchooseInput == _nVal.sCho && RowChoose == count)
					value = std::get<2>(ColRowData);
				while (count != std::get<1>(ColRowData))
				{
					columnsValues.reserve(value);
					count++;
					if (workchooseInput == _nVal.fCho || CollumnChooseFull == _nVal.NullValue)
					{

						columnsValues.emplace_back(AllPos.at(pos));
						pos += std::get<2>(ColRowData);

					}
					if (workchooseInput == _nVal.sCho && RowChoose == count)
					{
						if (count > _nVal.fCho)
						{
							uint16_t multiplication = count - _nVal.fPos;
							pos += std::get<2>(ColRowData) * multiplication;
						}
						columnsValues.emplace_back(AllPos.at(pos));
						return std::make_tuple(columnsValues, mainCoulmsChoose, RowChoose);
					}
					else
						continue;
				}
				return std::make_tuple(columnsValues, mainCoulmsChoose,oNullVal);
			}
			if (mainCoulmsChoose > _nVal.fCho && mainCoulmsChoose < std::get<0>(ColRowData))
			{
				uint16_t spos = mainCoulmsChoose - _nVal.fPos;
				uint16_t fpos = spos - _nVal.fPos;
				uint16_t value{};
				if(workchooseInput == _nVal.fCho || CollumnChooseFull == _nVal.NullValue)
					value = std::get<1>(ColRowData) * std::get<2>(ColRowData);
				if (workchooseInput == _nVal.sCho && RowChoose == count)
					value = std::get<2>(ColRowData);
				while (count != std::get<1>(ColRowData))
				{
					columnsValues.reserve(value);
					count++;
					if (workchooseInput == _nVal.fCho || CollumnChooseFull == _nVal.NullValue)
					{
						columnsValues.emplace_back(AllPos.at(fpos));
						columnsValues.emplace_back(AllPos.at(spos));
						fpos += std::get<2>(ColRowData);
						spos += std::get<2>(ColRowData);
					}
					if (workchooseInput == _nVal.sCho && RowChoose == count)
					{
						if (count > _nVal.fCho)
						{
							uint16_t multiplication = count - _nVal.fPos;
							fpos += std::get<2>(ColRowData) * multiplication;
							spos += std::get<2>(ColRowData) * multiplication;
						}
						columnsValues.emplace_back(AllPos.at(fpos));
						columnsValues.emplace_back(AllPos.at(spos));
						return std::make_tuple(columnsValues,mainCoulmsChoose, RowChoose);
					}

				}
				return std::make_tuple(columnsValues, mainCoulmsChoose, oNullVal);
			}
		}
		else
		{
			_outputStream.Print(_tValues->InvalitInput, _tValues->NewLine);
			continue;
		}
	}
	while (_nVal.infLoop);
}

bool Data::isDigit(const std::string& sData)
{
	return std::all_of(sData.begin(), sData.end(), ::isdigit);
}

uint32_t Data::chToUint(const std::string& sData)
{
	return std::stoi(sData);
}
ptrdiff_t Data::Count(const std::string& _Data, const char& Del)
{
	return std::count(_Data.begin(), _Data.end(), Del);
}
