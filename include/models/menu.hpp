/*
 * This file is part of Fractol.

 * Fractol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fractol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef FRACTOL_INCLUDE_MODELS_MENU_HPP_
#define FRACTOL_INCLUDE_MODELS_MENU_HPP_

#include "model.hpp"

#include <memory>
#include <vector>

namespace cozz {

class MenuController;

namespace zzgui {

class Window;
class WidgetsManager;
class Label;

template <class Data>
class Select;

}  // namespace zzgui

namespace clpp {

class Core;
class Platform;
class Device;

}  // namespace clpp

class MenuModel final : public zzgui::Model<MenuController> {
  public:
    MenuModel(std::shared_ptr<clpp::Core> cl_core);

    virtual void Create() override;

    virtual void Update(float delta) override;

    void SetClPlatform(std::shared_ptr<clpp::Platform> platform);

    void SetClDevice(std::shared_ptr<clpp::Device> device);

    std::weak_ptr<zzgui::Window> GetWindow() const;

    std::weak_ptr<zzgui::WidgetsManager> GetWidgetsManager() const;

    std::shared_ptr<const clpp::Platform> GetClPlatform() const;

    std::shared_ptr<const clpp::Device> GetClDevice() const;

    void CreateMenuWidgets();

    void CreateSettingsWidgets();

  private:
    std::shared_ptr<clpp::Core> cl_core_;

    std::weak_ptr<zzgui::Window> window_;

    std::shared_ptr<zzgui::WidgetsManager> widgets_manager_;

    std::weak_ptr<zzgui::Label> fps_counter_;

    std::shared_ptr<clpp::Platform> cl_platform_;
    std::shared_ptr<const clpp::Device> cl_device_;

    struct {
        std::weak_ptr<zzgui::Label> device_types_avaliable;
        std::weak_ptr<zzgui::Select<std::shared_ptr<clpp::Device>>> device_select;
    } platform_info_;

    struct {
        std::weak_ptr<zzgui::Label> type;
        std::weak_ptr<zzgui::Label> availability;
        std::weak_ptr<zzgui::Label> max_clock_frequency;
        std::weak_ptr<zzgui::Label> max_compute_units;
        std::weak_ptr<zzgui::Label> max_samplers;
        std::weak_ptr<zzgui::Label> max_memory_alloc_size;
        std::weak_ptr<zzgui::Label> max_parameter_size;
        std::weak_ptr<zzgui::Label> vendor;
        std::weak_ptr<zzgui::Label> device_version;
        std::weak_ptr<zzgui::Label> driver_version;
    } device_info_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_MENU_HPP_
