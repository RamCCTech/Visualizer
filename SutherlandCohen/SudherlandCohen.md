# Sutherland-Cohen Line Clipping

This project implements the Sutherland-Cohen line clipping algorithm to clip a line against a rectangular region.

## Overview

The Sutherland-Cohen algorithm is used for line clipping against a rectangular region defined by four lines. It categorizes points as being inside, outside, or on the boundary of the region and clips the line accordingly.

## Classes

### `SutherlandCohen`

This class represents the Sutherland-Cohen line clipping algorithm. It takes a `Shape` object representing the rectangular region and a `Line` object to be clipped.

#### Constructor
```cpp
SutherlandCohen::SutherlandCohen(Shape region, Line l);
```

#### Public Methods
```cpp
Line SutherlandCohen::getClippedLine();
```
Returns the clipped line based on the provided region and input line.

#### Private Methods
```cpp
void SutherlandCohen::setRegion();
```
Sets the region boundaries by analyzing the lines of the provided shape.

```cpp
int SutherlandCohen::computeCode(Point3D p);
```
Computes the region code for a given point based on its position relative to the rectangular region.

## How to Use

1. Create a `Shape` object to define the rectangular region.
2. Create a `Line` object to represent the line to be clipped.
3. Instantiate a `SutherlandCohen` object with the `Shape` and `Line`.
4. Call the `getClippedLine` method to obtain the clipped line.

```cpp
Shape region(/* Define the rectangular region */);
Line inputLine(/* Define the line to be clipped */);

SutherlandCohen scAlgorithm(region, inputLine);
Line clippedLine = scAlgorithm.getClippedLine();
```

## Snapshot
![image](https://github.com/RamCCTech/Visualizer/assets/149322355/ee5b00d4-73ae-44e8-8b13-83902d5fb48f)

![image](https://github.com/RamCCTech/Visualizer/assets/149322355/eee3dbd6-0a4f-4707-a8c6-fb6352f267f9)
