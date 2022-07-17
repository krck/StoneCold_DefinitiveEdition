
#ifndef STONECOLD_GUI_WIDGET_H
#define STONECOLD_GUI_WIDGET_H

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Enums.hpp"

namespace StoneCold::GUI {

using namespace StoneCold::Core;

class Widget {
public:
    Widget() : _parent(nullptr), _state(UiWidgetState::Idle), _callback(nullptr) { }

    // Widget Sprite functions
    virtual void Render(sf::RenderTarget* renderTarget) = 0;

    virtual void SetPosition(const sf::Vector2f& position) = 0;
    virtual void SetPosition(float x, float y) = 0;
    virtual const sf::Vector2f& GetPosition() const = 0;
    virtual sf::FloatRect GetGlobalPosition() = 0;

    virtual void SetScale(const sf::Vector2f& scale) = 0;
    virtual void SetScale(float width, float height) = 0;
    virtual const sf::Vector2f& GetScale() const = 0;
    virtual sf::Vector2f GetSize() = 0;

    virtual bool Contains(const sf::Vector2f& point) const = 0;

    // Widget Logic functions
    inline const UiWidgetState& GetState() const { return _state; }
    inline bool IsSelected() const { return (_state == UiWidgetState::Hover || _state == UiWidgetState::Pressed); }

    // Widget Callback functions
    inline void SetCallback(std::function<void(void)> callback) { _callback = callback; }

    virtual void OnStateChanged(UiWidgetState) { }
    virtual void OnMouseMoved(const sf::Vector2i&) { }
    virtual void OnMousePressed() { }
    virtual void OnMouseReleased() { }
    virtual void OnMouseWheelMoved(int) { }
    virtual void OnKeyPressed() { }
    virtual void OnKeyReleased() { }
    virtual void OnTextEntered(sf::Uint32) { }
 
    ~Widget() = default;

protected:
    inline void SetState(UiWidgetState state) { _state = state; OnStateChanged(state); }

    inline void SetParent(Widget* parent) { _parent = parent; }
    inline Widget* GetParent() { return _parent; }

protected:
    Widget* _parent;
    UiWidgetState _state;
    std::function<void(void)> _callback;
};

}

#endif
