// Algorithms.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Algorithms.h"


// This is an example of an exported variable
ALGORITHMS_API int nAlgorithms=0;

// This is an example of an exported function.
ALGORITHMS_API int fnAlgorithms(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CAlgorithms::CAlgorithms()
{
    return;
}
