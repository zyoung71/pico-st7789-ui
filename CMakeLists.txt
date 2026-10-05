if (NOT TARGET pico-st7789-ui)

    add_library(pico-st7789-ui STATIC
        src/display/ST7789.cpp
        lib/pico-st7789/src/st7789.c
    )

    target_include_directories(pico-st7789-ui PUBLIC
        include
        lib/pico-st7789/src/include
    )

    add_subdirectory(lib/pico-interactive-ui)

    target_link_libraries(pico-st7789-ui
        pico-interactive-ui
        hardware_spi
    )
    
endif()