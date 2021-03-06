cmake_minimum_required(VERSION 3.1)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})


set(${PROJECT_NAME}_HEADERS
        delaunay.h
        delaunay_2d.h
        delaunay_3d.h
        extrusion.h
        surface_mesh_geometry.h
        gaussian_noise.h
        point_cloud_normals.h
        point_cloud_poisson_reconstruction.h
        point_cloud_ransac.h
        point_cloud_simplification.h
        surface_mesh_components.h
        surface_mesh_curvature.h
        surface_mesh_enumerator.h
        surface_mesh_fairing.h
        surface_mesh_features.h
        surface_mesh_geodesic.h
        surface_mesh_hole_filling.h
        surface_mesh_parameterization.h
        surface_mesh_planar_partition.h
        surface_mesh_remeshing.h
        surface_mesh_sampler.h
        surface_mesh_simplification.h
        surface_mesh_smoothing.h
        surface_mesh_stitching.h
        surface_mesh_subdivision.h
        surface_mesh_topology.h
        surface_mesh_triangulation.h
        tessellator.h
        text_mesher.h
        triangle_mesh_kdtree.h
        )

set(${PROJECT_NAME}_SOURCES
        delaunay.cpp
        delaunay_2d.cpp
        delaunay_3d.cpp
        extrusion.cpp
        surface_mesh_geometry.cpp
        gaussian_noise.cpp
        point_cloud_normals.cpp
        point_cloud_poisson_reconstruction.cpp
        point_cloud_ransac.cpp
        point_cloud_simplification.cpp
        surface_mesh_components.cpp
        surface_mesh_curvature.cpp
        surface_mesh_enumerator.cpp
        surface_mesh_fairing.cpp
        surface_mesh_features.cpp
        surface_mesh_geodesic.cpp
        surface_mesh_hole_filling.cpp
        surface_mesh_parameterization.cpp
        surface_mesh_planar_partition.cpp
        surface_mesh_remeshing.cpp
        surface_mesh_sampler.cpp
        surface_mesh_simplification.cpp
        surface_mesh_smoothing.cpp
        surface_mesh_stitching.cpp
        surface_mesh_subdivision.cpp
        surface_mesh_topology.cpp
        surface_mesh_triangulation.cpp
        tessellator.cpp
        text_mesher.cpp
        triangle_mesh_kdtree.cpp
        )


add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "easy3d")

target_include_directories(${PROJECT_NAME} PRIVATE ${EASY3D_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${EASY3D_THIRD_PARTY}/RANSAC-1.1)

target_link_libraries(${PROJECT_NAME} core util kdtree poisson_recon-9.0.1 RANSAC-1.1 triangle tetgen libtess)

set(EIGEN_SOURCE_DIR ${EASY3D_THIRD_PARTY}/eigen)
target_include_directories(${PROJECT_NAME} PRIVATE ${EIGEN_SOURCE_DIR})

# It's "Boost", not "BOOST" or "boost". Case matters.
find_package(Boost)
if (Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_BOOST)
endif ()