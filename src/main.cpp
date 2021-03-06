#include <iostream>
#include <string>

#include "BasisManager.h"
#include "Base.h"
#include "Potential.h"
#include "State.h"
#include "Numerov.h"

void box_potential_example() {
	unsigned int nbox = 500;
	double mesh       = 0.01;
	double k          = 0.0;
	double height     = 0.0;
	double width      = 0.0;
	double energy     = 0.0;
	double e_min      = 0.0;
	double e_max      = 2.0;
	double e_step     = 0.01;
	int dimension     = 1;
	std::vector<double> wavefunction;

	// Initialize the base using preset and parameters
	BasisManager::Builder baseBuilder;
	Base base = baseBuilder.addContinuous(mesh, nbox).build(dimension);

	Potential::Builder potentialBuilder(base);

	// No need to setup Box_potential, is just 0 and the above defined cartesian basis sets up the box. 
	// With zero-edge boundary conditions this correspond to infinite well potential with the width of the cartesian basis
    Potential V = potentialBuilder.setType(Potential::PotentialType::BOX_POTENTIAL).build();
    
    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction  = state.getWavefunction();
    energy        = state.getEnergy();

	std::cout << std::endl << energy << std::endl;

	// Printing state
	std::cout << "Printing state" << std::endl;
	std::cout << state;

	// Save to file wavefunction and probability
	state.printToFile();
}

void finite_well_example() {
	unsigned int nbox = 1000;
	double mesh       = 0.1;
	double height     = 5.0;
	double width      = 7.0;
	double energy     = 0.0;
	double e_min      = 0.0;
	double e_max      = 2.0;
	double e_step     = 0.01;
	std::vector<double> wavefunction;

	// Initialize the base using a ContinuousInitializer
	ContinuousInitializer x_ini(mesh,nbox);
	BasisManager::Builder b;
	Base base = b.build(x_ini);
	
	Potential::Builder potentialBuilder(base);
    Potential V = potentialBuilder.setType(Potential::PotentialType::FINITE_WELL_POTENTIAL)
								  .setHeight(height)
								  .setWidth(width)
								  .build();
    
    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction  = state.getWavefunction();
    energy        = state.getEnergy();

	std::cout << std::endl << energy << std::endl;

	// Printing state
	std::cout << "Printing state" << std::endl;
	std::cout << state;
	
	// Save to file wavefunction and probability
	state.printToFile();
}

void harmonic_oscillator_example() {
	unsigned int nbox = 1000;
	double mesh       = 0.01;
	double k          = 1.0;
	double energy     = 0.0;
	double e_min      = 0.0;
	double e_max      = 2.0;
	double e_step     = 0.01;
	int dimension     = 1;
	std::vector<double> wavefunction;

	BasisManager::Builder baseBuilder;
	Base base = baseBuilder.addContinuous(mesh, nbox).build(dimension);

	Potential::Builder potentialBuilder(base);
    Potential V = potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR)
								  .setK(k)
								  .build();
    
    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction  = state.getWavefunction();
    energy        = state.getEnergy();

	std::cout << std::endl << energy << std::endl;

	// Printing state
	std::cout << "Printing state" << std::endl;
	std::cout << state;
	
	// Save to file wavefunction and probability
	state.printToFile();
}

void harmonic_oscillator_2D_example() {
	unsigned int nbox = 1000;
	double mesh       = 0.1;
	double k          = 0.5;
	double energy     = 0.0;
	double e_min      = 0.0;
	double e_max      = 2.0;
	double e_step     = 0.01;

	std::vector<double> wavefunction;

	BasisManager::Builder baseBuilder;
	Base base = baseBuilder.build(Base::basePreset::Cartesian, 2, mesh, nbox);
	
	Potential::Builder potentialBuilder(base);
    Potential V = potentialBuilder.setType(Potential::PotentialType::HARMONIC_OSCILLATOR)
								  .setSeparable(true)
								  .setK(k)
								  .build();
    

    Numerov solver = Numerov(V, nbox);
    State state    = solver.solve(e_min, e_max, e_step);

    wavefunction  = state.getWavefunction();
    energy        = state.getEnergy();

	std::cout << std::endl << energy << std::endl;

	// Save to file wavefunction and probability
	state.printToFile();
}

void custom_workflow() {
	BasisManager::Builder builder = BasisManager::Builder();
	BasisManager *manager = BasisManager::getInstance();
	Base base;
	std::vector<Base> basis;

	// Setup the properties of a new base, using the basis builder
	int dimension = 2;

    // Specify parameters of first dimension
	double start_1 = 0;
	double end_1   = 1000;
	double mesh_1  = 2;

    // Specify parameters of second dimension
    double start_2 = 0;
	double end_2   = 1000;
	double mesh_2  = 2;

    // Add the continuous representation to the base, using the basis builder
    builder.addContinuous(start_1, end_2, mesh_2);
    builder.addContinuous(start_2, end_2, mesh_2);

	// Getting a base object, building with the previous specified parameters in the basis builder.
	// (Specify that the base is Cartesian, passing also the dimension)
	base = builder.build(Base::basePreset::Cartesian, dimension);

	// Add the base in the basis list, using the basis manager
	manager->addBase(base);

	// Get a list of basis from the basis list (Not mandatory)
	basis = manager->getBasisList();

    // Print basis values for each dimension
	std::cout << base;
}

int main(int argc, char **argv) {
	int c = 0;

	std::cout << "Choose: " << std::endl;
	std::cout << "1) Harmonic oscillator (example)" << std::endl;
	std::cout << "2) Box (example)" << std::endl;
	std::cout << "3) Finite well1 (example)" << std::endl;
	std::cout << "4) Custom (step-by-step configuration)" << std::endl;
	std::cout << "5) 2D Harmonic oscillator (example)" << std::endl;
	std::cout << "\nInsert: ";
	std::cin >> c;

	switch(c){
		case 1:
			harmonic_oscillator_example();
			break;
		case 2:
			box_potential_example();
			break;
		case 3:
			finite_well_example();
			break;
		case 4:
			std::cout << "Not ready yet" << std::endl;
			break;
		case 5:
			harmonic_oscillator_2D_example();
			break;     	
		default:
			std::cout << "Not a valid option" << std::endl;
			break;
	}

    return 0;
}

