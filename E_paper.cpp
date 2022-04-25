#include "E_paper.h"
//#include "GxEPD_BitmapExamples"
extern UBXMessage ubxMessage;
static int update_epaper=2;
int gyro_right=1;

void Boot_screen(void){
  int offset =0;
  display.init(); 
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeSansBold12pt7b);
  display.setCursor(offset,24);
  display.println("WAKE UP.....");
  display.setCursor(offset,56);
  display.println(SW_version);//change to string / array
  display.setCursor(offset,88);
  display.print("GPS logger");//display.print(calibration_speed,2);
  display.setCursor(offset,120);
  display.print("Need for speed !");
  display.update();
}
void Off_screen(int choice){//choice 0 = oud scherm, anders Simon scherm
  int offset=0;
  float session_time=millis()/1000 ;
  if(choice==0){
      display.setRotation(1);
      display.fillScreen(GxEPD_WHITE);
      display.setTextColor(GxEPD_BLACK);
      display.setFont(&FreeSansBold12pt7b);
      display.setCursor(offset,24);
      display.println("Save session....");
      display.setCursor(offset,56);
      display.print("Time: ");
      display.print(session_time,0);
      display.print(" S");
      display.setCursor(offset,88);
      display.print("AVG: ");display.print(RTC_avg_10s,2);
      display.setCursor(offset,120);
      display.print("Dis: ");display.print(Ublox.total_distance/1000,0);
      display.updateWindow(0,0,250,122,true);
      }
  else{
      Serial.println("Off_screen Simon");
      display.setRotation(1);
      display.fillScreen(GxEPD_WHITE);
      display.setTextColor(GxEPD_BLACK);
      display.fillRect(0,0,255,122,GxEPD_WHITE);
    // Buddie logo:
      display.drawExampleBitmap(Surfbuddie_logoS_zwart, 195, 0, 48, 48, GxEPD_BLACK);
      display.setFont(&FreeSansBold9pt7b);
      display.setCursor(offset,14);
      display.println("opslaan gps sessie...");
      display.setCursor(offset,30);
      display.print("Avg 5x10sec: ");display.print(RTC_avg_10s,2);display.println(" km/u");
      display.setCursor(offset,46);
      display.print("Afstand: ");display.print(Ublox.total_distance/1000000,0);display.println(" km");
      display.setCursor(offset,62);
      display.print("Tijd gesurft: ");display.print(session_time/60,0);display.println(" min");
    // Buddie logo:
      display.drawExampleBitmap(Surfbuddie_logoS_zwart, 195, 0, 48, 48, GxEPD_BLACK);
      display.setCursor(offset,121);
      display.setFont(&SF_Distant_Galaxy9pt7b);
    //  display.print("surfbuddie: ");display.print("Jan");
      display.updateWindow(0,0,250,122,true);
  }
  //display.update();
  delay(10000);//om te voorkomen dat update opnieuw start !!!
}
//Screen in deepsleep, update bat voltage, refresh every 4000s !!
void Sleep_screen(int choice){
  if (offset>9)offset--;
  if (offset<1)offset++;
  display.init(); 
  display.setRotation(1);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  if(choice==0){
      display.setFont(&FreeSansBold18pt7b);
      display.setCursor(offset,24);
      display.print("Dis: ");
      display.println(RTC_distance,0);
      display.setCursor(offset,56);
      display.print("AVG: ");display.println(RTC_avg_10s,2);
      display.setCursor(offset,88);
      display.print("2s: ");display.print(RTC_max_2s);//display.println("Hz"); 
      display.setCursor(offset,120);
      display.print("Bat: ");display.print(voltage_bat,2);
      Bat_level(offset);
      display.update();
      }
   else{
      int row1=15;
      int row=15;
      int row2=row1+row;
      int row3=row2+row;
      int row4=row3+row;
      int row5=row4+row;
      int row6=row5+row;
      int col1=0+offset;
      int col2=34+offset;
      int col3=90+offset;
      int col4=146+offset;
      int line=0; 
      display.fillRect(0,0,255,122,GxEPD_WHITE);

     // display.drawExampleBitmap(Surfbuddie_logo_zwart, 185, 0, 64, 64, GxEPD_BLACK);
    
    // Board:
    if(logo_choice[0]==1)
      display.drawExampleBitmap(Starboard_logoS_zwart, 195, 0, 48, 48, GxEPD_BLACK);
    if(logo_choice[0]==2)  
      display.drawExampleBitmap(Fanatic_logoS_zwart, 195, 0, 48, 48, GxEPD_BLACK);
    if(logo_choice[0]==3)  
      display.drawExampleBitmap(JP_logoS_zwart, 195, 0, 48, 48, GxEPD_BLACK);
    if(logo_choice[0]==4)  
      display.drawExampleBitmap(NoveNove_logoS_zwart, 195, 0, 48, 48, GxEPD_BLACK);
    
    // Zeil:
    if(logo_choice[1]==1)
      display.drawExampleBitmap(GAsails_logoS_zwart, 195, 50, 48, 48, GxEPD_BLACK);
    if(logo_choice[1]==2)
      display.drawExampleBitmap(DuoTone_logoS_zwart, 195, 50, 48, 48, GxEPD_BLACK);
    if(logo_choice[1]==3)
      display.drawExampleBitmap(Pryde_logoS_zwart, 195, 50, 48, 48, GxEPD_BLACK);
    if(logo_choice[1]==4)
      display.drawExampleBitmap(NP_logoS_zwart, 195, 50, 48, 48, GxEPD_BLACK);
    
      display.setFont(&SF_Distant_Galaxy7pt7b);//font ??
      display.setCursor(col1,105);
      display.print(RTC_hour);display.print(":");display.print(RTC_min);display.print(" ");display.print(RTC_day);display.print("-");display.print(RTC_month);display.print("-");display.print(RTC_year);
    
      display.setCursor(col1,121);
      display.setFont(&SF_Distant_Galaxy9pt7b);
      display.print(Sleep_txt);//display.print("Jan");
    
      display.setRotation(0);
      display.setCursor(30,249);//was 30, 249
      display.setFont(&FreeSansBold6pt7b);
      if((int)(calibration_speed*100000)==194) display.print("speed in knots");//1.94384449 m/s to knots !!!
      if((int)(calibration_speed*1000000)==3600) display.print("speed in km/h");
      //display.print("speed in km/h");
    
      display.setRotation(1);
    // left column
      display.setFont(&FreeMonoBold9pt7b);
      display.setCursor(col1,row1);
      display.print("AV:");
      display.setCursor(col1,row2);
      display.print("R1:");
      display.setCursor(col1,row3);
      display.print("R2:");
      display.setCursor(col1,row4);
      display.print("R3:");
      display.setCursor(col1,row5);
      display.print("R4:");
      display.setCursor(col1,row6);
      display.print("R5:");
    
      display.setFont(&FreeSansBold9pt7b);
      display.setCursor(col2,row1);
      display.println(RTC_avg_10s,2);
      display.setCursor(col2,row2);
      display.println(RTC_R1_10s,2);
      display.setCursor(col2,row3);
      display.println(RTC_R2_10s,2);
      display.setCursor(col2,row4);
      display.println(RTC_R3_10s,2);
      display.setCursor(col2,row5);
      display.println(RTC_R4_10s,2);
      display.setCursor(col2,row6);
      display.println(RTC_R5_10s,2);
    
    // right column
      display.setFont(&FreeMonoBold9pt7b);
      display.setCursor(col3,row1);
      display.print("2sec:");
      display.setCursor(col3,row2);
      display.print("Dist:");
      display.setCursor(col3,row3);
      display.print("Alp :");
      display.setCursor(col3,row4);
      display.print("500m:");
      display.setCursor(col3,row5);
      display.print("Mile:");
      display.setCursor(col3,row6);
      display.print("Bat :");
  
      display.setFont(&FreeSansBold9pt7b);
      display.setCursor(col4,row1);
      display.println(RTC_max_2s,2);
      display.setCursor(col4,row2);
      display.println(RTC_distance,2);
      display.setCursor(col4,row3);
      display.println(RTC_alp,2);
      display.setCursor(col4,row4);
      display.println(RTC_500m,2);
      display.setCursor(col4,row5);
      display.println(RTC_mile,2); 
      display.setCursor(col4,row6);
      display.println(voltage_bat,2);  
      //display.updateWindow(0,0,250,122,true); 
      display.update(); 
      }
}
void Bat_level(int offset){
    float bat_symbol=0;
    display.fillRect(offset+225,87,6,3,GxEPD_BLACK);//display.fillRect(offset+206,105,4,6,GxEPD_BLACK);
    display.fillRect(offset+222,90,12,30,GxEPD_BLACK);//monitor=(4.2-voltage_bat)*26
    if(voltage_bat<4.2) {
        bat_symbol=(4.2-voltage_bat)*28;
        display.fillRect(offset+224,94,8,(int)bat_symbol,GxEPD_WHITE);
        }
    }
void Bat_level_Simon(int offset){
    float bat_perc=100*(1-(4.2-voltage_bat)/(4.2-3.4));
    if (bat_perc<0) bat_perc=0;
    if (bat_perc>100) bat_perc=100;

    int batW=8;
    int batL=15;
    int posX=250-batW-10;
    int posY=122-batL;
    int line=2;
    int seg=3;
    int segW=batW-2*line;
    int segL=(batL-0.25*batW-2*line-(seg-1))/seg;
    display.fillRect(offset+posX,posY,0.5*batW,0.25*batW,GxEPD_BLACK);//battery top
    display.fillRect(offset+posX-0.25*batW,posY+0.25*batW,batW,batL,GxEPD_BLACK);//battery body
    if (bat_perc<67) display.fillRect(offset+posX-0.25*batW+line, posY+0.25*batW+line,            segW, segL,GxEPD_WHITE);
    if (bat_perc<33) display.fillRect(offset+posX-0.25*batW+line, posY+0.25*batW+line+1*(segL+1), segW, segL,GxEPD_WHITE);
    if (bat_perc<1)  display.fillRect(offset+posX-0.25*batW+line, posY+0.25*batW+line+2*(segL+1), segW, segL,GxEPD_WHITE);
//    if (bat_perc<0)  display.fillRect(offset+posX-0.25*batW+line, posY+0.25*batW+line+3*(segL+1), segW, segL,GxEPD_WHITE);
//    if (bat_perc<0)  display.fillRect(offset+posX-0.25*batW+line, posY+0.25*batW+line+4*(segL+1), segW, segL,GxEPD_WHITE);
    if (bat_perc<100) display.setCursor(offset+193,120);
    else display.setCursor(offset+185,120);
    display.setFont(&FreeSansBold9pt7b);
    display.print(int(bat_perc)); display.print("%");
    }
void Sats_level(int offset){
    int circelL=5;
    int circelS=2;
    int posX=172+offset;
    int posY=122-(circelL+2*circelS);

/*  Quarter-circle drawer with fill, used for circles and roundrects
    Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color)
    @param  x0       Center-point x coordinate
    @param  y0       Center-point y coordinate
    @param  r        Radius of circle
    @param  corners  Mask bits indicating which half we're doing 1: right half, 2: left half
    @param  delta    Offset from center-point, used for round-rects
    @param  color    16-bit 5-6-5 Color to fill with

    Draw a triangle with color-fill
    Adafruit_GFX::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
    @param    x0  Vertex #0 x coordinate
    @param    y0  Vertex #0 y coordinate
    @param    x1  Vertex #1 x coordinate
    @param    y1  Vertex #1 y coordinate
    @param    x2  Vertex #2 x coordinate
    @param    y2  Vertex #2 y coordinate
    @param    color 16-bit 5-6-5 Color to fill/draw with
*/
    display.fillCircle ( posX, posY, circelL, GxEPD_BLACK);
    display.fillTriangle (posX, posY+(circelL+2*circelS), posX-circelL , posY+circelS, posX+circelL , posY+circelS,GxEPD_BLACK);
    display.fillCircle ( posX, posY, circelS, GxEPD_WHITE);

    display.setCursor(posX-25,posY+8);
    display.setFont(&FreeSansBold9pt7b);
    display.print(int(ubxMessage.navPvt.numSV));
    }     
   
void Update_screen(int screen){
    static int count,offset,old_screen,update_delay;
    if(screen!=old_screen)update_epaper=2;//klopt niet, altijd wit scherm tussendoor 
    update_epaper=1; //was zonder else
    if(count%20<10) offset++;
    else offset--; 
    if(offset>10)offset=0;//bij overschakelen scherm soms offset>20, laatste cijfer speed valt weg !!! 
    if(offset<0)offset=0;
    display.fillScreen(GxEPD_WHITE); 
    if(screen==SPEED){
        update_delay=100;
        int run_rectangle_length;
        int field=config.field;//standaard keuze van config.txt
        int bar_length=config.bar_length*1000/240;//standaard 100% lengte = 1852 m
        if(config.field==1){                      //alleen switchen indien config.field==1 !!!
             if((Ublox.alfa_distance/1000<400)&(alfa_window<100))field=5;//eerste 300 m na de gijp is het alfa screen zichtbaar !!
             if(Ublox.alfa_distance/1000>config.bar_length)field=8;//indien run langer dan 1852 m, NM scherm !!
            }
        if(config.field==2){     
            if(Ublox.run_distance/1000>config.bar_length)field=8;//indien run langer dan 1852 m, NM scherm !!
            }
        if(GPS_Signal_OK==true){
              display.setFont(&SansSerif_bold_96_nr);
              display.setCursor(offset,120);//was offset + 2
              display.println(ubxMessage.navPvt.gSpeed*calibration_speed,1);//calibration_speed is 3.6/1000 !!!
              }
        else{
              display.setCursor(offset,60);
              display.setFont(&FreeSansBold18pt7b);
              display.print("Low GPS signal !");
              }
        display.setCursor(offset,25);//was offset, 24
        display.setFont(&FreeSansBold18pt7b);
        display.setTextColor(GxEPD_BLACK);  
        if(field<=2){
            display.setFont(&FreeSansBold12pt7b); 
            display.print("Run ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S10.s_max_speed*calibration_speed,1);//actueel topspeed 10s van deze run
            //display.print(ref_heading,0);//dit is de referentie heading van 200 m eerder...
            display.setCursor(offset+122,24);
            display.setFont(&FreeSansBold12pt7b);
            display.print("Avg ");
            //display.print("Hd ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S10.avg_5runs*calibration_speed,1); 
            //display.print(delta_heading,0);//dit is het verschil met de referentie heading
            //display.print(ubxMessage.navPvt.heading/100000.0f,0);
            }
        if(field==3){
            display.setFont(&FreeSansBold12pt7b);
            display.print("Dis ");
            display.setFont(&FreeSansBold18pt7b);
            if(Ublox.total_distance/1000,0<9999)
            display.print(Ublox.total_distance/1000,0);//Total distance in meter, als test run_distance
            else
            display.print(Ublox.total_distance/1000000,1);//Total distance in km, als test run_distance
            display.setCursor(offset+135,24);
            display.setFont(&FreeSansBold12pt7b);
            display.print("R ");//15+9+7= 31 px
            display.setFont(&FreeSansBold18pt7b);
            display.print(Ublox.run_distance/1000,0);//Actuele run_distance  4*19=76 px, 107 px
            }
        if(field==4){
            //display.setTextColor(GxEPD_BLACK);  
            display.setFont(&FreeSansBold12pt7b);
            display.print("2S ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S2.display_max_speed*calibration_speed,1);  //best 2s
            display.setCursor(offset+124,24);
            display.setFont(&FreeSansBold12pt7b);
            display.print("10S ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S10.display_max_speed*calibration_speed,1);  //best 10s run
            }
        if(field==5){
            bar_length=250*1000/240;//volle lengte = 250m
            //display.setTextColor(GxEPD_BLACK);  
            display.setFont(&FreeSansBold12pt7b);
            if((alfa_window<100)&(Ublox.alfa_distance/1000<350)&(A500.alfa_speed_max*calibration_speed<1)){  //Window alleen indien Window<100 en Run>350 meter !!!!
                display.print("Wind ");                                                                     // en nog geen geldige alfa
                display.setFont(&FreeSansBold18pt7b);   //W55 E89 A23.1
                display.print(alfa_window,0);           //Wind 12 Ex 123 
                //display.print(A500.straight_dist_square,0);   
                }
            else{
                display.print("Alfa ");
                display.setFont(&FreeSansBold18pt7b);    
                display.print(A500.display_max_speed*calibration_speed,1);   //best Alfa from session on 500 m !! 
                }
            display.setCursor(offset+130,25);//was 24
            display.setFont(&FreeSansBold12pt7b);
            if(Ublox.alfa_distance/1000<255){                          //poging alfa nog bezig
                display.print("Ex ");
                display.setFont(&FreeSansBold18pt7b);
                if(alfa_exit>251)alfa_exit=250;//begrenzen alfa_exit...
                display.print(alfa_exit,0);//test functie
               }
            else if(A500.alfa_speed_max*calibration_speed>1){         //laatste alfa was geldig !!!!
                display.print("Al ");           //nieuwe alfa laatste gijp or MISSED !!!!
                display.setFont(&FreeSansBold18pt7b);
                //display.print(M500.m_speed_alfa*calibration_speed,1);  //dit is de actuale avg van de laatste 500 m !!!
                display.print(A500.alfa_speed_max*calibration_speed,1);  //last alfa, back to zero 500 m after jibe !!
                }
            else{
               display.setFont(&FreeSansBold18pt7b);            //laatste alfa was ongeldig !!!!
               display.print("MISS");   
              }
            }
         if(field==6){
            //display.setTextColor(GxEPD_BLACK);  
            display.setFont(&FreeSansBold12pt7b);
            display.print(".5A ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S1800.avg_s*calibration_speed,1);   //actual average last 30 min
            display.setCursor(offset+124,24);
            display.setFont(&FreeSansBold12pt7b);
            display.print(".5B ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S1800.display_max_speed*calibration_speed,1);   //best average over 30 min
            }    
        if(field==7){
            //display.setTextColor(GxEPD_BLACK);  
            display.setFont(&FreeSansBold12pt7b);
            display.print("1hA ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S1800.avg_s*calibration_speed,1);   //actual average last hour
            display.setCursor(offset+124,24);
            display.setFont(&FreeSansBold12pt7b);
            display.print("1hB ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(S3600.display_max_speed*calibration_speed,1);   //best 3600s
            }
         if(field==8){
            display.setFont(&FreeSansBold12pt7b); 
            display.print("NMa ");    //Actuele nautical mile
            display.setFont(&FreeSansBold18pt7b);
            display.print(M1852.m_max_speed*calibration_speed,1);//actueel topspeed 10s van deze run
            display.setCursor(offset+129,24);
            display.setFont(&FreeSansBold12pt7b);
            display.print("NM ");
            display.setFont(&FreeSansBold18pt7b);
            display.print(M1852.display_max_speed*calibration_speed,1);   //Snelste nautical mile van de sessie
            }  
        run_rectangle_length=(Ublox.alfa_distance/bar_length);
        if(bar_length){
            display.fillRect(offset,32,run_rectangle_length,8,GxEPD_BLACK);//balk voor run_distance weer te geven...
            }
        }
        if(screen==AVG_10S){
        update_delay=1000;
        display.setFont(&FreeSansBold12pt7b);
       // display.setCursor(0,18);
        for(int i=9;i>4;i--){
            display.setCursor(offset,24*(10-i));
            display.print("Run ");display.print(10-i);display.print(": ");
            display.print(S10.avg_speed[i]*calibration_speed,2);display.print(" @");
            display.print(S10.time_hour[i]);display.print(":");
            display.print(S10.time_min[i]);
            //display.println(ubxMessage.navPvt.gSpeed/1000.0f*calibration_speed,1);
            }   
        }      
    if(screen==BOOT_SCREEN){
        update_delay=1000;
        display.setFont(&FreeSansBold12pt7b);
        display.setCursor(offset,20);
        if(sdOK==true)
        display.print("SD OK!");
        else display.print("No SD!");
        if(config.dynamic_model==1)display.print(" SEA");
        else display.print(" Port");
        display.setCursor(offset,44);
        display.print(config.UBXfile);
        display.setCursor(offset,68);
        display.print("Rate: ");display.print(config.sample_rate);display.println("Hz"); 
        display.setCursor(offset,92);
        display.print("Speed: ");
        if((int)(calibration_speed*100000)==194) display.print("knots");//1.94384449 m/s to knots !!!
        if((int)(calibration_speed*1000000)==3600) display.print("km/h");
        display.setCursor(offset,116);
        if(config.config_fail==0) display.print("Config OK");
        else  display.print("Config FAIL !");
        if(screen!=old_screen)count=0;//eerste keer full update
      }
     if(screen==STATS1){                        //2s,10sF,10sS, AVG
        update_delay=1000;
        display.setFont(&FreeSansBold18pt7b);
        display.setCursor(offset,24);
        display.print("2s: ");display.print(S2.avg_speed[9]*calibration_speed);  //best 2s, was avg_speed[9]
        display.setFont(&FreeSansBold12pt7b);
        display.setCursor(202+offset%2,22);//zodat SXX niet groter wordt dan 244 pix
        display.print("S");
        display.println(ubxMessage.navPvt.numSV);
        display.setFont(&FreeSansBold18pt7b);
        display.setCursor(offset,56);
        display.print("10sF: ");display.println(S10.display_max_speed*calibration_speed); //best 10s(Fast), was avg_speed[9]
        display.setCursor(offset,88);
        display.print("10sS: ");display.println(S10.display_speed[5]*calibration_speed);  //langzaamste 10s(Slow) run van de sessie
        display.setCursor(offset,120);
        display.print("AVG: ");display.println(S10.avg_5runs*calibration_speed); //average 5*10s
        //display.print("M100: ");display.println(M100.m_max_speed*calibration_speed,2); //average 5*10s
        Bat_level(offset);
      }
     if(screen==STATS2){                        //alfa 500m,1852m, 1800s,total_dist
        update_delay=1000;
        getLocalTime(&tmstruct, 0);
        static int toggle=0;
        display.setFont(&FreeSansBold18pt7b);
        display.setCursor(offset,24);
        display.print("Dis: ");display.print(Ublox.total_distance/1000,0);
        display.setFont(&FreeSansBold12pt7b);
        display.setCursor(202+offset%2,22);//zodat SXX niet groter wordt dan 244 pix
        display.print("S");
        display.println(ubxMessage.navPvt.numSV);
        display.setFont(&FreeSansBold18pt7b);
        display.setCursor(offset,56);
        display.print("1852m: ");display.println(M1852.display_max_speed*calibration_speed);//was avg_speed[9]
        display.setCursor(offset,88);
        if(toggle==0){
          display.print("1800S: ");display.println(S1800.display_max_speed*calibration_speed);
          display.setCursor(offset,120);
          display.print("Alfa: ");display.print(A500.avg_speed[9]*calibration_speed);   //best Alfa on 500 m 
          toggle=1;
        }
        else{
          display.print("3600S: ");display.println(S3600.display_max_speed*calibration_speed);
          display.setCursor(offset,120);
          display.print(tmstruct.tm_hour);
          display.print(":");display.print(tmstruct.tm_min);
          display.print(":");display.print(tmstruct.tm_sec);
          toggle=0;
          }
        Bat_level(offset);
      }
   if(screen==STATS3){                        //100m,250m, 500m,Alfa
          update_delay=1000;
          display.setFont(&FreeSansBold18pt7b);
          display.setCursor(offset,24);
          display.print("100m: ");display.print(M100.avg_speed[9]*calibration_speed);  //best 2s, was avg_speed[9]
          //display.setFont(&FreeSansBold12pt7b);
          //display.setCursor(202+offset%2,22);//zodat SXX niet groter wordt dan 244 pix
          //display.print("S");
          //display.println(ubxMessage.navPvt.numSV);
          //display.setFont(&FreeSansBold18pt7b);
          display.setCursor(offset,56);
          display.print("250m: ");display.println(M250.display_max_speed*calibration_speed); //best 10s(Fast), was avg_speed[9]
          display.setCursor(offset,88);
          display.print("500m: ");display.println(M500.avg_speed[9]*calibration_speed);  //langzaamste 10s(Slow) run van de sessie
          display.setCursor(offset,120);
          display.print("Alfa: ");display.println(A500.avg_speed[9]*calibration_speed,2); //average 5*10s
          Bat_level(offset);
        }
     if(screen==STATS4){                        //10s,AVG,5 runs, update on the fly !!!
        update_delay=1000;static int j=0;
        display.setCursor(offset,26);
        display.setFont(&FreeSansBold12pt7b);
        display.print("10s AVG: "); 
        display.setFont(&FreeSansBold18pt7b);
        display.println(s10.avg_5runs*calibration_speed,2); //eerste regel, avg_5runs krijgt update tijdens run !!
        for(int i=9;i>6;i--){
          display.setCursor(offset,56+(9-i)*32);
          display.setFont(&FreeSansBold12pt7b);display.print("R");display.print(10-i);display.print(" ");
          display.setFont(&FreeSansBold18pt7b);display.print(s10.display_speed[i]*calibration_speed,1);
          display.setCursor(offset+118,56+(9-i)*32);
          if(i>7){
              display.setFont(&FreeSansBold12pt7b);display.print(" R");display.print(13-i);display.print(" ");
              display.setFont(&FreeSansBold18pt7b);display.print(s10.display_speed[i-3]*calibration_speed,1);
              }
          else{
              display.print(tmstruct.tm_hour);
              display.print(":");display.print(tmstruct.tm_min);
              }
          }
      }
      if(screen==STATS5){                        //alfa statistics
            update_delay=500;
            display.setCursor(offset,26);
            display.setFont(&FreeSansBold12pt7b);
            display.print("Last Alfa stats ! "); 
            display.setFont(&FreeSansBold18pt7b);
            //display.println(a500.avg_5runs*calibration_speed,2); //eerste regel
            for(int i=9;i>6;i--){
              display.setCursor(offset,56+(9-i)*32);
              display.setFont(&FreeSansBold12pt7b);display.print("A");display.print(10-i);display.print(" ");
              display.setFont(&FreeSansBold18pt7b);display.print(a500.avg_speed[i]*calibration_speed,1);
              display.setCursor(offset+118,56+(9-i)*32);
              if(i>7){
                  display.setFont(&FreeSansBold12pt7b);display.print(" A");display.print(13-i);display.print(" ");
                  display.setFont(&FreeSansBold18pt7b);display.print(a500.avg_speed[i-3]*calibration_speed,1);
                  }
              else{
                  display.print(tmstruct.tm_hour);
                  display.print(":");display.print(tmstruct.tm_min);
                  }
              }
          }
      if(screen==STATS6){ //Simon stat screen
          Serial.println("STATS6_Simon_screen");
          update_delay=2000;
          double S10avgNEW;
    
          if (S10.s_max_speed>S10.avg_speed[5]) S10avgNEW=(S10.avg_speed[9]+S10.avg_speed[8]+S10.avg_speed[7]+S10.avg_speed[6]+S10.s_max_speed)/5;
          else S10avgNEW=(S10.avg_speed[9]+S10.avg_speed[8]+S10.avg_speed[7]+S10.avg_speed[6]+S10.avg_speed[5])/5;
    
          int row1=15;
          int row=18;
          int row2=row1+row;
          int row3=row2+row;
          int row4=row3+row;
          int row5=row4+row;
          int row6=row5+row;
          int col1=0+offset;
          int col2=46+offset;
          int col3=114+offset;
          int col4=182+offset;
          int line=0;
    
          Bat_level_Simon(offset);
          Sats_level(offset);
          
          display.setCursor(offset,122);
          display.setFont(&FreeSansBold9pt7b);
          display.print(tmstruct.tm_hour);display.print(":");display.print(tmstruct.tm_min);
          
          display.setFont(&FreeMonoBold12pt7b);
          display.setCursor(col1,row1);
          display.print("AV:");
          display.setCursor(col1,row2);
          display.print("R1:");
          display.setCursor(col1,row3);
          display.print("R2:");
          display.setCursor(col1,row4);
          display.print("R3:");
          display.setCursor(col1,row5);
          display.print("R4:");
          display.setCursor(col1,row6);
          display.print("R5:");
        
          display.setFont(&FreeSansBold12pt7b);
          display.setCursor(col2,row1);
    
          display.println(S10avgNEW*calibration_speed,2); //Laat het gemiddelde incl de previous 10s zien mits in top5
          display.setCursor(col2,row2);
          display.println(S10.avg_speed[9]*calibration_speed,2);
          display.setCursor(col2,row3);
          display.println(S10.avg_speed[8]*calibration_speed,2);
          display.setCursor(col2,row4);
          display.println(S10.avg_speed[7]*calibration_speed,2);
          display.setCursor(col2,row5);
          display.println(S10.avg_speed[6]*calibration_speed,2);
          display.setCursor(col2,row6);
          display.println(S10.avg_speed[5]*calibration_speed,2);
    // right column
          display.setFont(&FreeMonoBold12pt7b);
          display.setCursor(col3,row1);
          display.print("2sec:");
          display.setCursor(col3,row2);
          display.print("Prv :");
          display.setCursor(col3,row3);
          display.print("Dist:");
          display.setCursor(col3,row4);
          display.print("Alp :");
          display.setCursor(col3,row5);
          display.print("500m:");
          display.setCursor(col3,row6);
          display.print("Mile:");
    
          display.setFont(&FreeSansBold12pt7b);
          display.setCursor(col4,row1);
          display.println(S2.avg_speed[9]*calibration_speed,2);
          display.setCursor(col4,row2);
          display.println(S10.s_max_speed*calibration_speed,2);
          display.setCursor(col4,row3);
          display.println(Ublox.total_distance/1000000);
          display.setCursor(col4,row4);
          display.println(A500.avg_speed[9]*calibration_speed,2);
          display.setCursor(col4,row5);
          display.println(M500.display_max_speed*calibration_speed,2);
          display.setCursor(col4,row6);
          display.println(M1852.display_max_speed*calibration_speed,2);
    
    // position line of actual 10s run
          if (S10.s_max_speed*calibration_speed>S10.avg_speed[9]*calibration_speed) line=row1;
          else if (S10.s_max_speed*calibration_speed>S10.avg_speed[8]*calibration_speed) line=row2;
          else if (S10.s_max_speed*calibration_speed>S10.avg_speed[7]*calibration_speed) line=row3;
          else if (S10.s_max_speed*calibration_speed>S10.avg_speed[6]*calibration_speed) line=row4;
          else if (S10.s_max_speed*calibration_speed>S10.avg_speed[5]*calibration_speed) line=row5;
          else line=row6;
          display.fillRect(0,line+2,col3-10,2,GxEPD_BLACK);//lijn voor actuele run weer te geven...
    
            }
                
    if(screen==WIFI_ON){  
        update_delay=250;
        if(count%20<10) offset++;
        else offset--;    
        display.setFont(&FreeSansBold18pt7b);
        display.setCursor(offset,26);
        if(Wifi_on==1){
              display.print("Wifi on  ");
              if(SoftAP_connection==true) display.print("AP !");//ap mode
              else display.print ("ST !");//station mode
              }
        else {
            display.println("Wifi off");
            display.setCursor(180+offset%2,26);//zodat SXX niet groter wordt dan 244 pix
            display.print("S");
            display.println(ubxMessage.navPvt.numSV);
            }
        display.setCursor(offset,56);
        display.setFont(&FreeSansBold12pt7b);
        display.println(IP_adress);
        display.setCursor(offset,88);
        //display.print("SATS: ");display.print(ubxMessage.navPvt.numSV);//geen GPS meer in Wifi ON !!
        display.print("FTP status: ");display.println(ftpStatus);
        display.setCursor(offset,120);
        display.print("Bat:");display.print(voltage_bat,2);   
        if(screen!=old_screen)count=0;//eerste keer full update 
      }
    if(screen==WIFI_STATION){  
        update_delay=0;   
        display.setFont(&FreeSansBold12pt7b);
        display.setCursor(offset,26);
        display.println("Connecting to ");
        display.setCursor(offset,56);
        display.setFont(&FreeSansBold12pt7b);
        display.println(config.ssid);
        display.setCursor(offset,88);
        display.print("AP on use magnet!");
        //display.print("SATS: ");display.println(ubxMessage.navPvt.numSV);
        display.setCursor(offset,120);
        display.print("Bat: ");
        display.print(voltage_bat,2); 
        display.setCursor(offset+190,120); 
        display.print(wifi_search); 
        if(screen!=old_screen)count=0;//eerste keer full update 
      }
       if(screen==WIFI_SOFT_AP){  
        update_delay=0;   
        display.setFont(&FreeSansBold18pt7b);
        display.setCursor(offset,26);
        display.print("Wifi AP:  ");
        display.setCursor(offset,56);
        display.setFont(&FreeSansBold12pt7b);
        display.println("ESP32AP");
        display.setCursor(offset,88);
        display.print("password ");
        display.setCursor(offset,120);
        display.print("Bat: ");display.print(voltage_bat,2); 
        display.setCursor(offset+190,120); 
        display.print(wifi_search);   
        if(screen!=old_screen)count=0;//eerste keer full update 
      }
    if(count%200==0){//was 200
        if(update_epaper>0) display.update();
        offset=0;
        }
    else {
          if(update_epaper==2){display.fillScreen(GxEPD_WHITE);}//test
          if(update_epaper>0) display.updateWindow(0,0,250,122,true);//was 244,122, true !!!
          //if(update_epaper>0) display.updateToWindow(0,0,0,0,250,122,true);//was 244,122, true !!!
          delay(update_delay);//update delay function of screen to show
          }
    old_screen=screen;
    count++;    
}
/*Eenmaal flankdetectie indien GPIO langer dan push_time gedrukt
* Ook variabele die dan long_pulse_time hoog blijft
* Ook variabele die optelt tot maw elke keer push
*/

Button_push::Button_push(int GPIO_pin,int push_time,int long_pulse_time,int max_count){
  pinMode(GPIO_pin,INPUT_PULLUP);
  Input_pin=GPIO_pin;
  time_out_millis=push_time;
  max_pulse_time=long_pulse_time;
  max_button_count=max_count;
}
boolean Button_push::Button_pushed(void){
  return_value=false;
  button_status=digitalRead(Input_pin);
  if(digitalRead(Input_pin)==1) push_millis=millis();
  if(((millis()-push_millis)>time_out_millis)&(old_button_status==0)){
    Serial.print ("Class button push ");
    Serial.println (millis()-push_millis);
    if (long_pulse) button_count++;
    if(button_count>max_button_count)button_count=0;
    old_button_status=1;
    millis_10s=millis();
    return_value=true;
    }
  else return_value=false; 
  if((millis()-millis_10s)<(1000*max_pulse_time)) long_pulse=true;
  else long_pulse=false; 
  if(digitalRead(Input_pin)==1) old_button_status=0;
  return return_value;
}

