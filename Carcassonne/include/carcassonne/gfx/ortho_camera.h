// Copyright (c) 2013 Dougrist Productions
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: Benjamin Crist
// File: carcassonne/gfx/ortho_camera.h

#ifndef CARCASSONNE_GFX_ORTHO_CAMERA_H_
#define CARCASSONNE_GFX_ORTHO_CAMERA_H_
#include "carcassonne/_carcassonne.h"

#include "carcassonne/gfx/rect.h"
#include "carcassonne/gfx/camera.h"
#include "carcassonne/gfx/graphics_configuration.h"

namespace carcassonne {
namespace gfx {

class OrthoCamera : public Camera
{
public:
   OrthoCamera(const GraphicsConfiguration& gfx_cfg);

   void setClient(const Rect& rect);

   void recalculate();

   glm::vec3 windowToWorld(const glm::vec2& window_coords) const;

private:
   const GraphicsConfiguration& gfx_cfg_;

   Rect client_;

   OrthoCamera(const OrthoCamera&);
   void operator=(const OrthoCamera&);
};

} // namespace carcassonne::gfx
} // namespace carcassonne

#endif
