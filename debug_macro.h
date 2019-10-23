#pragma once
// Macro for debugging or not (cannot use debug mode with VTK library (idk why); 

// External modules
#include <iostream>


#define DEBUG 1
#if		DEBUG==1

#define d_print(X) std::cout << X << std::endl; 

#elif	DEBUG==0

#define d_print(X)

#elif	DEBUG==-1

#define d_print(X)
/* Include VTK wrapper modules (made to simplify plotting code) */
#include "VTK_Line_plotter.h"

#endif

// Macro because i like having return EXIT_SUCCESS implemented by VTK but the above stops me using it! 
#define EXIT_SUCCESS 0
