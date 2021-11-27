/********************************** Uart2串行通信模块 V1.0 说明 ***************************************************************
Uart2模块提供Uart2模块初始化函数、3个应用函数,1个事件（enumUart2EventRxd）：
(1)	Uart2Init(unsigned int band,unsigned char Uart2mode)：Uart2模块初始化函数。
    函数参数：unsigned int band：定义串口2的通信波特率（单位：bps）（固定8个数据位、1个停止位，无奇偶校验位）
		          unsigned char Uart2mode：定义串口2位置
							     取值：Uart2UsedforEXT  —— 串口2在EXT扩展插座上
									       Uart2Usedfor485  —— 串口2用于485通信（半双工。发送数据包时不能接收数据）
(2)	void SetUart2Rxd(char *RxdPt, unsigned int Nmax, char *matchhead, unsigned int matchheadsize);	
    设置串口2接收参数：数据包存放位置、大小，包头匹配字符、匹配字符个数。收到符合条件的数据包时将产生enumEventRxd事件。
	  函数参数： char *RxdPt：指定接收数据包存放区（首地址）
				       unsigned int Nmax：接收数据包大小（字节数），最大65535
               char *matchhead：  需要匹配的数据包头（首地址）
               unsigned int matchheadsize：需要匹配的字节数
     补充说明：
         Nmax=1：为单字节接收，即收到一个字节就产生enumEventUart2Rxd事件（如果定义了匹配，还需满足匹配条件）；
	       0 < matchheadsize < Nmax：要求接收数据中连续matchheadsize个字节与*matchhead处数据完全匹配，才在收到Nmax数据时产生enumEventRxd事件；
         matchheadsize = Nmax：设定接收数据包完全匹配
		     matchheadsize=0 或 matchheadsize > Nmax：将不做匹配，接收到任意Nmax数据时产生enumEventRxd事件；
		     在enumEventRxd事件发出后，接收到的数据包应及时使用或取出，收到下一个数据时将破坏和覆盖前面收到的数据包
(3)  char Uart2Print(void *pt, unsigned int num)：发送数据包，非阻塞函数（即函数不等到所设定任务全部完成才返回），该函数从被调用到返回大约1uS左右时间。
	 函数参数：  void *pt ：指定发送数据包位置
	             unsigned int num：发送数据包大小；
   函数返回值：enumTxOK：调用成功，即所设定的发送数据包请求已被系统sys正确接受，sys将尽硬件资源最大可能及时发送数据。	
			         enumTxFailure：调用失败（主要原因是：串口正忙（上一数据包未发完）
	 补充说明：串口上发送1个字节数据大约需要时间0.1mS～10mS（视所设定的波特率），对计算机来说，如果发送多个字节是一个很要时间才能完成的事。
	           类似于前面用蜂鸣器演奏音乐，对这类事件与程序"异步"的问题，编程时不仅要注意程序逻辑性、还有注意程序时效性。（这个问题其实总是要注意、必须要注意的）
(4)  char GetUart2TxStatus(void)： 获取Uart2发送状态
	 函数返回值：enumUart2TxFree:串口2发送空闲
				       enumUart2TxBusy,串口2发送正忙
(5) Uart2接收事件：enumUart2EventRxd。表示收到了一个符合指定要求（数据包头匹配、数据包大小一致）的数据包。


补充说明：
  (1) 串口1、串口2波特率可独立设置，互不影响.
	(2) 串口1、串口2、红外通信可同时工作，互不影响
	(3) 串口1、串口2用法基本上完全一致，红外通信用法也基本相同。不同地方是：
          a，串口1固定在USB接口上，可用于与计算机通信；而串口2可初始化在EXT扩展、或485接口上（在485接口上时仅单工工作）；
		      b，红外通信速率固定不可变（大约相当于500～800 bps），通信时没有包头匹配功能。红外模块除通信功能外，还提供用于电器红外遥控的应用函数；
          c，红外通信模块仅为单工工作。不发送时自动进入接收状态；有数据发送时自动进入发送状态，但正在接收数据包过程中不会进入发送状态。

编写：徐成（电话18008400450）   2021年3月28日设计
*/


#ifndef _uart2_H_
#define _uart2_H_

extern void Uart2Init(unsigned int band,unsigned char Uart2mode);						                           //串口2初始化，参数：波特率、串口2位置
enum Uart2PortName  {Uart2UsedforEXT=00,Uart2Usedfor485}; 
extern void SetUart2Rxd(void *RxdPt, unsigned int Nmax, void *matchhead, unsigned int matchheadsize);	 //设置接收条件：数据包存放位置、大小，包头匹配字符、匹配字符个数。符合条件的包将产生enumUart2EventRxd事件
extern char Uart2Print(void *pt, unsigned int num);                                                    //发送数据包。非阻塞函数。数据包位置、大小。返回值enumUart2TxOK调用成功，enumUart2TxFailure失败（串口忙，上一数据包未发完）
extern char GetUart2TxStatus(void);                                                                    //获取串口2发送状态,enumUart2TxFree:串口2发送空闲, enumUart2TxBusy,串口2发送正忙
enum Uart2ActName {enumUart2TxFree=0,enumUart2TxBusy,enumUart2TxOK,enumUart2TxFailure};

#endif