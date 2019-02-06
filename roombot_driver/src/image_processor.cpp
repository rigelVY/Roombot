#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgcodecs.hpp>

cv::Mat image;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	try {
		image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
	}

	// dictionary生成
	const cv::aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = cv::aruco::DICT_4X4_50;
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionary_name);

	// マーカーの検出
	std::vector<int> marker_ids;
	std::vector< std::vector<cv::Point2f> > marker_corners;
	cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
	cv::aruco::detectMarkers(image, dictionary, marker_corners, marker_ids, parameters);

	// 検出したマーカーの描画
	cv::aruco::drawDetectedMarkers(image, marker_corners, marker_ids);
	cv::imshow("marker_detection", image);
	cv::waitKey(1);
}

int main(int argc, char** argv)
{
	ros::init (argc, argv, "img_subscriber");
	ros::NodeHandle nh("~");

	image_transport::ImageTransport it(nh);
	image_transport::Subscriber image_sub = it.subscribe("/img_publisher/image", 10, imageCallback);

	ros::spin();

	return 0;
}
