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
#include "../include/Chassis.h"

#include <unistd.h>

/* MOCKS */
#include "MockIRRangeFinderSensor.h"
#include "mocks/include/MockSensorManager.h"
#include "mocks/include/MockHardwareInterface.h"

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

        REQUIRE(IRSensor->getData() == mockData);
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
        REQUIRE_THROWS_AS(
                sensorManager->addSensor(mockHardware, mockSensor),
                DuplicateHardwareException
        );
    }

    SECTION("Updating non-existent hardware results in exception") {
        std::string data;
        data.append(1, 0b00000000);
        Message* msg = new Message(H_LEFT_MOTOR, data);
        std::list<Message*>* messages = new std::list<Message*>;
        messages->push_back(msg);

        REQUIRE_THROWS_AS(
                sensorManager->updateSensors(messages),
                NonexistentHardwareException
        );
    }

    SECTION("Updates sensors correctly") {
        Hardware mockHardware = {0b11111111, 1};
        MockIRRangeFinderSensor* mockSensor = new MockIRRangeFinderSensor();
        sensorManager->addSensor(mockHardware, mockSensor);

        std::string data;
        data.append(1, 0b11111111); // 255
        Message* msg = new Message(mockHardware, data);
        std::list<Message*>* messages = new std::list<Message*>;
        messages->push_back(msg);

        sensorManager->updateSensors(messages);

        REQUIRE(mockSensor->getData() == data);
    }


}

TEST_CASE("Message tests", "[Message]") {

    SECTION("Test normal message") {
        std::string mockData;
        mockData.append(1, 127);
        Hardware hardware = H_LEFT_MOTOR;
        Message* msg = new Message(hardware, mockData);

        REQUIRE((msg->getHardware()).address == hardware.address);
        REQUIRE(msg->getMessage() == mockData);
    }

    SECTION("Test message length too short") {
        std::string mockData;
        Hardware hardware = H_LEFT_MOTOR;

        REQUIRE_THROWS_AS(
                new Message(hardware, mockData),
                MessageLengthException
        );
    }

    SECTION("Test message length too long") {
        std::string mockData = "too long";
        Hardware hardware = H_LEFT_MOTOR;

        REQUIRE_THROWS_AS(
                new Message(hardware, mockData),
                MessageLengthException
        );
    }

    SECTION("Test message serialization") {
        std::string data;
        unsigned char d = 0b10101010;
        data.append(1, d);
        Message* msg = new Message(H_RIGHT_MOTOR, data);

        /* Expected string */
        std::string expected;
        expected.append(1, H_RIGHT_MOTOR.address);
        expected += data;

        REQUIRE(msg->serialize() == expected);
    }
}

TEST_CASE("Communicator Tests", "[Communicator]") {

    /* Initialize object */
    MockSensorManager* mockSensorManager = new MockSensorManager();
    MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

    SECTION("Test queuing message") {
        Communicator* comm = new Communicator(mockSensorManager, mockHardwareInterface);

        std::string mockData;
        mockData.append(1, 0b00000000);
        Message* mockMessage = new Message(H_LEFT_MOTOR, mockData);
        comm->queueMessage(mockMessage);

        comm->start();
        usleep(500000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockHardwareInterface->writeMessage == mockMessage);
    }

    SECTION("Test receiving messages") {
        Communicator* comm = new Communicator(mockSensorManager, mockHardwareInterface);

        std::list<Message*>* messages = new std::list<Message*>;
        mockHardwareInterface->setReadMessages(messages);

        comm->start();
        usleep(500000);
        comm->signal(1);
        comm->join();

        REQUIRE(messages == mockSensorManager->getUpdateMessages());

    }

}

TEST_CASE("Chassis tests", "[Chassis]") {

    Chassis *chassis = new Chassis();

    SECTION("Test writing message to left motor.") {
        std::string data;
        data.append(1, 0b00000000);
        Message* testMessage = new Message(H_LEFT_MOTOR, data);

        // TODO: Check that the data has been written to the appropriate registers
        chassis->write(testMessage);
    }

    SECTION("Test writing message to right motor.") {
        std::string data;
        data.append(1, 0b00000000);
        Message* testMessage = new Message(H_RIGHT_MOTOR, data);

        // TODO: Check that the data has been written to the appropriate registers
        chassis->write(testMessage);
    }

    SECTION("Test writing messages to an unsupported hardware throws an exception") {
        std::string data;
        data.append(1, 0b11111111); // 255
        Hardware mockHardware = {0b11111111, 1};
        Message* testMessage = new Message(mockHardware, data);

        REQUIRE_THROWS_AS(
                chassis->write(testMessage),
                NonexistentHardwareException
        );
    }

    SECTION("Test reading message returns empty list") {
        std::list<Message*>* messages = chassis->read();

        REQUIRE(messages->size() == 0);
    }

}
