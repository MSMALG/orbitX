int SignalLed = 8;    // LED pin
int Trig = 12;        // Ultrasonic sensor trigger pin
int Echo = 11;        // Ultrasonic sensor echo pin

long pinTravelTime;    // Time for pulse to travel
float distance;        // Distance measured by the sensor
const float threshold = 30.0;  // Distance threshold set to exactly 30 cm
const int numReadings = 5;     // Number of readings to average

// Function to calculate distance from the ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  long travelTime;
  float totalDistance = 0;

  // Take multiple readings and average them
  for (int i = 0; i < numReadings; i++) {
    // Send a pulse to the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);   
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);  
    digitalWrite(trigPin, LOW);

    // Measure the time for the pulse to return
    travelTime = pulseIn(echoPin, HIGH);

    // Calculate the distance in centimeters
    totalDistance += travelTime * 0.034 / 2;

    delay(10);  
  }

  // Return the average distance
  return totalDistance / numReadings;
}

void setup() {
  pinMode(SignalLed, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  Serial.begin(9600);
}

void loop() {
  distance = getDistance(Trig, Echo);

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the sensor detects an obstacle at 30 cm or less
  if (distance <= threshold) {
    digitalWrite(SignalLed, HIGH);  // Turn on LED if obstacle is 30 cm or closer
  } else {
    digitalWrite(SignalLed, LOW);   // Turn off LED if the obstacle is farther than 30 cm
  }

  delay(500);  
}
