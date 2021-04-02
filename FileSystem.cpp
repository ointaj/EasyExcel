#include "FileSystem.h"
#include "Data.h"

void PosFileSystem::inputPathDel()
{
	outputStream _outStream;
	inputStream _inpStream;
	std::unique_ptr<tValues> _tVal = std::make_unique<tValues>();

	eControl controlPath;

	_outStream.Print();
	do
	{
		_outStream.Print(_tVal->enterPath);
		auto cPath = _inpStream.sInput();
		this->Path = cPath;

		_outStream.Print(_tVal->enterDel);
		auto cDel = _inpStream.sInput();
		this->Delimeter = *cDel.c_str();

		controlPath = PosFileSystem::ControlPath();
	}
	while (controlPath != eControl::OK);

	PosFileSystem::pPath();
}

eControl PosFileSystem::ControlPath()
{
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	outputStream _outputStream;
	const auto FileExtencion = Path.rfind(_tValues->sDot);
	if (FileExtencion != std::string::npos)
	{
		std::string subFE = Path.substr(FileExtencion, Path.size() - FileExtencion);
		if (subFE == _tValues->txtFileExt)
		{
			this->readMyfile.open(this->Path);
			if (this->readMyfile.is_open())
			{
				if (this->readMyfile.peek() == std::ifstream::traits_type::eof())
				{
					_outputStream.Print(_tValues->emptyFile, _tValues->NewLine);
					this->readMyfile.close();
					return eControl::NOTOK;
				}
				this->readMyfile.close();
				auto controlDel = PosFileSystem::ControlDelimeter();
				if (controlDel == eControl::OK)
				{
					return eControl::OK;
				}
				else
				{
					return eControl::NOTOK;
				}
			}
			else
			{
				_outputStream.Print(_tValues->notExFile, _tValues->NewLine);
				this->readMyfile.close();
				return eControl::NOTOK;
			}
		}
		else
		{
			_outputStream.Print(_tValues->badExt, _tValues->NewLine);
			return eControl::NOTOK;
		}
	}
	else
	{
		_outputStream.Print(_tValues->failExt, _tValues->NewLine);
		return eControl::NOTOK;
	}
}

eControl PosFileSystem::ControlDelimeter()
{
	Data _data;
	outputStream _outStream;
	std::unique_ptr<tValues> _tVal = std::make_unique<tValues>();

	std::vector<ptrdiff_t> countControl;

	this->readMyfile.open(this->Path);
	while (getline(this->readMyfile, this->_Data))
	{
		if (this->readMyfile.is_open())
		{
			auto count = _data.Count(_Data, this->Delimeter);
			if (_Data.find(this->Delimeter) == std::string::npos)
			{
				_outStream.Print(_tVal->sNoDelimeter,_tVal->NewLine);
				this->readMyfile.close();
				return eControl::NOTOK;
			}
			countControl.emplace_back(count);
		}
	}
	if (std::adjacent_find(countControl.begin(), countControl.end(), std::not_equal_to<>()) == countControl.end())
	{
		this->readMyfile.close();
		return eControl::OK;
	}
	_outStream.Print(_tVal->sNoSameCount,_tVal->NewLine);
	this->readMyfile.close();
	return eControl::NOTOK;
}

std::pair<eFileSave, std::string> PosFileSystem::SaveFileCh()
{
	nValues _nValues;
	inputStream _inputStream;
	outputStream _outStream;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();

	_outStream.Print(_tValues->saveFile, _tValues->NewLine);
	do
	{
		_outStream.Print(_tValues->sSaveFileCh);
		auto choose = _inputStream.uiInput();
		if (choose == _nValues.fCho)
		{
			_outStream.Print(_tValues->chSameNewFile, _tValues->NewLine);
			do
			{
				_outStream.Print(_tValues->newPath);
				auto choose = _inputStream.uiInput();
				if (choose == _nValues.fCho)
				{
					return std::make_pair(eFileSave::SAVE, this->Path);
				}
				else if (choose == _nValues.sCho)
				{
					const auto _newPath = PosFileSystem::newPath();
					return std::make_pair(eFileSave::SAVE, _newPath);
				}
				else
				{
					_outStream.Print(_tValues->InvalitInput);
					continue;
				}
			}
			while (_nValues.infLoop);
		}
		if (choose == _nValues.sCho)
		{
			return std::make_pair(eFileSave::DONTSAVE,this->Path);
		}
		else
		{
			_outStream.Print(_tValues->InvalitInput, _tValues->NewLine);
			continue;
		}
	}
	while (_nValues.infLoop);
}

ePrintData PosFileSystem::PrintDataCh()
{
	inputStream _inputStream;
	nValues _nValues;
	outputStream _outStream;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();

	_outStream.Print(_tValues->chPrintData,_tValues->NewLine);
	do
	{
		_outStream.Print(_tValues->PrintData);
		auto choose = _inputStream.uiInput();
		if (choose == _nValues.fCho)
		{
			return ePrintData::PRINT;
		}
		if (choose == _nValues.sCho)
		{
			return ePrintData::DONTPRINT;
		}
		else
		{
			_outStream.Print(_tValues->InvalitInput, _tValues->NewLine);
			continue;
		}
	}
	while (_nValues.infLoop);
}

void PosFileSystem::pPath()
{
	outputStream _outStream;
	nValues _nVal;
	Data _data;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	
	auto fFind = this->Path.find(_tValues->sSlash);
	auto lFind = this->Path.rfind(_tValues->sSlash);
	auto dotFind = this->Path.rfind(_tValues->sDot);

	auto countDel = _data.Count(this->Path, *_tValues->sSlash.c_str());
	uint16_t count{};
	std::vector<std::string> pathData;
	pathData.reserve(countDel + _nVal.sPos);

	pathData.emplace_back(this->Path.substr(_nVal.NullValue, fFind - _nVal.fPos));
	pathData.emplace_back(this->Path.substr(lFind + _nVal.fPos, dotFind - lFind - _nVal.fPos));
	pathData.emplace_back(this->Path.substr(dotFind, this->Path.size() - dotFind));

	while (count != countDel - _nVal.fPos)
	{
		count++;
		auto sfind = this->Path.find(_tValues->sSlash, fFind + _nVal.fPos);
		if (sfind != std::string::npos)
		{
			pathData.emplace_back(this->Path.substr(fFind + _nVal.fPos, sfind - fFind - _nVal.fPos));
		}
		fFind = sfind;
	}
	_outStream.Print(_tValues->diskName, pathData.at(_nVal.NullValue),_tValues->NewLine);

	for (uint16_t pos = _nVal.tPos; pos < pathData.size(); pos++)
	{
		_outStream.Print(pos - _nVal.fPos , _tValues->dirName, pathData.at(pos),_tValues->NewLine);
	}
	_outStream.Print(_tValues->fileName, pathData.at(_nVal.fPos), _tValues->NewLine);
	_outStream.Print(_tValues->fileExt, pathData.at(_nVal.sPos),_tValues->NewLine);
	_outStream.Print(_tValues->del, this->Delimeter, _tValues->NewLine);
}

void PosFileSystem::CollALl(const uint16_t& Collumns)
{
	inputStream _inpStream;
	outputStream _outStream;
	nValues _nVal;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	do
	{
		_outStream.Print(_tValues->collAllCh,_tValues->NewLine);
		auto choose = _inpStream.uiInput();
		if (choose == _nVal.fCho)
		{
			do
			{
				auto chooseCol = _inpStream.uiInput();
				if (chooseCol >= _nVal.fPos && chooseCol <= Collumns)
				{
					this->AllColl = chooseCol;
					return;
				}
				else
				{
					_outStream.Print(_tValues->InvalitInput, _tValues->NewLine);
					continue;
				}
			}
			while (_nVal.infLoop);
		}
		if (choose == _nVal.sCho)
		{
			return;
		}
		else
		{
			_outStream.Print(_tValues->InvalitInput, _tValues->NewLine);
			continue;
		}

	} while (_nVal.infLoop);
}

void PosFileSystem::replaceAll()
{
	inputStream _inpStream;
	outputStream _outStream;
	nValues _nVal;
	std::unique_ptr<tValues> _tVal = std::make_unique<tValues>();

	uint16_t choose;
	_outStream.Print(_tVal->replaceAll,_tVal->NewLine);
	do
	{
		_outStream.Print();
		choose = _inpStream.uiInput();
		if (choose == _nVal.fCho)
		{
			_outStream.Print();
			this->AllReplaceVals = _inpStream.sInput();
			return;
		}
		else if (choose == _nVal.sCho)
		{
			return;
		}
		else
		{
			_outStream.Print(_tVal->InvalitInput);
			continue;
		}
	}
	while (_nVal.infLoop);
}

std::string PosFileSystem::newPath()
{
	outputStream _ousStrem;
	inputStream _inpStream;
	nValues _nVal;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	do
	{
		std::string newPath = _inpStream.sInput();
		this->readMyfile.open(newPath);
		if(this->readMyfile.is_open())
		{
			if (newPath.rfind(_tValues->txtFileExt) != std::string::npos)
			{
				this->readMyfile.close();
				return newPath;
			}
			else
			{
				_ousStrem.Print(_tValues->badExt,_tValues->NewLine);
				this->readMyfile.close();
				continue;
			}
		}
		else
		{
			_ousStrem.Print(_tValues->notExFile,_tValues->NewLine);
			this->readMyfile.close();
			continue;
		}
	}
	while(_nVal.infLoop);
}

void PosFileSystem::SaveChanges(const std::string& Data, const std::string& _Path)
{
	outputStream _outStream;
	inputStream _inpStream;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	this->writeInFile.open(_Path);
	if (this->writeInFile.is_open())
	{
		this->writeInFile  <<  Data << _tValues->NewLine;
	}
	else
	{
		_outStream.Print(_tValues->FileError, _tValues->NewLine);
	}
	this->writeInFile.close();
}

std::tuple<std::vector<std::size_t>, uint16_t, uint16_t> PosFileSystem::DelPos()
{
	outputStream _outputStream;
	nValues _nValues;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	std::vector<std::size_t> posDelVal;
	std::size_t findDel{}, Posicion{};
	uint16_t Rows{}, DelCount{}, Count{};
	this->readMyfile.open(this->Path);
	while (getline(this->readMyfile, this->_Data))
	{
		if (readMyfile.is_open())
		{
			Rows++;
			auto countDelinLine = std::count(_Data.begin(), _Data.end(), this->Delimeter);
			while (countDelinLine != Count)
			{
				findDel = _Data.find(this->Delimeter, Posicion);
				Count++;
				if (findDel != std::string::npos)
				{
					posDelVal.emplace_back(findDel);
					DelCount++;
				}
				Posicion = findDel + _nValues.fPos;
			}
			Count = _nValues.NullValue;		
			Posicion = _nValues.NullValue;
		}
		else
			_outputStream.Print(_tValues->FileError, _tValues->NewLine);
	}
	this->readMyfile.close();
	return std::make_tuple(posDelVal, Rows, DelCount);
}

void PosFileSystem::Fill(std::string& Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue)
{
	if (!_Data.substr(fPos, sPos).empty())
	{
		return;
	}

	outputStream _outStream;
	std::unique_ptr<tValues> _tVal = std::make_unique<tValues>();
	inputStream _inpStream;
	std::string value;
	
	if (this->AllReplaceVals.empty())
	{
		_outStream.Print(_tVal->sInputReFiVal);
		value = _inpStream.sInput();
	}
	else
	{
		value = this->AllReplaceVals;
	}
	_Data.replace(fPos, sPos,value);

}

void PosFileSystem::Erase(std::string& _Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue)
{
	if (_Data.substr(fPos, sPos).empty())
	{
		return;
	}
	_Data.erase(fPos, sPos);
}

void PosFileSystem::Replace(std::string& _Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue)
{
	if (_Data.substr(fPos, sPos).empty())
	{
		return;
	}
	inputStream _inputStream;
	outputStream _outStream;
	std::unique_ptr<tValues> _tVal = std::make_unique<tValues>();

	std::string value;
	
	if (this->AllReplaceVals.empty())
	{
		_outStream.Print(_tVal->sInputReFiVal);
		value = _inputStream.sInput();
	}
	else
	{
		value = this->AllReplaceVals;
	}
	_Data.replace(fPos, sPos, value);
}

void PosFileSystem::Swap(std::string& _Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue)
{
	std::string mainSub = _Data.substr(fPos, sPos);
	if (mainSub.empty())
	{
		return;
	}
	inputStream _inputStream;
	nValues _nVal;
	Data _data(this->AllColl);

	uint16_t loopCount{};
	uint8_t valusposmain{};
	std::vector<std::size_t> vPos;
	std::string secSub;
	auto delCount = _data.Count(_Data,this->Delimeter);
	uint16_t Collumns = delCount + _nVal.fPos;
	std::size_t pos{};
	std::optional<uint16_t> Row = 0;
	while (loopCount != delCount)
	{
		loopCount++;
		auto delFind = _Data.find(this->Delimeter,pos);
		if (delFind != std::string::npos)
			vPos.emplace_back(delFind);
		pos = delFind + _nVal.fPos;
	}
	if (RowValue != _nVal.NullValue || RowValue != std::nullopt)
	{
		Row = *RowValue;
	}
	auto val = _data.ColumnPos(vPos, std::make_tuple(Collumns, _nVal.fPos, delCount), Row);
	if (std::get<1>(val) == _nVal.fCho)
	{
		secSub = _Data.substr(_nVal.NullValue, std::get<0>(val).at(_nVal.NullValue));
		if (secSub.empty())
		{
			return;
		}
		_Data.replace(_nVal.NullValue, std::get<0>(val).at(_nVal.NullValue), mainSub);
		valusposmain++;
	}
	else if (std::get<1>(val) == Collumns)
	{
		secSub = _Data.substr(std::get<0>(val).at(_nVal.NullValue) + _nVal.fPos, _Data.size() - std::get<0>(val).at(_nVal.NullValue) - _nVal.fPos);
		if (secSub.empty())
		{
			return;
		}
		_Data.replace(std::get<0>(val).at(_nVal.NullValue) + _nVal.fPos, _Data.size() - std::get<0>(val).at(_nVal.NullValue), mainSub);
	}
	else if (std::get<1>(val) > _nVal.fCho && std::get<1>(val) < Collumns)
	{
		secSub = _Data.substr(std::get<0>(val).at(_nVal.NullValue) + _nVal.fPos,std::get<0>(val).at(_nVal.fPos) - std::get<0>(val).at(_nVal.NullValue) - _nVal.fPos);
		if (secSub.empty())
		{
			return;
		}
		_Data.replace(std::get<0>(val).at(_nVal.NullValue) + _nVal.fPos, std::get<0>(val).at(_nVal.fPos) - std::get<0>(val).at(_nVal.NullValue) - _nVal.fPos, mainSub);
	}
	_Data.replace(fPos + valusposmain, sPos, secSub);
}

void PosFileSystem::Sum(std::string& _Data, const std::size_t& fPos, const std::size_t& sPos, const std::optional<uint16_t>& RowValue)
{
	const auto subData = _Data.substr(fPos, sPos);
	if (subData.empty())
	{
		return;
	}
	Data _data;
	const auto digControl = _data.isDigit(subData);
	if (digControl == true)
	{
		const auto value = _data.chToUint(subData);
		this->sum += value;
	}
	else
	{
		return;
	}
}

void PosFileSystem::ReadData(const uint16_t& Input, const uint16_t& Columns, const std::vector<std::size_t>& posOfdels, const uint16_t& ColumnsChoose, void(bPosFilesystem::* _DataFunction)(std::string&, const std::size_t&, const std::size_t&, const std::optional<uint16_t>&), const std::optional<uint16_t>& Row = std::nullopt, const std::pair<eFileSave, std::string>& saveChoose = {}, const ePrintData& printChoose = {})
{
	outputStream _outputStream;
	inputStream _inputStream;
	nValues _nValues;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();

	std::string newData;
	std::size_t pos{};
	std::size_t fpos{};
	uint16_t CountRow{};

	this->readMyfile.open(this->Path);
	while (getline(this->readMyfile, this->_Data))
	{
		CountRow++;
		if(this->readMyfile.is_open())
		{

			if (ColumnsChoose > _nValues.fCho && ColumnsChoose < Columns && *Row == _nValues.NullValue|| ColumnsChoose > _nValues.fCho && ColumnsChoose < Columns && *Row == CountRow)
			{
				(this->*_DataFunction)(_Data,posOfdels.at(pos) + _nValues.fPos,posOfdels.at(pos + _nValues.fPos) - posOfdels.at(pos) - _nValues.fPos, Row);
				pos++;
				pos++;
			}
			else if (ColumnsChoose == _nValues.fCho && *Row == _nValues.NullValue || ColumnsChoose == _nValues.fCho && *Row == CountRow)
			{
				(this->*_DataFunction)(_Data, fpos, posOfdels.at(pos), *Row);
				pos++;
			}
			else if (ColumnsChoose == Columns && *Row == _nValues.NullValue || ColumnsChoose == Columns  && *Row == CountRow)
			{
				(this->*_DataFunction)(_Data, posOfdels.at(pos) + _nValues.fPos, _Data.size() - posOfdels.at(pos) + _nValues.fPos, *Row);
				pos++;
			}
		}
		else if(!this->readMyfile.is_open())
		{
			_outputStream.Print(_tValues->FileError,_tValues->NewLine);
			return;
		}
		if (saveChoose.first == eFileSave::SAVE)
		{
			newData.append(_Data).append(_tValues->NewLine);
		}
		if (printChoose == ePrintData::PRINT)
		{
			_outputStream.Print(_Data, _tValues->NewLine);
		}
	}
	if (Input == _nValues.foCho)
	{
		_outputStream.Print(_tValues->sumValue,this->sum,_tValues->NewLine);
	}
	if (saveChoose.first == eFileSave::SAVE)
	{
		PosFileSystem::SaveChanges(newData, saveChoose.second);
	}
	this->readMyfile.close();
}

void PosFileSystem::Choose(const uint16_t& Columns, const std::vector<std::size_t>& posOfdels, const uint16_t& ColumnsChoose, const std::optional<uint16_t>& Rows = std::nullopt)
{
	nValues _nValues;
	inputStream _inputstream;
	outputStream _outStream;
	std::optional<uint16_t> kk = std::nullopt;
	auto _tValues = std::make_unique<tValues>();
	do
	{
		auto saveChoose = PosFileSystem::SaveFileCh();
		auto printChoose = PosFileSystem::PrintDataCh();
		_outStream.Print(_tValues->NewLine, _tValues->Oper);
		auto input = _inputstream.uiInput();
		if (input == _nValues.fCho)
		{
			PosFileSystem::ReadData(input,Columns, posOfdels, ColumnsChoose, &bPosFilesystem::Erase,*Rows, saveChoose, printChoose);
			break;
		}
		if (input == _nValues.sCho)
		{
			if (!Rows || *Rows == _nValues.NullValue)
			{
				PosFileSystem::replaceAll();
			}
			PosFileSystem::ReadData(input,Columns, posOfdels,ColumnsChoose, &bPosFilesystem::Replace,*Rows, saveChoose, printChoose);
			break;
		}
		if (input == _nValues.tCho)
		{
			if (!Rows || *Rows == _nValues.NullValue)
			{
				PosFileSystem::CollALl(Columns);
			}
			PosFileSystem::ReadData(input,Columns, posOfdels, ColumnsChoose, &bPosFilesystem::Swap,*Rows, saveChoose, printChoose);
			break;
		}
		if (input == _nValues.foCho)
		{
			PosFileSystem::ReadData(input, Columns, posOfdels, ColumnsChoose, &bPosFilesystem::Sum, *Rows, saveChoose, printChoose);
			break;
		}
		if (input == _nValues.fiCho)
		{
			if (!Rows || *Rows == _nValues.NullValue)
			{
				PosFileSystem::replaceAll();
			}
			PosFileSystem::ReadData(input, Columns, posOfdels, ColumnsChoose, &bPosFilesystem::Fill, *Rows, saveChoose, printChoose);
			break;
		}
		else
		{
			_outStream.Print(_tValues->InvalitInput,_tValues->NewLine);
			continue;
		}
	}
	while (_nValues.infLoop);
}

void PosFileSystem::tRead()
{
	outputStream _outputStream;
	this->readMyfile.open(Path);
	while (getline(this->readMyfile, this->_Data));
	{
		_outputStream.Print(_Data);
	}
	this->readMyfile.close();
}
