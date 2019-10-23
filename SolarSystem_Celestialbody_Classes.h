#pragma once 
/* Interface file containing solar system class information for simulation and visualization */

// External modules 
#include <iostream>

// Internal modules 
#include "Constants.h"
#include "debug_macro.h"
#include "SolarSystem_functions.h"

class Celestial_body {

private:
	// Focal point parameters of celestial bodies (The sun) 
	float m_sun = 1.989e30f;


public:

	// Discretization parameters of orbit for plotting
	static const int NP_theta = 360;

	// Celestial body variables (unchanging)
	const char*		name;			// Name
	const float		m;				// Mass
	const float		diameter;		// Diameter
	const float		a;				// Semi-Major axis
	const float		rp;				// Pericentre
	const float		ra;				// Apocentre
	const float		T;				// Orbital period
	float			incl;			// Orbital inclination 
	const float		e;				// Eccentricity
	float			b;				// Semi-Minor axis (Not const as will be calculated) 
	float			h;				// Angular momentum 
	float			mu;				// Gravitational parameter
	float			OF;				// Distance between elipse origin and focal point
	float			epsilon;		// Energy


	// Changing variables in simulation 
	float			r;				// Current radius of orbit
	float			XYZ[3];			//
	float			theta;			// True anomoly 
	float			v;				// Current velocity
	float			gamma;			// Current flight path angle

	/* Plotting variables for orbits */
	float r_plot[NP_theta]; 
	float x_plot[NP_theta];
	float y_plot[NP_theta];
	float z_plot[NP_theta];
	float VTK_XYZ_plot_data[3][NP_theta]; 
	float theta_plot;
	float plot_increment; 



	/* Constructor with variable inputs */
	Celestial_body(const char* name, float mass, float diameter, float semi_major_axis, float pericentre,
		float apocentre, float orbital_period, float orbital_inclination, float eccentricity) :

		// Initializer list (faster for complex objects but no difference for prim types (using anyway..) )
		name(name), m(mass), diameter(diameter), a(semi_major_axis), rp(pericentre), ra(apocentre),
		T(orbital_period), incl(orbital_inclination), e(eccentricity), b(0), h(0), mu(0), OF(0), epsilon(0),
		r(0), XYZ{ 0 }, theta(0), v(0), gamma(0),
		r_plot{ 0 }, x_plot{ 0 }, y_plot{ 0 }, z_plot{ 0 }, VTK_XYZ_plot_data{ {0} }, theta_plot(0), plot_increment(0)
	{
		
		/* ======================================  Prepare input data for simulation ======================================  */

		// Convert units to correct data for simulation
		incl = incl* (180 / pi); 

		// Pre-calculate key characterstics for the orbit of the celestial body 
		b = a * std::pow((1 - e*e),(1/2));		// Semi-minor axis
		mu = G*(m_sun + m);						// Gravitational parameter
		OF = a * e;								// Distance between origin of ellipse orbit and focal point


		/* Calculate orbital trajectories for plotting */
		plot_increment = ((2*pi) / (NP_theta - 1));

		
		/* ====================================== Plot data ====================================== */
		// Loop over range of true anomolies and calculate radius, x, y and z and input into different
		// array configurations for VTK plotting wrapper (So can chose how to plot, either 2D or 3D, differnt functions etc) 
		for (int i = 0; i < NP_theta; i++) {

			// Calculate radius of orbit at angular position, theta_plot (true anomaly)
			r_plot[i] = SSF::orbital_radius(a, e, theta_plot); 

			// Calculate cartesian coordinates based off radius and true anomoly 
			x_plot[i] = SSF::x_coordinate(OF, r_plot[i], theta_plot); 
			y_plot[i] = SSF::y_coordinate(r_plot[i], theta_plot);
			z_plot[i] = SSF::z_coordinate(x_plot[i], incl, theta_plot); 

			VTK_XYZ_plot_data[0][i] = x_plot[i]; 
			VTK_XYZ_plot_data[1][i] = y_plot[i];
			VTK_XYZ_plot_data[2][i] = z_plot[i];

			// Increment theta_plot for next iteration 
			theta_plot += plot_increment; 
		}
	}

	/* Default constructor */
	// Celestial_body() {}; 

	/* Default destructor */

};