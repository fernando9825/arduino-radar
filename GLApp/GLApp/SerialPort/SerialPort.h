


#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_TIEMPO_ESPERA 2000
#define MAX_LONGINTUD_DATOS 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

class SerialPort
{
private:
    HANDLE manejador;
    bool conectado;
    COMSTAT estado;
    DWORD errores;
public:
    SerialPort(const char *nombrepuerto);
    ~SerialPort();

    int leerPuertoSerie(char *buffer, unsigned int buf_size);
    bool escribirPuertoSerie(const char *buffer, unsigned int buf_size);
    bool estaConectado();
};

#endif // SERIALPORT_H
