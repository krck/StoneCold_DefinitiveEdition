
#include "Button.hpp"

using namespace StoneCold::GUI;
using namespace StoneCold::Common;

Button::Button(scSptr<sf::Sprite> sprite, const sf::Font& font, scUint16 textSize, const sf::String& text) 
    : Widget(), _sprite(sprite), _text(sf::Text()), _pressed(false) {
    _text.setFont(font);
    _text.setStyle(sf::Text::Bold);
    _text.setCharacterSize(textSize);
    _text.setFillColor(sf::Color(80, 80, 80));
    SetText(text);
}

void Button::CenterText(scInt16 offsetX, scInt16 offsetY) {
    const auto textSize = _text.getLocalBounds();
    const auto buttonPos = GetGlobalPosition();
    _text.setOrigin(sf::Vector2f(textSize.left + std::round(textSize.width / 2.f), textSize.top + std::round(textSize.height / 2.f)));
    _text.setPosition(sf::Vector2f(buttonPos.left + std::round(buttonPos.width / 2.f) + offsetX, buttonPos.top + std::round(buttonPos.height / 2.f) + offsetY));
}

void Button::Render(sf::RenderTarget* renderTarget) {
    renderTarget->draw(*_sprite);
    renderTarget->draw(_text);
}

void Button::OnStateChanged(UiWidgetState state) {
    auto size = GetSize();
    switch (state) {
        case UiWidgetState::Idle:       _sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size.x, size.y)));             break;
        case UiWidgetState::Hover:      _sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, size.y), sf::Vector2i(size.x, size.y)));        break;
        case UiWidgetState::Pressed:    _sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, size.y * 2.f), sf::Vector2i(size.x, size.y)));  break;
        default:                        _sprite->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(size.x, size.y)));             break;
    }
}

void Button::OnMouseMoved(const sf::Vector2i& mousePos) {
    const bool mouseOnWidget = Contains(sf::Vector2f(mousePos));
    // If mouse is moved onto the button -> Set state to hover
    // (if mouse is already on the button and state is hover/pressed -> do nothing)
    if(mouseOnWidget && _state == UiWidgetState::Idle) {
        SetState(UiWidgetState::Hover);
    }
    // If mouse leaves the button -> reset to idle
    else if (!mouseOnWidget && _state != UiWidgetState::Idle){
        SetState(UiWidgetState::Idle);
    }
}

void Button::OnMousePressed() {
    if(IsSelected()) {
        CenterText(0, 3);
        SetState(UiWidgetState::Pressed);
    }
}

void Button::OnMouseReleased() {
    if(IsSelected()) {
        CenterText();
        SetState(UiWidgetState::Idle);
        if(_callback != nullptr)
            _callback();
    }
}

// void Button::OnKeyPressed() {
//     if(IsSelected() && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
//         SetState(UiWidgetState::Pressed);
//         std::cout <<"Pressed!" <<std::endl;
//     }
// }

// void Button::OnKeyReleased() {
//     if(IsSelected() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
//         SetState(UiWidgetState::Idle);
//         std::cout <<"Released!" <<std::endl;
//         if(_callback != nullptr)
//             _callback();
//     }
// }
