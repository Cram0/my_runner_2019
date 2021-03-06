/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** aju_game_core
*/

#include "../include/my_runner.h"

void aju_current_selector_color(option_scene *_scene)
{
    int idx = _scene->selector_index;
    for (int i = 0; i < OPTION_SLIDER_COUNT; i++) {
        if (i == idx) {
            sfRectangleShape_setFillColor(_scene->slider[i]->indicator, sfYellow);
        }
        else {
            sfRectangleShape_setFillColor(_scene->slider[i]->indicator, sfWhite);
        }
    }
}

void aju_option_selector(option_scene *_scene, sfKeyCode key)
{
    int idx = _scene->selector_index;
    int indicator_step = 1 * (sfRectangleShape_getLocalBounds(_scene->slider[idx]->slider).width / _scene->slider[idx]->max_value);

    if (key == sfKeyRight) {
        _scene->slider[idx]->curr_value++;
        if (_scene->slider[idx]->curr_value > _scene->slider[idx]->max_value) { _scene->slider[idx]->curr_value = _scene->slider[idx]->max_value; }
    }

    if (key == sfKeyLeft) {
        _scene->slider[idx]->curr_value--;
        if (_scene->slider[idx]->curr_value < _scene->slider[idx]->min_value) { _scene->slider[idx]->curr_value = _scene->slider[idx]->min_value; }
    }

    sfRectangleShape_setPosition(_scene->slider[idx]->indicator, (sfVector2f){_scene->slider[idx]->slider_pos.x + indicator_step * _scene->slider[idx]->curr_value, _scene->slider[idx]->indicator_pos.y});
}

void aju_option_background(menu_background *_bg)
{
    if (!_bg->clock) {_bg->clock = sfClock_create(); }
    if (sfTime_asSeconds(sfClock_getElapsedTime(_bg->clock)) > 0.250) {
        if (_bg->rect.left >= 1536)
            _bg->rect.left = 0;
        sfSprite_setTextureRect(_bg->sprite, _bg->rect);
        _bg->rect.left += _bg->rect.width;
        sfClock_restart(_bg->clock);
    }
}

void aju_option_preview_rect(option_scene *_scene)
{
    unsigned char r = _scene->slider[0]->curr_value;
    unsigned char g = _scene->slider[1]->curr_value;
    unsigned char b = _scene->slider[2]->curr_value;
    sfRectangleShape_setFillColor(_scene->preview_rect, (sfColor){r * 17, g * 17, b * 17, 255});
}

void aju_option_foreground(option_scene *_scene, sfEvent *_event)
{
    if (_event->type == sfEvtKeyPressed) {
        if (_event->key.code == sfKeyDown) {
            if (_scene->selector_index < OPTION_SLIDER_COUNT - 1) _scene->selector_index++;
        }
        if (_event->key.code == sfKeyUp) {
            if (_scene->selector_index > 0)_scene->selector_index--;
        }
        if (_event->key.code == sfKeyLeft) {
            aju_option_selector(_scene, sfKeyLeft);
        }
        if (_event->key.code == sfKeyRight) {
            aju_option_selector(_scene, sfKeyRight);
        }
    }
    aju_current_selector_color(_scene);
    aju_option_preview_rect(_scene);
}

void aju_edit_pixel(option_scene *_scene, int x, int y, sfUint8 color)
{
    if (color == 255) {
        sfColor color = {(_scene->slider[0]->curr_value * 17) / 5 * 4, (_scene->slider[1]->curr_value * 17) / 5 * 4, (_scene->slider[2]->curr_value * 17) / 5 * 4, 255};
        sfImage_setPixel(_scene->alucard_img, x, y, color);
    }
    if (color == 227) {
        sfColor color = {(_scene->slider[0]->curr_value * 17) / 3 * 2, (_scene->slider[1]->curr_value * 17) / 3 * 2, (_scene->slider[2]->curr_value * 17) / 3 * 2, 255};
        sfImage_setPixel(_scene->alucard_img, x, y, color);
    }
    if (color == 170) {
        sfColor color = {(_scene->slider[0]->curr_value * 17) / 3 * 1, (_scene->slider[1]->curr_value * 17) / 3 * 1, (_scene->slider[2]->curr_value * 17) / 3 * 1, 255};
        sfImage_setPixel(_scene->alucard_img, x, y, color);
    }
}

void aju_edit_alucard_cape(option_scene *_scene)
{
    sfTexture *org_txt = sfTexture_createFromFile("img/alucard/alucard_sheet_capes.png", NULL);
    _scene->alucard_img = sfTexture_copyToImage(org_txt);
    sfTexture_destroy(org_txt);
    sfVector2u img_size = sfImage_getSize(_scene->alucard_img);
    for (unsigned int y = 0; y < img_size.y; y++) {
        for (unsigned int x = 0; x < img_size.x; x++) {
            sfColor color = sfImage_getPixel(_scene->alucard_img, x, y);
            aju_edit_pixel(_scene, x, y, color.g);
        }
    }
    sfTexture_destroy(_scene->player_txt);
    _scene->player_txt = sfTexture_createFromImage(_scene->alucard_img, NULL);
}

void aju_option_scene_event(option_scene *_scene, sfEvent *_event)
{
    if (_event->type == sfEvtKeyPressed) {
        if (_event->key.code == sfKeyEscape) {
            aju_edit_alucard_cape(_scene);
            *_scene->game_state = MENU;
        }
    }
    aju_option_foreground(_scene, _event);
}

void aju_option_scene(option_scene *_scene, sfEvent *_event)
{
    aju_option_background(&_scene->background);
}

void aju_game_core(game_core *_game_core)
{
    while (sfRenderWindow_pollEvent(_game_core->window, &_game_core->event)) {
        if (_game_core->event.type == sfEvtClosed)
            sfRenderWindow_close(_game_core->window);
        if (sfEvtKeyPressed && sfKeyboard_isKeyPressed(sfKeyF12)) {
            if (_game_core->running_scene.debug == false)
                _game_core->running_scene.debug = true;
            else
                _game_core->running_scene.debug = false;
        }
        if (_game_core->game_state == OPTION) {
            aju_option_scene_event(&_game_core->option_scene, &_game_core->event);
        }
    }
    if (_game_core->game_state == MENU)
        aju_menu_scene(&_game_core->menu_scene);
    if (_game_core->game_state == INGAME)
        aju_running_scene(&_game_core->running_scene);
    if (_game_core->game_state == GAMEOVER)
        aju_game_over_scene(&_game_core->game_over_scene);
    if (_game_core->game_state == OPTION) {
        aju_option_scene(&_game_core->option_scene, &_game_core->event);
    }
}