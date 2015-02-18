#include "WPILib.h"

class Robot : public SampleRobot {
	//Use a joystick to control the motor
	Joystick m_stick;
	// This uses a Talon speed controller
	//(It may be a victor on the robot, if so change talon code to victor code)
	Talon m_motor;
	//Define the encoder
	Encoder encoder;

	// update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;

public:
	Robot() :
			m_stick(0), // Initialize Joystick on port 0.
			m_motor(0), // Initialize the Talon on channel 0.
			encoder(4, 5, true)
	{
	}

	/**
	 * Runs the motor from the output of a Joystick.
	 */
	void OperatorControl() {

		while (IsOperatorControl())
		{
			if (IsEnabled())
			{
				SmartDashboard::PutNumber
				("Motor Count", double ((encoder.Get()/71.164)/7));
				///Divides encoder.get by gear ratio of 71.164, then divide result by encoder ratio of 7:1. It will output the # of motor rotations.

				/*
				//If you want to have the count reset when the motor stops, add the following code:
				if (encoder.GetStopped() == "true")
				{
					encoder.Reset();
				}
				*/

				// Set the motor controller's output.
				// This takes a number from -1 (100% speed in reverse) to +1 (100% speed forwards).
				m_motor.Set(m_stick.GetY());

				Wait(kUpdatePeriod); // Wait 5ms for the next update.
			}
			else //Do when disabled
			{
				//Resets the encoder count when robot is disabled
				if (encoder.Get() != 0){
					encoder.Reset();
				}
			}
		}
	}
};

START_ROBOT_CLASS(Robot);
