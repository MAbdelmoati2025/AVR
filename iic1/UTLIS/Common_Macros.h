#ifndef UTLIS_COMMOM_MACROS_H_
#define UTLIS_COMMOM_MACROS_H_

#define SET_BIT(REG_Name,PIN_NO) REG_Name |= (1<<PIN_NO)			//Macro to set certain bit in certain register
#define CLEAR_BIT(REG_Name,PIN_NO) REG_Name &= (~(1<<PIN_NO))		//Macro to set certain bit in certain register
#define TOGGLE_BIT(REG_Name,PIN_NO) REG_Name ^= (1<<PIN_NO)			//Macro to set certain bit in certain register
#define BIT_IS_SET(REG_Name,PIN_NO) (REG_Name & (1<<PIN_NO))		//Macro to check if certain bit is set
#define BIT_IS_CLEAR(REG_Name,PIN_NO) (!(REG_Name & (1<<PIN_NO)))	//Macro to check if certain bit is clear

#endif
