//
// Created by Arthur Lockman on 4/5/17.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <commands/SimpleIteratorCommand.h>
#include "../include/CommandManager.h"
#include "../catch/catch.hpp"
#include "../include/ISensor.h"
#include "../include/IRangeFinderSensor.h"
#include "../include/RawSensorData.h"

/* MOCKS */
#include "MockIRRangeFinderSensor.h"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}


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
        while (!sc1->isFinished() && !sc2->isFinished()) {}
        REQUIRE(sc1->getCount() == 10);
        REQUIRE(sc2->getCount() == 20);
        commandManager1->kill();
    }
}

TEST_CASE("Sensor interface tests", "[ISensor]") {

    RawSensorData* mockRawSensorData_IR = new RawSensorData("12.2");

    SECTION("ISensor polymorphically updates") {
        ISensor* sensor = new MockIRRangeFinderSensor();
        sensor->updateSensor(mockRawSensorData_IR);
        MockIRRangeFinderSensor* IRSensor = (MockIRRangeFinderSensor*) sensor;
         
        REQUIRE( IRSensor->getDistanceCM() == 12.2 );
    }

}

TEST_CASE("RawSensorData tests", "[RawSensorData]") {

    std::string testString = "testString";

    SECTION("Data is correctly encapsulated and returned") {
        RawSensorData* data = new RawSensorData(testString);

        REQUIRE(data->getData() == testString);
    }
}


TEST_CASE("ISensor Manager tests", "[ISensorManager]") {




}

TEST_CASE() {


}
