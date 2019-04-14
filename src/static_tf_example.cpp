#include <ros/ros.h>
#include<fiducial_msgs/FiducialTransformArray.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>

void transform_callback1(const fiducial_msgs::FiducialTransformArray);
void transform_callback2(const fiducial_msgs::FiducialTransformArray);
void transform_callback3(const fiducial_msgs::FiducialTransformArray);

static int a = 0;
static int b = 0;
static int c = 0;

geometry_msgs::TransformStamped static_transformStamped[3];

int main(int argc, char **argv)
{
  ros::init(argc, argv, "calibrate");
  ros::NodeHandle n;
  tf2_ros::StaticTransformBroadcaster static_broadcaster;
  ros::Subscriber sub1 = n.subscribe("/camera1/fiducial_transforms", 10,transform_callback1); ///fill a static_transform_stamped message
  ros::Subscriber sub2 = n.subscribe("/camera2/fiducial_transforms", 10,transform_callback2);
  ros::Subscriber sub3 = n.subscribe("/camera3/fiducial_transforms", 10,transform_callback3);

  while( a == 0 || b == 0 || c == 0) {
      ros::spinOnce();
  }

  for (int i=0; i<3; i++) {
    static_broadcaster.sendTransform(static_transformStamped[i]);
  }

  ros::spin();

  ROS_INFO(" All TFs published");
  return 0;
}

void transform_callback1(const fiducial_msgs::FiducialTransformArray msg)
    {
       if(msg.transforms.size()>0 && a == 0)
        {
            a = 1;
            
            static_transformStamped[0].header.stamp = ros::Time::now();
            static_transformStamped[0].child_frame_id = "aruco1";
            static_transformStamped[0].header.frame_id = "/camera_color_frame";
            static_transformStamped[0].transform = msg.transforms[0].transform;

            ROS_INFO("camera1 fiducial detected");
        }
    }

void transform_callback2(const fiducial_msgs::FiducialTransformArray msg)
    {
       if(msg.transforms.size()>0 && b == 0)
        {
            b = 1;
            
            static_transformStamped[1].header.stamp = ros::Time::now();
            static_transformStamped[1].child_frame_id = "aruco2";
            static_transformStamped[1].header.frame_id = "/camera_color_frame";
            static_transformStamped[1].transform = msg.transforms[0].transform;

            ROS_INFO("camera2 fiducial detected");
        }
    }

void transform_callback3(const fiducial_msgs::FiducialTransformArray msg)
    {
       if(msg.transforms.size()>0 && c == 0)
        {
            c = 1;
            
            static_transformStamped[2].header.stamp = ros::Time::now();
            static_transformStamped[2].child_frame_id = "aruco3";
            static_transformStamped[2].header.frame_id = "/camera_color_frame";
            static_transformStamped[2].transform = msg.transforms[0].transform;
                        
            ROS_INFO("camera3 fiducial detected");
        }
    }

