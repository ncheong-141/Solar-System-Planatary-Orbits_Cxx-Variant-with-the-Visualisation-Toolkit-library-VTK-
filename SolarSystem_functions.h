#pragma once
/* Interface file containing functions for solar system simulation and visualization */

// External Modules
#include <iostream>

// Internal modules 
#include "Constants.h"
#include "debug_macro.h"


// Namespace for code clarity (differentiate between class and functions easier) 
namespace SSF {

	/* Gravitational attraction force: Newtons law of gravitational attraction (from III law) */
	float gravitational_attraction(int m1, int m2, float r) {
		return G * ((m1 * m2) / (r * r));
	}


	/* Polar Orbit equation */
	// Oribital radius calculation using geometric parameters(returns radius) 
	float orbital_radius(float a, float e, float theta) {
		return (a * (1 - e*e)) / (1 + e * std::cos(theta)); 
	}
	// Orbital radius calculation using dynamic parameters
	float orbital_radius(float h, float mu, float e, float theta) {
		return ((h*h) / mu) / (1 + e * std::cos(theta)); 
	}

	/* Calculating spatial coordinates of orbit */
	float x_coordinate(float OF, float r, float theta) {
		return (OF + (r * std::cos(theta)));
	}

	float y_coordinate(float r, float theta) {
		return r * std::sin(theta); 
	}

	float z_coordinate(float x_pos, float incl, float theta) {
		if (theta >= 0 && theta <= (pi / 2)) {
			return x_pos * std::tan(incl); 
		}
		else if (theta >= (3 / 2) * pi && theta <= 2 * pi) {
			return x_pos * std::tan(incl);
		}
		else {
			return x_pos * std::tan(incl + pi); 
		}
	}


	/*  Orbital energy derived from..
    Note, orbital energy is conserved anywhere on the orbit */
	float orbital_energy(float v, float mu, float r) {
		return ((v * v) / 2) - (mu / r);
	}
	float orbital_energy(float mu, float a) {
		return -mu / 2 * a;
	}

	/* Flight path angle (angle between velocity vector and theta^ ) */
	float flight_path_angle(float e, float theta) {
		return std::atan((e * std::sin(theta)) / (1 + (e * std::cos(theta))));
	}

	/* Orbital velocity at arbitrary point, r */
	float orbital_velocity(float mu, float r, float a) {
		return std::pow(((2 * mu / r) - (mu / a)), (1 / 2));
	}

	/* Velocity at pericentre and apocentre */
	float velocity_pericentre(float mu, float a, float e) {
		return std::pow(((mu / a) * ((1 + e) / (1 - e))), (1 / 2));
	}

	float velocity_apocentre(float mu, float a, float e) {
		return std::pow(((mu / a) * ((1 - e) / (1 + e))), (1 / 2));
	}

	/* Angular momentum at arbitrary  point, r CHANGE THIS */
	float orbital_angular_momentum(float v, float gamma, float r) {
		return r * v * std::cos(gamma);
	}





}