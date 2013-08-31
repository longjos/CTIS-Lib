#include <CTIS.h>

GUICursor::GUICursor(
    Adafruit_ST7735 *tft,
    uint8_t initial_width,
    uint8_t initial_height,
    uint8_t initial_step
  ){
    _tft = tft;
    x, y = 0;
    width = initial_width;
    height = initial_height;
    step_size = initial_step;
    current_position = 1;
    position_count = 0;
}

void GUICursor::draw_cursor(void){
    _tft->drawRoundRect(x, y, width, height, 5, ST7735_YELLOW);
}

void GUICursor::clear_cursor(void){
    _tft->drawRoundRect(x, y, width, height, 5, ST7735_BLACK);
}

uint8_t GUICursor::move_cursor(bool mv_dir){
    mv_dir ? current_position-- : current_position++;
    if(current_position > position_count){
        current_position = 1;
    }
    if(current_position == 0){
        current_position = position_count;
    }
    uint16_t new_y = step_size * (current_position - 1);
    clear_cursor();
    y = new_y;
    draw_cursor();
    return current_position;
}

void GUICursor::set_position_count(uint8_t initial_position_count){
    position_count = initial_position_count;
}

InflatorUI::InflatorUI(
    Adafruit_ST7735 *tft
){
    _tft = tft;
    _status = 0;
    _set_pressure = 0;
    _measured_pressure = 0;
}

void InflatorUI::draw(uint8_t set_pressure,
                      uint8_t measured_pressure,
                      uint8_t status){
    draw(set_pressure, measured_pressure, status, false);
}

void InflatorUI::draw(uint8_t set_pressure,
                      uint8_t measured_pressure,
                      uint8_t status,
                      bool refresh){
    if(refresh){
        _tft->setCursor(140, 83);
        _tft->setTextSize(1);
        _tft->setTextColor(ST7735_BLUE);
        _tft->println("PSI");
        _tft->setCursor(50, 100);
        _tft->setTextSize(1);
        _tft->setTextColor(ST7735_WHITE);
        _tft->println("Set Point:");
    }
    if((status != _status) || refresh){
        draw_status(status);
        _status = status;
    }
    if((set_pressure != _set_pressure) || refresh){
        draw_set_pressure(set_pressure);
        _set_pressure = set_pressure;
    }
    if((measured_pressure != _measured_pressure) || refresh){
        draw_measured_pressure(measured_pressure);
        _measured_pressure = measured_pressure;
    }
}

void InflatorUI::draw_status(uint8_t status){
    _tft->fillRect(0, 0, 41, 62, ST7735_BLACK);
    if(status == STATUS_INFLATE){
        _tft->fillTriangle(20, 0, 0, 20, 40, 20, ST7735_GREEN);
    } else {
        _tft->drawTriangle(20, 0, 0, 20, 40, 20, ST7735_GREEN);
    }
    if(status == STATUS_DEFLATE){
        _tft->fillTriangle(0, 41, 40, 41, 20, 61, ST7735_RED);
    } else {
        _tft->drawTriangle(0, 41, 40, 41, 20, 61, ST7735_RED);
    }
    if(status == STATUS_HOLD){
        _tft->fillRect(0, 23, 41, 16, ST7735_YELLOW);
    } else {
        _tft->drawRect(0, 23, 41, 16, ST7735_YELLOW);
    }
}

void InflatorUI::draw_measured_pressure(uint8_t measured_pressure){
    _tft->fillRect(50, 10, 110, 70, ST7735_BLACK);
    _tft->setCursor(50, 10);
    _tft->setTextSize(10);
    _tft->setTextColor(ST7735_RED);
    _tft->println(measured_pressure);
}

void InflatorUI::draw_set_pressure(uint8_t set_pressure){
    _tft->fillRect(110, 100, 10, 14, ST7735_BLACK);
    _tft->setCursor(110, 100);
    _tft->setTextSize(2);
    _tft->setTextColor(ST7735_WHITE);
    _tft->println(set_pressure);
}