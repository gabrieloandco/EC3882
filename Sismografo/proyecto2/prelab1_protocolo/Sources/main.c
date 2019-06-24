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
#include "led2.h"
#include "led_1.h"
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
#include "EInt1.h"
#include "EInt2.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
#include "Bit4.h"
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

int fir(char buffer[9], char coeff[9]){
	  int result;
      //result=coeff[0]*buffer[8]+coeff[1]*buffer[7]+coeff[2]*buffer[6]+coeff[3]*buffer[5]+coeff[4]*buffer[4]+coeff[5]*buffer[3]+coeff[6]*buffer[2]+coeff[7]*buffer[1]+coeff[8]*buffer[0];
      result=coeff[0]*buffer[12]+coeff[1]*buffer[11]+coeff[2]*buffer[10]+coeff[3]*buffer[9]+coeff[4]*buffer[8]+coeff[5]*buffer[7]+coeff[6]*buffer[6]+coeff[7]*buffer[5]+coeff[8]*buffer[4]+coeff[9]*buffer[3]+coeff[10]*buffer[2]+coeff[11]*buffer[1]+coeff[12]*buffer[0];
	  //result=coeff[0]*buffer[20]+coeff[1]*buffer[19]+coeff[2]*buffer[18]+coeff[3]*buffer[17]+coeff[4]*buffer[16]+coeff[5]*buffer[15]+coeff[6]*buffer[14]+coeff[7]*buffer[13]+coeff[8]*buffer[12]+coeff[9]*buffer[11]+coeff[10]*buffer[10]+coeff[11]*buffer[9]+coeff[12]*buffer[8]+coeff[13]*buffer[7]+coeff[14]*buffer[6]+coeff[15]*buffer[5]+coeff[16]*buffer[4]+coeff[17]*buffer[3]+coeff[18]*buffer[2]+coeff[19]*buffer[1]+coeff[20]*buffer[0];
	  return result;
}


void main(void)
{
  /* Write your local variable definition here */
  char value0;
  char value1;
  char mensaje[5];
  //char coeff[9]= {0, -6, 0, 70, 127, 70, 0, -6 ,0};
  //char bufferch1[9]= {0};
  //char bufferch2[9]= {0};
  char coeff[13]= {0, 2, 0, -14, 0, 76, 127 ,76, 0, -14, 0, 2, 0};
  char bufferch1[13]= {0};
  char bufferch2[13]= {0};
  //char coeff[21]= {0, 1, 0, -3, 0, 9, 0, -22, 0, 79, 127, 79, 0, -22, 0, 79, 0, -3, 0, 1, 0};
  //char bufferch1[21]= {0};
  //char bufferch2[21]= {0};
  char filter_order=12;
  int result0;
  int result1;
  int temporal;
  int i;
  bool filter0=1;
  bool filter1=1;
  bool button0=0;
  bool button1=0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  
  /* Write your code here */
  /* For example: for(;;) { } */
  //TI1_DisableEvent();
  activarADC();
 
  while(1){
	  //Cpu_Delay100US(50000);
	  Bit4_PutVal(!Bit4_GetVal());
	  if(flat == 1){
		 flat = 0;
			 
		 AD1_GetChanValue(0,&value0);			 
		 AD1_GetChanValue(1,&value1);
		 led_1_PutVal(filter0);
		 led2_PutVal(filter1);
		 //CH1	 
		 for(i=0; i<filter_order; i++){
		    bufferch1[i]=bufferch1[i+1];
		 	 }
		 bufferch1[filter_order]=value0;
		 
		 filter0=EInt1_GetVal();
		 if (button0){
			 filter0=!filter0;
		 }
		 if(filter0){
		     result0= fir(bufferch1, coeff);
		 }
		 else{
			 result0=value0*255;
		 }
		 //CH2
		 for(i=0; i<filter_order; i++){
		 		    bufferch2[i]=bufferch2[i+1];
		 		 	 }
		 bufferch2[filter_order]=value1;
		 		 
		 filter1=EInt2_GetVal();
		 if (button1){
		 	filter1=!filter1;
		 }
		 if(filter1){
		 	result1= fir(bufferch2, coeff);
		 }
		 else{
		 	result1=value1*255;
		 }
		 mensaje[0]=255;
		 temporal=result0>>8;
		 mensaje[1]=temporal;
		 temporal=result0&&255;
		 mensaje[2]=temporal;
		 temporal=result1>>8;
		 mensaje[3]=temporal;
		 temporal=result1&&255;
		 mensaje[4]=temporal;
		 for(i=0; i<5; i++){
		     enviarMensaje(mensaje[i]);
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
