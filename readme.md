# 0. 视频教程
我的[B站](https://www.bilibili.com/video/BV1Fa4y1u76m/?share_source=copy_web&vd_source=584714a0cf29c22026ad8acbe10986af)
# 1.下载源码
去[官网](https://github.com/olikraus/u8g2)下载源码
![在这里插入图片描述](https://img-blog.csdnimg.cn/a7f54e4859cf4c589837b5fa188c6c60.png)

也可以点击[我的链接](https://wwjw.lanzoum.com/ibjCm0sgbd8h)下载。
# 2.解压
解压出来其中的csrc文件夹，放到工程目录。
把自己的屏幕驱动保留下来，比如我用的128x64的ssd1306,就把里面的 u8x8_d_ssd1306_128x64_noname.c 保留，其他类似 u8x8_d_···.c 的都删了。
# 3. 打开keil工程
### 3.1 添加文件到工程
新建个组，把精简后的csrc的文件都添加都组里来，把csrc路径添加到项目包含目录里来，先编译，有问题没关系。
### 3.2 打开 u8g2_d_setup.c 文件，只保留下面6个函数

```c
/* ssd1306*/
/* ssd1306 1 */
void u8g2_Setup_ssd1306_128x64_noname_1(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_001, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_16_8_1(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
}
/* ssd1306 2 */
void u8g2_Setup_ssd1306_128x64_noname_2(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_001, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_16_8_2(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
}
/* ssd1306 f */
void u8g2_Setup_ssd1306_128x64_noname_f(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_001, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_16_8_f(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
}

/* ssd1306 IIC*/
/* ssd1306 1 */
//void u8g2_Setup_ssd1306_i2c_128x64_noname_1(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
//{
//  uint8_t tile_buf_height;
//  uint8_t *buf;
//  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_ssd13xx_fast_i2c, byte_cb, gpio_and_delay_cb);
//  buf = u8g2_m_16_8_1(&tile_buf_height);
//  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
//}

///* ssd1306 2 */
//void u8g2_Setup_ssd1306_i2c_128x64_noname_2(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
//{
//  uint8_t tile_buf_height;
//  uint8_t *buf;
//  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_ssd13xx_fast_i2c, byte_cb, gpio_and_delay_cb);
//  buf = u8g2_m_16_8_2(&tile_buf_height);
//  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
//}

///* ssd1306 f */
//void u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
//{
//  uint8_t tile_buf_height;
//  uint8_t *buf;
//  u8g2_SetupDisplay(u8g2, u8x8_d_ssd1306_128x64_noname, u8x8_cad_ssd13xx_fast_i2c, byte_cb, gpio_and_delay_cb);
//  buf = u8g2_m_16_8_f(&tile_buf_height);
//  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
//}
```
其中，前3个是SPI的，后三个是IIC的，因为我用的是SPI,所以后面三个注释了。
这6个函数名的最后一位（1，2，f）表示不同的显示buf,一般用带 f 的，具体意义如下：
- 1：128字节
- 2：256字节
- f：1024字节

### 3.3 打开 u8g2_d_memory.c 文件，只保留下面3个函数
```c
uint8_t *u8g2_m_16_8_1(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 1;
  return 0;
  #else
  static uint8_t buf[128];
  *page_cnt = 1;
  return buf;
  #endif
}
uint8_t *u8g2_m_16_8_2(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 2;
  return 0;
  #else
  static uint8_t buf[256];
  *page_cnt = 2;
  return buf;
  #endif
}
uint8_t *u8g2_m_16_8_f(uint8_t *page_cnt)
{
  #ifdef U8G2_USE_DYNAMIC_ALLOC
  *page_cnt = 8;
  return 0;
  #else
  static uint8_t buf[1024];
  *page_cnt = 8;
  return buf;
  #endif
}
```
这3函数会被上一步的6个函数调用。

### 3.4 编写回调函数
打开 main.c 文件,添加下面四个函数
```c
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
    switch (msg)
    {
    case U8X8_MSG_BYTE_SEND: /*通过SPI发送arg_int个字节数据*/
        //HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)arg_ptr, arg_int);while(hspi1.TxXferCount);//DMA
        HAL_SPI_Transmit(&hspi1,(uint8_t *)arg_ptr,arg_int,1000);//SPI
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
        delay_ms(arg_int);
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

```
第一个函数 ==u8x8_byte_4wire_hw_spi== 是通信的，用的硬件SPI或者SPI的DMA,具体看注释。
第二个函数 ==u8x8_stm32_gpio_and_delay== 是回调函数，控制片选、延时、初始化引脚的，具体看注释。
第三个函数 draw 是官方提供的Logo绘制demo。
第四个函数 u8g2Init 是初始化U8g2的，这个函数里面的 u8g2_Setup_ssd1306_128x64_noname_f 函数是之前保留的，这个函数会调用前面写的两个回调函数（u8x8_byte_4wire_hw_spi和u8x8_stm32_gpio_and_delay），所以这两个回调函数是 **重中之重**。

**==注意==** : 用硬件通信，无论是SPI、IIC或者其他协议,都需要自己写类似于==u8x8_byte_4wire_hw_spi== 的回调函数；用软件通信，都不用写，因为这个U8g2库里有，具体在 u8x8_byte.c 这个文件里，里面有 **4线软件SPI、3线软件SPI、软件IIC、6800、8080** 等通信的回调函数。**本篇介绍的是用硬件SPI的，主要是用硬件SPI的网上没有详细教程，所以贡献一下。如果用硬件IIC或者其他通信可以看[这里](https://github.com/olikraus/u8g2/wiki/Porting-to-new-MCU-platform)**。

### 3.5 主函数初始化U8g2，绘制logo
最后，在主函数里，先初始化oled，再调用 u8g2Init ，然后绘制logo，代码如下：

```c
	u8g2_t u8g2;
	
    u8g2Init(&u8g2);
    u8g2_FirstPage(&u8g2);
    do
    {
        draw(&u8g2);
    }
    while (u8g2_NextPage(&u8g2));
    
```

# 4. 现象
![在这里插入图片描述](https://img-blog.csdnimg.cn/45ab2085f2034d3c90bc6a720cc16c4f.png)

