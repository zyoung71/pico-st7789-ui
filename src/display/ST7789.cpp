#include <display/ST7789.hpp>
#include <hardware/gpio.h>

extern "C"
{
    void st7789_cmd(uint8_t cmd, const uint8_t* data, size_t len);
}

ST7789::ST7789(int32_t width, int32_t height, uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin, uint8_t bl_pin, spi_inst_t* spi_inst)
    : SPIDevice(clk_pin, din_pin, (uint8_t)255, cs_pin), screen_dimensions(width, height), pwm_brightness(bl_pin, 1000.f, 1.f)
{
    device.spi = spi_inst;
    device.gpio_din = din_pin;
    device.gpio_clk = clk_pin;
    device.gpio_cs = cs_pin;
    device.gpio_dc = dc_pin;
    device.gpio_rst = rst_pin;
    device.gpio_bl = bl_pin;

    st7789_init(&device, (uint16_t)width, (uint16_t)height);
    gpio_set_function(bl_pin, GPIO_FUNC_PWM); // this is reiterated as init func above resets the pin to regular output
}

ST7789::ST7789(const Vec2i32& dimensions, uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin, uint8_t bl_pin, spi_inst_t* spi_inst)
    : SPIDevice(clk_pin, din_pin, (uint8_t)255, cs_pin), screen_dimensions(dimensions), pwm_brightness(bl_pin, 1000.f, 1.f)
{
    device.spi = spi_inst;
    device.gpio_din = din_pin;
    device.gpio_clk = clk_pin;
    device.gpio_cs = cs_pin;
    device.gpio_dc = dc_pin;
    device.gpio_rst = rst_pin;
    device.gpio_bl = bl_pin;

    st7789_init(&device, (uint16_t)dimensions.x, (uint16_t)dimensions.y);
    gpio_set_function(bl_pin, GPIO_FUNC_PWM);
}

void ST7789::UpdateDisplay()
{
    // no operation
}

void ST7789::Power(bool power_on)
{
    if (power_on)
        st7789_cmd(0x28, nullptr, 0);
    else
        st7789_cmd(0x29, nullptr, 0);
}

void ST7789::SetBrightness(uint8_t brightness)
{
    pwm_brightness.SetDutyCycle((float)brightness / 255.f);
}

void ST7789::ClearDisplay()
{
    st7789_fill(0);
}

void ST7789::InvertColors()
{
    static bool inverted = false;
    if (inverted)
        st7789_cmd(0x20, nullptr, 0);
    else
        st7789_cmd(0x21, nullptr, 0);

    inverted = !inverted;
}

void ST7789::DrawPixel(Vec2i32 pos, RGBA color)
{
    st7789_set_cursor(pos.x, pos.y);
    st7789_put(color.ToRGB565());
}

void ST7789::DrawPixel(int32_t x, int32_t y, RGBA color)
{
    st7789_set_cursor(x, y);
    st7789_put(color.ToRGB565());
}

RGBA ST7789::GetPixel(Vec2i32 pos) const
{
    // unsupported
    return 0;
}

RGBA ST7789::GetPixel(int32_t x, int32_t y) const
{
    // unsupported
    return 0;
}