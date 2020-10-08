#ifndef SPACE_INVADER_BUTTON_HPP
#define SPACE_INVADER_BUTTON_HPP

#include "Widget.hpp"

#include <functional>

using namespace std;

namespace gui {

    class Button : public gui::Widget {
    public:
        Button();

        void setFunction( function<void(void)> func ); //set function of the button
        void setText( const string& str ); //set text display inside button

        void handleEvent( sf::Event evt, const sf::RenderWindow& window ) override; //handle event generated from button
        void render( sf::RenderTarget& renderer ) override; //render button
        void setPosition( const sf::Vector2f& pos ) override; //set position of the button
        sf::Vector2f getSize() const override; //return size of button

    private:
        void updateText(); //update text position

        sf::Vector2f w_position;
        Rectangle w_button;
        Text w_text;
        std::function<void(void)> w_function = [](){};
    };

    inline unique_ptr<Button> makeButton() { //create button widget
        return make_unique<Button>();
    }
}

#endif
