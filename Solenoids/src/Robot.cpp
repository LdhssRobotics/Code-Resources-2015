#include "WPILib.h" ///imports the WPILIP which has the classes needed

class Robot: public SampleRobot
{

	Joystick m_stick; ///Uses the Joystick to control the robot
	// Solenoid corresponds to a single solenoid.
	Solenoid m_solenoid;
	// DoubleSolenoid corresponds to a double solenoid.
	DoubleSolenoid doubleSolenoid;



	//Creates a variable to represent button #1 (Its easier for the user)
	const int kSolenoidButton = 1;
	//Creates a variable to represent button #2 (Its easier for the user)
	const int kDoubleSolenoidForward = 2;
	//Creates a variable to represent button #3 (Its easier for the user)
	const int kDoubleSolenoidReverse = 3;

public:
	Robot() :
			m_stick(0), /// Use joystick on port 0.
			m_solenoid(0), /// Use solenoid on channel 0.
			// Use double solenoid with Forward Channel of 1 and Reverse of 2.
			doubleSolenoid(1, 2)
	{
	}


	void OperatorControl()
	{

		while (IsOperatorControl() && IsEnabled())
		{
			//Note this is a single Solenoid example


			//sets the singleSolenoid to adjust to the pressure the user placed on button #1
			m_solenoid.Set(m_stick.GetRawButton(kSolenoidButton));

			//Note this is a doubleSolenoid example


			//if the button #2 is pressed...
			if (m_stick.GetRawButton(kDoubleSolenoidForward))
				//sets the doubleSolenoid to advance at the pressure the user placed on the button
				doubleSolenoid.Set(DoubleSolenoid::kForward);
			//if button #3 is pressed...
			else if (m_stick.GetRawButton(kDoubleSolenoidReverse))
				//sets the doubleSolenoid to reverse at the pressure the user placed on the button
				doubleSolenoid.Set(DoubleSolenoid::kReverse);
			//if none of these requirements are met...
			else
				//sets the doubleSolenoid to stop
				doubleSolenoid.Set(DoubleSolenoid::kOff);

			Wait(0.005);				/// wait for a motor update time
		}
	}
};
START_ROBOT_CLASS(Robot);
