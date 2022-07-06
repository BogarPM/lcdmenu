#include <Arduino.h>
#include <./lcdmenu.h>
#include <LiquidCrystal.h>
// #include<LiquidCrystal.h>

/* Private fields */

void lcdmenu::processState()
{
    // Algorythm
    if (_state[0] == 0 && _state[1] == 0 && _antstate[0] == 0 && _antstate[1] == 0)
    {
    }
    else if (_state[0] == 1 && _state[1] == 0 && _antstate[0] == 0 && _antstate[1] == 0)
    {
        _rawait = 1;
    }
    else if (_state[0] == 0 && _state[1] == 1 && _antstate[0] == 0 && _antstate[1] == 0)
    {
        _lawait = 1;
    }
    else if (_state[0] == 1 && _state[1] == 1 && (_antstate[0] == 1 && _antstate[1] == 0) || (_antstate[0] == 0 && _antstate[1] == 1))
    {
        if (_rawait == 1)
        {
            _idx += 1;
        }
        if (_lawait == 1)
        {
            _idx -= 1;
        }
        // Serial.println(_idx);
        _lawait = 0;
        _rawait = 0;
    }

    _antstate[0] = _state[0];
    _antstate[1] = _state[1];
}

lcdmenu::lcdmenu()
{
    _lcd.clear();
    _lcd.home();
    lines[0] = "Test Message";
    lines[1] = "Test Message T2";
}

lcdmenu::lcdmenu(uint8_t encoderR, uint8_t encoderL, uint8_t select)
{
    pinMode(encoderR, INPUT);
    pinMode(encoderL, INPUT);
    _encoder1 = encoderR;
    _encoder2 = encoderL;
    _lcd.begin(16, 4);
    _lcd.clear();
    _lcd.home();
    lines[0] = "Test Message\n";
    // lines[1] = "Test Message T2";
    
}

lcdmenu::lcdmenu(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t encoder)
{
    //_lcd -> init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

lcdmenu::~lcdmenu()
{
}


// void lcdmenu::setView(uint8_t* view, uint8_t len){
//     _lcd.print(view,len);
// }


void lcdmenu::init(uint8_t pages)
{
    // Serial.println("Init of lcd menu");
    _lcd.print("Init");
}

void lcdmenu::readEncoder(){
    bool en = digitalRead(_encoder1);
    if(en == 0 && _enl1 == 1){
        bool en2 = digitalRead(_encoder2);
        if(en2 == 1) {counter--;}
        else{counter++;}
        _enl1 = 0;
    }else if(en == 1){
        _enl1 = 1;
    }
}

void lcdmenu::printDelta()
{
    if (printFlag)
    {
        printFlag = false;
        // Serial.println(inputDelta);
    }
}

// Function that periodically refreshes display

void lcdmenu::onLoop()
{
    // readEncoder();
    // printDelta();
    // if(_enl1 == 1 && en1 == 1){_enl1 = 0;}
    // else if( en1 == 0){_enl1 = 1;}
    // if(_enl1 == 1 && en1 == 1){_enl1 = 0;}
    // else if( en1 == 0){_enl1 = 1;}
    // _state = [en1,en2];
    uint16_t current = millis();
    if( current - _lastmillis > T ){
        _lastmillis = current;
        _lcd.clear();
        _lcd.home();
        // Serial.println(counter);
        // _lcd.print('Counter: ');
        counter ++;
        for (uint8_t i = 0; i < 2; i++) {
            _lcd.print(lines[i]);
        }
        
        
    }
    delayMicroseconds(40);
}

void lcdmenu::setLine(char* str, uint8_t len,uint8_t line){
    lines[line] = str;
}