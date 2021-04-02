#pragma once

#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <tuple>	
#include <algorithm>
#include <utility>
#include <conio.h>

#include "Data.h"
#include "Values.h"
#include "FileSystem.h"

class binputStream
{
protected:
public:
	binputStream() = default;
	virtual uint16_t uiInput() = 0;
	virtual std::string sInput() = 0;
	~binputStream() = default;
};
class inputStream : public binputStream
{
private:
	
public:
	inputStream() = default;
	virtual uint16_t uiInput() override;
	virtual std::string sInput() override;
	~inputStream() = default;
};

class outputStream
{
public:
	outputStream() = default;

	template<class ...Arvv>
	void Print(Arvv&&... arg)
	{
		((std::cout << std::forward<Arvv>(arg)), ...);
	}

	~outputStream() = default;
};


		
