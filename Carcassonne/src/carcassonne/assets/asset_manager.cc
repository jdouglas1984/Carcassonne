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
// File: carcassonne/assets/asset_manager.cc

#include "carcassonne/assets/asset_manager.h"

namespace carcassonne {
namespace assets {

AssetManager::AssetManager(const std::string& filename)
   : db_(filename)
{
}

std::shared_ptr<Texture> AssetManager::getTexture(const std::string& name)
{
   auto i(textures_.find(name));
   if (i == textures_.end())
      textures_.insert(std::make_pair(name, std::weak_ptr<Texture>()));

   std::weak_ptr<Texture>& wptr = textures_[name];

   std::shared_ptr<Texture> sptr = wptr.lock();

   if (!sptr)
   {
      try
      {
         sptr.reset(new Texture(db_, name));
         wptr = sptr;
      }
      catch (const std::runtime_error& err)
      {
         std::cerr << "Failed to load texture \"" << name << "\": " << err.what();
      }
   }

   return sptr;
}

void AssetManager::vacuum()
{
   for (auto i(textures_.begin()), end(textures_.end()); i != end;)
   {
      if (i->second.expired())
         i = textures_.erase(i);
      else
         ++i;
   }
}

} // namespace assets
} // namespace carcassonne