/*
  HG7881_Motor_Driver_Example - Arduino sketch
   
  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.
   
  This example is meant to illustrate how to operate the motor driver
  and is not intended to be elegant, efficient or useful.
   
  Connections:
   
    Arduino digital output D3 to motor driver input A-IA.
    Arduino digital output D2 to motor driver input A-IB.
    Motor driver VCC to operating voltage 5V.
    Motor driver GND to common ground.
    Motor driver MOTOR B screw terminals to a small motor.
     
  Related Banana Robotics items:
   
    BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
    https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 
  https://www.BananaRobotics.com
*/
 
// wired connections
#define HG7881_A_IA 3 // D3 --> Motor A Input A --> MOTOR A +
#define HG7881_A_IB 2 // D2 --> Motor A Input B --> MOTOR A -
#define HG7881_B_IA 5 // D5 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 4 // D4 --> Motor B Input B --> MOTOR B -
#define HG7881_C_IA 9 // D8 --> Motor C Input A --> MOTOR A +
#define HG7881_C_IB 8 // D9 --> Motor C Input B --> MOTOR A -
#define HG7881_D_IA 6 // D7 --> Motor D Input A --> MOTOR B +
#define HG7881_D_IB 7 // D6 --> Motor D Input B --> MOTOR B -

 
// functional connections
#define MOTOR_A_PWM HG7881_A_IA // Motor A PWM Speed
#define MOTOR_A_DIR HG7881_A_IB // Motor A Direction
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction
#define MOTOR_C_PWM HG7881_C_IA // Motor C PWM Speed
#define MOTOR_C_DIR HG7881_C_IB // Motor C Direction
#define MOTOR_D_PWM HG7881_D_IA // Motor D PWM Speed
#define MOTOR_D_DIR HG7881_D_IB // Motor D Direction

 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 150  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 250 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes
#define TURN_DELAY 3000

// ultrasonic wired
#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10

 
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
  pinMode( MOTOR_C_DIR, OUTPUT );
  pinMode( MOTOR_C_PWM, OUTPUT );
  digitalWrite( MOTOR_C_DIR, LOW );
  digitalWrite( MOTOR_C_PWM, LOW );
  pinMode( MOTOR_D_DIR, OUTPUT );
  pinMode( MOTOR_D_PWM, OUTPUT );
  digitalWrite( MOTOR_D_DIR, LOW );
  digitalWrite( MOTOR_D_PWM, LOW );
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

int state = 0;
 
void loop()
{
  byte c = ultrasonic();
  
  do {
    delay( DIR_DELAY );
    c = ultrasonic();
  } while (state == c);
  state = c;
  
    // execute the menu option based on the character recieved
    switch( c )
    {
      case 1: // 1) Fast forward
        Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        stopMotors();
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_A_PWM, 255-PWM_FAST ); // PWM speed = fast
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_B_PWM, 255-PWM_FAST ); // PWM speed = fast
        digitalWrite( MOTOR_C_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_C_PWM, 255-PWM_FAST ); // PWM speed = fast
        digitalWrite( MOTOR_D_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_D_PWM, 255-PWM_FAST ); // PWM speed = fast
        
        break;      
         
      case 2: // 2) Forward      
        Serial.println( "Forward..." );
        // always stop motors briefly before abrupt changes
        stopMotors();
        
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_A_PWM, 255-PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_B_PWM, 255-PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_C_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_C_PWM, 255-PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_D_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_D_PWM, 255-PWM_SLOW ); // PWM speed = slow
        
        
        break;      
         
      case 3: // 3) Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        digitalWrite( MOTOR_A_DIR, LOW );
        digitalWrite( MOTOR_A_PWM, LOW );
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        digitalWrite( MOTOR_C_DIR, LOW );
        digitalWrite( MOTOR_C_PWM, LOW );
        digitalWrite( MOTOR_D_DIR, LOW );
        digitalWrite( MOTOR_D_PWM, LOW );
        
        break;      
 
      case 4: // 4) Reverse
        Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        stopMotors();
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_C_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_C_PWM, PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_D_DIR, LOW ); // direction = reverse
        analogWrite( MOTOR_D_PWM, PWM_SLOW ); // PWM speed = slow
        
        
        break;      
         
      case 5: // 5) Fast reverse
        Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        stopMotors();
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, LOW ); // direction = reverse      
        analogWrite( MOTOR_A_PWM, PWM_FAST ); // PWM speed = fast
        digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse      
        analogWrite( MOTOR_B_PWM, PWM_FAST ); // PWM speed = fast
        digitalWrite( MOTOR_C_DIR, LOW ); // direction = reverse      
        analogWrite( MOTOR_C_PWM, PWM_FAST ); // PWM speed = fast
        digitalWrite( MOTOR_D_DIR, LOW ); // direction = reverse      
        analogWrite( MOTOR_D_PWM, PWM_FAST ); // PWM speed = fast
        
        break;
         
      case 6: // 6) Hard stop (use with caution)
        Serial.println( "Hard stop (brake)..." );
        digitalWrite( MOTOR_A_DIR, HIGH );
        digitalWrite( MOTOR_A_PWM, HIGH );
        digitalWrite( MOTOR_B_DIR, HIGH );
        digitalWrite( MOTOR_B_PWM, HIGH );
        digitalWrite( MOTOR_C_DIR, HIGH );
        digitalWrite( MOTOR_C_PWM, HIGH );
        digitalWrite( MOTOR_D_DIR, HIGH );
        digitalWrite( MOTOR_D_PWM, HIGH );
        
        break;
        
      case 7: // 7) Turn left      
        Serial.println( "Turn left ..." );
        // always stop motors briefly before abrupt changes
        stopMotors();
        
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_A_PWM, 255-PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_B_DIR, LOW ); // direction = forward
        analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_C_DIR, LOW ); // direction = forward
        analogWrite( MOTOR_C_PWM, PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_D_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_D_PWM, 255-PWM_SLOW ); // PWM speed = slow
        
        delay( TURN_DELAY ); 
        
        stopMotors();
        
        break;
     
     case 8: // 7) Turn right      
        Serial.println( "Turn rigt ..." );
        // always stop motors briefly before abrupt changes
        stopMotors();
        
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, LOW ); // direction = forward
        analogWrite( MOTOR_A_PWM, PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_B_PWM, 255-PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_C_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_C_PWM, 255-PWM_SLOW ); // PWM speed = slow
        digitalWrite( MOTOR_D_DIR, LOW ); // direction = forward
        analogWrite( MOTOR_D_PWM, PWM_SLOW ); // PWM speed = slow
        
        delay( TURN_DELAY ); 
        
        stopMotors();        
        
        break;
        
      default:
        Serial.print("invalid");
        break;
    }
  
 
  // repeat the main loop and redraw the menu...
}

void stopMotors() {
    // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_A_DIR, LOW );
        digitalWrite( MOTOR_A_PWM, LOW );
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        digitalWrite( MOTOR_C_DIR, LOW );
        digitalWrite( MOTOR_C_PWM, LOW );
        digitalWrite( MOTOR_D_DIR, LOW );
        digitalWrite( MOTOR_D_PWM, LOW );
        
}

byte ultrasonic() {
  //delay(500);
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  if (distance < 15 && distance > 0) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
    return (byte)7;
  }
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
    return (byte)1;
  }
  /*if (distance >= 200 || distance <= 0){
   Serial.println("Out of range");
   }
   else {
   Serial.print(distance);
   Serial.println(" cm");
   }*/
 
}
/*EOF*/
