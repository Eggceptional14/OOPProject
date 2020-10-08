#include "Widget.hpp"

namespace gui {

    Widget::Text::Text() {
        //initialize all property of custom text
        setCharacterSize( 25 );
        setOutlineColor( sf::Color::Black );
        setFillColor( sf::Color::White );
        setFont( ResourceHolder::get().fonts.get("arcade" ) );
    }

    bool Widget::Rectangle::isRolledOn(const sf::RenderWindow &window) const {
        auto pos = sf::Mouse::getPosition( window ); //get position of mouse
        return getGlobalBounds().contains( (float)pos.x, (float)pos.y ); //return true if mouse is in the widget area
    }

    bool Widget::Rectangle::isClicked(sf::Event evt, const sf::RenderWindow &window) {
        if ( isRolledOn( window ) ) {
            if ( evt.type == sf::Event::MouseButtonPressed ) {
                return evt.mouseButton.button == sf::Mouse::Left; //return true if left click is clicked
            }
        }
        return false;
    }
}