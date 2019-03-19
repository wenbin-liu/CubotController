#ifndef __CONTROL_H
#define __CONTROL_H

#define X_MOTOR_PORT  GPIOA
#define X_MOTOR_PUL_PIN GPIO_PIN_9
#define X_MOTOR_DIR_PIN GPIO_PIN_3

#define Y_MOTOR_PORT GPIOA
#define Y_MOTOR_PUL_PIN GPIO_PIN_10
#define Y_MOTOR_DIR_PIN GPIO_PIN_2

#define CLIP_TIGHT_VAL_X   CLIP_LOOSE_VAL_X-42+3
#define CLIP_TIGHT_VAL_Y   CLIP_LOOSE_VAL_Y-42
#define CLIP_OPEN_VAL_X    CLIP_LOOSE_VAL_X+60
#define CLIP_OPEN_VAL_Y    CLIP_LOOSE_VAL_Y+55
#define CLIP_LOOSE_VAL_X   147-23-3
#define CLIP_LOOSE_VAL_Y   176+3
#define CLIP_HOLD_VAL_X    CLIP_TIGHT_VAL_X
#define CLIP_HOLD_VAL_Y    CLIP_TIGHT_VAL_Y

#define ANGLE90            800
#define ANGLE180           800*2+5  //XIFEN  3200/R

#define open_time    300+150
#define tight_time   300+150
#define turn_time    300+150

#define STEP_INTERVAL     80

void X_MOTOR_PUL_PIN_Init(void);
void Y_MOTOR_PUL_PIN_Init(void);
void X_MOTOR_DIR_PIN_Init(void);
void Y_MOTOR_DIR_PIN_Init(void);


void TURN_X_MOTOR(int step);
void TURN_Y_MOTOR(int step);

void STEER_XY_Init(void);
void MX_TIM2_Init(void);
#define STEER_XY_Init()  MX_TIM2_Init()
void X_STEER_OPEN(void);
void X_STEER_TIGHT(void);
void Y_STEER_OPEN(void);
void Y_STEER_TIGHT(void);
void X_STEER_LOOSE(void);
void Y_STEER_LOOSE(void);
void Y_STEER_HOLD(void);
void X_STEER_HOLD(void);


/*整体装动*/
void X_CLOCKWISE_90(void);
void X_CLOCKWISE_180(void);
void Y_CLOCKWISE_90(void);
void Y_CLOCKWISE_180(void);
void X_ANTICLOCKWISE_90(void);
void X_ANTICLOCKWISE_180(void);
void Y_ANTICLOCKWISE_90(void);
void Y_ANTICLOCKWISE_180(void);
/*面转动*/
void x_CLOCKWISE_90(void);
void x_CLOCKWISE_180(void);
void y_CLOCKWISE_90(void);
void y_CLOCKWISE_180(void);
void x_ANTICLOCKWISE_90(void);
void x_ANTICLOCKWISE_180(void);
void y_ANTICLOCKWISE_90(void);
void y_ANTICLOCKWISE_180(void);

/*XYxy*/
int X_TURN(char cmd);
int x_TURN(char cmd);
int Y_TURN(char cmd);
int y_TURN(char cmd);

void Solve(char * order);
#endif

