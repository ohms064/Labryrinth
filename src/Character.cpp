#include "Character.h"

#include "raymath.h"

void Character::initialize()
{
    current_square_ = grid_->get_start();
    previous_square_ = grid_->get_start();
    current_direction_ = static_cast<direction>(GetRandomValue(0, 3));
}

void Character::try_move()
{
    if(LabyrinthSquare next; grid_->get_neighbour_square(*current_square_, current_direction_, next))
    {
        previous_square_ = current_square_;
        current_square_ = &next;
    }
}

bool Character::check_obstacle()
{
    LabyrinthSquare next;
    return grid_->get_neighbour_square(*current_square_, current_direction_, next) && next.obstacle;
}

void Character::change_direction(direction new_direction)
{
    current_direction_ = new_direction;
}

void Character::turn(bool clockwise)
{
    switch(current_direction_) {
    case direction::up:
        current_direction_ = clockwise ? direction::right : direction::left;
        break;
    case direction::down:
        current_direction_ = clockwise ? direction::left : direction::right;
        break;
    case direction::left:
        current_direction_ = clockwise ? direction::down : direction::up;
        break;
    case direction::right:
        current_direction_ = clockwise ? direction::up : direction::down;
        break;
    }

}

float Character::current_distance_to_exit() const
{
    return grid_->distance_to_exit(*current_square_);
}

void Character::draw_character() const
{
    const float circle_radius = grid_->get_square_size() * 1.6f;
    Vector2 facing;
    switch (current_direction_) {
    case direction::up:
        facing = {circle_radius * 2, 0};
        break;
    case direction::down:
        facing = {circle_radius * -2, 0};
        break;
    case direction::left:
        facing = {0, circle_radius * -2};
        break;
    case direction::right:
        facing = {0, circle_radius * 2};
        break;
    }

    const Vector2 center = current_square_->screen_position;
    const float thickness = circle_radius * 0.7f;

    DrawCircleV(center, circle_radius, RED);
    DrawLineEx(center, Vector2Add(center, facing), thickness, PURPLE);
}
