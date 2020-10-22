/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "area.hpp"

namespace gol
{
namespace
{
constexpr auto VERTEXES_IN_QUAD = 4;
}  // namespace

class Graphics
{
public:
    Graphics(const std::size_t width, const std::size_t height)
        : m_w{width}
        , m_h{height}
    {}

    auto* draw(Area& area)
    {
        auto rectangles = new sf::Vertex[area.height() * area.width() * VERTEXES_IN_QUAD]();

        for (std::size_t i = 0; i < area.height(); ++i)
        {
            for (std::size_t j = 0; j < area.width(); ++j)
            {
                const auto pixelStartW = static_cast<float>(j) * m_pixelw;
                const auto pixelStartH = static_cast<float>(i) * m_pixelh;
                const auto quadNo = (i * area.width() + j) * VERTEXES_IN_QUAD;
                auto* quad = &rectangles[quadNo];

                quad[0].position = sf::Vector2f(pixelStartW, pixelStartH);
                quad[1].position = sf::Vector2f(pixelStartW + m_pixelw, pixelStartH);
                quad[2].position = sf::Vector2f(pixelStartW + m_pixelw, pixelStartH + m_pixelh);
                quad[3].position = sf::Vector2f(pixelStartW, pixelStartH + m_pixelh);

                if (area[i][j])
                {
                    quad[0].color = sf::Color::White;
                    quad[1].color = sf::Color::White;
                    quad[2].color = sf::Color::White;
                    quad[3].color = sf::Color::White;
                }
                else
                {
                    quad[0].color = sf::Color::Black;
                    quad[1].color = sf::Color::Black;
                    quad[2].color = sf::Color::Black;
                    quad[3].color = sf::Color::Black;
                }
            }
        }
        return rectangles;
    }

    void drawWindow(Area& area)
    {
        m_pixelw = static_cast<float>(m_w)/static_cast<float>(area.width());
        m_pixelh = static_cast<float>(m_h)/static_cast<float>(area.height());
        sf::RenderWindow window(sf::VideoMode(800, 600), "Game Of Life");
        while (window.isOpen())
        {
            handleEvents(window, area);
            drawArea(window, area);
        }
    }
private:
    void handleEvents(sf::RenderWindow& window, Area& area)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased and
                     event.key.code == sf::Keyboard::Space)
            {
                m_isPause = !m_isPause;
            }
            else if (event.type == sf::Event::MouseButtonReleased and
                     event.mouseButton.button == sf::Mouse::Left)
            {
                area.insert(m_activeObject,
                            (event.mouseButton.x + 0.5f) / m_pixelw,
                            (event.mouseButton.y + 0.5f) / m_pixelh);
            }
            else if (event.type == sf::Event::KeyReleased and
                     event.key.code == sf::Keyboard::C)
            {
                area.clear();
            }
            else if (event.type == sf::Event::KeyReleased and
                     event.key.code == sf::Keyboard::N)
            {
                m_activeObject.nextType();
            }
            else if (event.type == sf::Event::KeyReleased and
                     event.key.code == sf::Keyboard::P)
            {
                m_activeObject.previousType();
            }
            window.setFramerateLimit(10);
        }
    }

    void drawArea(sf::RenderWindow& window, Area& area)
    {
        auto* rectangles = draw(area);
        window.clear();
        window.draw(rectangles, area.height() * area.width() * VERTEXES_IN_QUAD, sf::Quads);
        window.display();
        if (not m_isPause)
        {
            area.next();
        }
        delete [] rectangles;
    }


private:
    Object m_activeObject{Object::Type::LWSS};
    float m_pixelw, m_pixelh;
    const std::size_t m_w, m_h;
    bool m_isPause{false};
};

}  // gol
