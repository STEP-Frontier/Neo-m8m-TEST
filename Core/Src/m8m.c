#include "m8m.h"

union u_Short uShort;
union i_Short iShort;
union u_Long uLong;
union i_Long iLong;



//initialization

void GNSS_Init(GNSS_StateHandle *GNSS,UART_HandleTypeDef *huart){
    GNSS->huart = huart;
    GNSS->year = 0;
    GNSS->month = 0;
    GNSS->min = 0;
    GNSS->sec = 0;
    GNSS->fixType = 0;//fixtype is parameter of position fix
    GNSS->lot = 0;//longitude
    GNSS->lat = 0;//latitude
    GNSS->height = 0;
    GNSS->hMSL = 0;
    GNSS->hAcc = 0;
    GNSS->vAcc = 0;
    GNSS->gSpeed = 0;
    GNSS->headMot = 0;
}

//Parse binary data
void GNSS_ParseBuffer(GNSS_StateHandle *GNSS){

    for (int var = 0; var<=100; var++){
        if(GNSS->uartWorkingBuffer[var] = 0xB5 && GNSS->uartWorkingBuffer[var + 1] ==0x62){
            if(GNSS->uartWorkingBuffer[var+2]== 0x27 && GNSS->uartWorkingBuffer[var + 3] == 0x03){
                GNSS_ParseUniqID(GNSS);
                //32.19.1.1_p438
            }else if (GNSS->uartWorkingBuffer[var + 2] == 0x01 && GNSS->uartWorkingBuffer[var + 3] == 0x21){
                GNSS_ParseaNavigatorData(GNSS);
                //32.17.14.1_p386
            }else if (GNSS->uartWorkingBuffer[var + 2] ==0x01 && GNSS->uartWorkingBuffer[var + 3] == 0x07){
                GNSS_ParsePVTDATA(GNSS);
                //32.17.30.1_p412
            }else if (GNSS->uartWorkingBuffer[var + 2] == 0x01 && GNSS->uartWorkingBuffer[var + 3] == 0x02){
                GNSS_ParsePOSLLHData(GNSS);
                //32.17.15.14
            }

        }
    }
}