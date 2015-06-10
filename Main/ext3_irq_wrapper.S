//Dependencies
#include "isr_support.h"

   .global ext3IrqWrapper
   .extern extIntHandler
   .extern xISRStackTop

   .set nomips16
   .set noreorder
   .set noat

   .ent ext3IrqWrapper

//External 3 interrupt
ext3IrqWrapper:
   //Save the current task context
   portSAVE_CONTEXT
   //Call interrupt handler
   jal extIntHandler
   nop
   //Restore the context of the next task to execute
   portRESTORE_CONTEXT

   .end ext3IrqWrapper
