#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h"
#include "std_msgs/Float32.h"

#include <sstream>

using namespace std;

double frequency = 100; //25000 for CPP Pub - CPP Sub pair;
int frequencyPub = 0;

void frequencyPubCallback(const ros::TimerEvent &event) {
  frequencyPub = 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sender");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<performance_tests::SuperAwesome>("test", 1);
  ros::Publisher freqpub = n.advertise<std_msgs::Float32>("testpubfreq", 1);
  ros::Timer freqChangeTmr = n.createTimer(ros::Duration(5), &frequencyPubCallback);

  ros::Rate loop_rate(frequency);
  performance_tests::SuperAwesome msg;
  std_msgs::Float32 pubFreq;

  ROS_INFO("pubf = %f", frequency);

  while (ros::ok())
  {
    std::stringstream ss;
    ss << ros::Time::now();
    msg.data = ss.str();
    pubFreq.data = (double)frequency;

//    ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);

    if(frequencyPub == 1)
    {
      freqpub.publish(pubFreq);
      ROS_INFO("pubf = %f", pubFreq.data);
      frequencyPub = 0;
    }
    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
