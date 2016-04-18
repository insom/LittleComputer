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

#undef DEBUG_BUILD

int address_pins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
int data_pins[] = {D0, D1, D2, D3, D4, D5, D6, D7};

unsigned char ram[] = {
  0x16, 0x64, 0x6a, 0x26,
  0x00, 0x72, 0x7a, 0xd3,
  0x55, 0x14, 0x7a, 0xd6,
  0xc8, 0x38, 0xf3, 0x18,
  0xef,
};

#define RAM_LENGTH sizeof(ram)

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

unsigned char getPins(int pins[]) {
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
#ifdef DEBUG_BUILD
  if(data != 0) {
    delay(100);
  }
#endif
  digitalWrite(WE_, LOW);
  digitalWrite(WE_, HIGH);
}

unsigned char readByte(int address) {
  setPinsMode(INPUT, data_pins);
  setPins(address, address_pins);
  digitalWrite(OE_, LOW);
  unsigned char pin = getPins(data_pins);
  digitalWrite(OE_, HIGH);
  return pin;
}

void assertBus() {
  pinMode(CE_, OUTPUT);
  pinMode(OE_, OUTPUT);
  digitalWrite(CE_, LOW);
  setPinsMode(OUTPUT, data_pins);
  setPinsMode(OUTPUT, address_pins);
}

void disownBus() {
  setPinsMode(INPUT, data_pins);
  setPinsMode(INPUT, address_pins);
  pinMode(OE_, INPUT_PULLUP);
  pinMode(WE_, INPUT_PULLUP);
  pinMode(CE_, INPUT_PULLUP);
}

void dumpRam() {
  assertBus();

  Serial.println();

  for(int i = 0; i < 256; i++) {
    int o = readByte(i);
    if(i % 16 == 0) {
      Serial.print("0x");    
      if(i < 0x10) { Serial.print("0"); }
      Serial.print(i, HEX);
      Serial.print(" ");
    }
    if(o < 0x10) { Serial.print("0"); }
    Serial.print(o, HEX);
    Serial.print(" ");
    if(i % 16 == 7) { Serial.print(" "); }
    if(i % 16 == 15) { Serial.println(); }
  }

  disownBus();
}

void zeroRam() {
  assertBus();

  pinMode(WE_, OUTPUT);
  for(int i = 0; i < 256; i++) {
    writeByte(i, 0);
  }

  disownBus();
}

void loadRam() {
  assertBus();

  pinMode(WE_, OUTPUT);
  for(int i = 0; i < RAM_LENGTH; i++) {
    writeByte(i, ram[i]);
  }

  disownBus();
}

void pokeRam() {
  int address, data;
  assertBus();

  pinMode(WE_, OUTPUT);

  address = Serial.parseInt();
  data = Serial.parseInt();
  writeByte(address, data);

  disownBus();
}


void setup() {
  /* Set every port to OUTPUT and bring them HIGH. WE, CE and OE are active
   * low, so this ensure we don't mess with control lines while getting set up.
   * */
  for(int i = 22; i < 54; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  /* Enable the RAM and start the serial port up. */
  Serial.begin(9600);
  Serial.println("SETUP");

  /* Zero out the RAM, it could be in any state. */
  zeroRam();

  loadRam();
}

void loop() {
  int input;

  disownBus();
  while(Serial.available() < 1); // Spin
  input = Serial.read();
  switch(input) {
    case 'd':
      dumpRam();
      break;
    case 'z':
      zeroRam();
      break;
    case 'l':
      loadRam();
      break;
    case 'o':
      pokeRam();
      break;
  }
}
