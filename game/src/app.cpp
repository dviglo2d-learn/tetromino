// Copyright (c) 2022-2023 the Dviglo project
// License: MIT

#include "app.hpp"

#include <dviglo/gl_utils/shader_cache.hpp>
#include <dviglo/gl_utils/texture_cache.hpp>
#include <dviglo/io/fs_base.hpp>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <fmt/format.h>

#include <iostream>

using namespace glm;
using namespace fmt;


App::App(const std::vector<StrUtf8>& args)
    : Application(args)
{
    cout << "Командная строка: " << join(args, " ") << endl;

    log_path_ = "путь/к/логу";
}

struct Vertex
{
    vec2 pos;
    u32 color;
    vec2 uv;
};

void App::start()
{
    StrUtf8 base_path = get_base_path();
    cout << "Папка программы: " << base_path << endl;

    texture_ = DV_TEXTURE_CACHE->get(base_path + "data/textures/tile128.png");
    sprite_batch_ = make_unique<SpriteBatch>();
    font_ = make_unique<SpriteFont>(base_path + "data/fonts/ubuntu-r_20_simple.fnt");
}

static float rotation = 0.f;

static StrUtf8 fps_text;

void App::update(u64 ms)
{
    rotation += ms * 0.0001f;
    while (rotation >= 360.f)
        rotation -= 360.f;

    float fps = 1000.f / ms;
    fps_text = format("FPS: {}", fps);
}

ivec2 screen_size{800, 600};

void App::draw()
{
    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    sprite_batch_->triangle_.v0 = {{0.f, 300.f}, 0xFFFFFFFF};
    sprite_batch_->triangle_.v1 = {{800.f, 300.f}, 0xFF0000FF};
    sprite_batch_->triangle_.v2 = {{800.f, 0.f}, 0xFF00FF00};
    sprite_batch_->add_triangle();

    sprite_batch_->set_shape_color(0xFFFF0000);
    sprite_batch_->draw_triangle({0.f, 600.f}, {400.f, 600.f}, {400.f, 0.f});

    sprite_batch_->draw_sprite(texture_, {100.f, 100.f});
    sprite_batch_->draw_sprite(texture_, {500.f, 100.f}, nullptr, 0xFFFFFFFF, rotation);

    sprite_batch_->draw_string(fps_text, font_.get(), vec2{4.f, 1.f}, 0xFF000000);
    sprite_batch_->draw_string(fps_text, font_.get(), vec2{3.f, 0.f}, 0xFFFFFFFF);

    sprite_batch_->flush();
}
