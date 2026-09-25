const int buzzer_pin = 18;
const int button_pin = 5;

volatile bool button_pressed = false;
volatile bool waiting_finished = false;
volatile unsigned long end_time = 0;

unsigned long start_time = 0;
bool reaction_active = false;
bool waiting = false;
hw_timer_t *timer = NULL;

void IRAM_ATTR timer_interrupt() {
  waiting_finished = true;
}

void IRAM_ATTR button_interrupt() {
  if (reaction_active) {
    end_time = micros();
    button_pressed = true;
  }
}

void start_round() {
  button_pressed = false;
  start_time = micros();
  reaction_active = true;
  digitalWrite(buzzer_pin, HIGH);
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(button_pin), button_interrupt, FALLING);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &timer_interrupt);
  randomSeed(esp_random());

  start_round();
}

void loop() {
  if (button_pressed && reaction_active) {
    reaction_active = false;
    button_pressed = false;
    digitalWrite(buzzer_pin, LOW);

    unsigned long reaction_time = end_time - start_time;
    Serial.print("Reaction time: ");
    Serial.print(reaction_time / 1000.0);
    Serial.println(" ms");

    unsigned long wait_time = random(5000, 8001);
    waiting_finished = false;
    waiting = true;
    timerWrite(timer, 0);
    timerAlarm(timer, wait_time * 1000ULL, false, 0);
  }

  if (waiting_finished && waiting) {
    waiting_finished = false;
    waiting = false;
    start_round();
  }
}
