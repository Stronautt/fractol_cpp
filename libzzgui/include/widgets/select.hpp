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

#ifndef LIBZZGUI_INCLUDE_WIDGETS_SELECT_HPP_
#define LIBZZGUI_INCLUDE_WIDGETS_SELECT_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "canvas.hpp"
#include "widget.hpp"

namespace cozz {

namespace zzgui {

class FontResource;
class Painter;

template <class Data>
class Select : public Widget {
  public:
    Select(const std::vector<std::pair<std::string, Data>>& options, std::shared_ptr<FontResource> font, uint64_t x = 0,
           uint64_t y = 0);

    virtual void Draw(std::shared_ptr<Painter> painter) override;

    virtual void SetSize(uint64_t width, uint64_t height) override;

    void SetOptions(const std::vector<std::pair<std::string, Data>>& options);

    void SetFont(std::shared_ptr<FontResource> font);

    void SetAutosize(bool value);

    void SetBorderThickness(uint16_t thickness);

    void SetBorderColor(const Canvas::PixelColor& border_color);

    void SetBackgroundColor(const Canvas::PixelColor& background_color);

    void SetForegroundColor(const Canvas::PixelColor& foreground_color);

    const std::vector<std::pair<std::string, Data>>& GetOptions() const;

    std::shared_ptr<FontResource> GetFont() const;

    uint16_t GetBorderThickness() const;

    const Canvas::PixelColor& GetBorderColor() const;

    const Canvas::PixelColor& GetBackgroundColor() const;

    const Canvas::PixelColor& GetForegroundColor() const;

    void OnChange(std::function<void(const Data&)> func);

    virtual bool DoOnMouseButton(const MouseButtonEvent& event) override;

  protected:
    std::vector<std::pair<std::string, Data>> options_;
    std::shared_ptr<FontResource> font_;

    bool autosize_;
    bool focus_;

    uint16_t border_thickness_;

    Canvas::PixelColor border_color_;
    Canvas::PixelColor background_color_;
    Canvas::PixelColor foreground_color_;

    std::function<void(const Data&)> change_callback_;

    virtual bool InBounds(uint64_t x, uint64_t y, const Event& event) override;

  private:
    std::vector<std::pair<uint64_t, uint64_t>> options_text_size_;
};

}  // namespace zzgui

}  // namespace cozz

#include "widgets/select.tpp"

#endif  // LIBZZGUI_INCLUDE_WIDGETS_SELECT_HPP_
