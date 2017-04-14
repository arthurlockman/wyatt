#pragma once

int wiringPiI2CRead           (int fd) ;
int wiringPiI2CReadReg8       (int fd, int reg) ;
int wiringPiI2CReadReg16      (int fd, int reg) ;

int wiringPiI2CWrite          (int fd, int data) ;
int wiringPiI2CWriteReg8      (int fd, int reg, int data) ;
int wiringPiI2CWriteReg16     (int fd, int reg, int data) ;

int wiringPiI2CSetupInterface (const char *device, int devId) ;
int wiringPiI2CSetup          (const int devId) ;

