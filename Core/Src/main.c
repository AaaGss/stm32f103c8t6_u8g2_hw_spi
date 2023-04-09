/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @author         :AaaGss-YYKF
  * @date           :2023/4/9
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"

#include "OLED.h"
#include "u8g2.h"

void SystemClock_Config(void);

/*官方提供的Logo绘制demo*/
void draw(u8g2_t *u8g2)
{
    u8g2_SetFontMode(u8g2, 1); /*字体模式选择*/
    u8g2_SetFontDirection(u8g2, 0); /*字体方向选择*/
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf); /*字库选择*/
    u8g2_DrawStr(u8g2, 0, 20, "U");

    u8g2_SetFontDirection(u8g2, 1);
    u8g2_SetFont(u8g2, u8g2_font_inb30_mn);
    u8g2_DrawStr(u8g2, 21, 8, "8");

    u8g2_SetFontDirection(u8g2, 0);
    u8g2_SetFont(u8g2, u8g2_font_inb24_mf);
    u8g2_DrawStr(u8g2, 51, 30, "g");
    u8g2_DrawStr(u8g2, 67, 30, "\xb2");

    u8g2_DrawHLine(u8g2, 2, 35, 47);
    u8g2_DrawHLine(u8g2, 3, 36, 47);
    u8g2_DrawVLine(u8g2, 45, 32, 12);
    u8g2_DrawVLine(u8g2, 46, 33, 12);

    u8g2_SetFont(u8g2, u8g2_font_4x6_tr);
    u8g2_DrawStr(u8g2, 1, 54, "github.com/olikraus/u8g2");
}


uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_BYTE_SEND: /*通过SPI发送arg_int个字节数据*/
        //HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)arg_ptr, arg_int);while(hspi1.TxXferCount);
        HAL_SPI_Transmit(&hspi1, (uint8_t *)arg_ptr, arg_int, 200);
        break;
    case U8X8_MSG_BYTE_INIT: /*初始化函数*/
        break;
    case U8X8_MSG_BYTE_SET_DC: /*设置DC引脚,表明发送的是数据还是命令*/
        HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, arg_int);
        break;
    case U8X8_MSG_BYTE_START_TRANSFER:
        u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
        u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
        break;
    case U8X8_MSG_BYTE_END_TRANSFER:
        u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
        u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
        break;
    default:
        return 0;
    }
    return 1;
}


uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay和GPIO的初始化，在main中已经初始化完成了*/
        break;
    case U8X8_MSG_DELAY_MILLI: /*延时函数*/
        HAL_Delay(arg_int);
        break;
    case U8X8_MSG_GPIO_CS: /*片选信号*/
        HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, arg_int);
        break;
    case U8X8_MSG_GPIO_DC:
        break;
    case U8X8_MSG_GPIO_RESET:
        break;
    }
    return 1;
}

void u8g2Init(u8g2_t *u8g2)
{
    /*
    U8G2_R0： 顺时针旋转0度
    U8G2_R1： 顺时针旋转90度
    U8G2_R2： 顺时针旋转180度
    U8G2_R3： 顺时针旋转270度
    U8G2_MIRROR：U8G2_R0的镜像
    */
    u8g2_Setup_ssd1306_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);
    u8g2_InitDisplay(u8g2); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
    u8g2_SetPowerSave(u8g2, 0); // 打开显示器
    u8g2_ClearBuffer(u8g2);

    HAL_Delay(1000);

    u8g2_DrawLine(u8g2, 0, 0, 127, 63);
    u8g2_DrawLine(u8g2, 127, 0, 0, 63);
    u8g2_SendBuffer(u8g2);
    HAL_Delay(1000);
}

int main(void)
{

    u8g2_t u8g2;
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_SPI1_Init();

    OLED_Init();

    u8g2Init(&u8g2);
    u8g2_FirstPage(&u8g2);
    do
    {
        draw(&u8g2);
    }
    while (u8g2_NextPage(&u8g2));

    while (1)
    {
    }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}
