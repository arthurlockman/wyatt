////
//// Created by Arthur Lockman on 4/5/17.
////

#include <commands/SimpleIteratorCommand.h>
#include <Communicator.h>
#include <iostream>
#include "../include/CommandManager.h"
#include "../catch/catch.hpp"
#include "../include/IRangeFinderSensor.h"
#include "../include/SensorManager.h"
#include "../include/Chassis.h"
#include <unistd.h>


/* MOCKS */
#include "mocks/include/MockIRRangeFinderSensor.h"
#include "mocks/include/MockSensorManager.h"
#include "mocks/include/MockHardwareInterface.h"
#include "mocks/include/MockIRRangeFinderSensorMessage.h"

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
        unsigned char data = 0;
        MotorMessage* msg = new MotorMessage(H_LEFT_MOTOR, data);
        std::list<IMessage*>* messages = new std::list<IMessage*>;
        messages->push_back(msg);

        REQUIRE_THROWS_AS(
                sensorManager->updateSensors(messages),
                NonexistentHardwareException
        );
    }

    SECTION("Updates sensors correctly") {
        Hardware mockHardware = {255, 1};
        MockIRRangeFinderSensor* mockSensor = new MockIRRangeFinderSensor();
        sensorManager->addSensor(mockHardware, mockSensor);

        std::string data = "255";
        IMessage* msg = new MockIRRangeFinderSensorMessage(mockHardware, data);
        std::list<IMessage*>* messages = new std::list<IMessage*>;
        messages->push_back(msg);

        sensorManager->updateSensors(messages);

        REQUIRE(mockSensor->getData() == data);
    }


}

TEST_CASE("Communicator Tests", "[Communicator]") {

    /* Initialize object */
    MockSensorManager* mockSensorManager = new MockSensorManager();
    MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

    SECTION("Test queuing message") {
        Communicator* comm = new Communicator(mockSensorManager, mockHardwareInterface);

        unsigned char data = 255;
        MotorMessage* mockMessage = new MotorMessage(H_LEFT_MOTOR, data);
        comm->queueMessage(mockMessage);

        comm->start();
        usleep(500000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockHardwareInterface->writeMessage == mockMessage);
    }

    SECTION("Test receiving messages") {
        Communicator* comm = new Communicator(mockSensorManager, mockHardwareInterface);

        std::list<IMessage*>* messages = new std::list<IMessage*>;
        mockHardwareInterface->setReadMessages(messages);

        comm->start();
        usleep(500000);
        comm->signal(1);
        comm->join();

        REQUIRE(messages == mockSensorManager->getUpdateMessages());

    }

}

TEST_CASE("MotorMessage Tests", "[MotorMessage]") {

    unsigned char address = 255;
    Hardware mockHardware = {address, 1};
    unsigned char mockData = 'a';
    MotorMessage* msg = new MotorMessage(mockHardware, mockData);

    SECTION("GetHardware returns proper hardware") {
        REQUIRE(msg->getHardware() == mockHardware);
    }

    SECTION("GetData returns proper data") {
        REQUIRE(msg->getData() ==  mockData);
    }

    SECTION("Not enough data throws MessageLengthException") {
        // Expect 2 bytes, given 1
        Hardware mockHardware = {address, 2};

        REQUIRE_THROWS_AS(
                new MotorMessage(mockHardware, mockData),
                MessageLengthException
        );
    }

    SECTION("Too much data throws MessageLengthException") {
        // Expect 0 bytes, given 1
        Hardware mockHardware = {address, 0};

        REQUIRE_THROWS_AS(
            new MotorMessage(mockHardware, mockData),
            MessageLengthException
        );
    }

    SECTION("Serialize to proper string") {
        std::string serial;
        serial.append(1, address);
        serial.append(1, mockData);

        REQUIRE(msg->serialize() == serial);
    }


    SECTION("Destructor") {
        delete msg;
    }

}

TEST_CASE("EncoderMessage Tests", "[EncoderMessage]") {
    unsigned char address = 255;
    Hardware mockHardware = {address, 8};
    double mockData = 128.0;
    EncoderMessage* msg = new EncoderMessage(mockHardware, mockData);

    SECTION("GetHardware returns proper hardware") {
        REQUIRE(msg->getHardware() == mockHardware);
    }

    SECTION("GetData returns proper data") {
        REQUIRE(msg->getData() ==  mockData);
    }

    SECTION("Not enough data throws MessageLengthException") {
        // Expect 10 bytes, given 8
        Hardware mockHardware = {address, 10};

        REQUIRE_THROWS_AS(
                new EncoderMessage(mockHardware, mockData),
                MessageLengthException
        );
    }

    SECTION("Too much data throws MessageLengthException") {
        // Expect 0 bytes, given 1
        Hardware mockHardware = {address, 0};

        REQUIRE_THROWS_AS(
                new EncoderMessage(mockHardware, mockData),
                MessageLengthException
        );
    }

    SECTION("Serialize to proper string") {
        std::string serial;
        serial.append(1, address);
        serial.append((char*)(&mockData), 8);

        // Serialized data is expected
        REQUIRE(msg->serialize() == serial);

        // Unserialized data is unchanged
        // Need to move pointer forward 1 byte to skip over the address
        double data = *((double*)(serial.c_str() + (unsigned char)1));
        REQUIRE(data == mockData);
    }


    SECTION("Destructor") {
        delete msg;
    }
}

TEST_CASE("Chassis tests", "[Chassis]") {

    Chassis *chassis = new Chassis();

    SECTION("Test writing message to left motor.") {
        unsigned char data = 0;
        MotorMessage* testMessage = new MotorMessage(H_LEFT_MOTOR, data);

        // TODO: Check that the data has been written to the appropriate registers
        chassis->write(testMessage);
    }

    SECTION("Test writing message to right motor.") {
        unsigned char data = 0;
        MotorMessage* testMessage = new MotorMessage(H_RIGHT_MOTOR, data);

        // TODO: Check that the data has been written to the appropriate registers
        chassis->write(testMessage);
    }

    SECTION("Test writing messages to an unsupported hardware throws an exception") {
        unsigned char data = 0;
        Hardware mockHardware = {0b11111111, 1};
        MotorMessage* testMessage = new MotorMessage(mockHardware, data);

        REQUIRE_THROWS_AS(
                chassis->write(testMessage),
                NonexistentHardwareException
        );
    }

    SECTION("Test reading message returns empty list") {
        std::list<IMessage*>* messages = chassis->read();

        REQUIRE(messages->size() == 0);
    }

}
