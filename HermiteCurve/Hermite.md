# Hermite Curve

The Hermite Curve is a mathematical spline that smoothly interpolates between a sequence of control points. This implementation provides a Hermite curve through the `HermiteCurve` class.

## Usage

### Class Initialization

To create a Hermite curve, instantiate the `HermiteCurve` class with a vector of `Point3D` control points:

```cpp
#include "HermiteCurve.h"

// Define your control points
std::vector<Point3D> controlPoints = { /* ... */ };

// Create a HermiteCurve
HermiteCurve hermiteCurve(controlPoints);
```

### Evaluate the Curve

You can calculate points along the Hermite curve using the `calculateHermite` method:

```cpp
// Calculate Hermite curve points
std::vector<Point3D> curvePoints = hermiteCurve.calculateHermite();
```
## Snapshots
![image](https://github.com/RamCCTech/Visualizer/assets/149322355/96fab638-d8d4-4056-960d-09212ce6a886)
