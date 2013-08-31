#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define STATUS_INFLATE 1
#define STATUS_HOLD 2
#define STATUS_DEFLATE 3

class GUICursor {

 public:
    GUICursor(Adafruit_ST7735 *tft, uint8_t initial_width, uint8_t initial_height, uint8_t initial_step);
    void draw_cursor(void);
    void clear_cursor(void);
    uint8_t move_cursor(bool mv_dir);
    void set_position_count(uint8_t initial_position_count);


 protected:
    Adafruit_ST7735 *_tft;
    uint16_t x;
    uint16_t y;
    uint8_t width;
    uint8_t height;
    uint8_t step_size;
    uint8_t position_count;
    uint8_t current_position;
};

class InflatorUI {

    public:
        InflatorUI(Adafruit_ST7735 *tft);
        void draw(
            uint8_t set_pressure,
            uint8_t measured_pressure,
            uint8_t status
        );
        void draw(
            uint8_t set_pressure,
            uint8_t measured_pressure,
            uint8_t status,
            bool refresh
        );
    protected:
        Adafruit_ST7735 *_tft;
        void draw_status(uint8_t status);
        void draw_set_pressure(uint8_t set_pressure);
        void draw_measured_pressure(uint8_t measured_pressure);
        uint8_t _measured_pressure;
        uint8_t _set_pressure;
        uint8_t _status;
};