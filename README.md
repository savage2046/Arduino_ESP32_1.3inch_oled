# Arduino_ESP32_1.3inch_oled
 1.3 inch Oled is NOT 128X64! It is 132X64
 基本工作流程是创建一个缓冲区（类似显存），要显示的内容通过 drawPixel（）写入缓冲，最后调用display()刷新整个屏幕
 本例子使用硬件IIC接口，重写接口部分就可以匹配SPI和软件IIC

1.123
 