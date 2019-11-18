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

#include "models/menu.hpp"

#include "clpp/core.hpp"
#include "clpp/device.hpp"
#include "clpp/platform.hpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"
#include "resources_manager.hpp"
#include "sdl_window.hpp"
#include "widget.hpp"
#include "widgets/button.hpp"
#include "widgets/image.hpp"
#include "widgets/label.hpp"
#include "widgets/select.hpp"
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

using std::placeholders::_1;

namespace cozz {

MenuModel::MenuModel(std::shared_ptr<clpp::Core> cl_core) : cl_core_(cl_core) {}

void MenuModel::Create() {
    const auto& ubuntu12_font = resources_manager_.lock()->LoadFont("Ubuntu12", "resources/fonts/ubuntu.ttf", 12);
    const auto& ubuntu14_font = resources_manager_.lock()->LoadFont("Ubuntu14", "resources/fonts/ubuntu.ttf", 14);
    const auto& logo_image = resources_manager_.lock()->LoadImage("FractolLogo", "resources/images/logo.jpg");
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>("Main Menu", logo_image->GetSize().first, 600);
    window_.lock()->IfClosed(std::bind(&MenuController::OnWindowClose, GetController().lock().get(), _1));

    window_.lock()->SetIcon(app_icon);

    GetController().lock()->RegisterWindow(window_);

    try {
        if (cl_core_) {
            cl_platform_ = cl_core_->GetPlatform();
        }
    } catch (...) {
    }

    CreateSettingsWidgets();
    CreateMenuWidgets();
}

void MenuModel::CreateMenuWidgets() {
    const auto resources_manager = resources_manager_.lock();
    const auto& ubuntu12_font = resources_manager->Get<zzgui::FontResource>("Ubuntu12");
    const auto& ubuntu14_font = resources_manager->Get<zzgui::FontResource>("Ubuntu14");
    const auto& logo_image = resources_manager->Get<zzgui::ImageResource>("FractolLogo");
    const auto& window_id = window_.lock()->GetId();

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    widgets_manager_->Create<zzgui::Image>(window_id, 0, logo_image);
    fps_counter_ = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    fps_counter_.lock()->SetPosition(0, window_.lock()->GetHeight() - fps_counter_.lock()->GetSize().second);

    auto mandelbrot_fractal_button =
        widgets_manager_->Create<zzgui::Button>(window_id, 0, "Mandelbrot Fractal", ubuntu14_font);
    mandelbrot_fractal_button.lock()->SetAutosize(false);
    mandelbrot_fractal_button.lock()->SetSize(200, 30);
    mandelbrot_fractal_button.lock()->OnClick(
        std::bind(&MenuController::OnMandelbrotFractalButtonClick, GetController().lock().get(), _1));
    mandelbrot_fractal_button.lock()->SetPosition(
        window_.lock()->GetWidth() / 2 - mandelbrot_fractal_button.lock()->GetSize().first - 5,
        logo_image->GetSize().second + 30);

    auto julia_fractal_button = widgets_manager_->Create<zzgui::Button>(window_id, 0, "Julia Fractal", ubuntu14_font);
    julia_fractal_button.lock()->SetAutosize(false);
    julia_fractal_button.lock()->SetSize(200, 30);
    julia_fractal_button.lock()->OnClick(
        std::bind(&MenuController::OnJuliaFractalButtonClick, GetController().lock().get(), _1));
    julia_fractal_button.lock()->PlaceRight(mandelbrot_fractal_button, 10);

    auto burning_ship_fractal_button =
        widgets_manager_->Create<zzgui::Button>(window_id, 0, "Burning Ship Fractal", ubuntu14_font);
    burning_ship_fractal_button.lock()->SetAutosize(false);
    burning_ship_fractal_button.lock()->SetSize(200, 30);
    burning_ship_fractal_button.lock()->OnClick(
        std::bind(&MenuController::OnBurningShipFractalButtonClick, GetController().lock().get(), _1));
    burning_ship_fractal_button.lock()->PlaceBottom(mandelbrot_fractal_button, 10);

    auto exit_button = widgets_manager_->Create<zzgui::Button>(window_id, 0, "Exit", ubuntu14_font);
    exit_button.lock()->SetAutosize(false);
    exit_button.lock()->SetSize(100, 30);
    exit_button.lock()->OnClick(std::bind(&MenuController::OnExitButtonClick, GetController().lock().get(), _1));
    exit_button.lock()->SetPosition(window_.lock()->GetWidth() / 2 - exit_button.lock()->GetSize().first / 2,
                                    window_.lock()->GetHeight() - exit_button.lock()->GetSize().second - 20);

    auto settings_button = widgets_manager_->Create<zzgui::Button>(window_id, 0, "Settings", ubuntu14_font);
    settings_button.lock()->SetAutosize(false);
    settings_button.lock()->SetSize(100, 30);
    settings_button.lock()->OnClick(
        std::bind(&MenuController::OnSettingsButtonClick, GetController().lock().get(), _1));
    settings_button.lock()->PlaceUp(exit_button, 5);
}

void MenuModel::CreateSettingsWidgets() {
    const auto resources_manager = resources_manager_.lock();
    const auto& ubuntu12_font = resources_manager->Get<zzgui::FontResource>("Ubuntu12");
    const auto& ubuntu14_font = resources_manager->Get<zzgui::FontResource>("Ubuntu14");
    const auto& window_id = window_.lock()->GetId();

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    auto logo_image = widgets_manager_->Create<zzgui::Image>(
        window_id, 0, resources_manager->Get<zzgui::ImageResource>("FractolLogo"));

    auto back_button = widgets_manager_->Create<zzgui::Button>(window_id, 0, "Back", ubuntu14_font);
    back_button.lock()->SetAutosize(false);
    back_button.lock()->SetSize(100, 30);
    back_button.lock()->OnClick(std::bind(&MenuController::OnMenuButtonClick, GetController().lock().get(), _1));
    back_button.lock()->SetPosition(window_.lock()->GetWidth() / 2 - back_button.lock()->GetSize().first / 2,
                                    window_.lock()->GetHeight() - back_button.lock()->GetSize().second - 20);

    std::vector<std::pair<std::string, std::shared_ptr<clpp::Platform>>> platform_select_list;
    if (cl_platform_) {
        platform_select_list.push_back(std::make_pair(cl_platform_->GetName(), cl_platform_));
        for (const auto& platform : cl_core_->GetPlatforms()) {
            const auto& platform_name = platform.first;
            const auto& platform_ptr = platform.second;

            if (platform_ptr != cl_platform_) {
                platform_select_list.push_back(std::make_pair(platform_name, platform_ptr));
            }
        }
    } else {
        platform_select_list.push_back(std::make_pair("< None >", nullptr));
    }

    auto platform_select_label = widgets_manager_->Create<zzgui::Label>(window_id, 0, "Platform:", ubuntu14_font);
    platform_select_label.lock()->PlaceBottom(logo_image, 30, 30);

    auto platform_select = widgets_manager_->Create<zzgui::Select<std::shared_ptr<clpp::Platform>>>(
        window_id, 1, platform_select_list, ubuntu12_font);
    platform_select.lock()->PlaceRight(platform_select_label, 10);
    platform_select.lock()->SetBackgroundColor({0xFF, 0xFF, 0xFF});
    platform_select.lock()->OnChange(
        std::bind(&MenuController::OnPlatformSelectChange, GetController().lock().get(), _1));
    platform_select.lock()->SetPadding(7);

    auto platform_info_label = widgets_manager_->Create<zzgui::Label>(window_id, 0, "Info:", ubuntu14_font);
    platform_info_label.lock()->PlaceBottom(platform_select_label);

    platform_info_.device_types_avaliable =
        widgets_manager_->Create<zzgui::Label>(window_id, 0, "No devices avaliable", ubuntu12_font);
    platform_info_.device_types_avaliable.lock()->PlaceRight(platform_info_label, 0, 2);

    auto device_select_label = widgets_manager_->Create<zzgui::Label>(window_id, 0, "Device:", ubuntu14_font);
    device_select_label.lock()->PlaceBottom(platform_info_label, 10, 20);

    platform_info_.device_select = widgets_manager_->Create<zzgui::Select<std::shared_ptr<clpp::Device>>>(
        window_id, 1, std::vector<std::pair<std::string, std::shared_ptr<clpp::Device>>>({{"< none >", nullptr}}),
        ubuntu12_font);
    platform_info_.device_select.lock()->PlaceRight(device_select_label, 10);
    platform_info_.device_select.lock()->SetBackgroundColor({0xFF, 0xFF, 0xFF});
    platform_info_.device_select.lock()->OnChange(
        std::bind(&MenuController::OnDeviceSelectChange, GetController().lock().get(), _1));
    platform_info_.device_select.lock()->SetPadding(7);

    auto device_info_label = widgets_manager_->Create<zzgui::Label>(window_id, 0, "Info:", ubuntu14_font);
    device_info_label.lock()->PlaceBottom(device_select_label, 10);

    device_info_.type = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.type.lock()->PlaceRight(device_info_label, 5, 5);
    device_info_.type.lock()->SetPadding(2);

    device_info_.availability = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.availability.lock()->PlaceBottom(device_info_.type);
    device_info_.availability.lock()->SetPadding(2);

    device_info_.max_clock_frequency = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.max_clock_frequency.lock()->PlaceBottom(device_info_.availability);
    device_info_.max_clock_frequency.lock()->SetPadding(2);

    device_info_.max_compute_units = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.max_compute_units.lock()->PlaceBottom(device_info_.max_clock_frequency);
    device_info_.max_compute_units.lock()->SetPadding(2);

    device_info_.max_samplers = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.max_samplers.lock()->PlaceBottom(device_info_.max_compute_units);
    device_info_.max_samplers.lock()->SetPadding(2);

    device_info_.max_memory_alloc_size = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.max_memory_alloc_size.lock()->PlaceBottom(device_info_.max_samplers);
    device_info_.max_memory_alloc_size.lock()->SetPadding(2);

    device_info_.max_parameter_size = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.max_parameter_size.lock()->PlaceBottom(device_info_.max_memory_alloc_size);
    device_info_.max_parameter_size.lock()->SetPadding(2);

    device_info_.vendor = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.vendor.lock()->PlaceBottom(device_info_.max_parameter_size);
    device_info_.vendor.lock()->SetPadding(2);

    device_info_.device_version = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.device_version.lock()->PlaceBottom(device_info_.vendor);
    device_info_.device_version.lock()->SetPadding(2);

    device_info_.driver_version = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu12_font);
    device_info_.driver_version.lock()->PlaceBottom(device_info_.device_version);
    device_info_.driver_version.lock()->SetPadding(2);

    SetClPlatform(cl_platform_);
}

void MenuModel::Update(float delta) {
    if (!fps_counter_.expired()) {
        fps_counter_.lock()->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS");
    }
}

namespace {

std::string ClDeviceTypeToString(cl_device_type type) {
    switch (type) {
        case CL_DEVICE_TYPE_CPU:
            return "CPU";
        case CL_DEVICE_TYPE_GPU:
            return "GPU";
        case CL_DEVICE_TYPE_ACCELERATOR:
            return "ACCELERATOR";
        default:
            throw std::runtime_error("Unknown device type");
    }
}

}  // namespace

void MenuModel::SetClPlatform(std::shared_ptr<clpp::Platform> platform) {
    cl_platform_ = platform;

    if (cl_platform_) {
        const auto& devices = cl_platform_->GetDevices();

        if (devices.empty()) {
            return platform_info_.device_types_avaliable.lock()->SetText("No devices avaliable");
        }

        SetClDevice(devices.begin()->second);

        std::vector<std::pair<std::string, std::shared_ptr<clpp::Device>>> device_select_list;
        std::map<cl_device_type, std::pair<std::string, uint64_t>> device_types;
        for (const auto& device : devices) {
            device_select_list.push_back({device.second->GetName(), device.second});
            try {
                device_types[device.first].first = ClDeviceTypeToString(device.first);
                device_types.at(device.first).second++;
            } catch (...) {
            }
        }

        platform_info_.device_select.lock()->SetOptions(device_select_list);

        std::string device_types_avaliable;
        for (const auto& device_type : device_types) {
            if (!device_types_avaliable.empty()) {
                device_types_avaliable += ", ";
            }
            device_types_avaliable += std::to_string(device_type.second.second) + "x" + device_type.second.first;
        }

        platform_info_.device_types_avaliable.lock()->SetText("Devices avaliable (" + std::to_string(devices.size()) +
                                                              "): " + device_types_avaliable);
    } else {
        platform_info_.device_types_avaliable.lock()->SetText("No information avaliable");
    }
}

void MenuModel::SetClDevice(std::shared_ptr<clpp::Device> device) {
    cl_device_ = device;
    if (!cl_device_) {
        return;
    }
    device_info_.type.lock()->SetText("Type: " + ClDeviceTypeToString(cl_device_->GetType()));
    device_info_.availability.lock()->SetText(std::string("Avaliable: ") +
                                              (cl_device_->IsAvailable() ? "True" : "False"));
    device_info_.max_clock_frequency.lock()->SetText(
        "Max clock frequency: " + std::to_string(cl_device_->GetMaxClockFrequency()) + "MHz");
    device_info_.max_compute_units.lock()->SetText("Max compute units: " +
                                                   std::to_string(cl_device_->GetMaxComputeUnits()));
    device_info_.max_samplers.lock()->SetText("Max samplers count: " + std::to_string(cl_device_->GetMaxSamplers()));
    device_info_.max_memory_alloc_size.lock()->SetText(
        "Max memory allocation size: " + std::to_string(cl_device_->GetMaxMemoryAllocSize()) + " bytes");
    device_info_.max_parameter_size.lock()->SetText(
        "Max parameter size: " + std::to_string(cl_device_->GetMaxParameterSize()) + " bytes");
    device_info_.vendor.lock()->SetText("Vendor name: " + cl_device_->GetVendor());
    device_info_.device_version.lock()->SetText("Device version: " + cl_device_->GetDeviceVersion());
    device_info_.driver_version.lock()->SetText("Driver version: " + cl_device_->GetDriverVersion());
}

std::weak_ptr<zzgui::Window> MenuModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> MenuModel::GetWidgetsManager() const { return widgets_manager_; }

std::shared_ptr<const clpp::Platform> MenuModel::GetClPlatform() const { return cl_platform_; }

std::shared_ptr<const clpp::Device> MenuModel::GetClDevice() const { return cl_device_; }

}  // namespace cozz
