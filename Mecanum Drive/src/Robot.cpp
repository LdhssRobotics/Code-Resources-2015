#include "WPILib.h"
#include "math.h"
#define ForwardAxis 1
#define TranslateAxis 0
#define RotateAxis 4
#define InvertForward 1 //-1 or 1, not for inverting actual wheels, just input axis
#define InvertSide 1
#define InvertRotate 1
#define InvertFR 1		//-1 or 1, for inverting individual wheels
#define InvertBR 1
#define InvertFL -1
#define InvertBL -1
#define AccelVal 0.01f  // Acceleration step value: bring the motor value closer to the joystick by 1%

class Robot: public IterativeRobot
{
	Joystick stick; // only joystick
	Talon motorFR;
	Talon motorFL;
	Talon motorBL;
	Talon motorBR;
	Servo mCamera;
	Encoder encoder;
	Ultrasonic Sonic;
	DigitalInput SonicPulse;
	DigitalInput limitswitch;
	LiveWindow *lw;
	int autoLoopCounter;
	double kUpdatePeriod = 0.005;
	bool SmoothAccel = true;
	float mCameraServoPosition = 0.5;         ///< Jacob - please confirm
	float CurSpeed[6] = { 0, 0, 0, 0, 0, 0 }; ///< Current speed values over 6 axes
	float CurJoy[6] = { 0, 0, 0, 0, 0, 0 };   ///< Current joystick values over 6 axes

public:
	Robot() :
		stick(0),
		motorFR(0),
		motorFL(1),
		motorBL(2),
		motorBR(3),
		mCamera(4),
		encoder(1, 2, true),
		Sonic(3,3, Ultrasonic::kMilliMeters),
		SonicPulse(3),//To measure pulses manually (TEST)
		limitswitch(0),
		lw(NULL),
		autoLoopCounter(0)
	{
	}

	/**
	 * Function for smoothing a target axis (in other words, applying acceleration).
	 */
	float GetSmoothAxis(int axis) {
			//fetch the target axis, since it is very important this is the same throughout the math it is fetched once here
			CurJoy[axis] = (true/*replace true with false to disable eg dead switch*/) ? stick.GetRawAxis(axis) : 0;
			if (SmoothAccel) {
				CurSpeed[axis] += (CurJoy[axis] > CurSpeed[axis]) ? AccelVal : -1*AccelVal; //bring the motor value closer to the joystick by 1%
			}
			else {
				CurSpeed[axis] = CurJoy[axis];
			}
			return CurSpeed[axis]; //return the value for the smoothed axis
		}

private:
	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{

			autoLoopCounter++;
			} else {

		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		if (IsEnabled())
		{
			if(stick.GetRawAxis(2)>0.5) {
				SmoothAccel = true;
			}
			else if(stick.GetRawAxis(3)>0.5) {
				SmoothAccel = false;
			}

			//mecanum drive code calculates values for each motor and writes them
			motorFR.Set(InvertFR*(GetSmoothAxis(ForwardAxis)+GetSmoothAxis(RotateAxis)+GetSmoothAxis(TranslateAxis)));
			motorFL.Set(InvertFL*(GetSmoothAxis(ForwardAxis)-GetSmoothAxis(RotateAxis)-GetSmoothAxis(TranslateAxis)));
			motorBL.Set(InvertBL*(GetSmoothAxis(ForwardAxis)-GetSmoothAxis(RotateAxis)+GetSmoothAxis(TranslateAxis)));
			motorBR.Set(InvertBR*(GetSmoothAxis(ForwardAxis)+GetSmoothAxis(RotateAxis)-GetSmoothAxis(TranslateAxis)));

			Wait(kUpdatePeriod);				// wait for a motor update tim
		}
		else //Do when disabled
		{
			SmartDashboard::PutNumber("is on", 0);
			for(int i=0; i<5; i++) {
			  CurSpeed[i] = 0;
			}
		}
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
