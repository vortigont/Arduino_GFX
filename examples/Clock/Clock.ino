/*
   Arduino Watch Lite Version
   You may find full version at: https://github.com/moononournation/ArduinoWatch
*/

/*******************************************************************************
 * Start of Arduino_GFX setting
 ******************************************************************************/
#include "SPI.h"
#include "Arduino_HWSPI.h"
#include "Arduino_ESP32SPI.h"
#include "Arduino_SWSPI.h"
#include "Arduino_GFX.h"            // Core graphics library
#include "Arduino_Canvas.h"         // Canvas (framebuffer) library
#include "Arduino_Canvas_Indexed.h" // Indexed Color Canvas (framebuffer) library
#include "Arduino_HX8347C.h"        // Hardware-specific library for HX8347C
#include "Arduino_HX8352C.h"        // Hardware-specific library for HX8352C
#include "Arduino_HX8357B.h"        // Hardware-specific library for HX8357B
#include "Arduino_ILI9225.h"        // Hardware-specific library for ILI9225
#include "Arduino_ILI9341.h"        // Hardware-specific library for ILI9341
#include "Arduino_ILI9481_18bit.h"  // Hardware-specific library for ILI9481
#include "Arduino_ILI9486_18bit.h"  // Hardware-specific library for ILI9486
#include "Arduino_SEPS525.h"        // Hardware-specific library for SEPS525
#include "Arduino_SSD1283A.h"       // Hardware-specific library for SSD1283A
#include "Arduino_SSD1331.h"        // Hardware-specific library for SSD1331
#include "Arduino_SSD1351.h"        // Hardware-specific library for SSD1351
#include "Arduino_ST7735.h"         // Hardware-specific library for ST7735
#include "Arduino_ST7789.h"         // Hardware-specific library for ST7789
#include "Arduino_ST7796.h"         // Hardware-specific library for ST7796

#if defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5STACK_FIRE)
#define TFT_BL 32
#include "Arduino_ILI9341_M5STACK.h"
Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(27 /* DC */, 14 /* CS */, SCK, MOSI, MISO);
Arduino_ILI9341_M5STACK *gfx = new Arduino_ILI9341_M5STACK(bus, 33 /* RST */, 1 /* rotation */);
#elif defined(ARDUINO_ODROID_ESP32)
#define TFT_BL 14
Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(21 /* DC */, 5 /* CS */, SCK, MOSI, MISO);
Arduino_ILI9341 *gfx = new Arduino_ILI9341(bus, -1 /* RST */, 3 /* rotation */);
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus,  -1 /* RST */, 1 /* rotation */, true /* IPS */);
#elif defined(ARDUINO_T) // TTGO T-Watch
#define TFT_BL 12
Arduino_ESP32SPI *bus = new Arduino_ESP32SPI(27 /* DC */, 5 /* CS */, 18 /* SCK */, 19 /* MOSI */, -1 /* MISO */);
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, -1 /* RST */, 2 /* rotation */, true /* IPS */, 240, 240, 0, 80);
#else /* not a specific hardware */

#if defined(ESP32)
#define TFT_CS 5
// #define TFT_CS -1 // for display without CS pin
// #define TFT_DC 16
#define TFT_DC 27
// #define TFT_DC -1 // for display without DC pin (9-bit SPI)
// #define TFT_RST 17
#define TFT_RST 33
#define TFT_BL 22
#elif defined(ESP8266)
#define TFT_CS 15
#define TFT_DC 5
#define TFT_RST -1
// #define TFT_BL 4
#else
#define TFT_CS 20
#define TFT_DC 19
#define TFT_RST 18
#define TFT_BL 10
#endif

/*
 * Step 1: Initize one databus for your display
*/

// General software SPI
// Arduino_DataBus *bus = new Arduino_SWSPI(TFT_DC, TFT_CS, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */);

// General hardware SPI
Arduino_DataBus *bus = new Arduino_HWSPI(TFT_DC, TFT_CS);

// ESP32 hardware SPI, more customizable parameters
// Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */, VSPI /* spi_num */);

/*
 * Step 2: Initize one driver for your display
*/

// Canvas (framebuffer)
// Arduino_ST7789 *output_display = new Arduino_ST7789(bus, TFT_RST, 0 /* rotation */, true /* IPS */);
// 16-bit color Canvas (240x320 resolution only works for ESP32 with PSRAM)
// Arduino_Canvas *gfx = new Arduino_Canvas(240, 320, output_display);
// Indexed color Canvas, mask_level: 0-2, larger mask level mean less color variation but can have faster index mapping
// Arduino_Canvas_Indexed *gfx = new Arduino_Canvas_Indexed(240, 320, output_display, MAXMASKLEVEL /* mask_level */);

// HX8347C IPS LCD 240x320
// Arduino_HX8347C *gfx = new Arduino_HX8347C(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

// HX8352C IPS LCD 240x400
// Arduino_HX8352C *gfx = new Arduino_HX8352C(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

// HX8357B IPS LCD 320x480
// Arduino_HX8357B *gfx = new Arduino_HX8357B(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

// ILI9225 LCD 176x220
// Arduino_ILI9225 *gfx = new Arduino_ILI9225(bus, TFT_RST);

// ILI9341 LCD 240x320
Arduino_ILI9341 *gfx = new Arduino_ILI9341(bus, TFT_RST);

// ILI9481 LCD 320x480
// Arduino_ILI9481_18bit *gfx = new Arduino_ILI9481_18bit(bus, TFT_RST);

// ILI9486 LCD 320x480
// Arduino_ILI9486_18bit *gfx = new Arduino_ILI9486_18bit(bus, TFT_RST);

// SEPS525 OLED 160x128
// Arduino_SEPS525 *gfx = new Arduino_SEPS525(bus, TFT_RST);

// SSD1283A OLED 130x130
// Arduino_SSD1283A *gfx = new Arduino_SSD1283A(bus, TFT_RST);

// SSD1331 OLED 96x64
// Arduino_SSD1331 *gfx = new Arduino_SSD1331(bus, TFT_RST);

// SSD1351 OLED 128x128
// Arduino_SSD1351 *gfx = new Arduino_SSD1351(bus, TFT_RST);

// ST7735 LCD
// 1.8" REDTAB 128x160
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST);
// 1.8" BLACKTAB 128x160
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 128 /* width */, 160 /* height */, 2 /* col offset 1 */, 1 /* row offset 1 */, 2 /* col offset 2 */, 1 /* row offset 2 */, false /* BGR */);
// 1.8" GREENTAB A 128x160
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 128 /* width */, 160 /* height */, 2 /* col offset 1 */, 1 /* row offset 1 */, 2 /* col offset 2 */, 1 /* row offset 2 */);
// 1.8" GREENTAB B 128x160
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 128 /* width */, 160 /* height */, 2 /* col offset 1 */, 3 /* row offset 1 */, 2 /* col offset 2 */, 1 /* row offset 2 */);
// 1.8" Wide angle LCD 128x160
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 2 /* rotation */, false /* IPS */, 128 /* width */, 160 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col offset 2 */, 0 /* row offset 2 */, false /* BGR */);
// 1.5" GREENTAB B 128x128
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 128 /* width */, 128 /* height */, 2 /* col offset 1 */, 3 /* row offset 1 */, 2 /* col offset 2 */, 1 /* row offset 2 */);
// 1.5" GREENTAB C 128x128
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 128 /* width */, 128 /* height */, 0 /* col offset 1 */, 32 /* row offset 1 */);
// 0.96" IPS LCD 80x160
// Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 3 /* rotation */, true /* IPS */, 80 /* width */, 160 /* height */, 26 /* col offset 1 */, 1 /* row offset 1 */, 26 /* col offset 2 */, 1 /* row offset 2 */);

// ST7789 LCD
// 2.4" LCD 240x320
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST);
// 2.4" IPS LCD 240x320
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 0 /* rotation */, true /* IPS */);
// 1.3"/1.5" square IPS LCD 240x240
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 2 /* rotation */, true /* IPS */, 240 /* width */, 240 /* height */, 0 /* col offset 1 */, 80 /* row offset 1 */);
// 1.14" IPS LCD 135x240 TTGO T-Display
// Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 0 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 53 /* col offset 1 */, 40 /* row offset 1 */, 52 /* col offset 2 */, 40 /* row offset 2 */);

// ST7796 LCD
// 4" LCD 320x480
// Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST);
// 4" IPS LCD 320x480
// Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

#endif /* not a specific hardware */
/*******************************************************************************
 * End of Arduino_GFX setting
 ******************************************************************************/

#define BACKGROUND BLACK
#define MARK_COLOR WHITE
#define SUBMARK_COLOR DARKGREY // LIGHTGREY
#define HOUR_COLOR WHITE
#define MINUTE_COLOR BLUE // LIGHTGREY
#define SECOND_COLOR RED

#define SIXTIETH 0.016666667
#define TWELFTH 0.08333333
#define SIXTIETH_RADIAN 0.10471976
#define TWELFTH_RADIAN 0.52359878
#define RIGHT_ANGLE_RADIAN 1.5707963

static uint8_t conv2d(const char *p)
{
    uint8_t v = 0;
    return (10 * (*p - '0')) + (*++p - '0');
}

static int16_t w, h, center;
static int16_t hHandLen, mHandLen, sHandLen, markLen;
static float sdeg, mdeg, hdeg;
static int16_t osx = 0, osy = 0, omx = 0, omy = 0, ohx = 0, ohy = 0; // Saved H, M, S x & y coords
static int16_t nsx, nsy, nmx, nmy, nhx, nhy;                         // H, M, S x & y coords
static int16_t xMin, yMin, xMax, yMax;                               // redraw range
static int16_t hh, mm, ss;
static unsigned long targetTime; // next action time

static int16_t *cached_points;
static int cached_points_idx = 0;
static int16_t *last_cached_point;

void setup(void)
{
    gfx->begin();
    gfx->fillScreen(BACKGROUND);

#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
#endif

    // init LCD constant
    w = gfx->width();
    h = gfx->height();
    if (w < h)
    {
        center = w / 2;
    }
    else
    {
        center = h / 2;
    }
    hHandLen = center * 3 / 8;
    mHandLen = center * 2 / 3;
    sHandLen = center * 5 / 6;
    markLen = sHandLen / 6;
    cached_points = (int16_t *)malloc((hHandLen + 1 + mHandLen + 1 + sHandLen + 1) * 2 * 2);

    // Draw 60 clock marks
    draw_square_clock_mark(
        center - markLen, center,
        center - (markLen * 2 / 3), center,
        center - (markLen / 2), center);

    hh = conv2d(__TIME__);
    mm = conv2d(__TIME__ + 3);
    ss = conv2d(__TIME__ + 6);

    targetTime = ((millis() / 1000) + 1) * 1000;
}

void loop()
{
    unsigned long cur_millis = millis();
    if (cur_millis >= targetTime)
    {
        targetTime += 1000;
        ss++; // Advance second
        if (ss == 60)
        {
            ss = 0;
            mm++; // Advance minute
            if (mm > 59)
            {
                mm = 0;
                hh++; // Advance hour
                if (hh > 23)
                {
                    hh = 0;
                }
            }
        }
    }

    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = SIXTIETH_RADIAN * ((0.001 * (cur_millis % 1000)) + ss); // 0-59 (includes millis)
    nsx = cos(sdeg - RIGHT_ANGLE_RADIAN) * sHandLen + center;
    nsy = sin(sdeg - RIGHT_ANGLE_RADIAN) * sHandLen + center;
    if ((nsx != osx) || (nsy != osy))
    {
        mdeg = (SIXTIETH * sdeg) + (SIXTIETH_RADIAN * mm); // 0-59 (includes seconds)
        hdeg = (TWELFTH * mdeg) + (TWELFTH_RADIAN * hh);   // 0-11 (includes minutes)
        mdeg -= RIGHT_ANGLE_RADIAN;
        hdeg -= RIGHT_ANGLE_RADIAN;
        nmx = cos(mdeg) * mHandLen + center;
        nmy = sin(mdeg) * mHandLen + center;
        nhx = cos(hdeg) * hHandLen + center;
        nhy = sin(hdeg) * hHandLen + center;

        // redraw hands
        redraw_hands_cached_draw_and_erase();

        ohx = nhx;
        ohy = nhy;
        omx = nmx;
        omy = nmy;
        osx = nsx;
        osy = nsy;

        delay(1);
    }
}

void draw_square_clock_mark(int16_t innerR1, int16_t outerR1, int16_t innerR2, int16_t outerR2, int16_t innerR3, int16_t outerR3)
{
    float x, y;
    int16_t x0, x1, y0, y1, innerR, outerR;
    uint16_t c;

    for (int i = 0; i < 60; i++)
    {
        if ((i % 15) == 0)
        {
            innerR = innerR1;
            outerR = outerR1;
            c = MARK_COLOR;
        }
        else if ((i % 5) == 0)
        {
            innerR = innerR2;
            outerR = outerR2;
            c = MARK_COLOR;
        }
        else
        {
            innerR = innerR3;
            outerR = outerR3;
            c = SUBMARK_COLOR;
        }

        if ((i >= 53) || (i < 8))
        {
            x = tan(SIXTIETH_RADIAN * i);
            x0 = center + (x * outerR);
            y0 = center + (1 - outerR);
            x1 = center + (x * innerR);
            y1 = center + (1 - innerR);
        }
        else if (i < 23)
        {
            y = tan((SIXTIETH_RADIAN * i) - RIGHT_ANGLE_RADIAN);
            x0 = center + (outerR);
            y0 = center + (y * outerR);
            x1 = center + (innerR);
            y1 = center + (y * innerR);
        }
        else if (i < 38)
        {
            x = tan(SIXTIETH_RADIAN * i);
            x0 = center - (x * outerR);
            y0 = center + (outerR);
            x1 = center - (x * innerR);
            y1 = center + (innerR);
        }
        else if (i < 53)
        {
            y = tan((SIXTIETH_RADIAN * i) - RIGHT_ANGLE_RADIAN);
            x0 = center + (1 - outerR);
            y0 = center - (y * outerR);
            x1 = center + (1 - innerR);
            y1 = center - (y * innerR);
        }
        gfx->drawLine(x0, y0, x1, y1, c);
    }
}

void redraw_hands_cached_draw_and_erase()
{
    gfx->startWrite();
    draw_and_erase_cached_line(center, center, nsx, nsy, SECOND_COLOR, cached_points, sHandLen + 1, false, false);
    draw_and_erase_cached_line(center, center, nhx, nhy, HOUR_COLOR, cached_points + ((sHandLen + 1) * 2), hHandLen + 1, true, false);
    draw_and_erase_cached_line(center, center, nmx, nmy, MINUTE_COLOR, cached_points + ((sHandLen + 1 + hHandLen + 1) * 2), mHandLen + 1, true, true);
    gfx->endWrite();
}

void draw_and_erase_cached_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color, int16_t *cache, int16_t cache_len, bool cross_check_second, bool cross_check_hour)
{
#if defined(ESP8266)
    yield();
#endif
    bool steep = _diff(y1, y0) > _diff(x1, x0);
    if (steep)
    {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    int16_t dx, dy;
    dx = _diff(x1, x0);
    dy = _diff(y1, y0);

    int16_t err = dx / 2;
    int8_t xstep = (x0 < x1) ? 1 : -1;
    int8_t ystep = (y0 < y1) ? 1 : -1;
    x1 += xstep;
    int16_t x, y, ox, oy;
    for (uint16_t i = 0; i <= dx; i++)
    {
        if (steep)
        {
            x = y0;
            y = x0;
        }
        else
        {
            x = x0;
            y = y0;
        }
        ox = *(cache + (i * 2));
        oy = *(cache + (i * 2) + 1);
        if ((x == ox) && (y == oy))
        {
            if (cross_check_second || cross_check_hour)
            {
                write_cache_pixel(x, y, color, cross_check_second, cross_check_hour);
            }
        }
        else
        {
            write_cache_pixel(x, y, color, cross_check_second, cross_check_hour);
            if ((ox > 0) || (oy > 0))
            {
                write_cache_pixel(ox, oy, BACKGROUND, cross_check_second, cross_check_hour);
            }
            *(cache + (i * 2)) = x;
            *(cache + (i * 2) + 1) = y;
        }
        if (err < dy)
        {
            y0 += ystep;
            err += dx;
        }
        err -= dy;
        x0 += xstep;
    }
    for (uint16_t i = dx + 1; i < cache_len; i++)
    {
        ox = *(cache + (i * 2));
        oy = *(cache + (i * 2) + 1);
        if ((ox > 0) || (oy > 0))
        {
            write_cache_pixel(ox, oy, BACKGROUND, cross_check_second, cross_check_hour);
        }
        *(cache + (i * 2)) = 0;
        *(cache + (i * 2) + 1) = 0;
    }
}

void write_cache_pixel(int16_t x, int16_t y, int16_t color, bool cross_check_second, bool cross_check_hour)
{
    int16_t *cache = cached_points;
    if (cross_check_second)
    {
        for (int i = 0; i <= sHandLen; i++)
        {
            if ((x == *(cache++)) && (y == *(cache)))
            {
                return;
            }
            cache++;
        }
    }
    if (cross_check_hour)
    {
        cache = cached_points + ((sHandLen + 1) * 2);
        for (int i = 0; i <= hHandLen; i++)
        {
            if ((x == *(cache++)) && (y == *(cache)))
            {
                return;
            }
            cache++;
        }
    }
    gfx->writePixel(x, y, color);
}