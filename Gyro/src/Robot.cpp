#include "WPILib.h"

class Robot : public SampleRobot {
	Joystick m_stick;
	Gyro m_gyro;
	RobotDrive m_drive;

	const uint32_t kFrontRightCh = 0; ///< Channel number for front right motor
	const uint32_t kFrontLeftCh = 2; ///< Channel number for front left motor
	const uint32_t kBackLeftCh = 3; ///< Channel number for back left motor
	const uint32_t kBackRightCh = 1; ///< Channel number for back right motor
	const double kUpdatePeriod = 0.005;

public:
	Robot() :
			m_stick(0), ///< Initialize Joystick on port 0.
			m_gyro(0), ///< Initialize the Gyro on channel TODO: set channel.
			m_drive(kFrontLeftCh, kBackLeftCh, kFrontRightCh, kBackRightCh) ///< Initialize RobotDrive to wheel ports.
	{
	}

	/**
	 * Prints Gyro readings as user controls robot's rotation.
	 */
	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			m_drive.MecanumDrive_Polar(0, 0, 0.25 * m_stick.GetAxis(4)); ///< Robot rotates using Joystick input.

			SmartDashboard::PutNumber("Current Angle: ", m_gyro.GetAngle()) ///< Gyro readings are printed to the SmartDashboard.
			Wait(kUpdatePeriod); ///< Wait 5ms for the next update.
		}
	}
};

START_ROBOT_CLASS(Robot);
