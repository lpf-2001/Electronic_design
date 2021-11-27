/**********************************ADC V1.1 ˵�� ************************************************************************
ADCģ�����ڡ�STC-Bѧϰ�塱����ADC��ص�·:�¶�Rt������Rop����������Nav����չ�ӿ�EXT�ϵ�ADCת�����ṩADCģ���ʼ��������2��Ӧ�ú���,2���¼���
  (1)  AdcInit(char ADCsel)��ADCģ���ʼ��������
	  ��������: ADCselѡ����չ�ӿ�EXT�Ƿ�����ADC���ܣ�ȡֵ��
      ADCincEXT   :  ������չ�ӿ�EXT����ADC���ܣ�EXT��P1.0��P1.1����������IO����ʹ�ã�
      ADCexpEXT   :  ��������չ�ӿ�EXT����ADC���ܣ�EXT��P1.0��P1.1��������IO����ʹ�ã� 		
  (2)  struct_ADC GetADC()����ȡADCֵ��
		������������
		��������ֵ���������ݽṹ struct_ADC��
		���ݽṹ���壺
		typedef struct                //ADCת�����
			{ unsigned int EXT_P10;		      // ��չ�ӿ�EXT��P1.0��ADC��10bit��
				unsigned int EXT_P11;	        // ��չ�ӿ�EXT��P1.1��ADC��10bit��
				unsigned int Rt;              // ����������ADC��10bit��
				unsigned int Rop;             // ����������ADC��10bit��
				unsigned int Nav;             // ����������ADC��10bit��	  		
			} struct_ADC;

˵��1��ÿ�����ֱ�ʾ  VCC/1024����λ��V��������VCCΪ��·�幩���ѹ��USB�ӿ�һ��Ϊ5V���ң� 
˵��2�����ڵ�������������GetAdcNavAct������������󵼺������¼���״̬��������ʹ�ã�

   (3)  char GetAdcNavAct(char Nav_button)����ȡ��������������K3��״̬
	 ����������Nav_button��ָ��Ҫ��ȡ״̬�ĵ���������ȡֵ��
					enumAdcNavKey3��K3����,   
					enumAdcNavKeyRight���Ұ���,
					enumAdcNavKeyDown���°���,
					enumAdcNavKeyCenter�����İ���
          enumAdcNavKeyLeft���󰴣�,
          enumAdcNavKeyUp���ϰ���.
��������ȡֵ������Ч��Χ������������enumKeyFail��
	 ��������ֵ�����ص�ǰ�����¼�������ֵ����ͬKeyģ��GetAdcKeyAct��������ֵ��
					enumKeyNull���ް���������,
					enumKeyPress�����£�,
					enumKeyRelease��̧��,
					enumKeyFail��ʧ�ܣ� 
	 ����ֵ�Ǿ�����μ�ⰴ��ʵʱ״̬��ͳ�Ƽ�������������������Ч�¼���
     ÿ��������ѯһ�κ�,�¼�ֵ���	enumKeyNull	(����ѯһ����Ч)				
  (4)  ���������¼�����enumEventNav
      ����������5������򰴼�K3�����⡱���¡���̧�𡰶���ʱ��������һ�������������¼���enumEventNav����Ӧ���������¼����û��ص��������û���д,����sys�ṩ��SetEventCallBack()����������Ӧ����.	 
  (5)  ��չ�ӿ�EXT��P1.0��P1.1�����˿����µ�ADֵ�¼�����enumEventXADC
     ��ADCģ���P1.0��P1.1����ADCת��������������µ�ADC���ʱ��������enumEventXADC�¼���֪ͨ�û����д�����ӦenumEventXADC�¼����û��ص��������û���д,����sys�ṩ��SetEventCallBack()����������Ӧ����.
     ADCģ���P1.0��P1.1����ADCת���ٶ�Ϊ3mS��Ҳ��ÿ3mS��ÿ����333��ת��.
  (6)  ����˵���� 
	 a����EXT��P1.0��P1.0��ת���ٶ�Ϊ3mS��Ҳ��ÿ�����ṩ333��ת��������ṩ������ת������¼���enumEventXADC�������û�����
b������Rt��Rop��ת���ٶ�Ϊ9mS��Ҳ��ÿ�����ṩ111��ת�������û���ṩ��Ӧ���¼������û���ʱ�ú���GetAdcResult()��ѯ��ʹ��
	 c���Ե����������������������������֧�ֵ�������ÿ��12�β����ٶȣ��ṩ�˵������������˲����¼���enumEventNav
	 d�����ڵ���������K3�������˵�Ƭ��ͬһ���˿ڣ�P1.7��������ADCģ���P1.7��IO����ʧЧ��ֻ����GetAdcNavAct(char Nav_button)������ȡK3�������¼���״̬��
	 e: STC-B����Rt�ͺ�Ϊ��10K/3950 NTC�������裬��������Rop�ͺ�Ϊ��GL5516. ���ǵ�ADCֵ���¶ȡ�����ǿ�ȹ�ϵ��������ǵ������ֲ���STC-B��·ͼ���л��㡣


��д����ɣ��绰18008400450��   2021��3��25�����,2021��8��30���޸�
*/

#ifndef _adc_H_
#define _adc_H_

#define ADCincEXT 0x9B
#define ADCexpEXT 0x98

typedef struct                //ADCת�����
  { unsigned int EXT_P10;		      // ��չ�ӿ�EXT��P1.0��ADC
    unsigned int EXT_P11;	        // ��չ�ӿ�EXT��P1.1��ADC
    unsigned int Rt;              // ����������ADC
    unsigned int Rop;             // ����������ADC
    unsigned int Nav;             // ����������ADC  		  		
  } struct_ADC;

extern void AdcInit(char ADCsel);

extern struct_ADC GetADC();
extern unsigned char GetAdcNavAct(char Nav_button);                  //��ȡ��������5�������ҡ��¡����ġ����ϣ��������Լ�����K3�������¼�
																																		 //����ֵ��enuKeyNull���ް���������,enuKeyPress�����£�,enuKeyRelease��̧��,enuKeyFail��ʧ�ܣ� 
enum KN_name  {enumAdcNavKey3=0,      //��������������K3
               enumAdcNavKeyRight,    //������������
               enumAdcNavKeyDown,     //������������
               enumAdcNavKeyCenter,   //��������������
               enumAdcNavKeyLeft,     //������������
               enumAdcNavKeyUp};      //������������
#endif