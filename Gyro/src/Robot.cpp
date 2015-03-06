#include "WPILib.h"

class Robot : public SampleRobot {
	Joystick m_stick;
	Gyro m_gyro;
	RobotDrive m_drive;

	float m_angle = 0.0;
	float m_referenceAngle = 0.0;
	float m_angleDelta = 0.0;
	bool m_isAbsoluteAngle = false;

	const uint32_t kFrontRightCh = 0; ///< Channel number for front right motor
	const uint32_t kFrontLeftCh = 2; ///< Channel number for front left motor
	const uint32_t kBackLeftCh = 3; ///< Channel number for back left motor
	const uint32_t kBackRightCh = 1; ///< Channel number for back right motor
	const float k_speedLimit = 0.25;
	const double k_updatePeriod = 0.005;

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
		float currentAngle = 0.0;

		while (IsOperatorControl() && IsEnabled()) {
			currentAngle = m_gyro.GetAngle();

			m_drive.MecanumDrive_Polar(0, 0, k_speedLimit * m_stick.GetAxis(1)); ///< Robot rotates using Joystick input.

			/**
			 * If button pressed, toggles between printing absolute angle and relative angle.
			 * Will set a reference point if set to printing relative angle.
			 */
			if(m_stick.GetRawButton(1))	{
				m_isAbsoluteAngle = !m_isAbsoluteAngle;
				if(!m_isAbsoluteAngle)	m_referenceAngle = currentAngle;
			}

			/**
			 * Calculates the angle value to be printed.
			 */
			if(m_isAbsoluteAngle) {
				m_angle = currentAngle;
			} else {
				m_angle = currentAngle - m_referenceAngle;
				SmartDashboard::PutNumber("Reference Angle: ", m_referenceAngle);
			}

			SmartDashboard::PutNumber("Current Angle: ", m_angle) ///< Gyro readings are printed to the SmartDashboard.

			Wait(k_updatePeriod); ///< Wait 5ms for the next update.
		}
	}
};

START_ROBOT_CLASS(Robot);
