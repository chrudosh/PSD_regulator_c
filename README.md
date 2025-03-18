# PSD_regulator_c
This repository is a simple PSD regulator in  the language C
## files:
**example.c** - code in one file, functions ready to be pasted into your code <br />
**float regulate()**, **void regulator_defaults()** and **struct pid_data** are required <br />

**psd_regulator.c** - code for usage as library <br />
**psd_regulator.h** - header file for usage as library

## usage:

### 1. Create instance of **pid_data**
```C
struct pid_data regulator1;
```
### 2. Initialize instance
Call the function **regulator_defaults** to avoid random values in structure upon initialisation
```C
regulator_defaults(&regulator1);
```
### 3. Regulator usage
First you want to set the regulator parameters
```C
// setting the kp, ki and kd weights 
regulator1.kp = 1;
regulator1.ki = 0.5;
regulator1.kd = 0.1;

// setting the maximum and minimum output value
regulator1.max effort = 255
regulator1.min_effort = -255;
```
Function **regulate** calculates the output of the regulator
```C
output = regulate(value, &regulator1);
```
The first parameter is the feedback signal from regulated system, second parameter is the instance of used regulator <br />
this allows the usage of more than one regulator with this function.<br />
<br />
Desired regulation value can be set with:
```C
regulator1.set_value = 10;
```





