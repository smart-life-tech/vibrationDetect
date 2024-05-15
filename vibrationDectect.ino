const int sensorPin = 2;

void setup()
{
    Serial.begin(9600);        // Start serial communication at 9600 baud rate
    pinMode(sensorPin, INPUT); // Set the sensorPin as an input pin
}

void loop()
{
    if (digitalRead(sensorPin)) // Check if there is any vibration detected by the sensor
    {
        Serial.println("Detected vibration..."); // Print "Detected vibration..." if vibration detected
    }

    // Add a delay to avoid flooding the serial monitor
    delay(100);
}