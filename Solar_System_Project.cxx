/* Solar System Project

Objective:			Simulate and visualize the movement of planets in the Solar System.
Visualization:		Visualization Toolkit (VTK) which uses OpenGL

VTK Packages currently in use:

#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>

---- IF THIS CHANGES YOU MUST CHANGE THE "CMakeLists.txt" file and re-construct the solution file (Solar_Sys.. .sln) in CMAKE 
TO RELINK THE PROJECT WITH THE VTK LIBRARY. ----

*/

// External modules
#include <iostream>
#include <vector>
#include <string>


// Internal modules 
#include "debug_macro.h"
#include "SolarSystem_Celestialbody_Classes.h"
#include "SolarSystem_functions.h"

// VTK wrapper for ease of visualization 
#include "VTK_2D_plotter.h"
#include "VTK_3D_plotter.h"

int main() {

	/* Define inital conditions */

	/* Define simyulation parameters */
	int max_time = 1000;
	int timestep = 1;
	const int no_planets = 9;
	// const int plot_disc = 360;

	/* Define planet parameters and set up celestial body arrays for processing during simulation */
	Celestial_body Planets[9] = {
	//			const char* name, float mass, float diameter,	float semi_major_axis,	float pericentre, float apocentre, float orbital_period,	float orbital_inclination,		float eccentricity
	Celestial_body("Mercury",   0.330e24f,       4879.0f,           57.9e6f,                 46e6f,           69.8e6f,             88.0f,						7.0f,                    0.205f),
	Celestial_body("Venus",     4.8e24f,         12104.0f,          108.2e6f,                107.5e6f,        108.9e6f,            224.7f,						3.4f,                    0.007f),
	Celestial_body("Earth",     5.97e24f,        12756.0f,          149.6e6f,                147.1e6f,        152.1e6f,            365.2f,						0.0f,                    0.017f),
	Celestial_body("Mars",      0.642e24f,       6792.0f,           227.9e6f,                206.6e6f,        249.2e6f,            687.0f,						1.9f,                    0.094f),
	Celestial_body("Jupiter",   1898e24f,        142984.0f,         778.6e6f,                740.5e6f,        816.6e6f,            4331.0f,						1.3f,                    0.049f),
	Celestial_body("Saturn",    568e24f,         120536.0f,         1433.5e6f,               1352.6e6f,       1514.5e6f,           10747.0f,					2.5f,                    0.057f),
	Celestial_body("Uranus",    86.8e24f,        51118.0f,          2872.5e6f,               2741.3e6f,       3003.6e6f,           30589.0f,					0.8f,                    0.046f),
	Celestial_body("Neptune",   102e24f,         49528.0f,          4495.1e6f,               4444.5e6f,       4545.7e6f,           59800.0f,					0.8f,                    0.011f),
	Celestial_body("Pluto",     0.0146e24f,      2370.0f,           5906.4e6f,               4436.8e6f,       7375.9e6f,           90560.0f,					17.2f,                   0.244f) };
	
	/* ===============================  3D Variant: =============================================
		Collect data for plotting and transform into VTK wrapper format to input into VTK function */

		// Array of names to enable looping over names 
	std::string names[no_planets];

	// 3D plot data for plot input 
	//float plot_data[W_VTK::_3D::spatial_dimensions][Celestial_body::NP_theta];

	for (int i = 0; i < no_planets; i++) {



		// Collect names to be able to loop over names for plotting (VTK Lines must be named!) 
		names[i] = Planets[i].name;

		// Randomly generate true anomoly positions for start and calculate respective values
		Planets[i].theta = (std::rand() % 360) * (180 / pi);

		Planets[i].r = SSF::orbital_radius(Planets[i].a, Planets[i].e, Planets[i].theta);
		Planets[i].XYZ[0] = SSF::x_coordinate(Planets[i].OF, Planets[i].r, Planets[i].theta);
		Planets[i].XYZ[1] = SSF::y_coordinate(Planets[i].r, Planets[i].theta);
		Planets[i].XYZ[2] = SSF::z_coordinate(Planets[i].XYZ[0], Planets[i].incl, Planets[i].theta);
	}


	// Instantiate plot data structure for VTK
	vtkSmartPointer<vtkChartXYZ> plot_datastructure = W_VTK::_3D::multiplot_chart_instantiation();


	// Calculate plot widths for plotting variables
	//float base = 10;			// Earth as base width
	//float diameter_ratios[9];
	//float plot_widths[9];

	// Plot the planet orbits 
	for (int i = 0; i < no_planets; i++) {
		W_VTK::_3D::Line_plotter<Celestial_body::NP_theta>(plot_datastructure, Planets[i].VTK_XYZ_plot_data, "snow", 1.0f);


		//if (i != 2) {
		//	//diameter_ratios[i] = Planets[i].diameter / Planets[2].diameter;
		//	diameter_ratios[i] = Planets[i].diameter / Planets[2].diameter;
		//}
		//else {
		//	diameter_ratios[i] = 1;  
		//}
		//// Calculate the respective plot width 
		//plot_widths[i] = diameter_ratios[i] * base;

	}
	
	// Plot the planets (different colours and widths so not in loop) 
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[0].XYZ, "cadmium_yellow_light"	, 5.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[1].XYZ, "light_goldenrod"		, 10.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[2].XYZ, "sky_blue_deep"			, 10.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[3].XYZ, "madder_lake_deep"		, 10.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[4].XYZ, "peach_puff"			, 20.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[5].XYZ, "beige"					, 17.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[6].XYZ, "alice_blue"			, 15.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[7].XYZ, "navy"					, 15.0f);
	W_VTK::_3D::Scatter_plotter(plot_datastructure, Planets[8].XYZ, "light_grey"			, 2.0f);


	// Create render window 
	W_VTK::_3D::multiplot_view_window(plot_datastructure, "cold_grey");



	return EXIT_SUCCESS;
}
