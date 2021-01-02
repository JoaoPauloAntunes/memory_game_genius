const int LED_R = 11;
const int LED_G = 10;
const int LED_B = 9;
const int LED_Y = 8;

const int BTN_R = 7;
const int BTN_G = 6;
const int BTN_B = 5;
const int BTN_Y = 4;

const int PIN_DISCONNECTED = 0;

const unsigned long DEBAUNCE_TIME = 25;
const unsigned long LED_OFF_TIME = 50;
const unsigned long BLINK_TIME = 100;
const unsigned long CONTEXT_CHANGE_TIME = 1000;

int level = 1;
String sequence = "";

int sequenceSize = 0;
int i = 0;

bool isNotPressedBtnR = false;
bool isNotPressedBtnG = false;
bool isNotPressedBtnB = false;
bool isNotPressedBtnY = false;

bool hasNotPressedBtnR = true; 
bool hasNotPressedBtnG = true;
bool hasNotPressedBtnB = true;
bool hasNotPressedBtnY = true;

void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_Y, OUTPUT);

  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_G, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_Y, INPUT_PULLUP);

  Serial.begin(9600);

  /* if an analog input pin is unconnected,
  its noise can cause the call to randomSeed() to generate
  different seed numbers each time the sketch runs.
  randomSeed() will then shuffle the random function. */
  randomSeed(analogRead(PIN_DISCONNECTED));
}

void loop()
{
  if (level == 1) {                           // se o nível for inicial
    delay(CONTEXT_CHANGE_TIME);
    Serial.println("Press any button to start the game");
    while(digitalRead(BTN_R) && digitalRead(BTN_G) && 
      digitalRead(BTN_B) && digitalRead(BTN_Y));
    delay(DEBAUNCE_TIME);

    Serial.println("New game started!");
    initPlayerStatus();
  }

  delay(CONTEXT_CHANGE_TIME);
  Serial.println("----------------");
  Serial.print("level: ");
  Serial.println(level);
  
  showSequence();
    
  i = 0;
  sequenceSize = sequence.length();
  while(i < sequenceSize) {                     // aguardar usuário pressionar botões até errar ou acertar a sequência

    isNotPressedBtnR = digitalRead(BTN_R);
    if (isNotPressedBtnR) {                     // se o botão não está pressionado
      hasNotPressedBtnR = true;                 // tenho que o botão não foi pressionado
    } else if (hasNotPressedBtnR) {             // se o botão está pressionado E tenho que ele não foi pressionado
      hasNotPressedBtnR = false;                // agora tenho que o botão foi pressionado
      
      blinkLed(LED_R, BLINK_TIME);
      delay(DEBAUNCE_TIME);

      if ('R' != sequence.charAt(i)) {          // se caractere referente ao botão não coincidir com a sequência
        break;                                  // quebrar iteração
      }

      i++;                                      // incrementar índice de varredura da sequência
    }

    isNotPressedBtnG = digitalRead(BTN_G);
    if (isNotPressedBtnG) {                     // se o botão não está pressionado
      hasNotPressedBtnG = true;                 // tenho que o botão não foi pressionado
    } else if (hasNotPressedBtnG) {             // se o botão está pressionado E tenho que ele não foi pressionado
      hasNotPressedBtnG = false;                // agora tenho que o botão foi pressionado
      
      blinkLed(LED_G, BLINK_TIME);
      delay(DEBAUNCE_TIME);

      if ('G' != sequence.charAt(i)) {          // se caractere referente ao botão não coincidir com a sequência
        break;                                  // quebrar iteração
      }

      i++;
    }

    isNotPressedBtnB = digitalRead(BTN_B);
    if (isNotPressedBtnB) {                     // se o botão não está pressionado
      hasNotPressedBtnB = true;                 // tenho que o botão não foi pressionado
    } else if (hasNotPressedBtnB) {             // se o botão está pressionado E tenho que ele não foi pressionado
      hasNotPressedBtnB = false;                // agora tenho que o botão foi pressionado
      
      blinkLed(LED_B, BLINK_TIME);
      delay(DEBAUNCE_TIME);

      if ('B' != sequence.charAt(i)) {          // se caractere referente ao botão não coincidir com a sequência
        break;                                  // quebrar iteração
      }

      i++;
    }

    isNotPressedBtnY = digitalRead(BTN_Y);
    if (isNotPressedBtnY) {                     // se o botão não está pressionado
      hasNotPressedBtnY = true;                 // tenho que o botão não foi pressionado
    } else if (hasNotPressedBtnY) {             // se o botão está pressionado E tenho que ele não foi pressionado
      hasNotPressedBtnY = false;                // agora tenho que o botão foi pressionado
      
      blinkLed(LED_Y, BLINK_TIME);
      delay(DEBAUNCE_TIME);

      if ('Y' != sequence.charAt(i)) {          // se caractere referente ao botão não coincidir com a sequência
        break;                                  // quebrar iteração
      }

      i++;
    }
  }
  if (i == sequenceSize) {                    // se a partida foi vencida
    levelUp();                                // subir nível
  } else {
    Serial.println("Game Over!");
    level = 1;                                // reiniciar nível
  }
}

void initPlayerStatus()
{
  Serial.print("Initializing player status");
  delay(BLINK_TIME);
  Serial.print(".");
  delay(BLINK_TIME);
  Serial.print(".");
  delay(BLINK_TIME);
  Serial.println(".");

  hasNotPressedBtnR = hasNotPressedBtnG = hasNotPressedBtnB = hasNotPressedBtnY = true;
  sequence = "";
  incSequence();
}

void levelUp()
{
  level++;
  incSequence();
}

char randomBtnCh()
{
  char randomBtnCh;

  switch (random(4)) {
    case 0:
      randomBtnCh = 'R';
      break;
    case 1:
      randomBtnCh = 'G';
      break;
    case 2:
      randomBtnCh = 'B';
      break;
    case 3:
      randomBtnCh = 'Y';
      break;
    default:
      randomBtnCh = '?';
      break;
  }

  return randomBtnCh;
}

void incSequence() 
{
  sequence += randomBtnCh();
}

void showSequence()
{
  unsigned long duration = (unsigned long) 4000 / sqrt(level);

  for (int i = 0; i < level; i++) {
    switch (sequence[i]) {
      case 'R':
        blinkLed(LED_R, duration);
        break;
      case 'G':
        blinkLed(LED_G, duration);
        break;
      case 'B':
        blinkLed(LED_B, duration);
        break;
      case 'Y':
        blinkLed(LED_Y, duration);
        break;
    }

    delay(BLINK_TIME);
  }
}

void blinkLed(int ledPin, unsigned long duration)
{
  if (2* duration < LED_OFF_TIME) {
    duration = LED_OFF_TIME;
  }

  digitalWrite(ledPin, HIGH);
  delay(duration - LED_OFF_TIME);
  digitalWrite(ledPin, LOW);
  delay(LED_OFF_TIME);
}
