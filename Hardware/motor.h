#ifndef __MOTOR_H
#define __MOTOR_H

void Fast_forward(unsigned char a);
void Forward(unsigned int left,unsigned int right,unsigned char a);
void turn(unsigned int left,unsigned int right);
void stop(void);
void back(unsigned char a);
void turn(unsigned int left,unsigned int right);

void turn_back();
void turn_back_r();

void turn_left_150(void);
void turn_left_90(void);
void turn_left_45(void);
void turn_left_120(void);

void turn_right_90(void);
void turn_right_150(void);
void turn_right_45(void);
void turn_right_120(void);
void fast_turn_right_90(void);
void turn_r(unsigned int left,unsigned int right);


#endif
