#include "LabyrinthGrid.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>

#include "raymath.h"

LabyrinthGrid::LabyrinthGrid(int size) : size_(size)
{
    squares_.reserve(static_cast<size_t>(size) * size);
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            auto square = LabyrinthSquare(Vector2(x, y));
            squares_.push_back(square);
            std::cout << "index:" << x * size_ + y << " x: " << square.get_x() << " y: " << square.get_y() << '\n';
        }
    }
}

LabyrinthSquare LabyrinthGrid::get_square(Vector2 coordinate) const
{
    return squares_[static_cast<int>(coordinate.x) * size_ + static_cast<int>(coordinate.y)];
}

bool LabyrinthGrid::get_neighbour_square(LabyrinthSquare square, direction dir, LabyrinthSquare& result_square) const
{
    auto coordinate = square.get_neighbour_coordinate(dir);
    if (!is_valid_coordinate(coordinate))
    {
        result_square = square;
        return false;
    }

    result_square = get_square(coordinate);
    return true;
}

void LabyrinthGrid::draw_labyrinth(const int square_size, const Vector2 offset)
{
    for (auto& square : squares_)
    {
        const int mod_y = std::fmod(square.get_y(), 2.f);
        square.screen_position = Vector2(offset.x + (square_size * square.get_x()),
            offset.y + (square_size * square.get_y()));
        DrawRectangle(square.screen_position.x, square.screen_position.y,
            square_size, square_size, square.obstacle ? BLACK : std::fmod(square.get_x() + mod_y, 2) == 0 ? GRAY : WHITE);

        square.screen_position = Vector2AddValue(square.screen_position, square_size * 0.5f);
    }

    const LabyrinthSquare& start = start_square();
    const LabyrinthSquare& exit  = exit_square();

    DrawText("Start",
        offset.x + (square_size * start.get_x()),
        offset.y + (square_size * start.get_y()),
        30, BLACK);
    DrawText("End",
        offset.x + (square_size * exit.get_x()),
        offset.y + (square_size * exit.get_y()),
        30, BLACK);
}

void LabyrinthGrid::create_labyrinth(bool add_noise)
{
    const int count = static_cast<int>(squares_.size());
    if (count < 2)
        return;

    for (auto& square : squares_)
        square.obstacle = !add_noise || GetRandomValue(0, 1) == 1;

    start_index_ = GetRandomValue(0, count - 1);
    exit_index_ = start_index_;
    while (exit_index_ == start_index_)
        exit_index_ = GetRandomValue(0, count - 1);

    const LabyrinthSquare& exit = exit_square();

    std::vector<LabyrinthSquare> critical_path;
    std::optional<LabyrinthSquare> previous;
    LabyrinthSquare current = squares_[start_index_];

    squares_[start_index_].obstacle = false;
    critical_path.push_back(current);

    while (current != exit)
    {
        LabyrinthSquare next = current;

        // Dead end: allow stepping back to the previous square
        if (!get_weighted_next_square(current, previous ? &*previous : nullptr, exit, next))
            get_weighted_next_square(current, nullptr, exit, next);

        previous = current;
        current = next;
        squares_[to_index(current)].obstacle = false;
        critical_path.push_back(current);
    }
}

float LabyrinthGrid::distance_to_exit(LabyrinthSquare from) const
{
    return Vector2DistanceSqr(from.get_coordinate(), exit_square().get_coordinate());
}

bool LabyrinthGrid::is_valid_coordinate(const Vector2 coordinate) const
{
    return is_coordinate_in_range(coordinate.x) && is_coordinate_in_range(coordinate.y);
}

bool LabyrinthGrid::is_coordinate_in_range(const float i) const
{
    return i >= 0 && i < size_;
}

bool LabyrinthGrid::get_weighted_next_square(const LabyrinthSquare& current,
                                             const LabyrinthSquare* previous,
                                             const LabyrinthSquare& end,
                                             LabyrinthSquare& result) const
{
    struct Candidate
    {
        LabyrinthSquare square;
        float dist_sqr;
    };

    std::vector<Candidate> candidates;
    candidates.reserve(4);

    const Vector2 end_pos{ end.get_x(), end.get_y() };

    for (int i = 0; i < 4; ++i)
    {
        LabyrinthSquare neighbour = current; // no default ctor, so start from a copy
        if (!get_neighbour_square(current, static_cast<direction>(i), neighbour))
            continue;
        if (previous && neighbour == *previous)
            continue;

        const Vector2 pos{ neighbour.get_x(), neighbour.get_y() };
        candidates.push_back({ neighbour, Vector2DistanceSqr(pos, end_pos) });
    }

    if (candidates.empty())
        return false;

    std::ranges::sort(candidates,
                      [](const Candidate& a, const Candidate& b) { return a.dist_sqr < b.dist_sqr; });

    // Closest x3, second x2, rest x1
    std::vector<const LabyrinthSquare*> pool;
    for (size_t rank = 0; rank < candidates.size(); ++rank)
    {
        const int weight = std::max(1, 3 - static_cast<int>(rank));
        for (int w = 0; w < weight; ++w)
            pool.push_back(&candidates[rank].square);
    }

    result = *pool[GetRandomValue(0, static_cast<int>(pool.size()) - 1)];
    return true;
}

int LabyrinthGrid::to_index(const LabyrinthSquare& square) const
{
    return static_cast<int>(square.get_x()) * size_ + static_cast<int>(square.get_y());
}