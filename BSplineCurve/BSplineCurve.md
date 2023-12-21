# BSpline Curve

## Overview

This project implements a B-Spline curve using C++ and provides functionality to calculate points on the curve.

## Usage

### 1. Constructor

```cpp
BSplineCurve::BSplineCurve(int degree);
```

The constructor initializes the B-Spline curve with the specified degree.

### 2. Generate Uniform Knots

```cpp
std::vector<float> BSplineCurve::generateUniformKnots(int num_control_points);
```

This function generates uniform knots for the B-Spline curve based on the number of control points.

### 3. B-Spline Basis Function

```cpp
float BSplineCurve::bSplineBasis(int i, int k, float t, const std::vector<float>& knots);
```

This function calculates the B-Spline basis function for a given control point, degree, parameter 't', and knot vector.

### 4. Evaluate B-Spline Curve

```cpp
std::vector<Point3D> BSplineCurve::evaluate(std::vector<Point3D> control_points, float t);
```

This function computes points on the B-Spline curve using the provided control points and parameter 't'.

## Snapshots
![image](https://github.com/RamCCTech/Visualizer/assets/149322355/b2fe5b7b-b6b8-4ef8-a53b-652912319ace)

