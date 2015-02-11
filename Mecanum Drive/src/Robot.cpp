#include "WPILib.h"
#include "math.h"
#define ForwardAxis 1
#define TranslateAxis 0
#define RotateAxis 4
#define InvertForward 1 //-1 or 1, not for inverting actual wheels, just input axis
#define InvertSide 1
#define InvertRotate 1
#define InvertFR 1 //-1 or 1, for inverting individual wheels
#define InvertBR 1
#define InvertFL -1
#define InvertBL -1
/**
* This is a change
* This is a demo program showing the use of the RobotDrive class.
* The SampleRobot class is the base of a robot application that will automatically call your
* Autonomous and OperatorControl methods at the right time as controlled by the switches on
* the driver station or the field controls.
*
* WARNING: While it may look like a good choice to use for your code if you're inexperienced,
* don't. Unless you know what you are doing, complex code will be much more difficult under
* this system. Use IterativeRobot or Command-Based instead if you're new.
*/
float CurSpeed[6] = { 0, 0, 0, 0, 0, 0 };
class Robot: public SampleRobot {
Joystick stick; // only joystick
Talon motorFR;
Talon motorBR;
Talon motorFL;
Talon motorBL;
double kUpdatePeriod = 0.005;
public:
Robot() :
stick(0), motorFR(0), motorBR(3), motorFL(1), motorBL(2),mCamera(4) {
}
float CurJoy[6] = { 0, 0, 0, 0, 0, 0 };
float GetSmoothAxis(int axis) { //function for smoothing a target axis, in other words acceleration
CurJoy[axis] = stick.GetRawAxis(axis); //fetch the target axis, since it is very important this is the same throught the math it is fetched once here
if(!stick.GetRawButton(5)) {
CurJoy[axis]=0;
}
if (true/*abs(CurJoy[axis]-CurSpeed[axis])>0.015*/) { //commented part would bypass changing the motor value if it was already close enough to the target value
CurSpeed[axis] = CurSpeed[axis]+ ((abs(CurJoy[axis] - CurSpeed[axis]) / (CurJoy[axis] - CurSpeed[axis])) * 0.01); //bring the motor value closer to the joystick by 1%
}
// CurSpeed[axis] = CurJoy[axis]; //uncomment this if the robot does not accelerate or move, it will disable acceleration
return CurJoy[axis]; //return the value for the smoothed axis
}
/**
* Runs the motors with arcade steering.
*/
void OperatorControl()
{
while (IsOperatorControl() && IsEnabled()) {
//uncomment this for full mecanum drive, disabled for acceleration testing
motorFR.Set(InvertFR*(GetSmoothAxis(ForwardAxis)+GetSmoothAxis(RotateAxis)+GetSmoothAxis(TranslateAxis)));
motorBR.Set(InvertBR*(GetSmoothAxis(ForwardAxis)+GetSmoothAxis(RotateAxis)-GetSmoothAxis(TranslateAxis)));
motorFL.Set(InvertFL*(GetSmoothAxis(ForwardAxis)-GetSmoothAxis(RotateAxis)-GetSmoothAxis(TranslateAxis)));
motorBL.Set(InvertBL*(GetSmoothAxis(ForwardAxis)-GetSmoothAxis(RotateAxis)+GetSmoothAxis(TranslateAxis)));
//motorFR.Set(GetSmoothAxis(ForwardAxis)); //for testing we only turn one motor
Wait(kUpdatePeriod); // wait for a motor update time
}
}
};
START_ROBOT_CLASS(Robot);