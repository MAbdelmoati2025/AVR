/******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Created on: ٢٥‏/٠٩‏/٢٠٢٣
 *
 * Description: Commonly used Macros
 *
 * Author: Mohamed A.Abdelmoati
 *
 *******************************************************************************/

#ifndef COMMON_MACROS
#define COMMON_MACROS

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT))

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))

/* Rotate right the register value with a specific number of rotates */
#define ROR_SWAP_PART(REG,BIT) (REG = ( REG >> BIT ) | ( REG << (8-BIT)))

/* Rotate left the register value with a specific number of rotates */
#define ROL_SWAP_CIRCLE(REG,BIT) (REG = ( REG << BIT ) | ( REG >> (8-BIT)))

/* Get the value of a specific bit in any register */
#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT )

#endif /* COMMON_MACROS */
