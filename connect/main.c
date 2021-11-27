#include "ir.h"
#include "Key.H"
#include "sys.h"
#include "uart1.h"
#include "STC15F2K60S2.H"        //必须。
#include "displayer.h"
#include "adc.h"
#include "stdio.H"
#include "math.h"
#include "beep.h"
#include "string.h"
#include "music.h"
#include "m24c02.h"
#include "stdlib.h"

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致
#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80,0x77,0x79,0x39,0x37,0x76,0x30};  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9       R    E    C    N    H    I*/
#endif

unsigned char funcmode;                  //举例。定义显示、按键功能模式
enum funcname {                       //                    
               Rectxt,                     //                   
               Sendtxt,
							 Checktxt,
							 AI_Response}; 
unsigned char tempmode=0;

unsigned char rxd[8];                          //举例。通信（串口1、串口2、红外共用）缓冲区8字节
unsigned char rxdhead[2]={0xaa,0x55};          //举例。通信（串口1、串口2）接收包头匹配字符2字节：（0xAA，0x55）    
unsigned char wordtxt[20];
unsigned char d1,d2,d3,d4,d5,d6,d7,d8;
static t;
static flag;
static fmc;
int weishu;
int Ledt=1;
int music_on=0;


void deal_Seg(){
		char temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		static unsigned char ct100mS=10;
		if(tempmode==2){
		temp1=d1;
		temp2=d2;
		temp3=d3;
		temp4=d4;
		temp5=10;
		temp6=29;
		temp7=27;
		temp8=5;
		if(--ct100mS == 0) ct100mS=10;
		if(ct100mS >= 8){
			if(flag){
			switch(weishu){
				case 1: temp1=10;break;
				case 2: temp2=10;break;
				case 3: temp3=10;break;
				case 4: temp4=10;break;
				default:break;
			}
			}
		}
		}
		if(tempmode==4){
			temp1=d1;
			temp2=d2;
			temp3=d3;
			temp4=d4;
			temp5=12;
			temp6=12;
			temp7=31;
			temp8=26;
			if(--ct100mS == 0) ct100mS=10;
			if(ct100mS >= 8){
				if(flag){
				switch(weishu){
				case 1: temp1=10;break;
				case 2: temp2=10;break;
				case 3: temp3=10;break;
				case 4: temp4=10;break;
				default:break;
				}
			}
		}
		
		}
		if(tempmode==1){
			temp8=26;
			temp7=27;
			temp6=28;
			temp5=10;
			temp4=GetIrRxNum()/1000%10;
			temp3=GetIrRxNum()/100%10;
			temp2=GetIrRxNum()/10%10;
			temp1=GetIrRxNum()%10;
		}
		if(tempmode==3){
			temp8=28;
			temp7=30;
			temp6=27;
			temp1=d1;
			temp2=d2;
			temp3=d3;
			temp4=d4;
			temp5=10;
		}
		if(tempmode==0){
			temp1=12;
			temp2=12;
			temp3=12;
			temp4=12;
			temp5=12;
			temp6=12;
			temp7=12;
			temp8=12;
		}
		Seg7Print(temp8,temp7,temp6,temp5,temp4,temp3,temp2,temp1);
}

void deal_Nav(){
		int i=0;
		int op;
		char temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8;
		if((tempmode==2)||(tempmode==4)){
						temp1=d1;
						temp2=d2;
						temp3=d3;
						temp4=d4;
		
			if(GetAdcNavAct(enumAdcNavKeyLeft) == enumKeyPress)  {if(flag) if(weishu<4){
				weishu++;
				switch(weishu){
						case 1:d1=0;break;
						case 2:d2=0;break;
						case 3:d3=0;break;
						case 4:d4=0;break;
						default:break;
				}
				SetBeep(1000,20);
			}
		}
		if(GetAdcNavAct(enumAdcNavKeyRight)  == enumKeyPress)  {if(flag) if(weishu>1){
			weishu--;
			switch(weishu){
				case 0:d1=10;break;
				case 1:d2=10;break;
				case 2:d3=10;break;
				case 3:d4=10;break;
				default:break;
			}
			SetBeep(1000,20);
			}
		}
		if(GetAdcNavAct(enumAdcNavKeyUp)== enumKeyPress)  {
			if(flag){
				switch(weishu){
					case 1:d1++;break;
					case 2:d2++;break;
					case 3:d3++;break;
					case 4:d4++;break;
					default:break;
				}
			}
		}
		if(GetAdcNavAct(enumAdcNavKeyDown)== enumKeyPress)  {
				if(flag){
					switch(weishu){
						case 1:d1--;break;
						case 2:d2--;break;
						case 3:d3--;break;
						case 4:d4--;break;
						default:break;
					}
				}
			}
			if(GetAdcNavAct(enumAdcNavKey3)== enumKeyPress){
				flag=!flag;
				if(tempmode==4)
					for(op=0;op<20;op++){
							wordtxt[op]='\0';
					}
				SetBeep(1000,20);
			}
			if(temp1==10)temp1=0;
			if(temp2==10)temp2=0;
			if(temp3==10)temp3=0;
			if(temp4==10)temp4=0;
			t=temp4*pow(10,3)+temp3*pow(10,2)+temp2*pow(10,1)+temp1;
			SetUart1Rxd(wordtxt, t, rxdhead, 0);
		}
}


void deal_music(){
		static ps=0;
		if(music_on==1){
			if(fmc==1){
				switch(wordtxt[ps]){
						case '1':
							if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x21, 0x10);
									ps++;
							}
							break;
						case '2':
							if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x22, 0x10);
									ps++;
							}
							break;
						case '3':
							if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x23, 0x10);
									ps++;
							}
						case '4':
							if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x24, 0x10);
									ps++;
							}
						case '5':
						  if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x25, 0x10);
									ps++;
							}
						case '6':
							if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x26, 0x10);
									ps++;
							}
						case '7':
							if(GetBeepStatus()==0){
									PlayTone(0xFA, 250 ,0x27, 0x10);
									ps++;
							}
				}
	
			}
					
		}
		if(ps>=t){
				ps=0;
		}
			
		
		

}

void deal_AI(){
		
		
		if(tempmode==4){
				if(strcmp(wordtxt,"music on")==0){
						music_on=1;
						Uart1Print("You are a creator",sizeof("You are a creator"));
				}
				/*if(music_on==1){
						Uart1Print("This is your music",sizeof("This is your music") );
				}*/
				if(strcmp(wordtxt,"music off")==0){
						music_on=0;
						Uart1Print("What do you want to do next",sizeof("What do you want to do next"));
				}
		}
		
}


void deal_Ir(){
	if(tempmode==1){
			if(GetIrRxNum()!=0){
					SetBeep(1000,60);
					Uart1Print(&wordtxt,GetIrRxNum());
			}
	}
	
}

void deal_Key(){
			if(GetKeyAct(enumKey1)==enumKeyPress){
				if(tempmode==2){
						IrPrint(&wordtxt,t);
				}
				if(tempmode==3)
				Uart1Print(&wordtxt,t);
				if(tempmode==4){
						if(music_on==1)
						{
								SetBeep(1000,20);
								fmc=!fmc;
								if(fmc==1)
								Uart1Print( "Let's Play",sizeof("Let's Play"));
						}
						else{
								SetBeep(1000,20);
								Uart1Print( "Have a good day",sizeof("Have a good day"));
						}
				}
			}
			if (GetKeyAct(enumKey2)== enumKeyPress){    		                                        //示例。按键2:（按下时）切换显示和按键功能模式         	
					SetBeep(1000,20);	
					if(++funcmode > AI_Response) funcmode= Rectxt;	
					M24C02_Write(0x00,funcmode); 
					if (funcmode == Checktxt){
							tempmode=3;
							SetUart1Rxd(wordtxt, t, rxdhead, 0);
					}
					if(funcmode == Rectxt){
							tempmode=1;
							SetIrRxd(wordtxt);
							SetUart1Rxd(wordtxt,GetIrRxNum(), rxdhead, 0);
					}
					if(funcmode == Sendtxt){
							tempmode=2;
					}
					if (funcmode == AI_Response){
							tempmode=4;
					}
			}
}

void deal_Led()
{
	static i;
	if((tempmode==2)||(tempmode==3))
			LedPrint(t);
	if((tempmode==0)||(tempmode==4)){
			i++;
			if(i==10){
					i=0;
					LedPrint(Ledt);
					Ledt=Ledt*2;
					if(Ledt>512)Ledt=1;
			}
	}
	if(tempmode==1){
			LedPrint(GetIrRxNum());
	}
}

void main(){
		MySTC_Init();	    // MySTC_OS 初始化         //此行必须！！！
		IrInit(NEC_R05d);
		DisplayerInit();
		BeepInit();
		AdcInit(ADCexpEXT);                              //举例，ADC模块初始化，有参数，选择扩展接口EXT上P1.0、P1.1是否也做ADC功能
		Key_Init();
		MusicPlayerInit();
		Uart1Init(1200);
		d1=0;
		d2=10;
		d3=10;
		d4=10;
		d5=10;
		d6=10;
		d7=10;
		d8=10;
		weishu=0;
		SetDisplayerArea(0,7); 
		SetEventCallBack(enumEventSys1mS , deal_Led);
		SetEventCallBack(enumEventSys100mS , deal_Seg);
		SetEventCallBack(enumEventSys10mS , deal_music);
		SetEventCallBack(enumEventKey, deal_Key);
		SetEventCallBack(enumEventIrRxd,deal_Ir);
		SetEventCallBack(enumEventUart1Rxd,deal_AI);
		SetEventCallBack(enumEventNav, deal_Nav); //导航按键事件触发
		
		while(1)            // 系统主循环              //此行必须！！！   	
		{ MySTC_OS();     // MySTC_OS 加载           //此行必须！！！
/*****************  MySTC_OS 初始化与加载结束  ********************************/  
			
//******* 用户程序段7：用户main()函数（主循环程序） *************//
			
			
		}	              //主循环while(1)结束         //此行必须！！！ 

}