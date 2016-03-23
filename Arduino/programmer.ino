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
#define OE_ 48

int address_pins[] = {A0,A1,A2,A3,A4,A5,A6,A7};
int data_pins[] = {D0,D1,D2,D3,D4,D5,D6,D7};

char ram[] = {0x11, 0x64, 0x00, 0x6b, 0x62, 0x73, 0x13, 0x7a, 0xee, 0x80, 0xd6, 0x81, 0x38, 0xf5, 0x18, 0xf0};

void setup() {
  for(int i = 22; i < 54; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.begin(9600);
  Serial.println("SETUP");
  for(int i = 0; i < 256; i++) {
    writeByte(i, 0);
  }
  for(int i = 0; i < 16; i++) {
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
    Serial.print("At 0x");
    Serial.print(i, HEX);
    Serial.print(" the value is ");
    Serial.println(o, DEC);
  }

  setPinsMode(INPUT, data_pins);
  setPinsMode(INPUT, address_pins);
  pinMode(OE_, INPUT);
  pinMode(WE_, INPUT);

while(Serial.available() < 1);
Serial.read();

}
