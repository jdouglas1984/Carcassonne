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
// File: carcassonne/tile.h
//
// Represents a single game tile which can be placed in a draw pile or on the
// board.

#ifndef CARCASSONNE_TILE_H_
#define CARCASSONNE_TILE_H_
#include "carcassonne/_carcassonne.h"

#include "carcassonne/gfx/sprite.h"

#include "carcassonne/features/feature.h"
#include "carcassonne/features/city.h"
#include "carcassonne/features/cloister.h"
#include "carcassonne/features/farm.h"
#include "carcassonne/features/road.h"

namespace carcassonne {

// Structure that represents the features present on a particular side of a tile
struct TileEdge
{
   TileEdge(features::Farm* farm);
   TileEdge(features::Road* road, features::Farm* cw_farm, features::Farm* ccw_farm);
   TileEdge(features::City* city);

   enum Type {
      TYPE_FARM = 0,  // a single farm over the entire edge
      TYPE_ROAD = 1,  // a road in the center with 2 farms (possibly the same farm) on either side
      TYPE_CITY = 2   // a single city over the entire edge
   } type;

   bool open;  // true if there is no tile connecting to this side

   union {
      features::Farm* farm;
      features::Road* road;
      features::City* city;
   };

   // these are null if type is not TYPE_ROAD
   features::Farm* cw_farm;
   features::Farm* ccw_farm;
};

class Tile
{
public:

   enum Type {
      // a tile which has been placed on the board.
      TYPE_PLACED = 0,                     

      // a tile which is in a pile or currently being placed.
      TYPE_FLOATING = 1,

      // a placeholder for a spot on the board where the tile that is currently
      // being placed could be placed.  Should have a semitransparent green
      // color.
      TYPE_EMPTY_PLACEABLE = 2,

      // a placeholder for a spot on the board where the tile that is currently
      // being placed will not fit, but could if it were rotated.  Should have
      // a semitransparent yellow color.
      TYPE_EMPTY_PLACEABLE_IF_ROTATED = 3,

      // a placeholder for a spot on the board where the tile that is currently
      // being placed will not fit, but could if it were rotated.  Should have
      // a semitransparent red color.
      TYPE_EMPTY_NOT_PLACEABLE = 4
   };

   enum Rotation {
      ROTATION_NONE = 0,
      ROTATION_CW = 1,
      ROTATION_180 = 2,
      ROTATION_CCW = 3
   };

   // the features which a particular side refer to depend on the rotation
   // of the tile.
   enum Side {
      SIDE_NORTH = 0,
      SIDE_EAST = 1,
      SIDE_SOUTH = 2,
      SIDE_WEST = 3
   };
   
   // Constructs a tile of one of the TYPE_EMPTY_* types
   Tile(Type type);

   // Sets the tile's type.  A TYPE_EMPTY_* tile can only be set to any of the
   // other TYPE_EMPTY_* types.  A TYPE_PLACED tile can't be changed to any
   // other type.  A TYPE_FLOATING tile can only be changed to TYPE_PLACED.
   void setType(Type type);


   // Rotates the tile if it is a TYPE_FLOATING tile
   void rotateClockwise();
   void rotateCounterclockwise();

   // Returns the type of features which currently exist on the requested side.
   const TileEdge& getEdge(Side side);

   std::vector<features::Feature*> getFeatures();

   // called when a tile is placed 
   void closeSide(Side side, Tile* new_neighbor);

   // 
   void closeDiagonal(Side clockwise_from, Tile* new_diagonal_neighbor);


   void draw() const;

   void replaceCity(const features::City& old_city, const features::City& new_city);
   void replaceFarm(const features::Farm& old_farm, const features::Farm& new_farm);
   void replaceRoad(const features::Road& old_road, const features::Road& new_road);
   

private:
   glm::vec4 color_;
   gfx::Sprite* sprite_;   // gfx::Mesh* instead perhaps?

   glm::vec3 position_;
   Rotation rotation_;

   TileEdge edges_[4];

   std::vector<std::shared_ptr<features::City> > cities_;
   std::vector<std::shared_ptr<features::Road> > roads_;
   std::vector<std::shared_ptr<features::Farm> > farms_;
   std::unique_ptr<features::Cloister> cloister_;

   // Disable copy-construction & assignment - do not implement
   Tile(const Tile&);
   void operator=(const Tile&);
};

} // namespace carcassonne

#endif