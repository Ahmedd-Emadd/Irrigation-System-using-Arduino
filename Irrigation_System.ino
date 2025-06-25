#define SENSOR A0
#define RELAY_PIN 8
#define RED 7
#define GREEN 4

int moisture = 0;
int dryThreshold = 700;

void setup() {
    Serial.begin(9600);
    
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
}

void loop() {
    // Bluetooth threshold adjustment
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        int newThreshold = input.toInt();
        if (newThreshold > 0 && newThreshold <= 1023) {
            dryThreshold = newThreshold;
            Serial.println(newThreshold);
        }
    }
    
    moisture = analogRead(SENSOR);
    Serial.println(moisture);

    // Pump control logic
    if (moisture > dryThreshold) {
        digitalWrite(RELAY_PIN, LOW);  // Pump ON
        digitalWrite(GREEN, HIGH);     // Green LED ON
        digitalWrite(RED, LOW);        // Red LED OFF
        Serial.println("Pump on");
        delay(100);
        digitalWrite(RELAY_PIN, HIGH);
    } 
    else {
        digitalWrite(RELAY_PIN, HIGH); // Pump OFF
        digitalWrite(GREEN, LOW);      // Green LED OFF
        digitalWrite(RED, HIGH);       // Red LED ON
        Serial.println("Pump off");
    }
    delay(500);
}