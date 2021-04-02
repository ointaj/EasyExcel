#include "Start.h"

void StartingThread::Start()
{
	inputStream _inputStream;
	Data _dataInfo;
	nValues nVal;
	PosFileSystem _posFileSystem;

	char choose;

	_posFileSystem.inputPathDel();
	auto DataAboutDels = _posFileSystem.DelPos();
	auto DataInfo = _dataInfo.DelData(std::make_pair(std::get<1>(DataAboutDels), std::get<2>(DataAboutDels)));
	do
	{
		auto PosOfColumn = _dataInfo.ColumnPos(std::get<0>(DataAboutDels), std::make_tuple(DataInfo.second, std::get<1>(DataAboutDels), DataInfo.first));
		_posFileSystem.Choose(DataInfo.second, std::get<0>(PosOfColumn), std::get<1>(PosOfColumn), std::get<2>(PosOfColumn));
		choose = StartingThread::End();
	}
	while (choose != nVal.END);


}

void StartingThread::Stop()
{
	std::cin.get();
}

char StartingThread::End()
{
	outputStream _outStream;
	std::unique_ptr<tValues> _tVal = std::make_unique<tValues>();
	_outStream.Print(_tVal->sEnd);
	char choose = _getch();
	_outStream.Print(_tVal->NewLine);
	return choose;
}