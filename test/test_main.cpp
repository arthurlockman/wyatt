////
//// Created by Arthur Lockman on 4/5/17.
////

#include <commands/SimpleIteratorCommand.h>
#include <Communicator.h>
#include "../include/CommandManager.h"
#include "../catch/catch.hpp"
#include "../include/IRangeFinderSensor.h"
#include "../include/SensorManager.h"
#include "../include/Chassis.h"
#include "../include/MotorAdapter.h"
#include "../include/EncoderSensor.h"
#include "../include/DataSizeException.h"
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
        int data = FULL_FORWARD;
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

    SECTION("Destructor") {
        delete sensorManager;
    }
}

TEST_CASE("Communicator Tests", "[Communicator]") {

    /* Initialize object */
    MockSensorManager* mockSensorManager = new MockSensorManager();
    Communicator* comm = new Communicator(mockSensorManager);

    SECTION("Test queuing message for single hardware interface") {

        Hardware mockHardware = {255, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();
        std::list<IMessage*>* readMessages = new std::list<IMessage*>;
        mockHardwareInterface->setReadMessages(readMessages);

        /* Register hardware */
        comm->registerHardware(mockHardware, mockHardwareInterface);

        /* Compose a mock message */
        int mockData = FULL_FORWARD;
        IMessage* mockMessage = new MotorMessage(mockHardware, mockData);

        /* Queue message and wait for it to be sent */
        comm->queueMessage(mockMessage);
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();
        REQUIRE(mockHardwareInterface->getWriteMessages()->size() == 1);
        REQUIRE(mockHardwareInterface->getWriteMessages()->front() == mockMessage);
    }

    SECTION("Test queuing messages for multiple hardware interfaces") {
        Hardware mockHardware1 = {255, sizeof(int)};
        Hardware mockHardware2 = {254, sizeof(int)};

        MockHardwareInterface* mockHardwareInterface1 = new MockHardwareInterface();
        MockHardwareInterface* mockHardwareInterface2 = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware1, mockHardwareInterface1);
        comm->registerHardware(mockHardware2, mockHardwareInterface2);

        /* Compose a mock message */
       int data1 = FULL_FORWARD, data2 = FULL_BACKWARD;
        IMessage* mockMessage1 = new MotorMessage(mockHardware1, data1);
        IMessage* mockMessage2 = new MotorMessage(mockHardware2, data2);

        /* Queue message and wait for it to be sent */
        comm->queueMessage(mockMessage1);
        comm->queueMessage(mockMessage2);
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockHardwareInterface1->getWriteMessages()->size() == 1);
        REQUIRE(mockHardwareInterface2->getWriteMessages()->size() == 1);

        REQUIRE(mockHardwareInterface1->getWriteMessages()->front() == mockMessage1);
        REQUIRE(mockHardwareInterface2->getWriteMessages()->front() == mockMessage2);
    }

    SECTION("Test receiving message from single hardware interface") {
        Hardware mockHardware = {255, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware, mockHardwareInterface);

        /* Compose a mock message */
        int data = FULL_FORWARD;
        IMessage* mockMessage = new MotorMessage(mockHardware, data);
        std::list<IMessage*>* messages = new std::list<IMessage*>;
        messages->push_back(mockMessage);
        mockHardwareInterface->setReadMessages(messages);

        /* Wait for it to be read */
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockSensorManager->updateMessages->size() == 1);
        REQUIRE(mockSensorManager->updateMessages->front() == mockMessage);
    }

    SECTION("Test receiving messages from multiple hardware interfaces") {
        Hardware mockHardware1 = {255, sizeof(int)};
        Hardware mockHardware2 = {254, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface1 = new MockHardwareInterface();
        MockHardwareInterface* mockHardwareInterface2 = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware1, mockHardwareInterface1);
        comm->registerHardware(mockHardware2, mockHardwareInterface2);

        /* Compose a mock message */
        int data1 = FULL_FORWARD, data2 = FULL_BACKWARD;
        IMessage* mockMessage1 = new MotorMessage(mockHardware1, data1);
        IMessage* mockMessage2 = new MotorMessage(mockHardware2, data2);
        std::list<IMessage*>* messages1 = new std::list<IMessage*>;
        messages1->push_back(mockMessage1);
        std::list<IMessage*>* messages2 = new std::list<IMessage*>;
        messages2->push_back(mockMessage2);

        mockHardwareInterface1->setReadMessages(messages1);
        mockHardwareInterface2->setReadMessages(messages2);

        /* Wait for it to be read */
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockSensorManager->updateMessages->size() == 2);

        REQUIRE(mockSensorManager->updateMessages->front() == mockMessage1);
        mockSensorManager->updateMessages->pop_front();
        REQUIRE(mockSensorManager->updateMessages->front() == mockMessage2);
    }

    SECTION("Test throws duplicate hardware exception when hardware with the same address is registered more than once.") {
        Hardware mockHardware1 = {255, sizeof(int)};
        Hardware mockHardware2 = {255, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware1, mockHardwareInterface);

        REQUIRE_THROWS_AS(
                comm->registerHardware(mockHardware2, mockHardwareInterface),
                DuplicateHardwareException
        );
    }

    SECTION("Test queue list of messages sent to single interface") {
        Hardware mockHardware = {255, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware, mockHardwareInterface);

        /* Compose two mock messages */
        int data1 = FULL_FORWARD, data2 = FULL_BACKWARD;
        IMessage* mockMessage1 = new MotorMessage(mockHardware, data1);
        IMessage* mockMessage2 = new MotorMessage(mockHardware, data2);
        std::list<IMessage*>* messages = new std::list<IMessage*>;
        messages->push_back(mockMessage1);
        messages->push_back(mockMessage2);

        /* Queue message and wait for them to be sent */
        comm->queueMessage(messages);
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockHardwareInterface->getWriteMessages()->size() == 2);

        REQUIRE(mockHardwareInterface->getWriteMessages()->front() == mockMessage1);
        mockHardwareInterface->getWriteMessages()->pop_front();
        REQUIRE(mockHardwareInterface->getWriteMessages()->front() == mockMessage2);
    }

    SECTION("Test queue list of messages sent to multiple interfaces") {
        Hardware mockHardware1 = {255, sizeof(int)};
        Hardware mockHardware2 = {254, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface1 = new MockHardwareInterface();
        MockHardwareInterface* mockHardwareInterface2 = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware1, mockHardwareInterface1);
        comm->registerHardware(mockHardware2, mockHardwareInterface2);

        /* Compose two mock messages */
        int data1 = FULL_FORWARD, data2 = FULL_BACKWARD;
        IMessage* mockMessage1 = new MotorMessage(mockHardware1, data1);
        IMessage* mockMessage2 = new MotorMessage(mockHardware2, data2);
        std::list<IMessage*>* messages = new std::list<IMessage*>;
        messages->push_back(mockMessage1);
        messages->push_back(mockMessage2);

        /* Queue message and wait for them to be sent */
        comm->queueMessage(messages);
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockHardwareInterface1->getWriteMessages()->size() == 1);
        REQUIRE(mockHardwareInterface2->getWriteMessages()->size() == 1);

        REQUIRE(mockHardwareInterface1->getWriteMessages()->front() == mockMessage1);
        REQUIRE(mockHardwareInterface2->getWriteMessages()->front() == mockMessage2);
    }

    SECTION("Test queuing multiple messages for different hardware sent to the same hardware interface") {
        Hardware mockHardware1 = {255, sizeof(int)};
        Hardware mockHardware2 = {254, sizeof(int)};
        MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

        /* Register hardware */
        comm->registerHardware(mockHardware1, mockHardwareInterface);
        comm->registerHardware(mockHardware2, mockHardwareInterface);

        /* Compose two mock messages */
        int data1 = FULL_FORWARD, data2 = FULL_BACKWARD;
        IMessage* mockMessage1 = new MotorMessage(mockHardware1, data1);
        IMessage* mockMessage2 = new MotorMessage(mockHardware2, data2);
        std::list<IMessage*>* messages = new std::list<IMessage*>;
        messages->push_back(mockMessage1);
        messages->push_back(mockMessage2);

        /* Queue message and wait for them to be sent */
        comm->queueMessage(messages);
        comm->start();
        usleep(100000);
        comm->signal(1);
        comm->join();

        REQUIRE(mockHardwareInterface->getWriteMessages()->size() == 2);

        REQUIRE(mockHardwareInterface->getWriteMessages()->front() == mockMessage1);
        mockHardwareInterface->getWriteMessages()->pop_front();
        REQUIRE(mockHardwareInterface->getWriteMessages()->front() == mockMessage2);
    }

    SECTION("Destructor") {
        delete comm;
    }

}

TEST_CASE("MotorMessage Tests", "[MotorMessage]") {

    unsigned char address = 255;
    Hardware mockHardware = {address, sizeof(int)};
    int mockData = FULL_FORWARD;
    MotorMessage* msg = new MotorMessage(mockHardware, mockData);

    SECTION("GetHardware returns proper hardware") {
        REQUIRE(msg->getHardware() == mockHardware);
    }

    SECTION("GetData returns proper data") {
        REQUIRE(msg->getData() ==  mockData);
    }

    SECTION("Not enough data throws MessageLengthException") {
        // Expect 5 bytes, given 4
        Hardware mockHardware = {address, 2};

        REQUIRE_THROWS_AS(
                new MotorMessage(mockHardware, mockData),
                MessageLengthException
        );
    }

    SECTION("Too much data throws MessageLengthException") {
        // Expect 0 bytes, given 4
        Hardware mockHardware = {address, 0};

        REQUIRE_THROWS_AS(
            new MotorMessage(mockHardware, mockData),
            MessageLengthException
        );
    }

    SECTION("Serialize to proper string") {
        std::string serial;
        serial.append(1, address);
        serial.append((char*)(&mockData), sizeof(int));

        REQUIRE(msg->serialize() == serial);
        int unserializeData = *((int*)(serial.c_str() + sizeof(char)));
        REQUIRE(unserializeData == mockData);
    }

    SECTION("Data too large throws DataSizeException") {
        REQUIRE_THROWS_AS(
            new MotorMessage(mockHardware, FULL_FORWARD + 1),
            DataSizeException
        );
    }

    SECTION("Data too small throws DataSizeException") {
        REQUIRE_THROWS_AS(
                new MotorMessage(mockHardware, FULL_BACKWARD - 1),
                DataSizeException
        );
    }

    SECTION("Destructor") {
        delete msg;
    }

}

TEST_CASE("EncoderMessage Tests", "[EncoderMessage]") {
    unsigned char address = 255;
    Hardware mockHardware = {address, sizeof(double)};
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
        serial.append((char*)(&mockData), sizeof(double));

        // Serialized data is expected
        REQUIRE(msg->serialize() == serial);

        // Unserialized data is unchanged
        // Need to move pointer forward 1 byte to skip over the address
        double data = *((double*)(serial.c_str() + sizeof(char)));
        REQUIRE(data == mockData);
    }


    SECTION("Destructor") {
        delete msg;
    }
}

TEST_CASE("MotorAdapter Tests", "[MotorAdapter]") {

    int forwardPin = 1, backwardPin = 2;
    AdafruitPWMServoHat* m_pwmHat = new AdafruitPWMServoHat();
    MotorAdapter* adapter = new MotorAdapter(m_pwmHat, forwardPin, backwardPin);
    Hardware hardware = H_RIGHT_MOTOR;

    SECTION("Read returns empty list. Cannot read motors.") {
        REQUIRE(adapter->read()->size() == 0);
    }

    SECTION("Drive the motor full backwards") {
        int speed = FULL_BACKWARD;
        IMessage* msg = new MotorMessage(hardware, speed);
        adapter->write(msg);

        // TODO: Check that the appropriate register has been written
    }

    SECTION("Drive the motor full forwards") {
        int speed = FULL_FORWARD;
        IMessage* msg = new MotorMessage(hardware, speed);
        adapter->write(msg);

        // TODO: Check that the appropriate register has been written
    }

    SECTION("MismatchedMessageException thrown when message of wrong type is passed in") {
        IMessage* msg = new EncoderMessage(H_RIGHT_ENCODER, 10.0);

        REQUIRE_THROWS_AS(
          adapter->write(msg),
          MismatchedMessageException
        );
    }

    SECTION("Destructor") {
        delete adapter;
    }


}

TEST_CASE("EncoderAdapter Tests", "[EncoderAdapter]") {

    Hardware mockHardware = {255, 8};
    int ticksPerRev = 100;
    int channelA = 0, channelB = 1;
    EncoderAdapter* adapter = new EncoderAdapter(channelA, channelB, ticksPerRev, mockHardware);

    SECTION("Destructor") {
        delete adapter;
    }
}

TEST_CASE("EncoderSensor Tests", "[EncoderSensor]") {

    EncoderSensor* sensor = new EncoderSensor();

    SECTION("Sensor value updates correctly") {
        double data = 1000;
        double expectedRPM = data * GEAR_RATIO;
        IMessage* msg = new EncoderMessage(H_LEFT_ENCODER, data);
        sensor->updateSensor(msg);

        REQUIRE(sensor->getRPM() == expectedRPM);

    }

    SECTION("MismatchMessageException thrown if wrong message type sent to encoder") {
        IMessage* msg = new MotorMessage(H_RIGHT_MOTOR, FULL_FORWARD);

        REQUIRE_THROWS_AS(
            sensor->updateSensor(msg),
            MismatchedMessageException
        );
    }

    SECTION("Destructor") {
        delete sensor;
    }
}