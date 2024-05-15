const int sensorPin = 2;
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

    // Indicate vibration with LED and buzzer if frequency is detected
    if (vibrationCount > 0)
    { // Calculate the frequency in Hz
        float frequency = vibrationCount / 1.0;

        // Print the frequency to the Serial Monitor
        Serial.print("Frequency: ");
        Serial.print(frequency);
        Serial.println(" Hz");

        Serial.println("Detected vibration...");
        vibrationCount=0;
    }

    // Add a delay to avoid flooding the serial monitor
    delay(10);
}
