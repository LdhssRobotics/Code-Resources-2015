// unfucking everything up after feilan dun goofed

#include "WPILib.h"

class Robot : public SampleRobot {
	DigitalInput limitswitch;
	// update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;

public:
	Robot() :
			limitswitch(0)
	{
	}

	void OperatorControl() {
		while (IsOperatorControl())
		{
			if (IsEnabled())
			{
				if(limitswitch.Get() == 1)
				{
					SmartDashboard::PutString("LimitSwitch", "Pushed");
				}else
				{
					SmartDashboard::PutString("LimitSwitch", "Not pushed");
				}

				Wait(kUpdatePeriod); // Wait 5ms for the next update.
			}
		}
	}
};

START_ROBOT_CLASS(Robot);
