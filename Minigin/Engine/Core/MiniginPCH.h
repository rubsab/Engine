#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

template<class T>
void Safe_Delete(T& toDelete)
{
	if (toDelete)
	{
		delete toDelete;
		toDelete = nullptr;
	}
}