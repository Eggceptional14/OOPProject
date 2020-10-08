#ifndef SPACE_INVADER_WIDGET_HPP
#define SPACE_INVADER_WIDGET_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "../Resources/ResHolder.hpp"

namespace gui {

    class Widget {
    public:
        virtual void handleEvent(sf::Event evt, const sf::RenderWindow &window) = 0; //handle widget event

        virtual void render(sf::RenderTarget &renderer) = 0; //render widget

        virtual void setPosition(const sf::Vector2f &pos) = 0; //set widget position

        virtual sf::Vector2f getSize() const = 0; //return size of the widget

        //Custom text
        class Text : public sf::Text {
        public:
            Text();
        };

        //Use for rectangle button
        class Rectangle : public sf::RectangleShape {
        public:
            bool isRolledOn(const sf::RenderWindow &window) const; //if mouse if on top of widget

            bool isClicked(sf::Event evt, const sf::RenderWindow &window); //return true if the widget is clicked
        };

    };
}

#endif
