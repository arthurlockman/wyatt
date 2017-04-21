////
//// Created by Arthur Lockman on 4/5/17.
////

#include <commands/SimpleIteratorCommand.h>
#include <Communicator.h>
#include <iostream>
#include "../include/CommandManager.h"
#include "../catch/catch.hpp"
#include "../include/ISensor.h"
#include "../include/IRangeFinderSensor.h"
#include "../include/RawSensorData.h"
#include "../include/Hardware.h"
#include "../include/ISensorManager.h"
#include "../include/SensorManager.h"
#include "../include/ISensorManagerExceptions.h"
#include "mocks/include/MockSensorManager.h"
#include "mocks/include/MockHardwareInterface.h"

/* MOCKS */
#include "MockIRRangeFinderSensor.h"

TEST_CASE("Command subsystem tests", "[CommandManager]") {

    SECTION("Command manager can be killed.") {
        CommandManager *commandManager = new CommandManager();
        REQUIRE(commandManager->kill() == 0);
    }

    SECTION("Simple commands run to completion.") {
        CommandManager *commandManager1 = new CommandManager();
        SimpleIteratorCommand *sc1 = new SimpleIteratorCommand(10);
        SimpleIteratorCommand *sc2 = new SimpleIteratorCommand(20);
        commandManager1->runCommand(sc1);
        commandManager1->runCommand(sc2);
        REQUIRE(commandManager1->inFlight() == 2);
        while (!sc1->isFinished() && !sc2->isFinished()) {}
        REQUIRE(sc1->getCount() == 10);
        REQUIRE(sc2->getCount() == 20);
        REQUIRE(commandManager1->inFlight() == 0);
        commandManager1->kill();
    }

    SECTION("Commands can be canceled.") {
        CommandManager *commandManager2 = new CommandManager();
        SimpleIteratorCommand *sc3 = new SimpleIteratorCommand(1000);
        commandManager2->runCommand(sc3);
        commandManager2->cancel(sc3);
        while (!sc3->isFinished()) {}
        REQUIRE(sc3->getCount() != 1000);
        SimpleIteratorCommand *sc4 = new SimpleIteratorCommand(1000);
        SimpleIteratorCommand *sc5 = new SimpleIteratorCommand(2000);
        SimpleIteratorCommand *sc6 = new SimpleIteratorCommand(3000);
        commandManager2->runCommand(sc4);
        commandManager2->runCommand(sc5);
        commandManager2->runCommand(sc6);
        commandManager2->cancelAll();
        while (!sc4->isFinished() && !sc5->isFinished() && !sc6->isFinished()) {}
        REQUIRE(sc4->getCount() != 1000);
        REQUIRE(sc5->getCount() != 2000);
        REQUIRE(sc6->getCount() != 3000);
        commandManager2->kill();
    }
}

TEST_CASE("Sensor interface tests", "[ISensor]") {

    std::string mockData = "12.2";
    RawSensorData* mockRawSensorData_IR = new RawSensorData(mockData);

    SECTION("ISensor polymorphically updates") {
        ISensor* sensor = new MockIRRangeFinderSensor();
        sensor->updateSensor(mockRawSensorData_IR);
        MockIRRangeFinderSensor* IRSensor = (MockIRRangeFinderSensor*) sensor;

        REQUIRE( IRSensor->getDistanceCM() == 12.2 );
    }

}

TEST_CASE("RawSensorData tests", "[RawSensorData]") {

    std::string mockData = "12.2";

    SECTION("Data is correctly encapsulated and returned") {
        RawSensorData* data = new RawSensorData(mockData);

        REQUIRE(data->getData() == mockData);
    }
}

TEST_CASE("ISensorManager tests", "[ISensorManager]") {

    ISensorManager* sensorManager = new SensorManager();

    SECTION("Adding hardware twice results in exception.") {
        Hardware mockHardware = H_LEFT_MOTOR;
        ISensor* mockSensor = new MockIRRangeFinderSensor();

        sensorManager->addSensor(mockHardware, mockSensor);
        REQUIRE_THROWS(
                sensorManager->addSensor(mockHardware, mockSensor)
        );
    }

    SECTION("Updating non-existent hardware results in exception") {
        Message* msg = new Message(H_LEFT_MOTOR, "12.2");
        std::list<Message*>* messages = new std::list<Message*>;
        messages->push_back(msg);
        REQUIRE_THROWS(
                sensorManager->updateSensors(messages)
        );
    }

    SECTION("Updates sensors correctly") {
        Hardware mockHardware = H_LEFT_MOTOR;
        MockIRRangeFinderSensor* mockSensor = new MockIRRangeFinderSensor();
        sensorManager->addSensor(mockHardware, mockSensor);

        Message* msg = new Message(H_LEFT_MOTOR, "12.2");
        std::list<Message*>* messages = new std::list<Message*>;
        messages->push_back(msg);

        sensorManager->updateSensors(messages);

        REQUIRE(mockSensor->getDistanceCM() == 12.2);
    }


}

TEST_CASE("Message tests", "[Message]") {
    std::string mockData = "12.2";
    Hardware hardware = H_LEFT_MOTOR;
    Message* msg = new Message(hardware, mockData);
    REQUIRE((msg->getHardware()).address == hardware.address);
    REQUIRE(msg->getMessage() == mockData);
}

TEST_CASE("Communicator Tests", "[Communicator]") {

    /* Initialize object */
    ISensorManager* mockSensorManager = new MockSensorManager();
    IHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

    Hardware hardwareTarget = H_LEFT_MOTOR;
    Communicator* comm = new Communicator(mockSensorManager, mockHardwareInterface);

    SECTION("Test queuing message") {
        std::string mockData = "13.2";
        Message* mockMessage = new Message(hardwareTarget, mockData);
        comm->queueMessage(mockMessage);
    }

    SECTION("Test receiving messages") {

    }

}

//
//#if IS_RASPI
//TEST_CASE("Integration Tests", "[Integration]") {
//
//    ISensorManager* mockSensorManager = new MockSensorManager();
//    std::string comPort = "/dev/ttyUSB0";
//    int baudRate = 9600;
//    Communicator* comm = new Communicator(mockSensorManager, baudRate);
//
//    SECTION("Integration test: Attach arduino and turn both motors") {
//        /* Attach motors to the arduino */
//        comm->attachHardware(comPort, H_LEFT_MOTOR);
//        comm->attachHardware(comPort, H_RIGHT_MOTOR);
//
//        /* Command for driving right motor forwards */
//        char commandLeftMotor[] = {H_LEFT_MOTOR.address, 0};
//        char commandRightMotor[] = {H_RIGHT_MOTOR.address, 0};
//        Message* msgRight = new Message(H_RIGHT_MOTOR, commandRightMotor);
//        Message* msgLeft = new Message(H_LEFT_MOTOR, commandLeftMotor);
//
//        /* Queue messages */
//        comm->queueMessage(msgRight);
//        comm->queueMessage(msgLeft);
//
//        /* Send messages */
//        comm->sendNextMsg(H_LEFT_MOTOR);
//        comm->sendNextMsg(H_RIGHT_MOTOR);
//
//    }
//}
//#endif
