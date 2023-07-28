#include <Keypad.h>
#include <Servo.h>
#include <string.h>

const byte rows = 4;
const byte columns = 3;

char keys[rows][columns] = {
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'},
};

byte pinRows[] = {8, 7, 6, 5};
byte pinColumns[] = {A2, A1, A0};

Keypad keyboard = Keypad(makeKeymap(keys), pinRows, pinColumns, rows, columns);

char key;

byte B = 4;
byte G = 3;
byte R = 2;

char password[8];
char correctPassword[] = "748567#";
byte index = 0;

Servo miServo;

byte pinPiezo = 10;

void setup() {

	Serial.begin(9600);
	
	pinMode(R, OUTPUT);
	pinMode(G, OUTPUT);
	pinMode(B, OUTPUT);

	miServo.attach(9);
	miServo.write(0);

	pinMode(pinPiezo, OUTPUT);
}

void loop() {


	key = keyboard.getKey();

	if (key && index <= 6){
		password[index] = key;
		index++;
		Serial.println(password);
	}
	else if (index > 6) {
		index = 6;
	}

	if (key == '#'){
		if (strcmp(password, correctPassword) == 0){
			digitalWrite(R, LOW);
			digitalWrite(G, HIGH);
			digitalWrite(B, LOW);
			Serial.println("Correct Password");
			miServo.write(180);
			index = 0;
		}
		else {
			digitalWrite(R, HIGH);
			digitalWrite(G, LOW);
			digitalWrite(B, LOW);
			Serial.println("Wrong Password");
			miServo.write(0);
			index = 0;
			digitalWrite(pinPiezo, HIGH);
		}
		
		delay(2000);
		digitalWrite(R, LOW);
		digitalWrite(G, LOW);
		digitalWrite(B, LOW);
		digitalWrite(pinPiezo, LOW);
	}
}
