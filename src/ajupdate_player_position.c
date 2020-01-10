/*
** EPITECH PROJECT, 2020
** MUL_my_runner_2019
** File description:
** ajupdate_player_position
*/

#include "../include/my_runner.h"
static const float GRAVITY = 1250;

void aju_player_position_y(player *_player)
{
    float dt = sfTime_asSeconds(sfClock_getElapsedTime(_player->move_clock));
    if (_player->state == RUNNING)
        _player->dy = 0;
    else {
        _player->dy += GRAVITY * dt;
        _player->pos.y += _player->dy * dt;
    }
    if (_player->pos.y > 357.0) {
        _player->pos.y = 357.0;
        _player->state = RUNNING;
    }
}

void aju_player_check_state(player *_player)
{
    if (_player->dy > 0)
        _player->state = FALLING;
}

void aju_player_position(player *_player)
{
    aju_player_check_state(_player);
    aju_player_position_y(_player);
    sfSprite_setPosition(_player->sprite, _player->pos);
    sfClock_restart(_player->move_clock);
}