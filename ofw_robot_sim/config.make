PROJECT_LDFLAGS=-Wl,-rpath=./libs
PROJECT_LDFLAGS+=$(SUBLIBS) $(ros_libs_nocolon) 
ros_libs = $(shell pkg-config --libs roscpp nav_msgs tf)
ros_libs_nocolon = $(subst -l:,,$(ros_libs))
PROJECT_OPTIMIZATION_CFLAGS_DEBUG = `pkg-config --cflags roscpp std_msgs nav_msgs tf geometry_msgs move_base_msgs sensor_msgs` -w -O2 
PROJECT_OPTIMIZATION_CFLAGS_RELEASE = `pkg-config --cflags roscpp std_msgs nav_msgs tf geometry_msgs move_base_msgs sensor_msgs` -w -O2

