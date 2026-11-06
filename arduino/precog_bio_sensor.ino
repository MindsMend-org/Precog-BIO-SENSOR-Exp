// M26 stream: raw GSR + pulse-sensor signal for training
// Line format: gsr_raw,hr_raw,hr_bit,t_us

const int gsrPin = A0;
const int hrPin = A1;
const int heartRateThreshold = 200;
const unsigned long sampleIntervalMicros = 4000; // 250 Hz target

bool collecting = false;
bool showedStop = true;
unsigned long lastSampleTime = 0;
unsigned long t0 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(gsrPin, INPUT);
  pinMode(hrPin, INPUT);
  delay(1500);
  t0 = micros();
  Serial.println("READY");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "START") {
      collecting = true;
      showedStop = false;
      lastSampleTime = micros();
      t0 = lastSampleTime;
    } else if (command == "STOP") {
      collecting = false;
    } else if (command == "RESET") {
      collecting = false;
      showedStop = true;
      Serial.println("READY");
    }
  }

  unsigned long now = micros();
  if (collecting && (now - lastSampleTime) >= sampleIntervalMicros) {
    lastSampleTime += sampleIntervalMicros;

    int gsr = analogRead(gsrPin);
    int hr = analogRead(hrPin);
    int hrBit = hr > heartRateThreshold ? 1 : 0;
    unsigned long tUs = now - t0;

    Serial.print(gsr);
    Serial.print(',');
    Serial.print(hr);
    Serial.print(',');
    Serial.print(hrBit);
    Serial.print(',');
    Serial.println(tUs);
  } else if (!collecting && !showedStop) {
    Serial.println("STOPPING");
    showedStop = true;
  }
}