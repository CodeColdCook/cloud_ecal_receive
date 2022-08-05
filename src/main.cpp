#include <iostream>
#include "ecal/ecal.h"
#include <ecal/msg/protobuf/publisher.h>
#include <ecal/msg/protobuf/subscriber.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include "sensor/cloud_common.pb.h"

static pcl::visualization::PCLVisualizer viewer_pcl("pro_cloud_show");

void callback(const char* topic_name_, const SensorMsg::PointCloudXYZI& pc, long long time_, long long clock_, long long id_) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = pc.width();
    cloud->height = pc.height();
    cloud->points.clear();

    const SensorMsg::PointXYZI* p = &pc.points(0);

    for (size_t i = 0; i < cloud->width * cloud->height; i++) {
        pcl::PointXYZ point;
        point.x = p->x();
        point.y = p->y();
        point.z = p->z();
        cloud->points.push_back(point);
        p++;
    }

    std::cout << "receive cloud size: " << cloud->width << std::endl;

    viewer_pcl.removeAllPointClouds();
    viewer_pcl.addPointCloud(cloud);
    viewer_pcl.updatePointCloud(cloud, "pro_cloud_show");
    viewer_pcl.spinOnce(0.1);
}

int main(int argc, char* argv[]) {
    eCAL::Initialize(argc, argv, "receive pcd");
    eCAL::Util::EnableLoopback(true);
    eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");

    eCAL::protobuf::CSubscriber<SensorMsg::PointCloudXYZI> sub("pmtd/livox_vcloud");
    SensorMsg::PointCloudXYZI data;

    auto lambda = [](const char*,
                     const SensorMsg::PointCloudXYZI& data,
                     long long, long long, long long) {
        callback("", data, 0, 0, 0);
    };
    sub.AddReceiveCallback(lambda);

    while (eCAL::Ok()) {
    }

    return 0;
}
