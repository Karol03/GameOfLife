/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include "graphics.hpp"

namespace gol
{

class GameOfLife
{
public:
    void start(std::size_t window_width, std::size_t window_height,
               std::size_t arena_width, std::size_t arena_height)
    {
        Area area(arena_width, arena_height);
        Graphics{window_width, window_height}.drawWindow(area);
    }
};

}  // namespace gol
