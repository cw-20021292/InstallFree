/// @file     Func_Uart.h
/// @date     2025/04/25
/// @author   Jaejin Ham, Hyunho Kang
/// @brief    Uart 동작 함수  File


#ifndef _FUNC_UART_H_
#define _FUNC_UART_H_


/*  User가 Uart 사용시 추가할 함수들
    => UART0_Transmit_Interrupt();              // r_Config_UART0_interrupt_send() 함수 안의 코드를 모두 삭제하고 대신에 추가
    => UART0_Recieve_Interrupt();               // r_Config_UART0_interrupt_receive() 함수 안의 코드를 모두 삭제하고 대신에 추가
    => UART0_Error_Interrupt();                 // r_Config_UART0_interrupt_error() 함수 안의 코드를 모두 삭제하고 대신에 추가

    => UART1, UART2, UART3, UARTA0, UARTA1도 위와 같은 동일한 형태로 사용
*/

#define UART0_USE                               USE     // UART0 사용 여부 - 0(No Use), 1(Use)
#define UART1_USE                               USE  // UART1 사용 여부 - 0(No Use), 1(Use)
#define UART2_USE                               USE  // UART2 사용 여부 - 0(No Use), 1(Use)
#define UART3_USE                               USE  // UART3 사용 여부 - 0(No Use), 1(Use)
#define UARTA0_USE                              NO_USE  // UARTA0 사용 여부 - 0(No Use), 1(Use)
#define UARTA1_USE                              NO_USE  // UARTA1 사용 여부 - 0(No Use), 1(Use)

/* 하기에 각 UART의 Tx 및 Rx 인터럽트 루틴 안에서 수행할 함수와 UART Start, Stop 함수 배치 시킨다 */
#if (UART0_USE == USE)
#define UART0_TX_INTERRUPT_FUNCTION()           
#define UART0_RX_INTERRUPT_FUNCTION()           
#define UART0_RX_ERROR_INTERRUPT_FUNCTION()     
#define UART0_START()                           
#define UART0_STOP()                            

void UART0_Transmit_Interrupt(void);
void UART0_Recieve_Interrupt(void);
void UART0_Error_Interrupt(void);
#endif


#if (UART1_USE == USE)
#define UART1_TX_INTERRUPT_FUNCTION()           
#define UART1_RX_INTERRUPT_FUNCTION()           
#define UART1_RX_ERROR_INTERRUPT_FUNCTION()     
#define UART1_START()                           
#define UART1_STOP()                            

void UART1_Transmit_Interrupt(void);
void UART1_Recieve_Interrupt(void);
void UART1_Error_Interrupt(void);
#endif


#if (UART2_USE == USE)
#define UART2_TX_INTERRUPT_FUNCTION()           
#define UART2_RX_INTERRUPT_FUNCTION()           
#define UART2_RX_ERROR_INTERRUPT_FUNCTION()     
#define UART2_START()                           
#define UART2_STOP()                            

void UART2_Transmit_Interrupt(void);
void UART2_Recieve_Interrupt(void);
void UART2_Error_Interrupt(void);
#endif


#if (UART3_USE == USE)
#define UART3_TX_INTERRUPT_FUNCTION()           
#define UART3_RX_INTERRUPT_FUNCTION()           
#define UART3_RX_ERROR_INTERRUPT_FUNCTION()     
#define UART3_START()                           
#define UART3_STOP()                            

void UART3_Transmit_Interrupt(void);
void UART3_Recieve_Interrupt(void);
void UART3_Error_Interrupt(void);
#endif


#if (UARTA0_USE == USE)
#define UARTA0_TX_INTERRUPT_FUNCTION()          
#define UARTA0_RX_INTERRUPT_FUNCTION()          
#define UARTA0_RX_ERROR_INTERRUPT_FUNCTION()    
#define UARTA0_START()                          
#define UARTA0_STOP()                           

void UARTA0_Transmit_Interrupt(void);
void UARTA0_Recieve_Interrupt(void);
void UARTA0_Error_Interrupt(void);
#endif


#if (UARTA1_USE == USE)
#define UARTA1_TX_INTERRUPT_FUNCTION()          
#define UARTA1_RX_INTERRUPT_FUNCTION()          
#define UARTA1_RX_ERROR_INTERRUPT_FUNCTION()    
#define UARTA1_START()                          
#define UARTA1_STOP()                           

void UARTA1_Transmit_Interrupt(void);
void UARTA1_Recieve_Interrupt(void);
void UARTA1_Error_Interrupt(void);
#endif


#endif

