
//tyre IDs for vehicle....(may need to prefix known IDs with leading 'F' to match reception)
  #define FRONT_LEFT   0x03C387594  
  #define FRONT_RIGHT  0x03C387ECD
  //#define REAR_RIGHT   0x03C388924
  #define REAR_RIGHT   0x0AC114501
  #define REAR_LEFT    0x03C3888AD  
  #define SPARE        0x01FFFFFFL
  #define WINTER_FRONT_LEFT   0x02721EB0L
  #define WINTER_FRONT_RIGHT  0x0272221FL
  #define WINTER_REAR_RIGHT   0x0272223EL
  #define WINTER_REAR_LEFT    0x02721E9AL 
  #define WINTER_SPARE        0x0FFFFFFFL


//Select the display type being used:
#define USE_1_INCH_YB_I2C_DISPLAY 1
//#define USE_2_INCH_ST7735_DISPLAY 1
//#define USE_2_INCH_ST7789_DISPLAY 1  //(round display)
//#define USE_24_INCH_ILI9341_DISPLAY 1


//Receive frequency
//#define UK_433MHz 1
#define US_315MHz 1

//Vehicle/sensor type
#define Toyota_TRW_C070 1
//#define Toyota_PMV_C210 1   //Toyota Auris, should also work for PMV-C010?? and PMV-C215 (Toyota Corolla)
//#define Hyundai_i35 1  //uses PMV-C210 sensor
//#define Schrader_C1100 1  //used on Hyundai Tucson TL/TLE 01/2015-12/2015
//#define Schrader_A9054100 1
//#define Toyota_PMV_107J 1   //used on Lexus RX series 07/2013-09/2015
//#define Renault 1
//#define Zoe 1   //for Renault Zoe 09/2012 to 06/2019 only (you must select 'Renault' define as well for this!)
//#define Dacia 1
//#define NissanLeaf 1
//#define Citroen 1
//#define PontiacG82009 1
//#define TruckSolar 1
//#define JansiteSolar 1 
//#define Subaru 1


//#define Ford 1

//Possible Ford variants..
//#define Ford_FSeries_SD 1
//#define Ford_FSeries_2006_2008 1
//#define Ford_ESeries_TEST 1
//#define Ford_OtherVariants 1



//#define Jansite 1  //requires bigger buffer sizes - won't work on Micro or Nano?
 


#ifdef Ford_FSeries_SD
   #define FordType 2
#elif Ford_FSeries_2006_2008
   #define FordType 1
#elif Ford_ESeries_TEST
   #define FordType 3
#else
   #define FordType 0
#endif



////#define INCLUDESPARETYRE 1    - nolonger used. If no spare with TPMS, just set the ID to 0xFFFFFFF
//#define INCLUDE_WINTER_SET 1

//Pressure display and limits units (default is PSI and deg C if these not set)
//#define DISPLAY_PRESSURE_AS_BAR 1
//#define DISPLAY_PRESSURE_AS_KPA 1
//#define DISPLAY_TEMP_AS_FAHRENHEIT 1  //if uncommented,temperature is displayed as deg F, otherwise displayed as deg C

#define ENABLE_PRESSURE_ALARMS 1
#define ENABLE_TEMPERATURE_ALARMS 1

//#define ENABLE_AUDIBLE_ALARM 1

#define ENABLE_PRESSURE_ALARM_TEMPERATURE_COMPENSATION 1


#if defined(USE_2_INCH_ST7735_DISPLAY) || defined(USE_2_INCH_ST7789_DISPLAY) || defined(USE_1_INCH_YB_I2C_DISPLAY)  || defined(USE_24_INCH_ILI9341_DISPLAY)
   #define USE_LCDDISPLAY 1
#endif

//config checks...

#if defined(UK_433MHz) && defined(US_315MHz)
   #error Cannot define both 433MHz and 315MHz simultaneously
#endif

#if !defined(UK_433MHz) && !defined(US_315MHz)
   #error Must define either 433MHz or 315MHz
#endif


#if defined(USE_LCDDISPLAY) && (defined(USE_2_INCH_ST7735_DISPLAY) || defined(USE_2_INCH_ST7789_DISPLAY)  || defined(USE_24_INCH_ILI9341_DISPLAY)) && defined(ARDUINO_AVR_PROMICRO)
   #error ProMicro does not have enough memory for this display!
#endif


int Ford_SensorType = FordType;  //3 different types seen, select 0,1,2 to match the pressure readings


//Settings for pressure and temperature limits (including Winter tyres if required). Used as flashing warnings on display and audible alarm if enabled in hardware

// All pressure settings below are in PSI
// All temp settings are in Celsius

const float PressureLimitsTemperature = 20;
const  double PressureLowLimits[]
{
  28, 28, 
  28, 28,
  28
  #ifdef INCLUDE_WINTER_SET
    , 30, 30, 
    30, 30,
    30
  #endif
};

const double  PressureHighLimits[]
{
  39, 39, 
  39, 39,
  39
  #ifdef INCLUDE_WINTER_SET
    , 39, 39, 
    39, 39,
    39
  #endif
};

//set temperature limits to Fahrenheit or Centigrade depending on DISPLAY_TEMP_AS_FAHRENHEIT setting (will be converted to centigrade when loading if required)
const float  TemperatureLowLimits[]
{
  -10, -10, 
  -10, -10,
  -10
  #ifdef INCLUDE_WINTER_SET
    , -20, -20, 
    -20, -20,
    -20
  #endif
};

const float  TemperatureHighLimits[]
{
  46, 46, 
  46, 46,
  46
  #ifdef INCLUDE_WINTER_SET
    , 33, 33, 
    33, 33,
    33
  #endif
};
