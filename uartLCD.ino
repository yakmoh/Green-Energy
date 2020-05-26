//#include <Wire.h>
#define LCD16X2   0
#define LCD20X4   1
#define DEBUG_LCD 2
#define VFD_LCD   3


#define HeaderPtr   0
#define ModePtr     1     //I
#define StatusPtr   2     //R
#define MainsVPtr    3    //220 V
#define InverterVPtr 6    //220 V
#define BatteryVPtr  9     //12.4 V
#define BatteryPPtr 12    //100 %
#define PowerPtr    15    //00800 VA
#define NBattPtr    20    //1
#define TBattPtr    21   //0
#define CBattPtr    22    //0200 AH
#define CurrPtr     26    //20 A
#define FooterPtr   28

#include <LiquidCrystal.h>

const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd20X4(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd16X2(rs, en, d4, d5, d6, d7);

int selectLcd = 8;

int lcdType = LCD16X2;

int  ptr;
String rxData ;


/* 
char lcd20Row0[]   = "     VA             ";
char lcd20Row1[]   = "BAT    AC     MODE  ";
char lcd20Row2[]   = "  . V     V         ";
char lcd20Row3[]   = "    %     V         ";
*/

char lcd20Row0[]   = "     VA    C      VA";
char lcd20Row1[]   = "DC:    A    AC:    A";
char lcd20Row2[]   = "  . V     V         ";
char lcd20Row3[]   = "    %     V         ";

                      
char lcd16Row0[]   = "  . V    V      ";
char lcd16Row1[]   = "    %    V      ";
                    

int updateLcd20X4(void);
int getLcd20X4Data  (void);

int getLcdDebugData(void);

int updateLcd16X2(void);
int getLcd16X2Data(void);
int getLcdVfdData(void);

void setup() {

  pinMode (selectLcd, INPUT);
  Serial.begin(115200);

  if (digitalRead (selectLcd) == 1 ){
      
      lcd20X4.begin(20, 4);
      
      lcd20X4.setCursor(0, 0);
      lcd20X4.print("     eriTPower      ");
      lcd20X4.setCursor(0, 1);
      lcd20X4.print("                    ");
      lcd20X4.setCursor(0, 2);
      lcd20X4.print("     ...loading     ");
      lcd20X4.setCursor(0, 3);
      lcd20X4.print("    please wait.    ");
      
      //updateLcd20X4();
      //lcdType = LCD20X4;   
      lcdType = DEBUG_LCD; 
  }
  else{
        lcd16X2.begin(16, 2);
        lcd16X2.setCursor(0, 0);
        lcd16X2.print("   eriTPower    ");
        lcd16X2.setCursor(0, 1);
        lcd16X2.print("   ...loading   ");
      
        //updateLcd16X2();  
        lcdType = LCD16X2 ;
       
  }
 
/*

        lcd16X2.begin(16, 2);
        lcd16X2.setCursor(0, 0);
        lcd16X2.print("   eriTPower    ");
        lcd16X2.setCursor(0, 1);
        lcd16X2.print("   ...loading   ");
     
        lcdType = VFD_LCD;
      */
}

void loop() {
 
   
    while(Serial.available()) {   
           rxData = Serial.readString();
           //Serial.print(rxData);
           
           ptr=rxData.indexOf( "*" );                                                                    
           if (ptr !=-1){ 
                 //*001VDC   1045rpm000VAC 34Hz 092C#
                if( (char)rxData.charAt(ptr + 28) == '#'){  //FooterPtr

                     if (lcdType == LCD16X2 )   { getLcd16X2Data();  updateLcd16X2(); }
                     
                     if (lcdType == LCD20X4 )   { getLcd20X4Data();  updateLcd20X4(); }

                     if (lcdType == DEBUG_LCD ) { getLcdDebugData();  updateLcd20X4(); }

                     if (lcdType == VFD_LCD ) { getLcdVfdData();  updateLcd16X2(); }
                }
                
           }
    }

}

int updateLcd20X4(void){

  lcd20X4.setCursor(0, 0);
  lcd20X4.print(lcd20Row0);
  lcd20X4.setCursor(0, 1);
  lcd20X4.print(lcd20Row1);
  lcd20X4.setCursor(0, 2);
  lcd20X4.print(lcd20Row2);
  lcd20X4.setCursor(0, 3);
  lcd20X4.print(lcd20Row3);

  return 1;
}

int updateLcd16X2(void){

  lcd16X2.setCursor(0, 0);
  lcd16X2.print(lcd16Row0);
  lcd16X2.setCursor(0, 1);
  lcd16X2.print(lcd16Row1);

  return 1;
}

int getLcd20X4Data(void){

    if((char)rxData.charAt(ptr+ModePtr)=='I')  { lcd20Row2[14]='I'; lcd20Row2[15]='N'; lcd20Row2[16]='V'; }    //mode
    if((char)rxData.charAt(ptr+ModePtr)=='M')  { lcd20Row2[14]='M'; lcd20Row2[15]='N'; lcd20Row2[16]='S'; }

    if((char)rxData.charAt(ptr+StatusPtr)=='S')  { lcd20Row3[14]='S';lcd20Row3[15]='D';lcd20Row3[16]='-';lcd20Row3[17]='B';lcd20Row3[18]='Y';  }  //status
    if((char)rxData.charAt(ptr+StatusPtr)=='R')  { lcd20Row3[14]='R';lcd20Row3[15]='U';lcd20Row3[16]='N';lcd20Row3[17]=' ';lcd20Row3[18]=' ';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='B')  { lcd20Row3[14]='B';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='A')  { lcd20Row3[14]='A';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='F')  { lcd20Row3[14]='F';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='N')  { lcd20Row3[14]='N';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='T')  { lcd20Row3[14]='T';lcd20Row3[15]='-';lcd20Row3[16]='E';lcd20Row3[17]='R';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='O')  { lcd20Row3[14]='O';lcd20Row3[15]='L';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='H')  { lcd20Row3[14]='H';lcd20Row3[15]='V';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='L')  { lcd20Row3[14]='L';lcd20Row3[15]='V';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='l')  { lcd20Row3[14]='L';lcd20Row3[15]='B';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='h')  { lcd20Row3[14]='H';lcd20Row3[15]='T';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='C')  { lcd20Row3[14]='C';lcd20Row3[15]='L';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='c')  { lcd20Row3[14]='C';lcd20Row3[15]='H';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }

    lcd20Row2[7]=(char)rxData.charAt(ptr+ 3); lcd20Row2[8]=(char)rxData.charAt(ptr+ 4); lcd20Row2[9]=(char)rxData.charAt(ptr+ 5);      //mains
    if(lcd20Row2[7]=='0'){ lcd20Row2[7]= ' ';}
    if((lcd20Row2[7]==' ')&&(lcd20Row2[8]=='0')){ lcd20Row2[7]= ' '; lcd20Row2[8]= ' '; lcd20Row2[9]= ' ';}
    
    lcd20Row3[7]=(char)rxData.charAt(ptr+ 6); lcd20Row3[8]=(char)rxData.charAt(ptr+ 7); lcd20Row3[9]=(char)rxData.charAt(ptr+ 8);      //inverter output voltage
    if(lcd20Row3[7]=='0'){ lcd20Row3[7]==' '; }
    if( (lcd20Row3[7]==' ')&&(lcd20Row3[8]=='0')){ lcd20Row3[7]==' '; lcd20Row3[8]==' '; lcd20Row3[9]==' '; }
    
    lcd20Row2[0]=(char)rxData.charAt(ptr+ 9); lcd20Row2[1]=(char)rxData.charAt(ptr+10); lcd20Row2[3]=(char)rxData.charAt(ptr+11);      //battery voltage
    lcd20Row3[1]=(char)rxData.charAt(ptr+12); lcd20Row3[2]=(char)rxData.charAt(ptr+13); lcd20Row3[3]=(char)rxData.charAt(ptr+14);      //battery parcentage
    lcd20Row0[0]=(char)rxData.charAt(ptr+15); lcd20Row0[1]=(char)rxData.charAt(ptr+16); lcd20Row0[2]=(char)rxData.charAt(ptr+17);      //power 
    lcd20Row0[3]=(char)rxData.charAt(ptr+18); lcd20Row0[4]=(char)rxData.charAt(ptr+19);      
    if (lcd20Row0[0] == '0') { lcd20Row0[0]= ' '; }
    if((lcd20Row0[0] == ' ')&&(lcd20Row0[1] == '0') ) { lcd20Row0[0]= ' '; lcd20Row0[1]= ' '; }
    return 1;
}

int getLcd16X2Data(void){

    if((char)rxData.charAt(ptr+ModePtr)=='I')  { lcd16Row0[11]='I'; lcd16Row0[12]='N'; lcd16Row0[13]='V'; }    //mode
    if((char)rxData.charAt(ptr+ModePtr)=='M')  { lcd16Row0[11]='M'; lcd16Row0[12]='N'; lcd16Row0[13]='S'; }

    if((char)rxData.charAt(ptr+StatusPtr)=='S')  { lcd16Row1[11]='S';lcd16Row1[12]='D';lcd16Row1[13]='-';lcd16Row1[14]='B';lcd16Row1[15]='Y';  }  //status
    if((char)rxData.charAt(ptr+StatusPtr)=='R')  { lcd16Row1[11]='R';lcd16Row1[12]='U';lcd16Row1[13]='N';lcd16Row1[14]=' ';lcd16Row1[15]=' ';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='B')  { lcd16Row1[11]='B';lcd16Row1[12]='-';lcd16Row1[13]='C';lcd16Row1[14]='H';lcd16Row1[15]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='A')  { lcd16Row1[11]='A';lcd16Row1[12]='-';lcd16Row1[13]='C';lcd16Row1[14]='H';lcd16Row1[15]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='F')  { lcd16Row1[11]='F';lcd16Row1[12]='-';lcd16Row1[13]='C';lcd16Row1[14]='H';lcd16Row1[15]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='N')  { lcd16Row1[11]='N';lcd16Row1[12]='-';lcd16Row1[13]='C';lcd16Row1[14]='H';lcd16Row1[15]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='T')  { lcd16Row1[11]='T';lcd16Row1[12]='-';lcd16Row1[13]='E';lcd16Row1[14]='R';lcd16Row1[15]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='O')  { lcd16Row1[11]='O';lcd16Row1[12]='L';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='H')  { lcd16Row1[11]='H';lcd16Row1[12]='V';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='L')  { lcd16Row1[11]='L';lcd16Row1[12]='V';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='l')  { lcd16Row1[11]='l';lcd16Row1[12]='B';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='h')  { lcd16Row1[11]='h';lcd16Row1[12]='T';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='C')  { lcd16Row1[11]='C';lcd16Row1[12]='L';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='c')  { lcd16Row1[11]='c';lcd16Row1[12]='H';lcd16Row1[13]='-';lcd16Row1[14]='S';lcd16Row1[15]='D';  }

    lcd16Row0[6]=(char)rxData.charAt(ptr+ 3); lcd16Row0[7]=(char)rxData.charAt(ptr+ 4); lcd16Row0[8]=(char)rxData.charAt(ptr+ 5);      //mains
    if(lcd16Row0[6]=='0'){ lcd16Row0[6]= ' ';}
    if((lcd16Row0[6]==' ')&&(lcd16Row0[7]=='0')){ lcd16Row0[6]= ' '; lcd16Row0[7]= ' '; lcd16Row0[8]= ' ';}
    
    lcd16Row1[6]=(char)rxData.charAt(ptr+ 6); lcd16Row1[7]=(char)rxData.charAt(ptr+ 7); lcd16Row1[8]=(char)rxData.charAt(ptr+ 8);      //inverter output voltage
    if(lcd16Row1[6]=='0'){ lcd16Row1[6]= ' ';}
    if((lcd16Row1[6]==' ')&&(lcd16Row1[7]=='0')){ lcd16Row1[6]= ' '; lcd16Row1[7]= ' '; lcd16Row1[8]= ' ';}
    
    lcd16Row0[0]=(char)rxData.charAt(ptr+ 9); lcd16Row0[1]=(char)rxData.charAt(ptr+10); lcd16Row0[3]=(char)rxData.charAt(ptr+11);      //battery voltage
    lcd16Row1[1]=(char)rxData.charAt(ptr+12); lcd16Row1[2]=(char)rxData.charAt(ptr+13); lcd16Row1[3]=(char)rxData.charAt(ptr+14);      //battery parcentage
    //lcd20Row0[1]=(char)rxData.charAt(ptr+15); lcd20Row0[2]=(char)rxData.charAt(ptr+16); lcd20Row0[3]=(char)rxData.charAt(ptr+17);      //power 
    
    return 1;
}

int getLcdDebugData(void){

    if((char)rxData.charAt(ptr+ModePtr)=='I')  { lcd20Row2[14]='I'; lcd20Row2[15]='N'; lcd20Row2[16]='V'; }    //mode
    if((char)rxData.charAt(ptr+ModePtr)=='M')  { lcd20Row2[14]='M'; lcd20Row2[15]='N'; lcd20Row2[16]='S'; }

    if((char)rxData.charAt(ptr+StatusPtr)=='S')  { lcd20Row3[14]='S';lcd20Row3[15]='D';lcd20Row3[16]='-';lcd20Row3[17]='B';lcd20Row3[18]='Y';  }  //status
    if((char)rxData.charAt(ptr+StatusPtr)=='R')  { lcd20Row3[14]='R';lcd20Row3[15]='U';lcd20Row3[16]='N';lcd20Row3[17]=' ';lcd20Row3[18]=' ';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='B')  { lcd20Row3[14]='B';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='A')  { lcd20Row3[14]='A';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='F')  { lcd20Row3[14]='F';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='N')  { lcd20Row3[14]='N';lcd20Row3[15]='-';lcd20Row3[16]='C';lcd20Row3[17]='H';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='T')  { lcd20Row3[14]='T';lcd20Row3[15]='-';lcd20Row3[16]='E';lcd20Row3[17]='R';lcd20Row3[18]='R';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='O')  { lcd20Row3[14]='O';lcd20Row3[15]='L';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='H')  { lcd20Row3[14]='H';lcd20Row3[15]='V';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='L')  { lcd20Row3[14]='L';lcd20Row3[15]='V';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='l')  { lcd20Row3[14]='l';lcd20Row3[15]='B';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='h')  { lcd20Row3[14]='h';lcd20Row3[15]='T';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='C')  { lcd20Row3[14]='C';lcd20Row3[15]='L';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }
    if((char)rxData.charAt(ptr+StatusPtr)=='c')  { lcd20Row3[14]='c';lcd20Row3[15]='H';lcd20Row3[16]='-';lcd20Row3[17]='S';lcd20Row3[18]='D';  }

    lcd20Row2[7]=(char)rxData.charAt(ptr+ 3); lcd20Row2[8]=(char)rxData.charAt(ptr+ 4); lcd20Row2[9]=(char)rxData.charAt(ptr+ 5);      //mains
    if(lcd20Row2[7]=='0'){ lcd20Row2[7]= ' ';}
    if((lcd20Row2[7]==' ')&&(lcd20Row2[8]=='0')){ lcd20Row2[7]= ' '; lcd20Row2[8]= ' '; lcd20Row2[9]= ' ';}
    
    lcd20Row3[7]=(char)rxData.charAt(ptr+ 6); lcd20Row3[8]=(char)rxData.charAt(ptr+ 7); lcd20Row3[9]=(char)rxData.charAt(ptr+ 8);      //inverter output voltage
    if( lcd20Row3[7]=='0'){ lcd20Row3[7]=' '; }
    if( (lcd20Row3[7]==' ')&&(lcd20Row3[8]=='0') ) { lcd20Row3[7]=' '; lcd20Row3[8]=' '; lcd20Row3[9]=' '; }
    
    lcd20Row2[0]=(char)rxData.charAt(ptr+ 9); lcd20Row2[1]=(char)rxData.charAt(ptr+10); lcd20Row2[3]=(char)rxData.charAt(ptr+11);      //battery voltage
    lcd20Row3[1]=(char)rxData.charAt(ptr+12); lcd20Row3[2]=(char)rxData.charAt(ptr+13); lcd20Row3[3]=(char)rxData.charAt(ptr+14);      //battery parcentage
    lcd20Row0[0]=(char)rxData.charAt(ptr+15); lcd20Row0[1]=(char)rxData.charAt(ptr+16); lcd20Row0[2]=(char)rxData.charAt(ptr+17);      //max power 
    lcd20Row0[3]=(char)rxData.charAt(ptr+18); lcd20Row0[4]=(char)rxData.charAt(ptr+19);      
    if (lcd20Row0[0] == '0') { lcd20Row0[0]= ' '; }
    if((lcd20Row0[0] == ' ')&&(lcd20Row0[1] == '0') ) { lcd20Row0[0]= ' '; lcd20Row0[1]= ' '; }

    lcd20Row0[13]=(char)rxData.charAt(ptr+44); lcd20Row0[14]=(char)rxData.charAt(ptr+45); lcd20Row0[15]=(char)rxData.charAt(ptr+46);      //current power 
    lcd20Row0[16]=(char)rxData.charAt(ptr+47); lcd20Row0[17]=(char)rxData.charAt(ptr+48);      
    if (lcd20Row0[13] == '0') { lcd20Row0[13]= ' '; }
    if((lcd20Row0[13] == ' ')&&(lcd20Row0[14] == '0') ) { lcd20Row0[13]= ' '; lcd20Row0[14]= ' '; }
    if((lcd20Row0[13] == ' ')&&(lcd20Row0[14] == ' ')&&(lcd20Row0[15] == '0') ) { lcd20Row0[13]= ' '; lcd20Row0[14]= ' '; lcd20Row0[15]= ' '; }
    if((lcd20Row0[13] == ' ')&&(lcd20Row0[14] == ' ')&&(lcd20Row0[15] == ' ')&&(lcd20Row0[16] == '0') ) { 
      lcd20Row0[13]= ' '; lcd20Row0[14]= ' '; lcd20Row0[15]= ' '; lcd20Row0[16]= ' ';
    }



    
    lcd20Row0[8]=(char)rxData.charAt(ptr+29); lcd20Row0[9]=(char)rxData.charAt(ptr+30); lcd20Row0[10]=(char)rxData.charAt(ptr+31);      // temperature
    lcd20Row1[3]=(char)rxData.charAt(ptr+32); lcd20Row1[4]=(char)rxData.charAt(ptr+33); lcd20Row1[5]=(char)rxData.charAt(ptr+34);       //DC current
    lcd20Row1[6]=(char)rxData.charAt(ptr+35);
    lcd20Row1[15]=(char)rxData.charAt(ptr+36); lcd20Row1[16]=(char)rxData.charAt(ptr+37); lcd20Row1[17]=(char)rxData.charAt(ptr+38);    //AC current
    lcd20Row1[18]=(char)rxData.charAt(ptr+39);


    
    return 1;
}


int getLcdVfdData(void){
    ptr++;
    for (int i=0;  i<16; i++ ){  lcd16Row0[i] = (char)rxData.charAt(ptr+i);  }
    for (int i=0;  i<16; i++ ){  lcd16Row1[i] = (char)rxData.charAt(ptr+i+16);  }

    return 1;
}
