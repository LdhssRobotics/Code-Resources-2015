#include "WPILib.h"

class Robot : public SampleRobot {
	Joystick m_stick;
	Encoder m_encoder;
	RobotDrive m_drive;
	Ultrasonic m_ultra;

	double m_distancePerPulse = 0.0;

	double m_accel = 0.0;
	double m_speed = 0.0;
	uint32_t m_initialCount = 0;
	uint32_t m_countDelta = 0;
	double m_initialPosition = 0.0;
	double m_positionDelta = 0.0;

	const uint32_t kFrontRightCh = 0; ///< Channel number for front right motor
	const uint32_t kFrontLeftCh = 2; ///< Channel number for front left motor
	const uint32_t kBackLeftCh = 3; ///< Channel number for back left motor
	const uint32_t kBackRightCh = 1; ///< Channel number for back right motor

	const double k_distance = 3.0;
	const double k_jerk = 0.0;
	const double k_updatePeriod = 0.005;
public:
	Robot() :
			m_stick(0), // Initialize Joystick on port 0.
			m_encoder(4, 5, true),
			m_drive(kFrontLeftCh, kBackLeftCh, kFrontRightCh, kBackRightCh), ///< Initialize RobotDrive to wheel ports.
			m_ultra(1, 2) //get the channels used
	{
	}

	/**
	 * Runs the motor from the output of a Joystick.
	 */
	void OperatorControl() {
		while(IsOperatorControl())
		{
			if (IsEnabled()) {
				if (m_speed < 1) {
					SmartDashboard::PutString("Robot accelerating", "");
					SmartDashboard::PutNumber("Speed", m_speed);

					m_accel += k_jerk;
					m_speed += m_accel;
				} else if (m_speed == 1) {
					if (m_initialCount == 0) 		m_initialCount = m_encoder.Get();
					if (m_initialPosition == 0.0)	m_initialPosition = m_ultra.GetRangeMM();

					if (m_positionDelta <= k_distance) {
						m_countDelta = m_encoder.Get() - m_initialCount;
						m_positionDelta = 1000 * (m_initialPosition - m_ultra.GetRangeMM());

						SmartDashboard::PutString("Robot at full speed", "Testing in progress");
						SmartDashboard::PutNumber("Change in Encoder Count", m_countDelta);
						SmartDashboard::PutNumber("Distance Travelled", m_positionDelta);
						SmartDashboard::PutNumber("Total Distance to Travel", k_distance);

					} else {
						if (m_distancePerPulse == 0.0)	m_distancePerPulse = m_positionDelta / m_countDelta;

						SmartDashboard::PutString("Full distance travelled", "Testing completed");
						SmartDashboard::PutNumber("Speed", m_speed);
						SmartDashboard::PutNumber("Distance travelled per encoder pulse", m_distancePerPulse);

						Decelerate();
					}
				}
			} else {
				Decelerate();
			}

			m_drive.MecanumDrive_Polar(m_speed, 0, 0);
		}
	}

	void Decelerate() {
		if (m_speed > 0) {
			m_accel -= k_jerk;
			m_speed -= m_accel;
		} else if (m_speed < 0) {
			m_speed = 0;
		}
	}
};

START_ROBOT_CLASS(Robot);
