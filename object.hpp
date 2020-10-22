/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include <vector>
#include <inttypes.h>

namespace gol
{

struct Grid
{
    Grid() = default;
    Grid(std::vector<std::vector<bool>> init)
        : m_data(std::move(init))
    {}
    Grid(std::initializer_list<std::vector<bool>> init)
        : m_data(std::move(init))
    {}
    inline auto width() const { return m_data.empty() ? 0 : m_data[0].size(); }
    inline auto height() const { return m_data.size(); }
    inline const auto& operator[](const std::size_t y) const { return m_data[y]; }
    inline auto& operator[](const std::size_t y) { return m_data[y]; }

private:
    std::vector<std::vector<bool>> m_data;
};

struct Object
{
    enum class Type : uint8_t
    {
        // Still lifes
        Point = 0,
        Block,
        Beehive,
        Loaf,
        Boat,
        Tub,

        // Oscillators
        Blinker,
        Toad,
        Beacon,

        // Spaceships
        Glider,
        LWSS,
        MWSS,
        HWSS,

        // Last element without presentation
        None
    };

public:
    Object() = default;
    Object(const Type type) : m_type{type} {}

    Grid toGrid() const
    {
        switch (m_type)
        {
            case Type::Point: return Grid({{1}});
            case Type::Block: return Grid({{1, 1}, {1, 1}});
            case Type::Beehive: return Grid({{0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0}});
            case Type::Loaf: return Grid({{0, 1, 1, 0}, {1, 0, 0, 1}, {0, 1, 0, 1}, {0, 0, 1, 0}});
            case Type::Boat: return Grid({{1, 1, 0}, {1, 0, 1}, {0, 1, 0}});
            case Type::Tub: return Grid({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});

            case Type::Blinker: return Grid({{1, 1, 1}});
            case Type::Toad: return Grid({{0, 1, 1, 1}, {1, 1, 1, 0}});
            case Type::Beacon: return Grid({{1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 1}});

            case Type::Glider: return Grid({{0, 0, 1}, {1, 0, 1}, {0, 1, 1}});
            case Type::LWSS: return Grid({{0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {0, 0, 0, 0, 1}, {1, 0, 0, 1, 0}});
            case Type::MWSS: return Grid({{0, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 0}});
            case Type::HWSS: return Grid({{0, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0}, {0, 0, 1, 1, 0, 0, 0}});
            default: return Grid({{0}});
        }
    }

    void nextType()
    {
        auto type = static_cast<uint8_t>(m_type);
        type = (type + 1)%static_cast<uint8_t>(Type::None);
        m_type = static_cast<Type>(type);
    }

    void previousType()
    {
        auto type = static_cast<uint8_t>(m_type);
        type = (type + static_cast<uint8_t>(Type::None) - 1)%static_cast<uint8_t>(Type::None);
        m_type = static_cast<Type>(type);
    }

private:
    Type m_type{Type::Point};
};

}  // namespace gol
