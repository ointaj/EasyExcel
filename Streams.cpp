#include "Streams.h"

uint16_t inputStream::uiInput()
{
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	outputStream _outStream;
	uint16_t value;
	while (!(std::cin >> value))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		_outStream.Print(_tValues->InvalitInput, _tValues->sArrow);
	}
	return value;
}

std::string inputStream::sInput()
{
	outputStream _outputStream;
	std::unique_ptr<tValues> _tValues = std::make_unique<tValues>();
	std::string value;
	std::cin >> value;
	_outputStream.Print(_tValues->NewLine);
	return value;
}

