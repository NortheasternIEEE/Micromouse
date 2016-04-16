#define PIN_CLK 5
#define PIN_MISO 6

volatile uint32_t ticks = 0;

void encoderISR(void);
void dataISR(void);

void encoderISR() {
  ticks++;
}

volatile uint8_t bits = 0;

void dataISR() {
  digitalWrite(PIN_MISO, ((ticks & (1 << bits)) ? HIGH : LOW));
  bits = (bits+1) % 32;
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), encoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(3), dataISR, RISING);
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_MISO, OUTPUT);
  sei();
}

void loop() {
  
}
