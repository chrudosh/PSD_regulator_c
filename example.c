/******************************************************************************
Simple PSD regolator example

pid_data structure serves as regulator instance and stores its data

float regulate(float input, struct pid_data *pid_regulator);

float input -> feedback from system
pid_data -> regulator instance

always initialise regulator instance with void regulator_defaults(); to avoid
random defaultvalues 

*******************************************************************************/
#include <stdio.h>


// structure for storing regulator data
struct pid_data {
    // weights
	float ki;
	float kd;
	float kp;
	
	//desired value
    float set_value;

    // regulator output limits
	float max_effort;
	float min_effort;

    // calculation data: do not modify
	float sum;
	float difference;
};

float regulate(float input, struct pid_data *pid_regulator);
void regulator_defaults(struct pid_data *pid_regulator);
float example_system(float in);


int main()
{
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
	for(int i = 0; i< 400; i++) {
		printf("%.6f\n",out );
		// calculate system and regulator
		out = example_system(regulate(out,&regulator1));
	}

	return 0;
}

// system has integrating behaviour so only P is needed
float example_system(float in) {
	static float a = 0;
	a+=in*0.01;
	return a;
}

// sets known values to regulator structure to avoid erratic behaviour
void regulator_defaults(struct pid_data *pid_regulator) {
	pid_regulator->kp=0;
	pid_regulator->ki=0;
	pid_regulator->kd=0;
	pid_regulator->max_effort= 32767;
	pid_regulator->min_effort=-32768;
	pid_regulator->difference=0;
	pid_regulator->sum = 0;
	pid_regulator->set_value =0;

}


// returns regulator effort (y)
// intput is the feedback signal, pid_data is data structure of the regulator instance
float regulate(float input, struct pid_data *pid_regulator) {

	// get PID constants
	float ki = pid_regulator -> ki;
	float kp = pid_regulator -> kp;
	float kd = pid_regulator -> kd;

	// calculate error
	float error = (pid_regulator -> set_value) - input;

	// calculate effort
	float output = kp*error + ki*pid_regulator->sum + kd*(error - (pid_regulator->difference));

	// calculate sum and difference
	pid_regulator->sum += error;
	pid_regulator->difference = error;

	// limit effort
	if(output > pid_regulator-> max_effort) {
		output = pid_regulator->max_effort;
	} else if (output<pid_regulator->min_effort) {
		output = pid_regulator->min_effort;
	}

	// return effort
	return output;
}
