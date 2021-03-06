# ------------------------------------------------------------------------------
# Box2D Project
# ------------------------------------------------------------------------------
project(Box2D)

# ------------------------------------------------------------------------------
# Box2D Sources
# ------------------------------------------------------------------------------
set(Box2D_sources ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2BroadPhase.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2CollideCircle.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2CollideEdge.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2CollidePolygon.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2Collision.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2Distance.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2DynamicTree.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/b2TimeOfImpact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/Shapes/b2ChainShape.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/Shapes/b2CircleShape.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/Shapes/b2EdgeShape.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Collision/Shapes/b2PolygonShape.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Common/b2BlockAllocator.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Common/b2Draw.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Common/b2Math.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Common/b2Settings.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Common/b2StackAllocator.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Common/b2Timer.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2CircleContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2Contact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2GearJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2Joint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2MotorJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2MouseJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2RopeJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2WeldJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/Joints/b2WheelJoint.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/b2Body.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/b2ContactManager.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/b2Fixture.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/b2Island.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/b2World.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Dynamics/b2WorldCallbacks.cpp
        ${PROJECT_SOURCE_DIR}/Box2D/Rope/b2Rope.cpp)

# ------------------------------------------------------------------------------
# Box2D Library
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${Box2D_sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
