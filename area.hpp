/**
 * Created by Karol Dudzic @ 2020
 */
#pragma once

#include "object.hpp"

namespace gol
{

struct Area
{
    Area(const std::size_t width, const std::size_t height) : m_w{width}, m_h{height}
    {
        m_data.resize(m_h);
        for (std::size_t i = 0; i < m_h; ++i)
        {
            m_data[i].resize(m_w);
        }
    }

    bool insert(Object object, std::size_t pos_x, std::size_t pos_y)
    {
        if (m_data.empty())
        {
            *this = Area{m_w, m_h};
        }
        const auto grid = object.toGrid();
        if ((grid.width() + pos_x < m_w) and
            (grid.height() + pos_y < m_h))
        {
            for (std::size_t i = 0; i < grid.height(); ++i)
            {
                for (std::size_t j = 0; j < grid.width(); ++j)
                {
                    m_data[pos_y + i][pos_x + j] = grid[i][j];
                }
            }
            return true;
        }
        return false;
    }

    inline auto width() const { return m_w; }
    inline auto height() const { return m_h; }
    inline const auto& operator[](const std::size_t y) const { return m_data[y]; }
    inline auto& operator[](const std::size_t y) { return m_data[y]; }

    inline void clear()
    {
        auto area = Area{m_w, m_h};
        std::swap(area, *this);
    }

    void next()
    {
        auto rep = std::vector<std::vector<int>>{};
        rep.resize(m_data.size());
        rep[0].resize(m_data[0].size());
        rep[1].resize(m_data[1].size());
        for (std::size_t i = 1; i < m_h - 1; ++i)
        {
            rep[i + 1].resize(m_data[i + 1].size());
            for (std::size_t j = 1; j < m_w - 1; ++j)
            {
                if (m_data[i][j])
                {
                    ++rep[i - 1][j];
                    ++rep[i - 1][j + 1];
                    ++rep[i][j + 1];
                    ++rep[i + 1][j + 1];
                    ++rep[i + 1][j];
                    ++rep[i + 1][j - 1];
                    ++rep[i][j - 1];
                    ++rep[i - 1][j - 1];
                }
            }
        }
        for (std::size_t i = 1; i < m_h - 1; ++i)
        {
            if (m_data[i][0])
            {
                ++rep[i - 1][0];
                ++rep[i - 1][1];
                ++rep[i][1];
                ++rep[i + 1][1];
                ++rep[i + 1][0];
            }
            if (m_data[i][m_w - 1])
            {
                ++rep[i - 1][m_w - 1];
                ++rep[i + 1][m_w - 1];
                ++rep[i + 1][m_w - 2];
                ++rep[i][m_w - 2];
                ++rep[i - 1][m_w - 2];
            }
        }
        for (std::size_t j = 1; j < m_w - 1; ++j)
        {
            if (m_data[0][j])
            {
                ++rep[0][j + 1];
                ++rep[1][j + 1];
                ++rep[1][j];
                ++rep[1][j - 1];
                ++rep[0][j - 1];
            }
            if (m_data[m_h - 1][j])
            {
                ++rep[m_h - 2][j];
                ++rep[m_h - 2][j + 1];
                ++rep[m_h - 1][j + 1];
                ++rep[m_h - 1][j - 1];
                ++rep[m_h - 2][j - 1];
            }
        }
        if (m_data[0][0])
        {
            ++rep[0][1];
            ++rep[1][1];
            ++rep[1][0];
        }
        if (m_data[0][m_w - 1])
        {
            ++rep[1][m_w - 1];
            ++rep[1][m_w - 2];
            ++rep[0][m_w - 2];
        }
        if (m_data[m_h - 1][0])
        {
            ++rep[m_h - 2][0];
            ++rep[m_h - 2][1];
            ++rep[m_h - 1][1];
        }
        if (m_data[m_h - 1][m_w - 1])
        {
            ++rep[m_h - 2][m_w - 1];
            ++rep[m_h - 2][m_w - 2];
            ++rep[m_h - 1][m_w - 2];
        }

        for (std::size_t i = 0; i < m_h; ++i)
        {
            for (std::size_t j = 0; j < m_w; ++j)
            {
                m_data[i][j] = m_data[i][j] ? (rep[i][j] == 2 or rep[i][j] == 3)
                                            : (rep[i][j] == 3);
            }
        }
    }

private:
    std::vector<std::vector<bool>> m_data;
    std::size_t m_w, m_h;
};

}  // namespace gol
