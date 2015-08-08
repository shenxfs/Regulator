/**
*/
#include "config.h"
#define DELAY_TICKS (F_CPU/50) 
static const __flash int16_t regtab[15]={
82,247,394,498,577,644,699,748,788,826,862,893,921,938,972
};
volatile  int16_t times;

ISR(TIMER1_OVF_vect )
{
  times ++;
  if(times > 7812)
    {
    times = 0;
//    LED_PORT ^= _BV(LED_PIN);
    }
  LED_PORT |= _BV(LED_PIN);
}

ISR(TIMER1_COMPA_vect)
{
  LED_PORT &= ~_BV(LED_PIN);
}

int main(void)
{
  int16_t ind,del;
  hw_init();
  ind = 0;
  del = 0;
  OCR1A =  regtab[0];
  while(1)
    {
#ifdef BOARDHIGH
    if((BOARD_IN & _BV(BOARD_PIN)) == _BV(BOARD_PIN))
#else   
    if((BOARD_IN & _BV(BOARD_PIN)) != _BV(BOARD_PIN))
#endif
          {
      if((KEY_IN & KEY_MASK) != KEY_MASK)
              {
        __builtin_avr_delay_cycles (DELAY_TICKS);
        if((KEY_IN & KEY_MASK) != KEY_MASK)        
                  {
          if((KEY_IN & KEY_MASK) == _BV(KEY_PIN_DOWN))
                       {        
            ind++;       
                       }
          else
                      {
            if((KEY_IN & KEY_MASK) ==_BV(KEY_PIN_UP))
                           {
              ind--;
                           }
                      }              
          while(((KEY_IN & KEY_MASK) != KEY_MASK)&&(del<150U))
                      {
            __builtin_avr_delay_cycles (DELAY_TICKS);
            del++;
                      }
          __builtin_avr_delay_cycles (DELAY_TICKS);
          del++;
          while(((KEY_IN & KEY_MASK) != KEY_MASK)&&(del<150U))
                      {
            __builtin_avr_delay_cycles (DELAY_TICKS);
            del++;
                      }
          del = 0;
          if(ind<0)
                      {
            ind = 0;
                       } 
          else if(ind>14)
                      {
            ind = 14;
                       }
          OCR1A = regtab[ind];
                   }
              }   
          }
    else
         {
      ind = 0;
      OCR1A = regtab[0];
         }
    } 
  return 0;
}
