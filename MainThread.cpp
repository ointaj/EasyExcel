#include "Streams.h"

int main()
{
	std::unique_ptr<StartingThread> _startinThread = std::make_unique<StartingThread>();
	_startinThread->Start();
	_startinThread->Stop();
}