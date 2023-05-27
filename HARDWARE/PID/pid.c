#include "pid.h"
//����һ���ṹ�����ͱ���
tPid pidMotor1Speed;//���1�ٶ�PID�ջ�����
tPid pidMotor2Speed;//���2�ٶ�PID�ջ�����

//���ṹ�����ͱ�������ֵ
void PID_init()
{
	pidMotor1Speed.actual_val=0.0;
	pidMotor1Speed.target_val=0.00;
	pidMotor1Speed.err=0.0;
	pidMotor1Speed.err_last=0.0;
	pidMotor1Speed.err_sum=0.0;
	pidMotor1Speed.Kp=15;
	pidMotor1Speed.Ki=5;
	pidMotor1Speed.Kd=0;
	
	pidMotor2Speed.actual_val=0.0;
	pidMotor2Speed.target_val=0.00;
	pidMotor2Speed.err=0.0;
	pidMotor2Speed.err_last=0.0;
	pidMotor2Speed.err_sum=0.0;
	pidMotor2Speed.Kp=15;
	pidMotor2Speed.Ki=5;
	pidMotor2Speed.Kd=0;
	
	
}

// PID���ƺ���
float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//������ʵֵ
	pid->err = pid->target_val - pid->actual_val;////��ǰ���=Ŀ��ֵ-��ʵֵ
	pid->err_sum += pid->err;//����ۼ�ֵ = ��ǰ����ۼƺ�
	//ʹ��PID���� ��� = Kp*��ǰ���  +  Ki*����ۼ�ֵ + Kd*(��ǰ���-�ϴ����)
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
	//�����ϴ����: �����ֵ���ϴ����
	pid->err_last = pid->err;
	
	return pid->actual_val;
}
