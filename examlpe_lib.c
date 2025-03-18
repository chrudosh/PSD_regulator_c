#include <stdio.h>
#include "psd_regulator.h"

int main() {
    // create regulator instance
    struct pid_data regulator1;

    // initialise values
    regulator_defaults(&regulator1);

    // set weights
    regulator1.kp = 1;
    regulator1.ki = 0;
    regulator1.kd = 0;

    // set set value
    regulator1.set_value = 1;

    // variable to store feedback
    float out = 0;

    // 400 regulating cycles
    for (int i = 0; i < 400; i++) {
        printf("%.6f\n", out);
        // calculate system and regulator
        out = example_system(regulate(out, &regulator1));
    }

    return 0;
}
