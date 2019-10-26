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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_CONTROLLER_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_CONTROLLER_HPP_

#include "base_controller.hpp"

#include <memory>

#include "event_handler.hpp"

namespace cozz {

namespace zzgui {

class WindowResizedEvent;

template <class ModelType, class ViewType>
class Controller : public BaseController {
  public:
    virtual ~Controller();

    virtual void Render(float delta) override;

    virtual void Pause() override;

    virtual void Resume() override;

    virtual void Resized(std::weak_ptr<Window> window) override;

    virtual void SetControllersManager(std::weak_ptr<ControllersManager> controllers_manager) override;

    virtual void SetEventHandler(std::weak_ptr<EventHandler> event_handler) override;

    virtual void SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) override;

    virtual void SetResourcesManager(std::weak_ptr<ResourcesManager> resources_manager) override;

    virtual void SetBaseModel(std::shared_ptr<BaseModel> model) override;

    virtual void SetBaseView(std::shared_ptr<BaseView> view) override;

    void SetModel(std::shared_ptr<ModelType> model);

    void SetView(std::shared_ptr<ViewType> view);

    virtual std::weak_ptr<ControllersManager> GetControllersManager() const override;

    virtual std::weak_ptr<EventHandler> GetEventHandler() const override;

    virtual std::weak_ptr<WindowsManager> GetWindowsManager() const override;

    virtual std::weak_ptr<ResourcesManager> GetResourcesManager() const override;

    virtual std::weak_ptr<BaseModel> GetBaseModel() const override;

    virtual std::weak_ptr<BaseView> GetBaseView() const override;

    std::weak_ptr<ModelType> GetModel() const;

    std::weak_ptr<ViewType> GetView() const;

    void RegisterWindow(std::weak_ptr<Window> window);

  protected:
    std::weak_ptr<ControllersManager> controllers_manager_;
    std::weak_ptr<EventHandler> event_handler_;
    std::weak_ptr<WindowsManager> windows_manager_;
    std::weak_ptr<ResourcesManager> resources_manager_;

    std::shared_ptr<ModelType> model_;
    std::shared_ptr<ViewType> view_;

    std::list<EventHandler::HandlerID> registered_event_callbacks_;
    std::list<std::weak_ptr<Window>> registered_windows_;

    Controller(std::shared_ptr<ViewType> view);

  private:
    void OnWindowResize(const WindowResizedEvent& event);
};

}  // namespace zzgui

}  // namespace cozz

#include "controller.tpp"

#endif  // LIBZZGUI_INCLUDE_INTERFACES_CONTROLLER_HPP_
