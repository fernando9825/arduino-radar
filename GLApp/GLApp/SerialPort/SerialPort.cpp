
#include "SerialPort.h"

SerialPort::SerialPort(const char *nombrepuerto)
{
	
    this->conectado = false;

	
    this->manejador = CreateFileA(static_cast<LPCSTR>(nombrepuerto),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (this->manejador == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
            printf("ERROR: No se puede abrir. Raz\xa2n: %s no esta disponible\n", nombrepuerto);
        }
    else
        {
            printf("ERROR!!!");
        }
    }
    else {
        DCB dcbSerialParametros = {0};

        if (!GetCommState(this->manejador, &dcbSerialParametros)) {
            printf("fallo al obtener los parametros del puerto");
        }
        else {
            dcbSerialParametros.BaudRate = CBR_9600;
            dcbSerialParametros.ByteSize = 8;
            dcbSerialParametros.StopBits = ONESTOPBIT;
            dcbSerialParametros.Parity = NOPARITY;
            dcbSerialParametros.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(manejador, &dcbSerialParametros))
            {
                printf("ALERTA: No se puede configurar los parametros del puerto\n");
            }
            else {
                this->conectado = true;
                PurgeComm(this->manejador, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_TIEMPO_ESPERA);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if (this->conectado){
        this->conectado = false;
        CloseHandle(this->manejador);
    }
}

int SerialPort::leerPuertoSerie(char *buffer, unsigned int buf_size)
{
    DWORD bytesLeer;
    unsigned int aLeer = 0;

    ClearCommError(this->manejador, &this->errores, &this->estado);

    if (this->estado.cbInQue > 0){
        if (this->estado.cbInQue > buf_size){
            aLeer = buf_size;
        }
        else aLeer = this->estado.cbInQue;
    }

    memset(buffer, 0, buf_size);

    if (ReadFile(this->manejador, buffer, aLeer, &bytesLeer, NULL)) return bytesLeer;

    return 0;
}

bool SerialPort::escribirPuertoSerie(const char *buffer, unsigned int buf_size)
{
    DWORD bytesEnviar;

    if (!WriteFile(this->manejador, (void*) buffer, buf_size, &bytesEnviar, 0)){
        ClearCommError(this->manejador, &this->errores, &this->estado);
        return false;
    }
    else return true;
}

bool SerialPort::estaConectado()
{
    if (!ClearCommError(this->manejador, &this->errores, &this->estado))
		this->conectado = false;
        
    return this->conectado;
}
