/**
 * Created by Karol Dudzic @ 2020
 */

#include "gameoflife.hpp"

using namespace std;

int main()
{
    constexpr std::size_t WINDOW_WIDTH = 800;
    constexpr std::size_t WINDOW_HEIGHT = 600;
    constexpr std::size_t AREA_WIDTH = 60;
    constexpr std::size_t AREA_HEIGHT = 60;

    gol::GameOfLife{}.start(WINDOW_WIDTH, WINDOW_HEIGHT, AREA_WIDTH, AREA_HEIGHT);
    return 0;
}
