#ifndef PSD_REGULATOR_H
#define PSD_REGULATOR_H

// structure for storing regulator data
struct pid_data {
    // weights
    float ki;
    float kd;
    float kp;
    
    // desired value
    float set_value;

    // regulator output limits
    float max_effort;
    float min_effort;

    // calculation data: do not modify
    float sum;
    float difference;
};

// Function prototypes
void regulator_defaults(struct pid_data *pid_regulator);
float regulate(float input, struct pid_data *pid_regulator);
float example_system(float in);

#endif // PSD_REGULATOR_H
