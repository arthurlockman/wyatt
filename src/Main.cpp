#include "Main.h"

int main (void)
{
    // Setup WiringPi 
    wiringPiSetup();

    // Create robot command manager
//    CommandManager* m_commandManager = new CommandManager();

    // Create robot chassis object
//    Chassis* m_chassis = new Chassis();
//    EncoderCounter* m_rightEncoderCounter = new EncoderCounter(3, 4, 64, H_RIGHT_ENCODER);
//    EncoderCounter* m_leftEncoderCounter = new EncoderCounter(1, 2, 64, H_LEFT_ENCODER);

    // Temporary, testing drive
//    DriveForwardSecondsCommand* tmp_driveCmd = new DriveForwardSecondsCommand(m_chassis, 5.0);
//    m_commandManager->runCommand(tmp_driveCmd);

    // Wait for command to finish
//    while (!tmp_driveCmd->isFinished()) {
//        std::list<Message*>* chassisMessages = m_chassis->read();
//
//        while(!chassisMessages->empty()) {
//
//            Message* msg = chassisMessages->front();
//            if( (msg->getHardware()).address == LEFT_ENCODER_ADDRESS) {
//                const char* charArray = (msg->getMessage()).c_str();
//                double left = *((double*)charArray);
//                std::cout << "Left: " << left << std::endl;
//            }
//
//            if( (msg->getHardware()).address == RIGHT_ENCODER_ADDRESS) {
//                const char* charArray = (msg->getMessage()).c_str();
//                double right = *((double*)charArray);
//                std::cout << "Right: " << right << std::endl;
//            }
//
//            delete msg;
//            chassisMessages->pop_front();
//        }
//        delete chassisMessages;
//    }

    //Kill command manager.
//    m_commandManager->kill();

    return 0 ;
}

