#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int ledPin = 2;    // Define the pin for the LED
const int buzzerPin = 3; // Define the pin for the buzzer

volatile int vibrationCount = 0; // Variable to count vibrations
const float threshold = 1.0;     // Threshold for detecting significant vibration (adjust as necessary)

void setup()
{
    Serial.begin(9600);         // Start serial communication at 9600 baud rate
    pinMode(ledPin, OUTPUT);    // Set the ledPin as an output pin
    pinMode(buzzerPin, OUTPUT); // Set the buzzerPin as an output pin

    Wire.begin();
    mpu.initialize();

    if (mpu.testConnection())
    {
        Serial.println("MPU6050 connection successful");
    }
    else
    {
        Serial.println("MPU6050 connection failed");
        while (1)
            ;
    }
}

void loop()
{
    vibrationCount = 0;
    unsigned long startTime = millis();

    while (millis() - startTime < 1000)
    {
        // Read accelerometer data
        int16_t ax, ay, az;
        mpu.getAcceleration(&ax, &ay, &az);

        // Calculate the magnitude of acceleration
        float magnitude = sqrt(ax * ax + ay * ay + az * az) / 1.63840; // 16384 is the LSB sensitivity for +/- 2g
        //Serial.print("magnitude :");
        //Serial.println(magnitude);
        // Check if the magnitude exceeds the threshold
        if (magnitude > threshold)
        {
            vibrationCount++;
        }

        delay(10); // Adjust delay as needed to control sampling rate
    }

    // Indicate vibration with LED and buzzer if frequency is detected
    if (vibrationCount > 0)
    {
        Serial.println("Detected vibration...");
        // Calculate frequency in Hz and per minute
        float frequencyHz = vibrationCount / 1.0;         // Counts per second
        float frequencyPerMinute = vibrationCount * 60.0; // Counts per minute

        // Print the frequency to the Serial Monitor
        Serial.print("Frequency: ");
        Serial.print(frequencyHz);
        Serial.print(" Hz, ");
        Serial.print(frequencyPerMinute);
        Serial.println(" counts per minute");
        vibrationCount=0;
    }

    // Add a delay to avoid flooding the serial monitor
    delay(1000);
}
