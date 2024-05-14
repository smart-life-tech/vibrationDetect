const int sensorPin = 4;
const int ledPin = 2;    // Define the pin for the LED
const int buzzerPin = 3; // Define the pin for the buzzer

void setup()
{
    Serial.begin(9600);         // Start serial communication at 9600 baud rate
    pinMode(sensorPin, INPUT);  // Set the sensorPin as an input pin
    pinMode(ledPin, OUTPUT);    // Set the ledPin as an output pin
    pinMode(buzzerPin, OUTPUT); // Set the buzzerPin as an output pin
}

void loop()
{
    if (digitalRead(sensorPin)) // Check if there is any vibration detected by the sensor
    {
        Serial.println("Detected vibration..."); // Print "Detected vibration..." if vibration detected
        digitalWrite(ledPin, HIGH);              // Turn on the LED
        tone(buzzerPin, 1000);                   // Play a 1kHz tone on the buzzer
    }
    else
    {
        Serial.println("...");     // Print "..." otherwise
        digitalWrite(ledPin, LOW); // Turn off the LED
        noTone(buzzerPin);         // Stop playing any tone on the buzzer
    }

    // Add a delay to avoid flooding the serial monitor
    delay(100);
}