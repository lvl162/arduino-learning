int latchPin = 6;
int clockPin = 7;
int dataPin = 5;
/* hàng và cột của LED matrix*/
int row[] = {1, 2, 4, 8, 16, 32, 64, 128};
int column[] = {128, 64, 32, 16, 8, 4, 2, 1};


/*biểu diễn các ký tự chữ và số ở dạng HEX*/
unsigned int characterHEX[][8] = {
{0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x66},//A
{0x78,0x64,0x68,0x78,0x64,0x66,0x66,0x7C},//B
{0x3C,0x62,0x60,0x60,0x60,0x62,0x62,0x3C},//C
{0x78,0x64,0x66,0x66,0x66,0x66,0x64,0x78},//D
{0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x7E},//E
{0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x60},//F
{0x3C,0x62,0x60,0x60,0x66,0x62,0x62,0x3C},//G
{0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x66},//H
{0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x7E},//I
{0x7E,0x18,0x18,0x18,0x18,0x18,0x1A,0x0C},//J
{0x62,0x64,0x68,0x70,0x70,0x68,0x64,0x62},//K
{0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7E},//L
{0xC3,0xE7,0xDB,0xDB,0xC3,0xC3,0xC3,0xC3},//M
{0x62,0x62,0x52,0x52,0x4A,0x4A,0x46,0x46},//N
{0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x3C},//O
{0x7C,0x62,0x62,0x7C,0x60,0x60,0x60,0x60},//P
{0x38,0x64,0x64,0x64,0x64,0x6C,0x64,0x3A},//Q
{0x7C,0x62,0x62,0x7C,0x70,0x68,0x64,0x62},//R
{0x1C,0x22,0x30,0x18,0x0C,0x46,0x46,0x3C},//S
{0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18},//T
{0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C},//U
{0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x18},//V
{0x81,0x81,0x81,0x81,0x81,0x99,0x99,0x66},//W
{0x42,0x42,0x24,0x18,0x18,0x24,0x42,0x42},//X
{0xC3,0x66,0x3C,0x18,0x18,0x18,0x18,0x18},//Y
{0x7E,0x02,0x04,0x08,0x10,0x20,0x40,0x7E},//Z
{0x3C,0x66,0x66,0x6E,0x76,0x66,0x66,0x3C},//0
{0x18,0x38,0x58,0x18,0x18,0x18,0x18,0x7E},//1
{0x3C,0x66,0x66,0x0C,0x18,0x30,0x7E,0x7E},//2
{0x7E,0x0C,0x18,0x3C,0x06,0x06,0x46,0x3C},//3
{0x0C,0x18,0x30,0x6C,0x6C,0x7E,0x0C,0x0C},//4
{0x7E,0x60,0x60,0x7C,0x06,0x06,0x46,0x3C},//5
{0x04,0x08,0x10,0x38,0x6C,0x66,0x66,0x3C},//6
{0x7E,0x46,0x0C,0x18,0x18,0x18,0x18,0x18},//7
{0x3C,0x66,0x66,0x3C,0x66,0x66,0x66,0x3C},//8
{0x3C,0x66,0x66,0x36,0x1C,0x08,0x10,0x20},//9
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},// khoảng trắng
{0x00,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x00}// hình trái tim, kí hiệu là '&'
};
/* ký tự đại diện để biểu diễn chữ và số trên matrix*/
char character[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ','&'};

  
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}


void scrollImage(unsigned int image[])
{
  int shift, hold, a;//biến shift dùng để lưu số bit cần shiftOut
                     //biến hold dùng để điều chỉnh độ dài của hiệu ứng
                     //biến a dùng để lưu column và row hiện tại
  for(shift = 0; shift < 9; shift++)
  {
    for(hold = 0; hold < 100; hold++)
    {
      for(a = 0; a < 8; a++)
      {
        digitalWrite(latchPin, 0);
        /* dịch ký tự sang trái*/
        shiftOut(dataPin,clockPin,MSBFIRST,~(image[7-a]<<shift));//column
        shiftOut(dataPin,clockPin,MSBFIRST,row[a]);//row
        digitalWrite(latchPin, 1);
//        delay(1);
      }
    }
  }
}
void scrollTextUp(String string, int speed = 100) {

  int index = 0;
  int hold;
  int a;
  int N = string.length();
  unsigned short idxs[N+1];
  unsigned char cur_word[8];
  for(int k = 0;k < string.length();k++)
     {
       for(int i=0;i < sizeof(character);i++)
       {
         if(string.charAt(k) == character[i])
         {
           //bỏ "//" nếu muốn sử dụng hàm blinkImage()
           //blinkImage(characterHEX[i],1,30,30);
           idxs[index++] = i;
           break;
         }
}
}
  for (int i =0;i<N; i++) {
    Serial.println(idxs[i]);
    }
  unsigned char scripts[N*10];
  index = 0;
  for (int i=0; i<N; i++) {
    scripts[index++] = 0;
    for (int j = 0; j<8; j++)
    scripts[index++] = characterHEX[idxs[i]][j];
   
    scripts[index++] = 0;
    } 
  
  
  for(int shift = 0; shift < 10*N; shift++)
  {
    for (int k = 0; k<8; k++) {
      cur_word[k] = scripts[(k+shift)%(N*10)];
      }
    for(hold = 0; hold < speed; hold++)
    {

      for(a = 0; a <8; a++)
      {
        
        digitalWrite(latchPin, 0);
        shiftOut(dataPin,clockPin,MSBFIRST,~cur_word[a]);//column
        shiftOut(dataPin,clockPin,MSBFIRST,row[7-a]);//row
        digitalWrite(latchPin, 1);}
      }

    
  }
  }
void scrollTextDown(String string, int speed = 100) {

  int index = 0;
  int hold;
  int a;
  int N = string.length();
  unsigned short idxs[N+1];
  unsigned char cur_word[8];
  for(int k = 0;k < string.length();k++)
     {
       for(int i=0;i < sizeof(character);i++)
       {
         if(string.charAt(k) == character[i])
         {
           //bỏ "//" nếu muốn sử dụng hàm blinkImage()
           //blinkImage(characterHEX[i],1,30,30);
           idxs[index++] = i;
           break;
         }
}
}
  for (int i =0;i<N; i++) {
    Serial.println(idxs[i]);
    }
  unsigned char scripts[N*10];
  index = 0;
  for (int i=0; i<N; i++) {
    scripts[index++] = 0;
    for (int j = 0; j<8; j++)
    scripts[index++] = characterHEX[idxs[i]][7-j];
   
    scripts[index++] = 0;
    } 
  
  
  for(int shift = 0; shift < 10*N; shift++)
  {
    for (int k = 0; k<8; k++) {
      cur_word[k] = scripts[(k+shift)%(N*10)];
      }
    for(hold = 0; hold < speed; hold++)
    {

      for(a = 0; a <8; a++)
      {
        
        digitalWrite(latchPin, 0);
        shiftOut(dataPin,clockPin,MSBFIRST,~cur_word[a]);//column
        shiftOut(dataPin,clockPin,MSBFIRST,row[a]);//row
        digitalWrite(latchPin, 1);}
      }

    
  }
  }  
void scrollTextLeft(String string, int speed = 100) {
  int N = string.length();
  if (string[N-1]!= ' ') string += ' ';
  int index = 0;
  int hold;
  int step = 1;
  int a;
  char* temp;
  unsigned int buff;
  temp = (char*) &buff;
  unsigned short idxs[N];
  for(int k = 0;k < N;k++)
     {
       for(int i=0;i < sizeof(character);i++)
       {
         if(string.charAt(k) == character[i])
         {
           //bỏ "//" nếu muốn sử dụng hàm blinkImage()
           //blinkImage(characterHEX[i],1,30,30);
           idxs[index++] = i;
           break;
         }
}
}

  unsigned short int ax[8];
  for (int i = 0; i< 8; i++) {
    ax[i] = 0;
    }
    
    unsigned char cur_word[8];
  // unsigned int ax = 0;
  for (int i = 0; i < sizeof(idxs)/sizeof(unsigned short); i++) {
    
  for (int j=0; j<8; j++) {
      
       cur_word[j] = characterHEX[idxs[i]][7-j];
       }
  for (int k = 0; k<8; k++) ax[k] = (ax[k] << 8) + cur_word[k];
  
  
      for(int shift = 0; shift <= 8; shift++)
  {
    // ax = 0;
    
    for(hold = 0; hold < speed; hold++)
    {

      for(a = 7; a >=0; a--)
      {

        
        buff = ~(ax[a]<<shift);
        digitalWrite(latchPin, 0);
        /* dịch ký tự sang trái*/
        shiftOut(dataPin,clockPin,MSBFIRST,*(temp+1));//column
        shiftOut(dataPin,clockPin,MSBFIRST,row[a]);//row
        digitalWrite(latchPin, 1);}
      }

    }
  }}

void scrollTextRight(String string, int speed = 100) {
  int N = string.length();
//  if (string[N-1]!= ' ') string += '  ';
  int index = 0;
  int hold;
  int step = 1;
  int a;
  char* temp;
  unsigned int buff;
  temp = (char*) &buff;
  unsigned short idxs[N];
  for(int k = 0;k < N;k++)
     {
       for(int i=0;i < sizeof(character);i++)
       {
         if(string.charAt(k) == character[i])
         {
           //bỏ "//" nếu muốn sử dụng hàm blinkImage()
           //blinkImage(characterHEX[i],1,30,30);
           idxs[index++] = i;
           break;
         }
}
}

  unsigned short int ax[8];
  for (int i = 0; i< 8; i++) {
    ax[i] = 0;
    }
    
    unsigned char cur_word[8];
  // unsigned int ax = 0;
  for (int i = 0; i < sizeof(idxs)/sizeof(unsigned short); i++) {
    
  for (int j=0; j<8; j++) {
      
       cur_word[j] = characterHEX[idxs[i]][7-j];
       }
  for (int k = 0; k<8; k++){ ax[k] =  (cur_word[k] << 8 ) + (ax[k]>> 8); }
  
  
      for(int shift = 0; shift <= 8; shift++)
  {
    // ax = 0;
    
    for(hold = 0; hold < speed; hold++)
    {

      for(a = 0; a <8; a++)
      {

        
        buff = ~(ax[a]>>shift);
        digitalWrite(latchPin, 0);
        /* dịch ký tự sang trái*/
        shiftOut(dataPin,clockPin,MSBFIRST,*(temp));//column
        shiftOut(dataPin,clockPin,MSBFIRST,row[a]);//row
        digitalWrite(latchPin, 1);}
      }

    }
  }}  

void loop() 
{
//  delay(3000);
  scrollTextLeft("LOI ", 250);
}
