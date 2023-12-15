#include "pch.h"

// This class is exported from the dll
class GEOMETRY_API Geometry {
public:
	Geometry(void);
	// TODO: add your methods here.
	void print();
};

extern GEOMETRY_API int nGeometry;

GEOMETRY_API int fnGeometry(void);