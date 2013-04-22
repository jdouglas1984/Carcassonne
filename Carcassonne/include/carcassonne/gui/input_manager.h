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
// File: carcassonne/gui/input_manager.h

#ifndef CARCASSONNE_GUI_INPUT_MANAGER_H_
#define CARCASSONNE_GUI_INPUT_MANAGER_H_
#include "carcassonne/_carcassonne.h"

#include <functional>
#include <set>
#include <SFML/Window.hpp>

namespace carcassonne {
namespace gui {

class InputManager
{
public:
   InputManager();

   void onMouseMoved(const glm::ivec2& window_coords);
   //void onMouseWheel(int delta);
   void onMouseButton(sf::Mouse::Button button, bool down);

   void onKey(const sf::Event::KeyEvent& event, bool down);
   //void onCharacter(const sf::Event::TextEvent& event);
   
   void cancelInput();


   const glm::ivec2& getMousePosition() const;
   const glm::ivec2& getMouseDelta() const;

   void setMouseDownHandler(sf::Mouse::Button button,
      const std::function<void()>& func);

   void setMouseDragHandler(sf::Mouse::Button button,
      const std::function<void(const glm::ivec2&)>& func);

   void setMouseUpHandler(sf::Mouse::Button button,
      const std::function<void(const glm::ivec2&)>& func);

   void setMouseCancelHandler(sf::Mouse::Button button,
      const std::function<void(const glm::ivec2&)>& func);

   void setMouseHoverHandler(const std::function<void()>& func);

private:
   glm::ivec2 current_pos_;
   glm::ivec2 last_delta_;

   bool btn_down_[3];
   
   glm::ivec2 btn_down_pos_[3];

   std::function<void()> down_handler_[3];
   std::function<void(const glm::ivec2&)> drag_handler_[3];
   std::function<void(const glm::ivec2&)> up_handler_[3];
   std::function<void(const glm::ivec2&)> cancel_handler_[3];
   std::function<void()> hover_handler_;

   // disable copy/assign
   InputManager(const InputManager&);
   void operator=(const InputManager&);
};

} // namespace carcassonne::gui
} // namespace carcassonne

#endif