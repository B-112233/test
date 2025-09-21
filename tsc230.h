#define pred   9
#define pgreen 13
#define pblue  13



sbit  LED  =   P1^3;
sbit  S0   =   P2^1;     
sbit  S1   =   P2^2;     
sbit  S2   =   P2^3;    
sbit  S3   =   P2^4;

int disp_tc;
long int red , blue, green;

void Timer_tsc_init()
{
	TMOD = 0x51;        					//设置定时器0以方式一10ms，计数器1方式一
	TH0 = 0xFC;         					//设置定时器0计数值1ms
	TL0 = 0x66;
	TH1 = 0x00;
	TL1 = 0x00;
	EA = 1;									 //设置允许总中断 	
	ET0 = 1;								 //设置允许定时器一中断
	ET1 = 0;
	TR0=1;
	TR1=1;
}					  

void Timer0_Rountine() interrupt 1
{
	TR0 = 0;
	TR1 = 0;	
	disp_tc++;
	TH0 = 0xfc;         					//设置定时器0计数值
	TL0 = 0x66+TL0;
	TR0 = 1;
	TR1 = 1;
}

void tsc_init()
{
	Timer_tsc_init();
	LED=1;
	S0=1;
	S1=1;
}

void Filtermode(int s2,int s3)
{		  //01蓝  11绿  00红
	int count = 0;
	S2=s2;
	S3=s3;
	if(s2 == 0 && s3 == 0) count = pred;
	if(s2 == 0 && s3 == 1) count = pblue;
	if(s2 == 1 && s3 == 1) count = pgreen;
	TR0 = 1;
	TR1 = 1;
	while(disp_tc!=count);
	TR0=0;
	TR1=0;
	if(S2==0&&S3==1)blue  =  (TH1*256+TL1);
	if(S2==1&&S3==1)green =  (TH1*256+TL1);
	if(S2==0&&S3==0)red   =  (TH1*256+TL1);
	TL1=0x00;
	TH1=0x00;
	disp_tc=0;
}

int get_color(void)
{ 
	int Blue=0,Black=0,Red=0,White=0,Yellow=0,Co=0,Temp=0,colori =0;
	while(Co++<10)
	{
		disp_tc=0;
		//选择蓝色滤光
		Filtermode(0,1);TR0=1;TR1=1;
		//选择绿色滤光
		Filtermode(1,1);TR0=1;TR1=1;
		 //选择红色滤光
		Filtermode(0,0); 
//		printf("red=%ld,green=%ld,blue=%ld\n",red,green,blue);
		if(red>=5   && red<=35 && green>=10  && green<=35  && blue>=20  && blue<=50)Blue++;//blue
		if(red>=0   && red<=25  && green>=0   && green<=25  && blue>=0   && blue<=20)Black++;///black
		if(red>=100 && red<=190  && green>=10  && green<=60 && blue>=5   && blue<= 80)Red++;//red
		if(red>=120 && red<=280 && green>=171 && green<=280 && blue>=160 && blue<=280)White++;//white
		if(red>=280 && green>=280 && blue>=200)Yellow++;//yellow  
	}
	TR0 = 0;
	TR1 = 0;
	Temp=Blue;
	if(Temp<Black)	{Temp=Black;  colori=4;}
	if(Temp<Red)		{Temp=Red;	  colori=3;}
	if(Temp<White)	{Temp=White;  colori=2;}
	if(Temp<Yellow)	{Temp=Yellow; colori=1;}
	if(Temp==Blue)    colori=5;
					//===============================
	LED=0;									
	return colori;		
}
					
		



