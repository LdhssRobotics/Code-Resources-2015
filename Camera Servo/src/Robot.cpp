#include "WPILib.h"
class Robot : public SampleRobot {
	Joystick stick;
	Servo mCamera;
	public:
Robot() :
stick(0),
mCamera(4)
{}
void OperatorControl()
{
while (IsOperatorControl() && IsEnabled()) {
	float mCameraServoPosition=0.6;		//Starting postion
	mCamera.Set(mCameraServoPosition);
	if(stick.GetRawButton(3)) {
	mCameraServoPosition+=0.0001;		//Button X moves it down
	}
	else if(stick.GetRawButton(4)) {
	mCameraServoPosition-=0.0001;		//Button Y moves it up
	}
	Wait(0.0001);
  }
}
};
START_ROBOT_CLASS(Robot);
