/****************************
 * CRC Library
 * LuHuajun, CarrotHu
 * 2025.03.04
 *****************************/
#pragma once
#ifndef _CRC_H_
#ifdef __cplusplus
extern "C"
{
#endif

#define CRC_VERSION "2.0.0"

#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>


typedef uint32_t crc_word_t;

typedef struct
{
    char* Name;
    uint8_t Width;
    crc_word_t Poly;
    crc_word_t Init;
    crc_word_t XorOut;
    bool RefIn;
    bool RefOut;

    // CrcUpdateTable
    bool TableUpdated;
    crc_word_t Table[256];
} CrcInfoType;

#define PRINTF_DBG printf

void CrcUpdateTable(CrcInfoType* crc);
void CrcTablePrint(CrcInfoType* crc);
crc_word_t CrcCalculate(CrcInfoType* crc, uint8_t* buf, uint32_t bufLen);

#ifdef __cplusplus
}
#endif

#endif // !_CRC_H_
