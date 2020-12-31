#include "Configuracion_Bits.h"

#define PINS_TRIS       TRISB
#define PINS            PORTB
#define PULSADOR_TRIS   TRISAbits.TRISA0
#define PULSADOR_READ   PORTAbits.RA0

void Antirrebote(void);

void main(void)
{
    // Configuracion Modo digital:
    CMCON = 0x07;
    
    // Configuracion leds:
    PINS_TRIS = 0;          // Setea como salida todo el puerto B // Es lo mismo que poner TRISB = 0;
    PINS = 0;               // Setea todos los pines en 0         // Es lo mismo que poner PORTB = 0;
    
    // Configuracion pulsador:
    PULSADOR_TRIS = 1;      // Seteamos como entrada el pinA0
    
//    while(1)
//    {
//        if(PULSADOR_READ==1)
//        {
//            Antirrebote();
//            PORTBbits.RB0 = 1;
//            for(char i=1;i<8;i++)
//            {
//                __delay_ms(200);        // Esta funcion va a detener el programa durante este tiempo
//                PINS = PINS << 1;       // Realiza un corrimiento hacia la izquierda 
//            }
//            __delay_ms(200);
//            PORTB = 0;
//            /**
//             * Con i = 0 tenemos PORTB = 0b00000001;
//             * con i = 1 tenemos PORTB = 0b00000010;
//             * con i = 2 tenemos PORTB = 0b00000100;
//             * .
//             * .
//             * .
//             * con i = 7 tenemos PORTB = 0b10000000;
//             */
//        }
//    } 
    
    while(1)
    {
        if(PULSADOR_READ==1)
        {
            Antirrebote();
            PORTBbits.RB0 = 1;
            for(char i=1;i<8;i++)
            {
                __delay_ms(200);
                PINS |= PINS << 1;  // Suma el valor del corrimiento al valor de bits actuales
            }
              /**
               * Con i = 0 tenemos PORTB = 0b00000001;
               * con i = 1 tenemos PORTB = 0b00000011;
               * con i = 2 tenemos PORTB = 0b00000111;
               * .
               * .
               * .
               * con i = 7 tenemos PORTB = 0b11111111;
               */
            __delay_ms(200);
            PORTB = 0;
        }
    }
    
    return;
}

void Antirrebote(void)
{
    __delay_ms(30);
    while(PULSADOR_READ==1) __delay_ms(30);
    
    return;
}