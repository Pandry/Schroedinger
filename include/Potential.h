#ifndef POTENTIAL
#define POTENTIAL

#include <vector>
#include <string>
#include <algorithm>

class Potential {
private:
    std::vector<double> x;
    std::vector<double> v;
    std::string pot_name;

public:
    Potential(std::vector<double>);
    Potential(std::vector<double>, std::string, double);

    std::vector<double> get_v();

    void ho_potential(double);
    void box_potential();
    void finite_well_potential();
};

#endif