## CarrotCRC - CRC校验库

🌐 Language: [English](README.md) | [中文](README.zh-CN.md)

![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)

---

CarrotCRC 是一个轻量级的CRC(循环冗余校验)计算库，支持多种CRC算法配置。该库提供了灵活的CRC参数设置，包括多项式、初始值、输入输出反转等，并支持查表法优化计算速度。

## 功能特性

- 支持4位到64位CRC计算（默认配置支持32位）
- 支持输入/输出数据位反转(RefIn/RefOut)
- 支持自定义多项式(Poly)、初始值(Init)和输出异或值(XorOut)
- 提供查表法优化计算速度
- 包含多种常见CRC算法预设(CRC4/ITU, CRC8, CRC16/CCITT, CRC32等)

## 快速开始

### 构建说明

#### Visual Studio
1. 打开Visual Studio
2. 创建新项目或打开现有项目
3. 添加`crc.c`, `crc.h`和`main.c`到项目中
4. 编译并运行

#### Keil MDK
1. 打开Keil MDK
2. 创建新项目或打开现有项目
3. 添加`crc.c`, `crc.h`和`main.c`到项目中
4. 配置目标设备选项
5. 编译并运行

### 使用示例

```c
#include "crc.h"

int main() {
    CrcInfoType crc = {
        .Name = "CRC16/CCITT",
        .Width = 16,
        .Poly = 0x1021,
        .Init = 0x0000,
        .XorOut = 0x0000,
        .RefIn = true,
        .RefOut = true
    };
    
    uint8_t data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    crc_word_t result = CrcCalculate(&crc, data, sizeof(data));
    
    printf("CRC result: 0x%04X\n", result);
    return 0;
}
```

## 支持的CRC算法

库中已预设以下CRC算法：
- CRC4/ITU
- CRC8
- CRC16/CCITT
- CRC32
- CRC16_7606
- CRC64/ECMA (当CRC_MAX > 32时)

## 测试

项目包含测试用例，验证了各种CRC算法的正确性。运行程序将自动执行测试并输出结果。

## 许可证

本项目采用Apache License 2.0开源协议。详情请参阅LICENSE文件。

## 贡献

欢迎提交问题和拉取请求。请确保您的代码风格与现有代码保持一致。

## 作者

- LuHuajun
- CarrotHu

## 版本

当前版本：2.1.0

---

*本README由DeepSeek生成*