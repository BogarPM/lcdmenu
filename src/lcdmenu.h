#ifndef LCDMENU_H
#define LCDMENU_H

#include <Arduino.h>
#include <LiquidCrystal.h>

// #define rspin 2
// #define rwpin 3
// #define enpin 4
// #define d0pin 5
// #define d1pin 6
// #define d2pin 7
// #define d3pin 8

class lcdmenu{
private:
    // encoder section
    bool printFlag = false;
    int16_t inputDelta = 0;
    uint16_t _lastmillis = 0;
    uint16_t T = 500;
    char* lines[2];
    
    // Testing for encoder states


    uint8_t _enstate = 3;

    // Test 2 
    int counter = 0; 
    int aState;
    int aLastState;
    // Encoder latches
    bool _enl1 = 1;
    bool _enl2 = 1;

    bool _state[2] = {0,0};
    bool _antstate[2] = {0,0};
    bool _rawait = 0;
    bool _lawait = 0;

    int _idx = 0;

    const uint8_t rspin = 2;
    const uint8_t rwpin = 3;
    const uint8_t enpin = 4;
    const uint8_t d0pin = 5;
    const uint8_t d1pin = 6;
    const uint8_t d2pin = 7;
    const uint8_t d3pin = 8;
    uint8_t _pages = 1;

    uint8_t _encoder1 = 0;
    uint8_t _encoder2 = 0;
    uint8_t _select = 0;
    void readEncoder();
    void printDelta();
    void processState();
    // UI variables
    // States
    
    const uint8_t PAGE_SELECTION = 1;
    const uint8_t OPTION_SELECTION = 1;

    uint8_t page;



public:
    // Only 4 bytes available for this
    LiquidCrystal _lcd = LiquidCrystal(rspin,rwpin,enpin,d0pin,d1pin,d2pin,d3pin);
    lcdmenu();
    lcdmenu(uint8_t encoderR,uint8_t encoderL,uint8_t select);
    lcdmenu(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t encoder);
    ~lcdmenu();
    // void setView(uint8_t* view, uint8_t len);
    void init(uint8_t pages);
    void setLine(char* str, uint8_t len,uint8_t line);
    void onLoop();
};

#endif