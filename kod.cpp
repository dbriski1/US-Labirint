#include "mbed.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_lcd.h"
#include "string"
#include "sstream"
#include <cstdlib>
#include <vector>
 

InterruptIn igracF(p5);
InterruptIn igracB(p6);
InterruptIn igracL(p7);
InterruptIn igracR(p8);
DigitalIn resetovanje(p9);

class Tacka{
    int x,y,r;
public:
    Tacka(int x){
        this->x = x;
        this->y=10;
        this->r = 11;

    }
    void setuj(int x, int y){
         this->x = x;
          this->y = y;
    };
    bool test1(Tacka a){
        int x11;
        int y11;
        x11=a.Dajx();
        y11=a.Dajy();
        if((((BSP_LCD_ReadPixel (x11, y11-4))==0)&&((BSP_LCD_ReadPixel (x11, y11-5))==0)&&((BSP_LCD_ReadPixel (x11, y11-6))==0)))
        return true;
        else return false;
    }
     bool test2(Tacka a){
        int x11;
        int y11;
        x11=a.Dajx();
        y11=a.Dajy();
        if((((BSP_LCD_ReadPixel (x11, y11+4))==0)&&((BSP_LCD_ReadPixel (x11, y11+5))==0)&&((BSP_LCD_ReadPixel (x11, y11+6))==0)))
        return true;
        else return false;
    }
     bool test3(Tacka a){
        int x11;
        int y11;
        x11=a.Dajx();
        y11=a.Dajy();
        if((((BSP_LCD_ReadPixel (x11-4, y11))==0)&&((BSP_LCD_ReadPixel (x11-5, y11))==0)&&((BSP_LCD_ReadPixel (x11-6, y11))==0)))
        return true;
        else return false;
    }
     bool test4(Tacka a){
        int x11;
        int y11;
        x11=a.Dajx();
        y11=a.Dajy();
        if((((BSP_LCD_ReadPixel (x11+4, y11))==0)&&((BSP_LCD_ReadPixel (x11+5, y11))==0)&&((BSP_LCD_ReadPixel (x11+6, y11))==0)))
        return true;
        else return false;
    }
    void gore(){
        if(test1(*this)==true)
        this->y-=3;
    }
    void dole(){
        if(test2(*this)==true)
        this->y+=3;
    }
    void desno(){
        if(test4(*this)==true)
        this->x+=3;
    }
    void lijevo(){
        if(test3(*this)==true)
        this->x-=3;
    }
//tacka kojom upravljamo
    void display(){
        if(y>0){
//     kugla
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillCircle(x, y, 3);
    }
}
//finalna tacka
    void displayfinal(){
//     kugla
    BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
    BSP_LCD_FillCircle(120, 95, 4);
    
}
float distance(int x1, int y1, int x2, int y2){
    float a=sqrt(pow(x2 - x1, 2) +  pow(y2 - y1, 2) * 1.0);
    return (sqrt(pow(x2 - x1, 2)) +  sqrt(pow(y2 - y1, 2)));
};
 int Dajx() const{
        return this->x;
    }
 int Dajy() const{
        return this->y;
    }
bool udariloCilj(Tacka b){
        if(distance(b.Dajx(),b.Dajy(),120,95) < 15){ 
            printf("Kraj!\n");
            return true;
        }
        return false;
    }
};
 Tacka igrac1(10);
 
void upute(){
    
    while(1){
        
    BSP_LCD_Init();
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    std::string s("Labirint");    
    unsigned char *ime=new unsigned char[s.length()+1];
    strcpy((char*)ime,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(50, 50, ime, LEFT_MODE);    
    delete []ime;
       
    s="START!";
    unsigned char *start=new unsigned char[s.length()+1];
    strcpy((char*)start,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font20);
    BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
    BSP_LCD_DisplayStringAt(75, 90, start, LEFT_MODE);  
    delete []start;    
   
    {s="Upute:";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 120, c, LEFT_MODE);
    delete []c;}
   
    {s="Za pokretanje pritisnite p9.";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 135, c, LEFT_MODE);
    delete []c;}
   
    {s="Tasterima pomjerate objekat kroz";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 150, c, LEFT_MODE);
    delete []c;}
   
    {s="labirint, kako bi dosli do";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 165, c, LEFT_MODE);
    delete []c;}    
   
   
    {s="cilja (narancasto oznacene tacke).";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 180, c, LEFT_MODE);
    delete []c;}
   
   {s="Navigacija:";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 195, c, LEFT_MODE);
    delete []c;}
   
    {s="p5-gore p6-dole";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 210, c, LEFT_MODE);
    delete []c;}
   
    {s="p7-lijevo p8-desno";
    unsigned char *c=new unsigned char[s.length()+1];
    strcpy((char*)c,s.c_str());
    BSP_LCD_Init();
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(100);
    BSP_LCD_DisplayStringAt(5, 225, c, LEFT_MODE);
    delete []c;}
   
    //uslov da igra krene
   if(resetovanje==1)
        break;
       
   wait_ms(1);
   }
   
}
 
void Smjesko(){
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillCircle(120,120,50);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    //oci
    BSP_LCD_FillCircle(100,105,7);
    BSP_LCD_FillCircle(140,105,7);
     //usta
    BSP_LCD_FillEllipse (120, 140, 17,7);
    BSP_LCD_FillCircle(102,137,5);
    BSP_LCD_FillCircle(104,137,5);
    BSP_LCD_FillCircle(136,137,5);
    BSP_LCD_FillCircle(138,137,5);
    BSP_LCD_FillCircle(115,143,5);
    BSP_LCD_FillCircle(120,144,5);
    BSP_LCD_FillCircle(125,143,5);
    BSP_LCD_FillCircle(110,141,5);
    BSP_LCD_FillCircle(130,141,5);
     BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
     BSP_LCD_FillEllipse (120, 140, 7,2);
     
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
 
    std::string ex = "Cestitamo !";
    unsigned char *exporuka=new unsigned char[ex.length()+1];
    strcpy((char*)exporuka,ex.c_str());
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(7, 190, exporuka, CENTER_MODE);  
    ex = "p9-za povratak";
    strcpy((char*)exporuka,ex.c_str());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(7, 210, exporuka, CENTER_MODE);
    
    while(1){
        if(resetovanje==0) return;
        wait_ms(5);
    }
}
void Ljutko(){
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
   
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillCircle(120,120,50);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    //oci
    BSP_LCD_FillCircle(100,105,7);
    BSP_LCD_FillCircle(140,105,7);
     //usta
    BSP_LCD_FillEllipse (120, 140, 17,7);
    BSP_LCD_FillCircle(102,144,5);
    BSP_LCD_FillCircle(138,144,5);
    BSP_LCD_FillCircle(115,137,5);
    BSP_LCD_FillCircle(120,137,5);
    BSP_LCD_FillCircle(125,137,5);
    BSP_LCD_FillCircle(110,139,5);
    BSP_LCD_FillCircle(130,139,5);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_FillCircle(115,148,5);
    BSP_LCD_FillCircle(125,148,5);
    BSP_LCD_FillCircle(120,148,5);
    BSP_LCD_FillCircle(128,148,5);
    BSP_LCD_FillCircle(112,148,5);
    std::string ex = "Probaj ponovo!";
    unsigned char *exporuka=new unsigned char[ex.length()+1];
    strcpy((char*)exporuka,ex.c_str());
    BSP_LCD_SetFont(&Font16);
    BSP_LCD_DisplayStringAt(7, 190, exporuka, CENTER_MODE);  
    ex = "p9-za povratak";
    strcpy((char*)exporuka,ex.c_str());
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(7, 210, exporuka, CENTER_MODE);
    
    while(1){
        if(resetovanje==0) return;
        wait_ms(5);
    }
}
 void gore1(){
     igrac1.gore();
 }
 void dole1(){
     igrac1.dole();
 }
 void lijevo1(){
     igrac1.lijevo();
 }
 void desno1(){
     igrac1.desno();
 }
 Tacka final(238);

    void crtanje1(){
        BSP_LCD_SetFont(&Font24);
       BSP_LCD_DrawCircle (120, 95, 80);  
       BSP_LCD_DrawCircle (120, 95, 79); 
       BSP_LCD_DrawCircle (120, 95, 15);
       BSP_LCD_DrawCircle (120, 95, 16);
      
       BSP_LCD_DrawLine(108, 104, 89, 120 );
       BSP_LCD_DrawLine(131, 85,151 , 70);
       BSP_LCD_DrawLine(131, 104, 151, 120 );
       BSP_LCD_DrawLine(73, 58, 88, 70);
       BSP_LCD_DrawLine(151,120 , 167, 132 );
       BSP_LCD_DrawLine(73, 132, 57, 144);
       BSP_LCD_DrawLine(167, 58, 182, 45);
       BSP_LCD_DrawRect(88, 70, 63, 50);
       BSP_LCD_DrawRect(73, 57, 94, 74);
       BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
    BSP_LCD_FillRect (35,81, 15, 27);
    BSP_LCD_FillRect (107, 50, 20, 12);
    BSP_LCD_FillRect (110, 126, 21, 11);
    BSP_LCD_FillRect (82, 84, 16, 16);
    BSP_LCD_FillRect (105, 79, 10, 13);
    BSP_LCD_DrawLine(167,57 , 167, 132 );
    }
    void crtanje2(){
       BSP_LCD_SetFont(&Font24);
       BSP_LCD_DrawCircle (120, 95, 80);  
       BSP_LCD_DrawCircle (120, 95, 79); 
       BSP_LCD_DrawCircle (120, 95, 60);
       BSP_LCD_DrawCircle (120, 95, 59);
       BSP_LCD_DrawCircle (120, 95, 40);
        BSP_LCD_DrawCircle (120, 95, 39);
       BSP_LCD_DrawCircle (120, 95, 20);
       BSP_LCD_DrawCircle (120, 95, 19);
       BSP_LCD_DrawLine(41, 81, 60, 85 );
       BSP_LCD_DrawLine(120, 155, 120, 135 );
       BSP_LCD_DrawLine(155, 112, 137, 104);
       BSP_LCD_DrawLine(118, 175, 118, 155 );
       BSP_LCD_DrawLine(190, 134, 172, 125);
       BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
    BSP_LCD_FillRect (68, 22, 17, 12);
    BSP_LCD_FillRect (177, 95, 10, 16);
    BSP_LCD_FillRect (100, 55, 13, 5);
    BSP_LCD_FillRect (134, 80, 8, 13);
    }
     void crtanje3(){
       BSP_LCD_SetFont(&Font24);
       BSP_LCD_DrawCircle (120, 95, 80);  
       BSP_LCD_DrawCircle (120, 95, 79); 
       BSP_LCD_DrawCircle (120, 95, 60);
       BSP_LCD_DrawCircle (120, 95, 59);
       BSP_LCD_DrawCircle (120, 95, 40);
        BSP_LCD_DrawCircle (120, 95, 39);
       BSP_LCD_DrawCircle (120, 95, 20);
       BSP_LCD_DrawCircle (120, 95, 19);
       BSP_LCD_DrawLine(158, 141, 170, 157 );
       BSP_LCD_DrawLine(90, 43, 100, 60 );
       BSP_LCD_DrawLine(120, 135, 120, 115);
       BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
    BSP_LCD_FillRect (106, 174,21,4 );
    BSP_LCD_FillRect (150, 43, 16, 14);
    BSP_LCD_FillRect (75, 95, 10, 14);
    BSP_LCD_FillRect (134, 80, 8, 13);
    }
    void crtanje4(){
       BSP_LCD_SetFont(&Font24);
       BSP_LCD_DrawCircle (120, 95, 80);  
       BSP_LCD_DrawCircle (120, 95, 79); 
       BSP_LCD_DrawCircle (120, 95, 60);
       BSP_LCD_DrawCircle (120, 95, 59);
       BSP_LCD_DrawCircle (120, 95, 40);
       BSP_LCD_DrawCircle (120, 95, 39);
       BSP_LCD_DrawCircle (120, 95, 20);
       BSP_LCD_DrawCircle (120, 95, 19);
       BSP_LCD_DrawLine(174, 69, 191, 59 );
       BSP_LCD_DrawLine(90, 121, 74, 134 );
       BSP_LCD_DrawLine(108, 111, 94, 125);
        BSP_LCD_DrawLine(100, 94, 80, 94 );
       BSP_LCD_SetTextColor (LCD_COLOR_BLACK);
    BSP_LCD_FillRect (165, 146,16,16 );
    BSP_LCD_FillRect (90, 35, 20, 10);
    BSP_LCD_FillRect (106, 132, 15, 10);
    BSP_LCD_FillRect (118, 74, 15, 13);
    }
int main() {
    
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    wait_ms(500); 
    double brojac(0);
    srand(time(0));
    int r = rand() % 4;
    upute();
    while(1){
    std::string s1="";
    int procenat=brojac/(1920/100);
    if(brojac<864)
    s1 = "Sretno!";
    if(brojac>864 && brojac<1056)
    s1 = "Pola puta!";
    if(brojac>1056)
    s1 = std::to_string(100-procenat);
       
        unsigned char *score1=new unsigned char [s1.length()+1];
        strcpy((char *)score1, s1.c_str());
       
            BSP_LCD_Init();
            BSP_LCD_SetFont(&Font24);
            //bojanje ekrana
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
            //kraj bojanja ekrana
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_FillRect(brojac/8,190,240,10);            /// vremenska traka
            
            BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
            
           //Donji dio ekrana
           if(brojac<864)
            BSP_LCD_DisplayStringAt(60, 210, score1, LEFT_MODE);
           if(brojac>864 && brojac<1056)
            BSP_LCD_DisplayStringAt(40, 210, score1, LEFT_MODE);
           if(brojac>1056)
            BSP_LCD_DisplayStringAt(110, 210, score1, LEFT_MODE);
        //Okvir
        BSP_LCD_DrawRect(0, 0, 84, 48);
        BSP_LCD_SetTextColor (LCD_COLOR_WHITE);
    	BSP_LCD_DrawRect (0, 0, 239, 185);
    	//crtanje mape
    	
    	if ((r+1)==1)
        crtanje1();
        if ((r+1)==2)
        crtanje2();
        if ((r+1)==3)
        crtanje3();
        if ((r+1)==4)
        crtanje4();
        //prikaz tackica
        igrac1.display();
        final.displayfinal();
          //kontrola
          igracF.rise(&gore1);
          igracL.rise(&lijevo1);
          igracB.rise(&dole1);
          igracR.rise(&desno1);
       
                 
        brojac+=4;
            
            if(brojac>=1920||final.udariloCilj(igrac1)){
                srand(time(0));
                r = rand() % 4;
                igrac1.setuj(220,8);
                if(brojac>=1920){
                Ljutko();}
                else{
                Smjesko();}
                brojac=0;
                BSP_LCD_Clear(LCD_COLOR_WHITE);
                upute();
                wait_ms(5);
                
             }
            wait_ms(5);
     }
   }

