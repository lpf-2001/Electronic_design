/********************************** music V2.0 ˵�� ************************************************************************
Musicģ����Beep��Displayerģ��������ٴη�װ�����ڿ��ơ�STC-Bѧϰ�塱�ϲ������֡����ظ�ģ�飬��ͬʱ����Beepģ�顢displayerģ�顣musicģ�鹲�ṩ1��music����������4��Ӧ�ú�����
 ��1��MusicPlayerInit()������musicģ�飻
 ��2��char PlayTone(unsigned char tone, unsigned char beatsPM ,unsigned char scale, unsigned char beats)�������������ף�ʵ����ָ��������ָ�������ʡ���ָ�����ס�������������
����������
      tone��ָ����������Чֵ��0xFA��0xFB��0xFC��0xFD��0xFE��0xFF��0xF9�ֱ��Ӧ����A��B��C��D��E��F��G��
			beatsPM�������ʣ���ÿ���ӽ�������ֵ��Χ10~255��/����
			scale�����ּ������ߣ�1�ֽڡ�
0x00������ֹ��
��4λ��1������8���� 2������8����  3������8����
��3λ��1-7��Ӧ������������ֵ��Ч��
�磺0x13��ʾ����3��mi��
	  beats������(������),��λ1/16�ġ�
�磺16��0x10����Ӧ1�ģ�32��0x20����Ӧ2�ģ�8��0x08����Ӧ����...... ��
��������ֵ��enumBeepOK�����óɹ�
				enumBeepBusy��æ����һ��δ���趨���꣬������������ڷ�����	
				enumBeepFail������ʧ�ܣ���������tone���ԣ������߱���scale���ԣ� 
							����Beep.h�ж���BeepActName��
 ��3��SetMusic(unsigned char beatsPM, unsigned char tone, unsigned char *pt, unsigned int datasize, unsigned char display)���趨��ı�Ҫ�������ֺͲ��Ų�����
����������
      beatsPM�������ʣ���ÿ���ӽ�������ֵ��Χ10~255��/���ӣ��������ֵΪenumModeInvalid�����ı�ԭbeatsPM��
			tone��ָ�������� ��Чֵ��0xFA��0xFB��0xFC��0xFD��0xFE��0xFF��0xF9�ֱ��Ӧ����A��B��C��D��E��F��G��������ֵΪenumModeInvalid������ֵ�����ı�ԭtone
			*pt ��ָ��Ҫ���ŵ����ֱ�����׵�ַ            ��*pt �� datasize ֻ����һ������ = enumModeInvalid�������ı� *pt �� datasize
			datasize��Ҫ���ŵ����ֱ���ĳ��ȣ��ֽ�����    ��*pt �� datasize ֻ����һ������ = enumModeInvalid�������ı� *pt �� datasize
			display��Seg7��Led�Ƿ�������ʾ����������Ϣ��ȡֵ�� 
enumMscNull          ���� ����
			  enumMscDrvSeg7      ���� ��7�������Seg7����ʾ��Ϣ��
			  enumMscDrvLed       ���� ��Ledָʾ�ƣ����ģ�							  enumMscDrvSeg7andLed ���� ��Seg7 �� Led
			 ����ֵΪenumModeInvalid������ֵ�����ı�ԭdisplay
���ֱ������
1���������ּ��׷������루�ɶԳ��֣����ɷֿ����м䲻�ܲ�����������Ϳ����֣�
	   ������ʽ�����ߣ�1�ֽڣ�����������1�ֽڣ������ߣ����ģ�......
         ���С����ߡ����֣�
0x11 �� 0x17 ����Ӧ���� do��re��mi��fa��so��la��si��						    0x21 �� 0x27 ����Ӧ���� do��re��mi��fa��so��la��si
          0x31 �� 0x37 ����Ӧ���� do��re��mi��fa��so��la��si
		���С������������֣�
0x01-0xFF����λ1/16�ġ�Ҳ��ʮ�������У���4λ��ʾ����������4λ��ʾ��������1/16��
	    �磺����2�ģ�  0x20
		    �������ģ�  0x08
			    ����1�İ룺0x18
	2�����ֱ����п��Բ������¿����֣������趨���ֲ��Ų����ȣ�ǰ6��Ҳ����ͨ���������ó����趨��ʵ�֣�:
       enumMscNull              ��  ����
       enumMscDrvSeg7          ��  ��7�������Seg7����ʾ��Ϣ��
			 enumMscDrvLed           ��  ��Ledָʾ�ƣ����ģ�
			 enumMscDrvSeg7andLed    ��  ��Seg7 �� Led
			 enumMscSetBeatsPM       ��  ���ý����ʣ� �����ٸ� �����ʣ�1�ֽڣ�
			 enumMscSetTone          ��   ���������� �����ٸ� ������1�ֽڣ�
0xFA �� 0xFB �� 0xFC �� 0xFD �� 0xFE �� 0xFF �� 0xF9
�ֱ��Ӧ���֣�A�� ��B��������
	   enumMscRepeatBegin       ��  �������ֲ����ظ���ʼ�����ظ�һ�Σ��ݲ�֧�ֶ�Σ����ݲ���Ƕ�ף�Ƕ����Ч����ܵ��²���Ԥ�ڽ����
     enumMscRepeatEnd         ��  �������ֲ����ظ�������
																		
 ��4��SetPlayerMode(unsigned char play_ctrl)	�����ֲ��ſ��ƺ�����
    ����������
          play_ctrl��enumModePlay   �� �����š�
					enumModePause  �� ����ͣ��
					enumModeStop    ����ֹͣ/������
         ������������Ч��
���в����ڵ�ǰ������������ɺ���Ч��				                                  
 ��5��char GetPlayerMode(void)�� ��ȡ��ǰ����״̬
		��������ֵ����play_ctrlֵ��
				enumModePlay      ��  ����״̬
				enumModePause     ��  ��ͣ״̬
				enumModeStop      ��  ֹͣ/����
����������Ӧ���ͺ����ɸ�����Ҫ���ú����ӣ� 

  
��д����ɣ��绰18008400450��   2021��3��5����ƣ�2021��9��5�ո���
*/

#ifndef _music_H_			
#define _music_H_		
							       
extern void MusicPlayerInit();
extern char PlayTone(unsigned char tone, unsigned char beatsPM ,unsigned char scale, unsigned char beats);
																//  tone�� ������F9,FA,FB,FC,FD,FE,FF�ֱ��ӦG\A\B\C\D\E\F��,����ֵ��Ч
																//  beatsPM���ڴգ���λ��ÿ���ӽ�����		
																//  scale: ���ߡ�0x00������ֹ������4λ��1������8���� 2������8����  3������8��������3λ��1-7��������������Ч
																//  beats: ����(������),��λ1/16�ġ�16��0x10����Ӧ1�ģ�32��0x20����Ӧ2�ģ�8��0x08����Ӧ����......  
extern void SetMusic(unsigned char beatsPM, unsigned char tone, unsigned char *pt, unsigned int datasize, unsigned char display);
                                //�����û�ı䣺ȫ�����򲿷ֲ��Ų����������ʡ���������ʾ��ʽ������ԭ���ݣ�
																//���н����ʡ���������ʾ��ʽ Ҳ���������ֱ���������
extern void SetPlayerMode(unsigned char play_ctrl);   
                                //�������ţ�enumModePlay �� enumModePause �� enumModeStop���ֱ��������֡����š�������ͣ������ֹͣ/�����������в����ڵ�ǰ������������ɺ���Ч��
extern char GetPlayerMode(void);   //��ȡ��ǰ����״̬

enum PlayerMode   {enumModeInvalid=0,             //����ģʽ�Ƿ�
                   enumModePlay,                  //����          
                   enumModePause,                 //��ͣ���ɻָ����ţ�
                   enumModeStop};                 //ֹͣ��������
enum MusicKeyword {enumMscNull=0xF0,              //��������ʱ������7������ܡ�LEDָʾ�ƣ���ʾ���ֲ��������Ϣ��
                   enumMscDrvSeg7,                //��������ʱ��  ��7�������
                   enumMscDrvLed,                 //��������ʱ��  ��           LEDָʾ��
                   enumMscDrvSeg7andLed,          //��������ʱ��  ��7������ܡ�LEDָʾ��
                   enumMscSetBeatsPM,             //���ֱ����йؼ��֣� ���� ���ֽ���
                   enumMscSetTone,                //���ֱ����йؼ��֣� ����   ����
                   enumMscRepeatBegin,            //���ֱ����йؼ��֣� ���� �ظ���ʼ 
                   enumMscRepeatEnd};             //���ֱ����йؼ��֣� ���� �ظ�����

#endif