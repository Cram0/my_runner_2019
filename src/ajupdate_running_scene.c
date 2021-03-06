/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** ajupdate_running_scene
*/

#include "../include/my_runner.h"

void aju_running_scene(running_scene *_running_scene)
{
    aju_running_scene_event(_running_scene);
    aju_parallax(&_running_scene->parallax);
    aju_player(&_running_scene->player);
    aju_enemy_list(_running_scene);
    aju_item_list(_running_scene->items);
    aju_score(_running_scene);
    aju_thunder(_running_scene);
}