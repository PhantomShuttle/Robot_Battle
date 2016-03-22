#define A1 0
#define A2 1
#define B1 2
#define B2 3
#define C1 4
#define C2 5
#define D1 6
#define D2 7
#define delay_time 100  //delay_time  每一步间隔的时间 单位 ms       一般值 100
/*robot_stand
Foot_age   -90~90 两腿展开还是并拢 一般值 0
Foot_height -90~90脚的高度位置 一般值-90*/
void robot_stand(int Foot_age,int Foot_height)
{servo_age(A1,Foot_age);servo_age(A2,Foot_height);
 servo_age(B1,-Foot_age);servo_age(B2,Foot_height);
 servo_age(C1,Foot_age);servo_age(C2,Foot_height);
 servo_age(D1,-Foot_age);servo_age(D2,Foot_height);	
}


 void rest(uchar R){
	 static uchar R_l=0;
	 if (!(R_l==R))
	 {time_seve=0;robot_stand(0,-90); }
	 R_l=R;
 }
 
 /*robot_move
  x_step +90~-90 x轴方向 每一步的大小 正值右移 负值左移                 一般值 45
  y_step +90~-90 y轴方向 每一步的大小 正值前进 负值后退                 一般值 45
  turn_step +90~-90 z轴转动 每一步角度 正值逆时针 负值顺时针            一般值 20
  Foot_height_down -90~0   脚的放下时的角度                             一般值 -90
  Foot_height_up   0~100   抬脚时候 相对于Foot_height_down 抬起多少角度 一般值 90
  step_time    0~65535     每一步间隔时间 单位ms 分辨率20ms             一般值 100
 */
 void robot_move(int x_step,int y_step,int turn_step,int Foot_height_down,int Foot_height_up,unsigned int step_time)
 {  static uint con1,con2;
	 con1=time_seve;con1=con1%(step_time/20*6)/(step_time/20);
	 if (!(con1==con2))
	 {	 
		 switch (con1)
		 {
			 case 0: servo_age(A2,Foot_height_up+Foot_height_down);servo_age(C2,Foot_height_up+Foot_height_down);//抬起
			         servo_age(B1,y_step+ turn_step-x_step);servo_age(D1,-1*y_step+ turn_step+x_step);break;
			 case 1: servo_age(A1,-1*y_step- turn_step-x_step);	servo_age(C1,y_step- turn_step+x_step);break;
			 case 2: servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);break; //放下
			 
			 case 3: servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);//抬起
			         servo_age(A1,y_step+ turn_step+x_step);servo_age(C1,-1*y_step+ turn_step-x_step);break;
			 case 4: servo_age(B1,-1*y_step- turn_step+x_step);servo_age(D1,y_step- turn_step-x_step);break;//旋转
			 case 5: servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);break;//放下
			 
			 default:time_seve=0;break;	
	      }
	    con2=con1;
	 }
 }
 void robot_Sur_Place(char foot,int Foot_height_down,int Foot_height_up,unsigned int step_time)
 {
	robot_move( 0,0,0,Foot_height_down, Foot_height_up,step_time);
 }
/*
 
/ *
   robot_walk
step             +90~-90 每一步的大小 正值前进 负值后退               一般值 45
Foot_height_down -90~0   脚的放下时的角度                             一般值 -90 
Foot_height_up   0~100   抬脚时候 相对于Foot_height_down 抬起多少角度 一般值 90 
* /
void robot_walk(int step,int Foot_height_down,int Foot_height_up)
{  static uint con1,con2;
   con1=time_seve;con1=con1%30/5;
 if (!(con1==con2))
 {
 
 	switch (con1)
 	{
 	case 0:servo_age(A2,Foot_height_up+Foot_height_down);servo_age(C2,Foot_height_up+Foot_height_down);//抬起
 	        servo_age(B1,step);servo_age(D1,-1*step);break;
	case 1: servo_age(A1,-1*step);	servo_age(C1,step);break; 
 	case 2:	servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);break; //放下
	 
	case 3:servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);//抬起
	          servo_age(A1,step);servo_age(C1,-1*step);break;
	case 4: servo_age(B1,-1*step);servo_age(D1,step);break;//旋转
	case 5:servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);break;//放下
	 default:time_seve=0;break;
 	}
 }
con2=con1;
	 
/ *
	static char move_star=0;

	if (move_star==0)
	{
		servo_age(A2,Foot_height_up+Foot_height_down);servo_age(C2,Foot_height_up+Foot_height_down);//抬起
		
		 servo_age(B1,step);servo_age(D1,-1*step);_delay_ms(delay_time);
		 servo_age(A1,-1*step);	servo_age(C1,step);_delay_ms(delay_time);
		servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);_delay_ms(delay_time);//放下
		move_star=1;
	}
	else if (move_star==1)
	{
		servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);//抬起
		
		servo_age(A1,step);servo_age(C1,-1*step);_delay_ms(delay_time);
		servo_age(B1,-1*step);servo_age(D1,step);_delay_ms(delay_time);//旋转
		servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);_delay_ms(delay_time);//放下
		move_star=0;
	}
* /

}

/ *   robot_turn
foot     1或-1 先抬起哪对腿 1-AC 2-BD
step             +90~-90 每一步的大小 正值左转 负值右转               一般值 45
Foot_height_down -90~0   脚的放下时的角度                             一般值 -90 
Foot_height_up   0~100   抬脚时候 相对于Foot_height_down 抬起多少角度 一般值 90 
* /
void robot_turn(char foot,int step,int Foot_height_down,int Foot_height_up)
{    static uint con1,con2;
	con1=time_seve;con1=con1%30/5;
	 if (!(con1==con2))
	 {
	   if (foot==1)
	   {
	  	switch (con1)
	  	  {
		    case 0:	servo_age(A2,(Foot_height_up+Foot_height_down));servo_age(C2,(Foot_height_up+Foot_height_down));break;//抬起
		    case 1:	servo_age(A1,-1*step);servo_age(B1,step);servo_age(C1,-1*step);servo_age(D1,step);break;
		    case 2: 	servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);break;//放下
		  	
		    case 3:	servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);break;//抬起
		    case 4:	servo_age(A1,0);servo_age(B1,0);servo_age(C1,0);servo_age(D1,0);break;
		    case 5:	servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);break;//放下
			 default:time_seve=0;break;
	  	  }
	   }
	  	
       else if (foot==-1)
	  	{
		 switch (con1)
		  	{
			 case 0:servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);break;//抬起
		     case 1:	servo_age(A1,step);servo_age(B1,-1*step);servo_age(C1,step);servo_age(D1,-1*step);break;
		     case 2:	servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);break;//放下
		  	
		     case 3:	servo_age(A2,Foot_height_up+Foot_height_down);servo_age(C2,Foot_height_up+Foot_height_down);break;//抬起
		     case 4:	servo_age(A1,0);servo_age(B1,0);servo_age(C1,0);servo_age(D1,0);break;
		     case 5:	servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);break;//放下
	         }
		 }
	
	  }
	  con2=con1;
	
	/ *  	if (foot==1)
   {   
	servo_age(A2,(Foot_height_up+Foot_height_down));servo_age(C2,(Foot_height_up+Foot_height_down));_delay_ms(delay_time);//抬起
	servo_age(A1,-1*step);servo_age(B1,step);servo_age(C1,-1*step);servo_age(D1,step);_delay_ms(delay_time);
	servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);_delay_ms(delay_time);//放下
	
	servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);_delay_ms(delay_time);//抬起
	servo_age(A1,0);servo_age(B1,0);servo_age(C1,0);servo_age(D1,0);_delay_ms(delay_time);
	servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);_delay_ms(delay_time);//放下
    }
	
   else if (foot==-1)
   {   
	servo_age(B2,Foot_height_up+Foot_height_down);servo_age(D2,Foot_height_up+Foot_height_down);_delay_ms(delay_time);//抬起
	servo_age(A1,step);servo_age(B1,-1*step);servo_age(C1,step);servo_age(D1,-1*step);_delay_ms(delay_time);
	servo_age(B2,Foot_height_down);servo_age(D2,Foot_height_down);_delay_ms(delay_time);//放下
	
	servo_age(A2,Foot_height_up+Foot_height_down);servo_age(C2,Foot_height_up+Foot_height_down);_delay_ms(delay_time);//抬起
	servo_age(A1,0);servo_age(B1,0);servo_age(C1,0);servo_age(D1,0);_delay_ms(delay_time);
	servo_age(A2,Foot_height_down);servo_age(C2,Foot_height_down);_delay_ms(delay_time);//放下
    }* /	
}


void robot_turn_little(void)
{
	 //小旋转
		/ *servo_age(A2,0);servo_age(C2,0);_delay_ms(100);//抬起a2c 	
	    servo_age(A1,45);servo_age(C1,45);_delay_ms(100);//旋转a1c1
		servo_age(A2,-90);servo_age(C2,-90);_delay_ms(100);//放下a2c2	
	
		servo_age(B2,0);servo_age(D2,0);_delay_ms(100);//抬起
		servo_age(B1,45);servo_age(D1,45);_delay_ms(100);//旋转
		servo_age(B2,-90);servo_age(D2,-90);_delay_ms(100);//放下
		servo_age(A1,0);servo_age(B1,0);servo_age(C1,0);servo_age(D1,0);_delay_ms(100);* /
}*/