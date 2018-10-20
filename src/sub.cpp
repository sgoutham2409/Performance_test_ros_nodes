#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include "std_msgs/Float32.h"

#include <sstream>

using namespace std;

std_msgs::Float32 subFreq;

int num_msgs_received = 0;
int newFreqCalc = 0;
double frequency = 1;
double time_now = 0;
double time_prev = 0;

void frequencyCalcCallback(const ros::TimerEvent &event) {
  time_now = ros::Time::now().toNSec()*pow(10,-9);
  double dt = time_now-time_prev;
  time_prev = time_now;

  // ROS_INFO("num of messages received: %d, time interval: %.4f",num_msgs_received,dt);
  subFreq.data = double(num_msgs_received)/dt;
  ROS_INFO("subf = %f", subFreq.data);
  newFreqCalc = 1;
  num_msgs_received = 0;
}

void callback(const performance_tests::SuperAwesome::ConstPtr& data)
{
  stringstream ss;
  ss << "CPP sub " << data->data;
  num_msgs_received++;

//  ROS_INFO("%s", ss.str().c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("test", 1, callback);
  ros::Publisher freqpub = n.advertise<std_msgs::Float32>("testsubfreq", 1);
  ros::Timer freqCalcTimer = n.createTimer(ros::Duration(1), &frequencyCalcCallback);

  if(newFreqCalc == 1)
  {
     freqpub.publish(subFreq);
     newFreqCalc = 0;
  }
  ros::spin();

  return 0;
}
