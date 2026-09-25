const int enable_pin = 4;
const int input1_pin = 25;
const int input2_pin = 27;
const int button_pin = 5;

hw_timer_t *timer = NULL;
volatile bool timer_finished = false;
volatile bool button_pressed = false;

int duty = 70;
bool forward = true;

void IRAM_ATTR timer_interrupt() {
  timer_finished = true;
}

void IRAM_ATTR button_interrupt() {
  button_pressed = true;
}

void apply_direction() {
  digitalWrite(input1_pin, forward ? HIGH : LOW);
  digitalWrite(input2_pin, forward ? LOW : HIGH);
}

void setup() {
  Serial.begin(115200);

  pinMode(enable_pin, OUTPUT);
  pinMode(input1_pin, OUTPUT);
  pinMode(input2_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);

  ledcAttach(enable_pin, 1000, 8);
  ledcWrite(enable_pin, duty);
  apply_direction();

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &timer_interrupt);
  timerAlarm(timer, 300000, true, 0);

  attachInterrupt(digitalPinToInterrupt(button_pin), button_interrupt, FALLING);
}

void loop() {
  if (timer_finished) {
    timer_finished = false;
    duty += 10;
    if (duty > 255) {
      duty = 70;
    }
    ledcWrite(enable_pin, duty);
  }

  if (button_pressed) {
    button_pressed = false;
    forward = !forward;
    apply_direction();
    Serial.println("Motor direction changed");
    delay(30);
  }
}
