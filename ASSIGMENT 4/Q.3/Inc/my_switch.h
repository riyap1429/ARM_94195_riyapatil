/*
 * my_switch.h
 *
 *  Created on: Dec 17, 2025
 *      Author: kiran_z6dopa8
 */

#ifndef MY_SWITCH_H_
#define MY_SWITCH_H_


#define BV(n) (1 << (n))

void switch_init(void);
int switch_status(void);
int  switch_press_count(void);
int switch_read(void);



#endif /* MY_SWITCH_H_ */
