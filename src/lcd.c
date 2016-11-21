#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <wiringPi.h>           //WiringPi headers
#include <lcd.h>                //LCD headers from WiringPi
#include "lcd.h"
#include "gateway_main.h"

//Pin numbers below are the WiringPi pin numbers
const int LCD_RS = 3;
const int LCD_E = 0;
const int LCD_D4 = 6;
const int LCD_D5 = 1;
const int LCD_D6 = 5;
const int LCD_D7 = 4;
const int LCD_ROW = 4;
const int LCD_COL = 20;

const int LED_WARNING = 13; //wiringPi pin 2

void *lcd_update(void *data){
    int lcd; //Handle for LCD

    // wiringPiSetup();        //Initialise WiringPi

    //init LCD
    if (lcd = lcdInit (LCD_ROW, LCD_COL, 4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0)){
            printf ("lcdInit failed! \n");
    }

    //init warning LED
    init_warning_LED();

    //test example
    // strncpy(lcd_data.row[0],"Hello World!" , 20);
    // strncpy(lcd_data.row[1],"2nd row" , 20);
    // strncpy(lcd_data.row[2],"3nd row" , 20);
    int i;int y=0;

    while(1){
        //check is there update for lcd
        if(update_flag.lcd == 1){
            //write lcd
            // printf("same memory shared check\n");
            lcdClear(lcd);
            lcdPosition(lcd,0,0);
            lcdPuts(lcd, lcd_data.row[0]);
            lcdPosition(lcd,0,1);
            lcdPuts(lcd, lcd_data.row[1]);
            lcdPosition(lcd,0,2);
            lcdPuts(lcd, lcd_data.row[2]);
            lcdPosition(lcd,0,3);
            lcdPuts(lcd, lcd_data.row[3]);

            //for debug
            //sprintf(lcd_data.row[3],"%d", y); y++;

            update_flag.lcd = 0;
        }

        //check is there update for led
        update_warning_LED();

        sleep(1); //check for each second

    } //while end


}

void init_warning_LED(){
    pullUpDnControl(LED_WARNING, PUD_DOWN); //pull-down
    pinMode(LED_WARNING, OUTPUT);
}

void update_warning_LED(){
    if(update_flag.warning == 1){
        digitalWrite(LED_WARNING, HIGH);
    }
    else{
        digitalWrite(LED_WARNING, LOW);
    }

}
