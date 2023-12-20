# Bezier Curve

## Overview

This project implements a Bezier curve using C++ and provides functionality to calculate points on the curve.

## Usage

### 1. Constructor

```cpp
BezierCurve::BezierCurve(std::vector<Point3D> points);
```

The constructor initializes the Bezier curve with control points.

### 2. Calculate Bezier Curve

```cpp
std::vector<Point3D> BezierCurve::calculateBezier();
```

This function computes points on the Bezier curve using the control points.

### 3. Evaluate Bezier Curve at a Specific Parameter

```cpp
Point3D BezierCurve::evaluateBezier(double t);
```

This function evaluates the Bezier curve at a specific parameter 't' within the range [0, 1].

## Example

```cpp
// Create a Bezier curve with control points
BezierCurve bezierCurve({Point3D(0, 0), Point3D(1, 2), Point3D(3, 4), Point3D(5, 6)});

// Calculate points on the Bezier curve
std::vector<Point3D> curvePoints = bezierCurve.calculateBezier();
```

## Snapshots
![image](https://github.com/RamCCTech/Visualizer/assets/149322355/c3900227-3d91-4167-8042-39fbd9ed76d6)
