#define PIN_CLK 5
#define PIN_MISO 6

volatile uint32_t ticks = 0;

void encoderISR(void);

void encoderISR() {
  ticks++;
  digitalWrite(8, HIGH);
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), encoderISR, RISING);
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_MISO, OUTPUT);
}

volatile uint8_t previousPIN_CLKState = 0;
volatile uint8_t bits = 0;

void loop() {
  if(digitalRead(PIN_CLK) && previousPIN_CLKState == LOW) {
    digitalWrite(PIN_MISO, ((0x10 & (1 << bits)) ? HIGH : LOW));
    bits = (bits+1) % 32;
  }
  previousPIN_CLKState = digitalRead(PIN_CLK);
  delayMicroseconds(1);
}
