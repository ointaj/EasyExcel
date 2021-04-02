#pragma once
#include "Streams.h"

class dStartingThread
{
public:

	dStartingThread() = default;
	
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual char End() = 0;

	~dStartingThread() = default;
};

class StartingThread :  public dStartingThread
{
public:
	StartingThread() = default;

	virtual void Start() override;
	virtual void Stop() override;
	virtual char End() override;

	~StartingThread() = default;
};