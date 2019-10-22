/*
 * This file is part of LibZZgui.

 * LibZZgui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgui. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZGUI_INCLUDE_WIDGETS_IMAGE_HPP_
#define LIBZZGUI_INCLUDE_WIDGETS_IMAGE_HPP_

#include "widget.hpp"

#include <memory>

namespace cozz {

namespace zzgui {

class ImageResource;
class Painter;

class Image : public Widget {
  public:
    Image(std::shared_ptr<ImageResource> img, uint64_t x, uint64_t y);

    virtual void Draw(std::shared_ptr<Painter> painter) override;

    void SetImage(std::shared_ptr<ImageResource> img);

    std::shared_ptr<ImageResource> GetImage() const;

    virtual void DoOnMouseButton(const MouseButtonEvent& event) override;

  protected:
    std::shared_ptr<ImageResource> img_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_WIDGETS_IMAGE_HPP_
