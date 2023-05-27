#include "GPS.h"
#include "usart.h"
#include "stdio.h"
#include "stm32f1xx_it.h"
#include "string.h"
#include "stdlib.h"
_SaveData Save_Data;
void errorLog(int num)//������������ʱ���������Ϣ
{
	
	while (1)
	{
//	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()//������ GPS ģ����յ������ݲ�������������Ϣ�洢�� _SaveData �ṹ����
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
//		printf("**************\r\n");
//		printf(Save_Data.GPS_Buffer);

		
		for (i = 0 ; i <= 6 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//��������
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					char usefullBuffer[2]; 
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//��ȡE/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//��������
				}
			}


		}
	}
}

void printGpsBuffer()//������������Ϣת��Ϊ�ɶ���ʽ�����
{
		int a,b,c,d,i,j;
		float latitude3,latitude4,longitude3,longitude4;
		char latitude1[3],latitude2[9],longitude1[4],longitude2[9];
		a=0;
		b=0;
		c=0;
		d=0;
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		for(i=0;i<11;i++)
		{
			if(i<2)
			{
				latitude1[a]=Save_Data.latitude[i];
				a++;
			}else
			{
				latitude2[b]=Save_Data.latitude[i];
				b++;
			}
		}
		for(j=0;j<12;j++)
		{
			if(j<3)
			{
				longitude1[c]=Save_Data.longitude[j];
				c++;
			}else
			{
				longitude2[d]=Save_Data.longitude[j];
				d++;
			}
		}
		latitude3=atof(latitude1);
		latitude4=atof(latitude2);
		longitude3=atof(longitude1);
		longitude4=atof(longitude2);
		latitude=latitude3+(latitude4/60);
		longitude=longitude3+(longitude4/60);
//		printf("Save_Data.UTCTime = ");
//		printf(Save_Data.UTCTime);
//		printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
//			printf("latitude = ");
//			printf("%f",latitude);
//			printf(Save_Data.N_S);
//			printf("\r\n");

//			printf("longitude = ");
//			printf("%f",longitude);
//			printf(Save_Data.E_W);
//			printf("\r\n");
		}
		else
		{
//			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}
void GPS(void)
{
		parseGpsBuffer();
		printGpsBuffer();
}
