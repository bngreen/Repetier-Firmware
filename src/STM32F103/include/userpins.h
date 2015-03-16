#define CPU_ARCH ARCH_ARM
/*****************************************************************
* STM32F103 Pin Assignments
******************************************************************/

#define ORIG_X_STEP_PIN     10
#define ORIG_X_DIR_PIN      11
#define ORIG_X_MIN_PIN      45
#define ORIG_X_MAX_PIN      13
#define ORIG_X_ENABLE_PIN   12

#define ORIG_Y_STEP_PIN     25
#define ORIG_Y_DIR_PIN      26
#define ORIG_Y_MIN_PIN      28
#define ORIG_Y_MAX_PIN      29
#define ORIG_Y_ENABLE_PIN   27

#define ORIG_Z_STEP_PIN     32
#define ORIG_Z_DIR_PIN      33
#define ORIG_Z_MIN_PIN      46
#define ORIG_Z_MAX_PIN      -1
#define ORIG_Z_ENABLE_PIN   20

// Note that on the Due pin A0 on the board is channel 2 on the ARM chip
#define HEATER_0_PIN     21
#define TEMP_0_PIN       18 // Due analog pin #54
#define HEATER_1_PIN     22
#define TEMP_1_PIN       19 // Due analog pin #58
#define HEATER_2_PIN     -1
#define TEMP_2_PIN       -1 // Due analog pin #55
#define HEATER_3_PIN     -1
#define TEMP_3_PIN       -1 // Due analog pin #56
#define TEMP_4_PIN       -1 // Due analog pin #57

#define ORIG_E0_STEP_PIN    41 // A7
#define ORIG_E0_DIR_PIN     42 // A6
#define ORIG_E0_ENABLE_PIN  43 // A8

#define ORIG_E1_STEP_PIN    -1 // A10
#define ORIG_E1_DIR_PIN     -1 // A9
#define ORIG_E1_ENABLE_PIN  -1 // A11

#define ORIG_E2_STEP_PIN    -1
#define ORIG_E2_DIR_PIN     -1
#define ORIG_E2_ENABLE_PIN  -1

#define ORIG_E3_STEP_PIN    -1
#define ORIG_E3_DIR_PIN     -1
#define ORIG_E3_ENABLE_PIN  -1

#define ORIG_E4_STEP_PIN    -1
#define ORIG_E4_DIR_PIN     -1
#define ORIG_E4_ENABLE_PIN  -1

#define SDSUPPORT      0
#define SDPOWER 	   -1
#define SDSS		    -1// 4,10,52 if using HW SPI.
#define SDCARDDETECT       -1
#define SDCARDDETECTINVERTED 0
#define LED_PIN 	   -1
#define ORIG_FAN_PIN 	   -1
#define ORIG_FAN2_PIN           -1
#define ORIG_PS_ON_PIN          -1
#define KILL_PIN	   -1
#define SUICIDE_PIN    -1  //PIN that has to be turned on right after start, to keep power flowing.

#define SDA_PIN 				-1  	// 20 or 70
#define SCL_PIN 				-1  	// 21 or 71


#define E0_PINS ORIG_E0_STEP_PIN,ORIG_E0_DIR_PIN,ORIG_E0_ENABLE_PIN,
#define E1_PINS ORIG_E1_STEP_PIN,ORIG_E1_DIR_PIN,ORIG_E1_ENABLE_PIN,
#define E2_PINS ORIG_E2_STEP_PIN,ORIG_E2_DIR_PIN,ORIG_E2_ENABLE_PIN,
#define E3_PINS ORIG_E3_STEP_PIN,ORIG_E3_DIR_PIN,ORIG_E3_ENABLE_PIN,
#define E4_PINS ORIG_E4_STEP_PIN,ORIG_E4_DIR_PIN,ORIG_E4_ENABLE_PIN,

#define TWI_CLOCK_FREQ          400000
// see eeprom device data sheet for the following values these are for 24xx256
#define EEPROM_SERIAL_ADDR      0x50   // 7 bit i2c address (without R/W bit)
#define EEPROM_PAGE_SIZE        64     // page write buffer size
#define EEPROM_PAGE_WRITE_TIME  7      // page write time in milliseconds (docs say 5ms but that is too short)
// specify size of eeprom address register
// TWI_MMR_IADRSZ_1_BYTE for 1 byte, or TWI_MMR_IADRSZ_2_BYTE for 2 byte
#define EEPROM_ADDRSZ_BYTES     TWI_MMR_IADRSZ_2_BYTE
#define EEPROM_AVAILABLE 0

