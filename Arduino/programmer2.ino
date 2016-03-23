#define D0 23
#define D1 25
#define D2 27
#define D3 29
#define D4 31
#define D5 33
#define D6 35
#define D7 37

#define A0 39
#define A1 41
#define A2 43
#define A3 45
#define A4 47
#define A5 49
#define A6 51
#define A7 53

#define WE_ 52
#define CE_ 50
#define OE_ 48

int address_pins[] = {A0,A1,A2,A3,A4,A5,A6,A7};
int data_pins[] = {D0,D1,D2,D3,D4,D5,D6,D7};

/*
unsigned char ram[] = {
 0x21,0x00,0x80,0x36,0x55,0x21,0x01,0x80,0x36,0x00,0x21,0x02,
  0x80,0x36,0x55,0xFD,0x21,0x02,0x80,0xFD,0x36,0x01,0x00,0x11,
  0x64,0x00,0x6B,0x62,0x73,0x13,0x7A,0xEE,0x80,0xD6,0x81,0x38,
  0xF5,0xF5,0xC5,0x3A,0x00,0x80,0xED,0x4B,0x02,0x80,0xED,0x79,
  0xC1,0xF1,0x18,0xE3,0x0,
};*/
/*
unsigned char ram[] = {
 0x16, 0x64, 0x6a, 0x26, 0x00, 0x72, 0x14, 0x7a, 0xd6, 0xc8, 0x38, 0xf6, 0x18, 0xf2,
}; 
*/
unsigned char raxm[] = {
 0x16, 0x00, 0x14, 0x1e, 0x64, 0x6b, 0x26, 0x00,
 0x73, 0x1c, 0x7b, 0xd6, 0xc8, 0x38, 0xf6, 0x7a,
 0xd3, 0x55, 0x18, 0xee,
}; 
unsigned char ram[] = {
 0x16,0x64, 0x6a, 0x26, 0x00, 0x72, 0x7a, 0xd3, 0x55, 0x14, 0x7a, 0xd6, 0xc8, 0x38, 0xf3, 0x18, 0xef,
};

 
void setup() {
  for(int i = 22; i < 54; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  digitalWrite(CE_, LOW);
  Serial.begin(9600);
  Serial.println("SETUP");
  for(int i = 0; i < 256; i++) {
    writeByte(i, 0);
  }
  for(int i = 0; i < 17; i++) {
    writeByte(i, ram[i]);
  }
}

void setPinsMode(int mode, int pins[]) {
  for(int i = 0; i < 8; i++) {
    pinMode(pins[i], mode);
  }
}

void setPins(int a, int pins[]) {
  for(int i = 0; i < 8; i++) {
    int o = a & 1;
    digitalWrite(pins[i], o == 0 ? LOW : HIGH);
    a = a >> 1;
  }
}

int getPins(int pins[]) {
  int a = 0;
  for(int i = 0; i < 8; i++) {
    a = a >> 1;
    int o = (digitalRead(pins[i]) == HIGH ? 1 : 0);
    a = a | (o == 1 ? 128 : 0);
  }
  return a;
}

void writeByte(int address, int data) {
  digitalWrite(OE_, HIGH);
  digitalWrite(WE_, HIGH);
  setPinsMode(OUTPUT, data_pins);
  setPins(address, address_pins);
  setPins(data, data_pins);
  if(data != 0) {
    delay(100);
  }
  digitalWrite(WE_, LOW);
  digitalWrite(WE_, HIGH);
}

unsigned char readByte(int address) {
  setPinsMode(INPUT, data_pins);
  setPins(address, address_pins);
  digitalWrite(OE_, LOW);
  int pin = getPins(data_pins);
  digitalWrite(OE_, HIGH);
  return pin;
}

void loop() {
  pinMode(OE_, OUTPUT);
  //pinMode(WE_, OUTPUT);
  setPinsMode(OUTPUT, data_pins);
  setPinsMode(OUTPUT, address_pins);

  for(int i = 0; i < 16; i++) {
    //writeByte(i, ram[i]);
  }
  /*for(int i = 0; i < 32; i++) {
    writeByte(i, i);
  }*/

  for(int i = 0; i < 256; i++) {
    int o = readByte(i);
    if(i % 16 == 0) {
    Serial.print("0x");    
    if(i < 0x10) {
      Serial.print("0");
    }
    Serial.print(i, HEX);
    Serial.print(" ");
    }
    if(o < 0x10) {
      Serial.print("0");
    }
    Serial.print(o, HEX);
    Serial.print(" ");
    if(i % 16 == 7) {
     Serial.print(" ");
    }
    if(i % 16 == 15) {
      Serial.println();
    }
  }

  setPinsMode(INPUT, data_pins);
  setPinsMode(INPUT, address_pins);
  pinMode(OE_, INPUT);
  pinMode(WE_, INPUT);

while(Serial.available() < 1);
Serial.read();

}
