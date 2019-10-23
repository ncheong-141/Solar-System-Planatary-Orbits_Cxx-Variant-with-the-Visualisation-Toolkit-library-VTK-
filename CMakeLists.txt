cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Solar_System_Project)

find_package(VTK COMPONENTS 
  vtkChartsCore
  vtkCommonCore
  vtkCommonDataModel
  vtkInteractionStyle
  vtkRenderingContext2D
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkViewsContext2D QUIET)
if (NOT VTK_FOUND)
  message("Skipping Solar_System_Project: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(Solar_System_Project MACOSX_BUNDLE Solar_System_Project.cxx )
  target_link_libraries(Solar_System_Project PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(Solar_System_Project MACOSX_BUNDLE Solar_System_Project.cxx )
  target_link_libraries(Solar_System_Project PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS Solar_System_Project
    MODULES ${VTK_LIBRARIES}
    )
endif ()