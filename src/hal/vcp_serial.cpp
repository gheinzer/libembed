// #include <libembed/hal/vcp_serial.hpp>
// #include <libembed/hal/stm32_hal.h>
// #include <string.h>

// UART_HandleTypeDef vcp_serial::uartHandle = { 0 };

// void vcp_serial::init(unsigned long baudrate) {
//     vcp_serial::uartHandle.Instance = USART2;
//     vcp_serial::uartHandle.Init.BaudRate = baudrate;
//     vcp_serial::uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
//     vcp_serial::uartHandle.Init.StopBits = UART_STOPBITS_1;
//     vcp_serial::uartHandle.Init.Parity = UART_PARITY_NONE;
//     vcp_serial::uartHandle.Init.Mode = UART_MODE_TX_RX;
//     vcp_serial::uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//     vcp_serial::uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
//     vcp_serial::uartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//     vcp_serial::uartHandle.Init.ClockPrescaler = UART_PRESCALER_DIV1;
//     vcp_serial::uartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//     HAL_UART_Init(&vcp_serial::uartHandle);
// }

// void vcp_serial::print(const char* message) {
//     HAL_UART_Transmit(&vcp_serial::uartHandle, (uint8_t*)message, strlen(message), 1000);
// }

// extern "C" void HAL_UART_MspInit(UART_HandleTypeDef* huart)
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};
//     if(huart->Instance==USART2)
//     {
//         __HAL_RCC_USART2_CLK_ENABLE();
//         __HAL_RCC_GPIOA_CLK_ENABLE();
//         GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
//         GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//         GPIO_InitStruct.Pull = GPIO_NOPULL;
//         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//         GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
//         HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//     }
// }