#include "psd_regulator.h"

// sets known values to regulator structure to avoid erratic behaviour
void regulator_defaults(struct pid_data *pid_regulator) {
    pid_regulator->kp = 0;
    pid_regulator->ki = 0;
    pid_regulator->kd = 0;
    pid_regulator->max_effort = 32767;
    pid_regulator->min_effort = -32768;
    pid_regulator->difference = 0;
    pid_regulator->sum = 0;
    pid_regulator->set_value = 0;
}

// returns regulator effort (y)
// input is the feedback signal, pid_data is the data structure of the regulator instance
float regulate(float input, struct pid_data *pid_regulator) {
    // get PID constants
    float ki = pid_regulator->ki;
    float kp = pid_regulator->kp;
    float kd = pid_regulator->kd;

    // calculate error
    float error = (pid_regulator->set_value) - input;

    // calculate effort
    float output = kp * error + ki * pid_regulator->sum + kd * (error - pid_regulator->difference);

    // calculate sum and difference
    pid_regulator->sum += error;
    pid_regulator->difference = error;

    // limit effort
    if (output > pid_regulator->max_effort) {
        output = pid_regulator->max_effort;
    } else if (output < pid_regulator->min_effort) {
        output = pid_regulator->min_effort;
    }

    // return effort
    return output;
}


