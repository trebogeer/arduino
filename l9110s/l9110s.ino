/*
 */

// wired connections
#define HG7881_A_IA 3 // D3 --> Motor A Input A --> MOTOR A +
#define HG7881_A_IB 2 // D2 --> Motor A Input B --> MOTOR A -
#define HG7881_B_IA 5 // D5 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 4 // D4 --> Motor B Input B --> MOTOR B -


// functional connections
#define MOTOR_A_PWM HG7881_A_IA // Motor A PWM Speed
#define MOTOR_A_DIR HG7881_A_IB // Motor A Direction
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction


// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 150  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 250 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes
#define TURN_DELAY 3000

#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PING_DELAY 50
#define LED0 11
#define LED1 10
 

void setup()
{
  Serial.begin( 9600 );
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

int state = 0;

void loop()
{
  byte c = ultrasonicPing();

  do {
    delay( DIR_DELAY );
    c = ultrasonicPing();
  } 
  while (state == c);
  state = c;

  // execute command based upon ultrasonic ping result
  switch( c )
  {
  case 1: // Fast forward
    Serial.println( "Fast forward..." );
    // always stop motors briefly before abrupt changes
    stopMotors();
    delay( DIR_DELAY );
    // set the motor speed and direction
    digitalWrite( MOTOR_A_DIR, HIGH ); // direction = forward
    analogWrite( MOTOR_A_PWM, 255-PWM_FAST ); // PWM speed = fast
    digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
    analogWrite( MOTOR_B_PWM, 255-PWM_FAST ); // PWM speed = fast
    break;      

  case 2: // Forward      
    Serial.println( "Forward..." );
    // always stop motors briefly before abrupt changes
    stopMotors();

    delay( DIR_DELAY );
    // set the motor speed and direction
    digitalWrite( MOTOR_A_DIR, HIGH ); // direction = forward
    analogWrite( MOTOR_A_PWM, 255-PWM_SLOW ); // PWM speed = slow
    digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
    analogWrite( MOTOR_B_PWM, 255-PWM_SLOW ); // PWM speed = slow
    
    break;      

  case 3: // Soft stop (preferred)
    Serial.println( "Soft stop (coast)..." );
    digitalWrite( MOTOR_A_DIR, LOW );
    digitalWrite( MOTOR_A_PWM, LOW );
    digitalWrite( MOTOR_B_DIR, LOW );
    digitalWrite( MOTOR_B_PWM, LOW );
    
    break;      

  case 4: // Reverse
    Serial.println( "Reverse..." );
    // always stop motors briefly before abrupt changes
    stopMotors();
    delay( DIR_DELAY );
    // set the motor speed and direction
    digitalWrite( MOTOR_A_DIR, LOW ); // direction = reverse
    analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow
    digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
    analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow

    break;      

  case 5: // Fast reverse
    Serial.println( "Fast forward..." );
    // always stop motors briefly before abrupt changes
    stopMotors();
    delay( DIR_DELAY );
    // set the motor speed and direction
    digitalWrite( MOTOR_A_DIR, LOW ); // direction = reverse      
    analogWrite( MOTOR_A_PWM, PWM_FAST ); // PWM speed = fast
    digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse      
    analogWrite( MOTOR_B_PWM, PWM_FAST ); // PWM speed = fast
    break;

  case 6: // Hard stop (use with caution)
    Serial.println( "Hard stop (brake)..." );
    digitalWrite( MOTOR_A_DIR, HIGH );
    digitalWrite( MOTOR_A_PWM, HIGH );
    digitalWrite( MOTOR_B_DIR, HIGH );
    digitalWrite( MOTOR_B_PWM, HIGH );
    break;

  case 7: // Turn left      
    Serial.println( "Turn left ..." );
    // always stop motors briefly before abrupt changes
    stopMotors();

    delay( DIR_DELAY );
    // set the motor speed and direction
    digitalWrite( MOTOR_A_DIR, HIGH ); // direction = forward
    analogWrite( MOTOR_A_PWM, 255-PWM_SLOW ); // PWM speed = slow
    digitalWrite( MOTOR_B_DIR, LOW ); // direction = forward
    analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
    break;

  case 8: // Turn right      
    Serial.println( "Turn rigt ..." );
    // always stop motors briefly before abrupt changes
    stopMotors();

    delay( DIR_DELAY );
    // set the motor speed and direction
    digitalWrite( MOTOR_A_DIR, LOW ); // direction = forward
    analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow
    digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
    analogWrite( MOTOR_B_PWM, 255-PWM_SLOW ); // PWM speed = slow
    break;

  default:
    Serial.print("invalid");
    break;
  }
}

void stopMotors() {
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
}


int ultrasonicPing() {
  int duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 15 && distance > 0) { 
    digitalWrite(LED0,HIGH);
    digitalWrite(LED1,LOW);
    return 7;
  }
  else {
    digitalWrite(LED0,LOW);
    digitalWrite(LED1,HIGH);
    return 1;
  }
}

/*EOF*/

