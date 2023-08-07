#define RX_ENABLED 0
#define SERVO_ENABLED 1
#define MOTION_SENSOR_ENABLED 1
#define LIGHT_SENSOR_ENABLED 0

#define DEBUG_LED_ENABLED 1
#define DEBUG_SERIAL_ENABLED 1

#if MOTION_SENSOR_ENABLED && RX_ENABLED
    #error "RX Trigger and Motion Trigger are Mutually Exclusive"
#endif

void setup() {
#if DEBUG_SERIAL_ENABLED
    Serial.begin(9600);
#endif

#if DEBUG_LED_ENABLED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
#endif


#if RX_ENABLED
    setupRx();
#endif

#if MOTION_SENSOR_ENABLED
    setupMotionSensor();
#endif

#if SERVO_ENABLED
    setupServo();
#endif

#if LIGHT_SENSOR_ENABLED
    setupLightSensor();
#endif

#if DEBUG_SERIAL_ENABLED
    Serial.println("Setup Complete");
    Serial.flush();
#endif
}

#if LIGHT_SENSOR_ENABLED
static void (* lightPresser)(bool) = lightSensitiveSwitch;
#else
static void (* lightPresser)(bool) = servoPress;
#endif

void loop() {
    // testServo();
#if MOTION_SENSOR_ENABLED
    motionOnOff(lightPresser);
#endif

#if RX_ENABLED
    runOnCodeMatch(lightPresser);
#endif
}

