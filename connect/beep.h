/**********************************Beep V2.0 ˵�� ************************************************************************
Beep���ڿ��ơ�STC-Bѧϰ�塱����Դ�������ķ�����Beepģ�鹲�ṩ1������������2��Ӧ�ú�����
  (1)  BeepInit()��������ģ����������
  (2)  Set_Beep(unsigned int Beep_freq, unsigned char Beep_time)�����Ʒ�������������������
        Beep_freq��ָ������Ƶ�ʣ���λHz��С��10�������  
			  Beep_time��ָ������ʱ��������ʱ����10*Beep_time	  (mS)  ��� 655350mS
				��������ֵ��enumSetBeepOK�����óɹ���enumSetBeepFail������ʧ�ܣ�������������ڷ�����	 
	(3)  GetBeepStatus(void):	��ȡBeep��ǰ״̬,enmuBeepFree:����, enumBeepBusy ,���ڷ���
	(4)  Beepģ��ʹ����STC�ڲ�CCPģ��1ͨ��

��д����ɣ��绰18008400450��   2021��3��3����ƣ�2021��3��26�ո���
*/

#ifndef _beep_H_			
#define _beep_H_		

extern void BeepInit();										                             //  ��������ʼ��

extern char SetBeep(unsigned int Beep_freq, unsigned int Beep_time);   //  ��ָ��Ƶ�������� ����ʱ����10��Beep_time	  (mS)  ��� 655350mS
                                                                       //  Beep_freq < 10 Hz, ������
                                                                       //  �������� enumSetBeepOK�����óɹ���   enumSetBeepFail������ʧ�ܣ�����ʱ���ڷ�����

extern unsigned char GetBeepStatus(void);                              //  ��ȡ״̬,enumBeepFree:����, enumBeepBusy,���ڷ���

enum BeepActName {enumBeepFree=0,enumBeepBusy,enumSetBeepOK,enumSetBeepFail}; 

#endif