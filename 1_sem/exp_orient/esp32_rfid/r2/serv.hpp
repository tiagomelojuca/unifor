// ----------------------------------------------------------------------------------------------------------
// SERV
// ----------------------------------------------------------------------------------------------------------

#include <Servo.h>

#define DELAY_IN_MS   2000
#define SERVO_PIN       13
#define ANGLE_LOCKED     0
#define ANGLE_UNLOCKED 180

// ----------------------------------------------------------------------------------------------------------

inline void serv_setup(Servo* instance)
{
    instance->attach(SERVO_PIN);
}

// ----------------------------------------------------------------------------------------------------------

inline void serv_lock(Servo* instance)
{
    instance->write(ANGLE_LOCKED);
}

// ----------------------------------------------------------------------------------------------------------

inline void serv_unlock(Servo* instance)
{
    instance->write(ANGLE_UNLOCKED);
}

// ----------------------------------------------------------------------------------------------------------

inline void serv_unlock_and_relock(Servo* instance)
{
    serv_unlock(instance);
    delay(DELAY_IN_MS);
    serv_lock(instance);
}

// ----------------------------------------------------------------------------------------------------------
