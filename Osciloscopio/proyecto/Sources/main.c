/* ###################################################################
**     Filename    : main.c
**     Project     : prelab1
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-02-06, 14:56, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
#include "Bit4.h"
#include "led_1.h"
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
char flat = 0;

void enviarMensaje(char msj){
	char error;
	 do{
				 error = AS1_SendChar(msj);
			 }while(error!=ERR_OK);
}


void activarADC(void){
	char error;
	 do{
		   error = AD1_Start();

			 }while(error!=ERR_OK);
}



void main(void)
{
  /* Write your local variable definition here */
  int value0;
  int value1;
  char mensaje[4];
  int header;
  int mask;
  int temporal;
  int i;
  int d1;
  int d2;
  int d3=0;
  int d4=0;
  int i3=0;
  int i4=0;
  int state_change_3=0;
  int state_change_4=0;
  char handshake;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  
  /* Write your code here */
  /* For example: for(;;) { } */
  //TI1_DisableEvent();
  activarADC();
 
  while(1){
	  //Cpu_Delay100US(50000);
	  
	  if(flat == 1){
		 flat = 0;
		 //AS1_RecvChar(&handshake);
		 
		 handshake='s';
		 if (handshake=='s'){
			 
			 AD1_GetChanValue(0,&value0);			 
			 AD1_GetChanValue(1,&value1);
			 led_1_NegVal();
			 
			 mask=0b00111111;
			 //d1=Bit1_GetVal();
			 //d1=d1<<6;
			 //mask=mask|d1;
			 temporal=value0 >> 6;
			 temporal= temporal&mask;
			 //temporal=temporal;
			 mensaje[0]=temporal;
		 
			 header=0b10;
			 mask=0x3f;
			 //d2=Bit2_GetVal();
			 //header=d2|header;
			 temporal=value0 & mask;
			 temporal= (header << 6) | temporal;
			 mensaje[1]=temporal;
		 
			 header=0b10;
			 i3=Bit3_GetVal();
			 if(i3==0){ d3=0;}
			 else {d3=1;}
			 d3 =0;
			 header=d3|header;
			 temporal=value1 >> 6;
			 temporal= (header << 6) | temporal;
			 mensaje[2]=temporal;
		 
			 header=0b10;
			 i4=Bit4_GetVal();
			 if(i4==0){ d4=0;}
			 else {d4=1;}
			 d4 =0;
			 header=d4|header;
			 mask=0x3f;
			 temporal=value1 & mask;
			 temporal= (header << 6) | temporal;
			 mensaje[3]=temporal;

			 for(i=0; i<4; i++){
			 
				 enviarMensaje(mensaje[i]);
			 }
		 }
	  }
  }
	  
  
  //TI1_EnableEvent();
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
