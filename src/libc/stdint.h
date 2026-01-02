#ifndef STDINT_H
#define STDINT_H

// O 'int' comum já é 32-bit assinado nesta arquitetura.
// Definimos apenas os tipos de tamanhos específicos:
typedef signed char        int8_t;
typedef unsigned char      uint8_t;

typedef short              int16_t;
typedef unsigned short     uint16_t;

typedef unsigned int       uint32_t; // int de 32 bits sem sinal

typedef long long          int64_t;
typedef unsigned long long uint64_t;

#endif