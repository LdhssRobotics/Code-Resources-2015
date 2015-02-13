// unfucking everything up after feilan dun goofed

#include "WPILib.h"
class Robot : public SampleRobot {
Talon mRight;
Talon mLeft;
Joystick Stick;
public:
Robot():
mRight(0),
mLeft(1),
Stick(1)
{}
void OperatorControl()
{
float speedX=0;
float speedY=0;
while(IsOperatorControl()&&IsEnabled())
{
while(IsOperatorControl() && IsEnabled())
{
if(Stick.GetRawButton(5)==0) //Dead Man Switch
{
speedY=0;
speedX=0;
mRight.Set((speedX-speedY)/2); //Movement
mLeft.Set((speedY+speedX)/2);
}
else if(Stick.GetRawButton(5)==1)
{
if(Stick.GetRawButton(2)) //turning
{
speedX=Stick.GetX();
}
else
{
speedX=Stick.GetX()/2; //Turning
}
if(Stick.GetRawButton(1))
{
mRight.Set((speedX-speedY)/2); //Movement
mLeft.Set((speedY+speedX)/2);
}
else
{
mRight.Set(speedX-speedY); //Movement
mLeft.Set(speedY+speedX); //Movement
}
if(Stick.GetY()>speedY) //Forward speed
{
speedY+=0.001;
}
else if(Stick.GetY()<speedY) //Backward speed
{
speedY-=0.001;
}
if(Stick.GetX()<0.1&&Stick.GetX()>-0.1&&Stick.GetY()<0.1&&Stick.GetY()>-0.1) //Override stop
{
if(speedY>0) //Slow Forward Speed
{
speedY-=0.001;
}
if(speedY<0) //Slow Reverse Speed
{
speedY+=0.001;
}
if(Stick.GetRawButton(6)) //Emergency Stop
{
speedX=0;
speedY=0;
}
Wait(0.001); //Wait Until Time Is Up.
}
}
}
}
}
};
START_ROBOT_CLASS(Robot);
