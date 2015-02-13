// unfucking everything up after feilan dun goofed

#include "WPILib.h" ///Includes the WPILIP which has the UltraSonic class.

class Robot : public SampleRobot {

	Ultrasonic Sonic; ///Define the ultrasonic class 

	// update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;

public:
	Robot() :
			Sonic(3,4, Ultrasonic::kMilliMeters)
	{
	}

	void OperatorControl() {

		while (IsOperatorControl())
		{
			if (IsEnabled())
			{
				Sonic.SetAutomaticMode(true);
				Sonic.SetEnabled(true);
				double myDistance = (Sonic.GetRangeMM()/10); ///my distance is diclaired and is getting the distance in CM
				SmartDashboard::PutNumber("Ultrasonic Measurement", myDistance);///The Distance is put on to the Smart DashBoad where it's shown to the User

				Wait(kUpdatePeriod); /// Wait 5ms for the next update.
			}
			else ///Do when disabled
			{
				Sonic.SetAutomaticMode(false);
			}
		}
	}
};

START_ROBOT_CLASS(Robot);
