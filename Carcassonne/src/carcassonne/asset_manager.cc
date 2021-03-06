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
// File: carcassonne/asset_manager.cc

#include "carcassonne/asset_manager.h"

namespace carcassonne {

AssetManager::AssetManager(Game& game, const std::string& filename)
   : game_(game),
     db_(filename)
{
}

db::DB& AssetManager::getDB()
{
   return db_;
}

void AssetManager::reload()
{
   for (auto i(textures_.begin()), end(textures_.end()); i != end; ++i)
   {
      try
      {
         i->second->init();
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to reinitialize texture \"" << i->second->getName() << "\": " << err.what() << std::endl;
      }
   }

   for (auto i(fonts_.begin()), end(fonts_.end()); i != end; ++i)
      i->second->init();

   for (auto i(meshes_.begin()), end(meshes_.end()); i != end; ++i)
   {
      try
      {
         i->second->init();
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to reinitialize mesh \"" << i->second->getName() << "\": " << err.what() << std::endl;
      }
   }
}

gfx::Texture* AssetManager::getTexture(const std::string& name)
{
   std::unique_ptr<gfx::Texture>& ptr = textures_[name];

   if (!ptr)
   {
      try
      {
         ptr.reset(new gfx::Texture(db_, name));
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to load texture \"" << name << "\": " << err.what() << std::endl;
      }
   }

   return ptr.get();
}

gfx::TextureFont* AssetManager::getTextureFont(const std::string& name)
{
   std::unique_ptr<gfx::TextureFont>& ptr = fonts_[name];

   if (!ptr)
   {
      try
      {
         ptr.reset(new gfx::TextureFont(*this, name));
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to load texture font \"" << name << "\": " << err.what() << std::endl;
      }
   }

   return ptr.get();
}

gfx::Mesh* AssetManager::getMesh(const std::string& name)
{
   std::unique_ptr<gfx::Mesh>& ptr = meshes_[name];

   if (!ptr)
   {
      try
      {
         ptr.reset(new gfx::Mesh(*this, name));
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to load mesh \"" << name << "\": " << err.what() << std::endl;
      }
   }

   return ptr.get();
}

gfx::Sprite AssetManager::getSprite(const std::string& name)
{
   auto i(sprites_.find(name));
   if (i == sprites_.end())
   {
      try
      {
         gfx::Sprite s(*this, name);
         sprites_.insert(std::make_pair(name, s));
         return s;
      }
      catch (std::runtime_error& err)
      {
         std::cerr << "Failed to load sprite \"" << name << "\": " << err.what() << std::endl;   
         return gfx::Sprite();
      }
   }
   return i->second;
}

std::unique_ptr<gui::Menu> AssetManager::getMenu(const std::string& name)
{
   std::unique_ptr<gui::Menu>& ptr = menus_[name];

   if (!ptr)
   {
      try
      {
         ptr = gui::Menu::load(game_, name);
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to load menu \"" << name << "\": " << err.what() << std::endl;
      }
   }

   return ptr ? ptr->clone() : nullptr;
}


// Returns a pile of all the tiles in a specific tileset.  The top tile is the
// tileset's starting tile.
Pile AssetManager::getTileSet(const std::string& name)
{
   try
   {
      return Pile(*this, name);
   }
   catch (std::runtime_error& err)
   {
      std::cerr << "Failed to load tileset \"" << name << "\": " << err.what() << std::endl;
   }

   return Pile();
}

} // namespace carcassonne
