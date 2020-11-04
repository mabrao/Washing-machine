

// Define function prototypes
void Stepper_Drive(char mode,uint8_t revolutions);
void Motor_Control (char mode, uint8_t mTime);
void Stepper_Drive_Time(char mode,uint8_t t);
//void io_init(void);
// Define
//#define PushButton (PINA & 0x07) //use the toggle switch to control the type of stepping, use bit masking
#define Wave_Step 0x01
#define Full_Step 0x02
#define Half_Step 0x04
//global variables can’t define the array in .h file
extern uint8_t Wave[4];
extern uint8_t Full[4];
extern uint8_t Half[8];