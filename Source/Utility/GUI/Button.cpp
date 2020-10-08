#include "Button.hpp"

#include <iostream>

namespace gui {

    Button::Button() {
        //initialize all button property
        w_button.setOutlineThickness( 1 );
        w_button.setOutlineColor( sf::Color::Blue );
        w_button.setFillColor( sf::Color::Black );
        w_button.setSize( { 256, 64 } );
    }

    void gui::Button::setFunction(function<void ()> func) {
        w_function = func; //set function of the button
    }

    void gui::Button::setText(const string &str) {
        w_text.setString( str );
        updateText();
    }

    void gui::Button::handleEvent(sf::Event evt, const sf::RenderWindow &window) {
        auto pos = sf::Mouse::getPosition( window );

        switch ( evt.type ) { //switch case for event type
            case sf::Event::MouseButtonPressed:
                if ( evt.mouseButton.button == sf::Mouse::Left ) {
                    if ( w_button.getGlobalBounds().contains( (float)pos.x, (float)pos.y ) ) {
                        w_function();
                    }
                }
            default:
                break;
        }
    }

    void gui::Button::render(sf::RenderTarget &renderer) {
        renderer.draw( w_button );
        renderer.draw( w_text );
    }

    void gui::Button::setPosition(const sf::Vector2f &pos) {
        //set position of whole button widget
        w_position = pos;
        w_button.setPosition( w_position );
        w_text.setPosition( w_position );
        updateText();
    }

    sf::Vector2f gui::Button::getSize() const {
        return w_button.getSize();
    }

    void gui::Button::updateText() {
        //set text position
        w_text.setOrigin( w_text.getGlobalBounds().width / 2, w_text.getGlobalBounds().height / 2 );
        w_text.move( w_button.getGlobalBounds().width / 2.0f, w_button.getGlobalBounds().height / 2.5f );
    }

}