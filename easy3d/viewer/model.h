/**
 * Copyright (C) 2015 by Liangliang Nan (liangliang.nan@gmail.com)
 * https://3d.bk.tudelft.nl/liangliang/
 *
 * This file is part of Easy3D. If it is useful in your research/work,
 * I would be grateful if you show your appreciation by citing it:
 * ------------------------------------------------------------------
 *      Liangliang Nan.
 *      Easy3D: a lightweight, easy-to-use, and efficient C++
 *      library for processing and rendering 3D data. 2018.
 * ------------------------------------------------------------------
 * Easy3D is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * Easy3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EASY3D_MODEL_H
#define EASY3D_MODEL_H


#include <string>
#include <vector>
#include <unordered_map>

#include <easy3d/core/types.h>


namespace easy3d {

    class Drawable;
    class PointsDrawable;
    class LinesDrawable;
    class TrianglesDrawable;

    /*
    * Model is the base class for 3D models, e.g., SurfaceMesh, PointCloud.
    * A Model can have multiple drawables, e.g., faces, vertices, edges.
    */
    class Model
    {
    public:
        Model(const std::string& name = "unknown");
        virtual ~Model();

        const std::string& name() const { return name_; }
        void set_name(const std::string& n) { name_ = n; }

        virtual const Box3& bounding_box() const;

        /// returns number of vertices in the model
        virtual unsigned int n_vertices() const = 0;

        /// vector of vertex positions (read only)
        virtual const std::vector<vec3>& points() const = 0;

        /// Sets the model modified after operations like remeshing/smoothing. This will update the OpenGL buffers,
        /// ensuring the rendering to be updated automatically.
        /// Note: all drawables associated with this model will be updated. This is equivalent to call the set_modified()
        ///       function for every drawables. Performance may be improved by calling only the affected drawables (e.g.,
        ///       the change in texture coordinates of a surface mesh doesn't change the rendering of its wireframe).
        void update();

        //-------------------- rendering  -----------------------

        bool is_visible() const { return visible_; }
        void set_visible(bool b) { visible_ = b; }

        // Gets the drawable named 'name'.
        // Returns a nullptr if the drawable does not exist.
        PointsDrawable* get_points_drawable(const std::string& name) const;
        LinesDrawable*  get_lines_drawable(const std::string& name) const;
        TrianglesDrawable*  get_triangles_drawable(const std::string& name) const;

        /// Create a drawable assign it a name.
        /// \param name The name of the drawable
        /// \param update_func An callback function for the OpenGL buffers to be automatically updated when the model
        ///        or the drawable has changed. This function is not needed for standard drawables, e.g.,
        ///             - SurfaceMesh: "faces", "edge", "vertices", "borders", "locks";
        ///             - PointCloud: "vertices";
        ///             - Graph: "edge", "vertices".
        ///        For non-standard drawable, the user must provide such a callback function in order for Easy3D to
        ///        update the OpenGL buffers. The parameters of the function are:
        ///             - the pointer to the base class of this model;
        ///             - the pointer to the base class of the drawable;
        ///             - user data.
        /// \return The created drawable. If a drawable with 'name' already exists, the creation will be ignored and
        ///         the existing drawable will be returned.
        PointsDrawable* add_points_drawable(const std::string& name, std::function<void(Model*, Drawable*)> update_func = nullptr);
        LinesDrawable*  add_lines_drawable(const std::string& name, std::function<void(Model*, Drawable*)> update_func = nullptr);
        TrianglesDrawable*  add_triangles_drawable(const std::string& name, std::function<void(Model*, Drawable*)> update_func = nullptr);

        // Returns all available drawables.
        const std::vector<PointsDrawable*>&  points_drawables() const { return points_drawables_; }
        const std::vector<LinesDrawable*>&   lines_drawables() const { return lines_drawables_; }
        const std::vector<TrianglesDrawable*>& triangles_drawables() const { return triangles_drawables_; }

        /// prints the names of all properties to an output stream (e.g., std::cout).
        virtual void property_stats(std::ostream &output) const = 0;

        bool is_selected() const { return selected_; }
        void set_selected(bool b) { selected_ = b; }

    protected:
        std::string	name_;
        bool		visible_;
        Box3		bbox_;
        bool		bbox_known_;
        bool        selected_;

        std::vector<PointsDrawable*>    points_drawables_;
        std::vector<LinesDrawable*>     lines_drawables_;
        std::vector<TrianglesDrawable*> triangles_drawables_;
    };

}

#endif  // EASY3D_MODEL_H
