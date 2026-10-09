#pragma once

#include <hardware/spi.h>

extern "C" {
#include <pico/st7789.h>
typedef struct st7789_config st7789_config_t;
}

#include <interactive-ui/DisplayInterface.hpp>
#include <util/SPIDevice.hpp>
#include <hardware/PulseWidthModulation.hpp>

class ST7789 : public DisplayInterface, public SPIDevice
{
protected:
    const Vec2i32 screen_dimensions;
    PulseWidthModulation pwm_brightness;
    st7789_config_t device;

public:
    ST7789(int32_t width, int32_t height, uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin, uint8_t bl_pin, spi_inst_t* spi_inst);
    ST7789(const Vec2i32& dimensions, uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin, uint8_t bl_pin, spi_inst_t* spi_inst);

    inline Vec2u32 GetDimensions() const override
    {
        return (Vec2u32)screen_dimensions;
    }

    void UpdateDisplay() override;
    void Power(bool power_on) override;
    void SetBrightness(uint8_t contrast) override;
    void ClearDisplay() override;
    void InvertColors() override;

    void DrawPixel(Vec2i32 pos, RGBA color) override;
    void DrawPixel(int32_t x, int32_t y, RGBA color) override;
    RGBA GetPixel(Vec2i32 pos) const override;
    RGBA GetPixel(int32_t x, int32_t y) const override;
};