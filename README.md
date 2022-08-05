# cloud_ecal_receive

#### 介绍
​      **[cloud_ecal](https://github.com/CodeColdCook/cloud_ecal)**   data receive test

#### 依赖

- pcl >= 1.8

- **eCAL** (Protobuf 3.0.0)

  ```
  sudo add-apt-repository ppa:ecal/ecal-latest
  sudo apt-get update
  sudo apt-get install ecal
  ```

- **[cloud_ecal](https://github.com/CodeColdCook/cloud_ecal)**  

#### 安装教程

```shell
cd workspace
git clone https://github.com/CodeColdCook/cloud_ecal_receive.git
cd cloud_ecal_receive
mkdir build && cd build
cmake ..
make 
```

- 管理protobuf文件生成

```shell
set(PROTO_GEN_CXX ON CACHE BOOL "enable CXX protobuf file generate")
set(PROTO_GEN_JAVA OFF CACHE BOOL "enable JAVA protobuf file generate")
set(PROTO_GEN_PYTHON OFF CACHE BOOL "enable PYTHON protobuf file generate")
```

#### 使用

- 启动发布程序

```shell
./test_receive_ecal_cloud
```

