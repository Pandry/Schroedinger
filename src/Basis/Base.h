#ifndef BASE_H
#define BASE_H

#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

#include "DiscreteBase.h"
#include "ContinuousBase.h"

class Base
{
public:
	enum basePreset { Custom = 0, Cartesian = 1, Spherical = 2, Cylindrical = 3 };
	enum baseType { Radial = 0, Momentum = 1, Other = 2};
	enum boundaryCondition { ZEROEDGE = 0, PERIODIC = 1 };

	Base(basePreset, int, std::vector< ContinuousBase >, std::vector< DiscreteBase >);
	Base(std::vector<double> coords);
	Base() {}

	int getDim() { return this->dimensions; };
	boundaryCondition getBoundary(){ return this->boundary; };
	std::vector<ContinuousBase> getContinuous() { return this->continuous; };
	std::vector<DiscreteBase> getDiscrete() { return this->discrete; };

	std::vector<double> getCoords();
	friend std::ostream& operator<< (std::ostream& stream, Base& base);

private:
	std::vector< DiscreteBase > discrete;
	std::vector< ContinuousBase > continuous;
	int dimensions;
	boundaryCondition boundary;
};

#endif
