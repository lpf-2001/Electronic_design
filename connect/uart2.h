/********************************** Uart2����ͨ��ģ�� V1.0 ˵�� ***************************************************************
Uart2ģ���ṩUart2ģ���ʼ��������3��Ӧ�ú���,1���¼���enumUart2EventRxd����
(1)	Uart2Init(unsigned int band,unsigned char Uart2mode)��Uart2ģ���ʼ��������
    ����������unsigned int band�����崮��2��ͨ�Ų����ʣ���λ��bps�����̶�8������λ��1��ֹͣλ������żУ��λ��
		          unsigned char Uart2mode�����崮��2λ��
							     ȡֵ��Uart2UsedforEXT  ���� ����2��EXT��չ������
									       Uart2Usedfor485  ���� ����2����485ͨ�ţ���˫�����������ݰ�ʱ���ܽ������ݣ�
(2)	void SetUart2Rxd(char *RxdPt, unsigned int Nmax, char *matchhead, unsigned int matchheadsize);	
    ���ô���2���ղ��������ݰ����λ�á���С����ͷƥ���ַ���ƥ���ַ��������յ��������������ݰ�ʱ������enumEventRxd�¼���
	  ���������� char *RxdPt��ָ���������ݰ���������׵�ַ��
				       unsigned int Nmax���������ݰ���С���ֽ����������65535
               char *matchhead��  ��Ҫƥ������ݰ�ͷ���׵�ַ��
               unsigned int matchheadsize����Ҫƥ����ֽ���
     ����˵����
         Nmax=1��Ϊ���ֽڽ��գ����յ�һ���ֽھͲ���enumEventUart2Rxd�¼������������ƥ�䣬��������ƥ����������
	       0 < matchheadsize < Nmax��Ҫ���������������matchheadsize���ֽ���*matchhead��������ȫƥ�䣬�����յ�Nmax����ʱ����enumEventRxd�¼���
         matchheadsize = Nmax���趨�������ݰ���ȫƥ��
		     matchheadsize=0 �� matchheadsize > Nmax��������ƥ�䣬���յ�����Nmax����ʱ����enumEventRxd�¼���
		     ��enumEventRxd�¼������󣬽��յ������ݰ�Ӧ��ʱʹ�û�ȡ�����յ���һ������ʱ���ƻ��͸���ǰ���յ������ݰ�
(3)  char Uart2Print(void *pt, unsigned int num)���������ݰ������������������������ȵ����趨����ȫ����ɲŷ��أ����ú����ӱ����õ����ش�Լ1uS����ʱ�䡣
	 ����������  void *pt ��ָ���������ݰ�λ��
	             unsigned int num���������ݰ���С��
   ��������ֵ��enumTxOK�����óɹ��������趨�ķ������ݰ������ѱ�ϵͳsys��ȷ���ܣ�sys����Ӳ����Դ�����ܼ�ʱ�������ݡ�	
			         enumTxFailure������ʧ�ܣ���Ҫԭ���ǣ�������æ����һ���ݰ�δ���꣩
	 ����˵���������Ϸ���1���ֽ����ݴ�Լ��Ҫʱ��0.1mS��10mS�������趨�Ĳ����ʣ����Լ������˵��������Ͷ���ֽ���һ����Ҫʱ�������ɵ��¡�
	           ������ǰ���÷������������֣��������¼������"�첽"�����⣬���ʱ����Ҫע������߼��ԡ�����ע�����ʱЧ�ԡ������������ʵ����Ҫע�⡢����Ҫע��ģ�
(4)  char GetUart2TxStatus(void)�� ��ȡUart2����״̬
	 ��������ֵ��enumUart2TxFree:����2���Ϳ���
				       enumUart2TxBusy,����2������æ
(5) Uart2�����¼���enumUart2EventRxd����ʾ�յ���һ������ָ��Ҫ�����ݰ�ͷƥ�䡢���ݰ���Сһ�£������ݰ���


����˵����
  (1) ����1������2�����ʿɶ������ã�����Ӱ��.
	(2) ����1������2������ͨ�ſ�ͬʱ����������Ӱ��
	(3) ����1������2�÷���������ȫһ�£�����ͨ���÷�Ҳ������ͬ����ͬ�ط��ǣ�
          a������1�̶���USB�ӿ��ϣ�������������ͨ�ţ�������2�ɳ�ʼ����EXT��չ����485�ӿ��ϣ���485�ӿ���ʱ��������������
		      b������ͨ�����ʹ̶����ɱ䣨��Լ�൱��500��800 bps����ͨ��ʱû�а�ͷƥ�书�ܡ�����ģ���ͨ�Ź����⣬���ṩ���ڵ�������ң�ص�Ӧ�ú�����
          c������ͨ��ģ���Ϊ����������������ʱ�Զ��������״̬�������ݷ���ʱ�Զ����뷢��״̬�������ڽ������ݰ������в�����뷢��״̬��

��д����ɣ��绰18008400450��   2021��3��28�����
*/


#ifndef _uart2_H_
#define _uart2_H_

extern void Uart2Init(unsigned int band,unsigned char Uart2mode);						                           //����2��ʼ���������������ʡ�����2λ��
enum Uart2PortName  {Uart2UsedforEXT=00,Uart2Usedfor485}; 
extern void SetUart2Rxd(void *RxdPt, unsigned int Nmax, void *matchhead, unsigned int matchheadsize);	 //���ý������������ݰ����λ�á���С����ͷƥ���ַ���ƥ���ַ����������������İ�������enumUart2EventRxd�¼�
extern char Uart2Print(void *pt, unsigned int num);                                                    //�������ݰ������������������ݰ�λ�á���С������ֵenumUart2TxOK���óɹ���enumUart2TxFailureʧ�ܣ�����æ����һ���ݰ�δ���꣩
extern char GetUart2TxStatus(void);                                                                    //��ȡ����2����״̬,enumUart2TxFree:����2���Ϳ���, enumUart2TxBusy,����2������æ
enum Uart2ActName {enumUart2TxFree=0,enumUart2TxBusy,enumUart2TxOK,enumUart2TxFailure};

#endif