#include <hardware/spi.h>
#include <pico/stdio.h>

#include <display/ST7789.hpp>
#include <interactive-ui/Screen.hpp>
#include <interactive-ui/components/TextComponent.hpp>

struct _init
{
    _init()
    {
        spi_init(spi0, 45 * 1000 * 1000);
    }
} _init_inst;

ST7789 display(320, 240, 19, 18, 17, 20, 21, 22, spi0);

ScreenManager manager(&display);
Screen main_screen(&manager, display.GetDimensions());

TextComponent text(&manager, static_cast<Vec2i32>(display.GetDimensions() / 2), "ST7789", &fonts::default_font_group, 0, &main_screen);

int main()
{
    stdio_init_all();

    display.ClearDisplay();
    main_screen.SortComponents();
    manager.PushScreen(&main_screen);
    manager.EnableCBF(true);
    manager.ForceUpdate();

    while (1)
    {
        // This is actually not ran constantly as the ST7789
        // updates changes immediately. Only update when necessary.
        // manager.Update();
    }
}