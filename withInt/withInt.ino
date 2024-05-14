const int sensorPin = 4;
const int ledPin = 2;            // Define the pin for the LED
const int buzzerPin = 3;         // Define the pin for the buzzer
volatile int vibrationCount = 0; // Variable to count vibrations

// Interrupt service routine for counting vibrations
void count()
{
    vibrationCount++;
}

void setup()
{
    Serial.begin(9600);                                                // Start serial communication at 9600 baud rate
    pinMode(sensorPin, INPUT);                                         // Set the sensorPin as an input pin
    pinMode(ledPin, OUTPUT);                                           // Set the ledPin as an output pin
    pinMode(buzzerPin, OUTPUT);                                        // Set the buzzerPin as an output pin
    attachInterrupt(digitalPinToInterrupt(sensorPin), count, FALLING); // Attach interrupt to sensorPin
}

void loop()
{
    // Clear the vibration count
    vibrationCount = 0;

    // Measure vibrations for 1 second
    unsigned long startTime = millis();
    while (millis() - startTime < 1000)
    {
        // Do nothing, just wait for 1 second while the ISR counts vibrations
    }

    // Calculate the frequency in Hz
    float frequency = vibrationCount / 1.0;

    // Print the frequency to the Serial Monitor
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Indicate vibration with LED and buzzer if frequency is detected
    if (vibrationCount > 0)
    {
        Serial.println("Detected vibration...");
        digitalWrite(ledPin, HIGH); // Turn on the LED
        tone(buzzerPin, 1000);      // Play a 1kHz tone on the buzzer
    }
    else
    {
        Serial.println("...");
        digitalWrite(ledPin, LOW); // Turn off the LED
        noTone(buzzerPin);         // Stop playing any tone on the buzzer
    }

    // Add a delay to avoid flooding the serial monitor
    delay(1000);
}
