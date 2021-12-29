#include "User.h"
#include "can.h"
#include "tim.h"
#include "stdio.h"

CAN_TxHeaderTypeDef TXHeader;
CAN_RxHeaderTypeDef RXHeader;

uint8_t TXmessage[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
uint8_t RXmessage[8];
uint32_t pTxMailbox = 0;

//void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* _hcan)
//{
//	
//	if(_hcan==&hcan1)
//	{
//	  //  Analysis_RM_Can(&hcan1);//CAN1����
//	   __HAL_CAN_ENABLE_IT(&hcan1, CAN_RX_FIFO0);
//	}
//	if(_hcan==&hcan2)
//	{
//	 //   Analysis_RM_Can(&hcan2);//CAN2����
//	   __HAL_CAN_ENABLE_IT(&hcan2, CAN_RX_FIFO0);
//	}
//	
//}

void CAN_getMessage()
{

}

void CAN_sendMessage()
{

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)//��������0�����жϻص�����
{
	if(hcan->Instance==CAN1)
	{
		HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO0,&RXHeader,RXmessage);//��ȡ����
    printf("ID: %x \r\n",RXHeader.StdId);
  }
  if(hcan->Instance==CAN2)
	{
		HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO0,&RXHeader,RXmessage);//��ȡ����
  }
	
}

void Set_moto_current(CAN_HandleTypeDef* hcan,uint16_t ID,int16_t Current1, int16_t Current2, int16_t Current3, int16_t Current4)
{
  
    CAN_TxHeaderTypeDef TxHeader;
  	uint32_t TxMailbox = 0;
	  uint8_t message[8];
  
    TxHeader.StdId=ID;        //��׼��ʶ��
    TxHeader.IDE=CAN_ID_STD;    //ʹ�ñ�׼֡
    TxHeader.RTR=CAN_RTR_DATA;  //����֡
    TxHeader.DLC=8;       
    TXHeader.TransmitGlobalTime = DISABLE;
  
    message[0] = Current1 >> 8;
    message[1] = Current1;
    message[2] = Current2 >> 8;
    message[3] = Current2;
    message[4] = Current3 >> 8;
    message[5] = Current3 ;
    message[6] = Current4 >> 8;
    message[7] = Current4;
//	
	//HAL_CAN_Transmit(hcan, 1000);
  HAL_CAN_AddTxMessage(hcan, &TxHeader, message, &TxMailbox);
}	

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
{
  if(htim->Instance == TIM7 )
	{
		Set_moto_current(&hcan2,0x100,1000,2000,3000,4000);
	}
}

