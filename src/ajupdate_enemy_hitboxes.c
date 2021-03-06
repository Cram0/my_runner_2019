/*
** EPITECH PROJECT, 2020
** MUL_my_runner_2019
** File description:
** ajupdate_enemy_hitboxes
*/

#include "../include/my_runner.h"

void aju_bat_hitbox(enemy_t *_bat)
{
    _bat->hitbox.left = _bat->pos.x;
    _bat->hitbox.top = _bat->pos.y + 7.142857143 * SCALE_FACTOR;
}

void aju_ww_hitbox(enemy_t *_ww)
{
    _ww->hitbox.left = _ww->pos.x + 7.142857143 * SCALE_FACTOR;
    _ww->hitbox.top = _ww->pos.y + 4.285714286 * SCALE_FACTOR;
}

void aju_panther_hitbox(enemy_t *_panther)
{
    _panther->hitbox.left = _panther->pos.x + 14.285714286 * SCALE_FACTOR;
    _panther->hitbox.top = _panther->pos.y + 7.142857143 * SCALE_FACTOR;

}

void aju_knight_hitbox(enemy_t *_knight)
{
    _knight->hitbox.left = _knight->pos.x + 14.285714286 * SCALE_FACTOR;
    _knight->hitbox.top = _knight->pos.y + 8 * SCALE_FACTOR;

}

void aju_enemy_hitbox(enemy_t *_enemy)
{
    switch (_enemy->type) {
        case BAT: aju_bat_hitbox(_enemy);
            break;
        case WEREWOLF: aju_ww_hitbox(_enemy);
            break;
        case PANTHER: aju_panther_hitbox(_enemy);
            break;
        case KNIGHT: aju_knight_hitbox(_enemy);
            break;
    }
}

void aju_enemy_list_hitboxes(enemy_t *_enemy)
{
    if (_enemy->next == NULL) {
        aju_enemy_hitbox(_enemy);
    }
    else
        while (_enemy->next != NULL) {
            aju_enemy_hitbox(_enemy);
            _enemy = _enemy->next;
        }
}
