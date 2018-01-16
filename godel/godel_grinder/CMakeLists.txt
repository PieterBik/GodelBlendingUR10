cmake_minimum_required(VERSION 2.8.3)
project(godel_grinder)
add_definitions(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
        godel_msgs
        std_msgs
        tf
        geometry_msgs
        message_generation
        genmsg
        cmake_modules
        moveit_core
        moveit_ros_planning_interface
        )

catkin_package(
        INCLUDE_DIRS
        include
        CATKIN_DEPENDS
        tf
        godel_msgs
        moveit_ros_planning_interface
        moveit_core
        geometry_msgs
        std_msgs
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
)

add_executable(godel_grinder_node
        src/node.cpp
        src/godel_grinder_service.cpp
        )

add_dependencies(godel_grinder_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


target_link_libraries(godel_grinder_node
        ${catkin_LIBRARIES}
        )
