
#ifndef STONECOLD_GUI_BUTTON_H
#define STONECOLD_GUI_BUTTON_H

#include <cmath>
#include "Types.hpp"
#include "Enums.hpp"
#include "Widget.hpp"

namespace StoneCold::GUI {

using namespace StoneCold::Core;

class Button : public Widget {
public:
    Button(scSptr<sf::Sprite> sprite, const sf::Font& font, scUint16 textSize, const sf::String& text);

    void Render(sf::RenderTarget* renderTarget) override;

    inline void SetPosition(const sf::Vector2f& position) { _sprite->setPosition(position); CenterText(); }
    inline void SetPosition(float x, float y) { _sprite->setPosition(sf::Vector2f(x, y)); CenterText(); }
    inline const sf::Vector2f& GetPosition() const { return _sprite->getPosition(); }
    inline sf::FloatRect GetGlobalPosition() { return _sprite->getGlobalBounds(); }

    inline void SetScale(const sf::Vector2f& scale) { _sprite->setScale(scale); CenterText(); }
    inline void SetScale(float width, float height) { _sprite->setScale(sf::Vector2f(width, height)); CenterText(); }
    inline const sf::Vector2f& GetScale() const { return _sprite->getScale(); }
    inline sf::Vector2f GetSize() { return sf::Vector2f(_sprite->getLocalBounds().width, _sprite->getLocalBounds().height); }

    inline void SetTextSize(scUint16 size) { _text.setCharacterSize(size); CenterText(); }
    inline void SetText(const sf::String& text) { _text.setString(text); CenterText(); }
    inline const sf::String& GetText() const { return _text.getString(); }

    inline bool Contains(const sf::Vector2f& point) const { return _sprite->getGlobalBounds().contains(point); }

    // Callback functions
    void OnStateChanged(UiWidgetState state) override;
    void OnMouseMoved(const sf::Vector2i& mousePos) override;
    void OnMousePressed() override;
    void OnMouseReleased() override;
    // void OnKeyPressed() override;
    // void OnKeyReleased() override;

private:
    void CenterText(scInt16 offsetX = 0, scInt16 offsetY = 0);

private:
    scSptr<sf::Sprite> _sprite;
    sf::Text _text;
    bool _pressed;
};

}

#endif
