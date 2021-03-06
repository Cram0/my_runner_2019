/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** ajdisplay_running_scene
*/

#include "../include/my_runner.h"

void ajd_running_scene(running_scene *_running_scene)
{
    ajd_parallax_thunder(_running_scene);
    ajd_player(&_running_scene->player, _running_scene->window);
    ajd_enemy_list(_running_scene->enemies, _running_scene->window, _running_scene->debug);
    ajd_item_list(_running_scene->items, _running_scene->window, _running_scene->debug);
    ajd_item_tag(_running_scene, _running_scene->window);
    if (_running_scene->debug == true) {
        ajd_dbg_player_hitbox(_running_scene);
    }
    ajd_score(_running_scene);
}