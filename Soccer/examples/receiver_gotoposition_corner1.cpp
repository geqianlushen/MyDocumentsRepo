#include "goReceivePosKickoffCenter.h"

extern "C"_declspec(dllexport)PlayerTask player_plan(const WorldModel* model, int robot_id);

//�Զ��嵥λ
float AngularUnits = PI / 180;


//�Զ��庯��



//�����ĽǶ�
float ang(point2f a)
{
	return a.angle();
}

//�����ĳ���
float len(point2f a)
{
	return sqrt(a.x*a.x + a.y*a.y);
}

//a��b�������ĽǶ�
float angle_atob(const point2f& a, const point2f& b)
{
	return (b - a).angle();
}

//a��b����������
float length_atob(const point2f& a, const point2f& b)
{
	return (b - a).length();
}

//��OΪԭ�㣬x�᷽��Ϊ���᷽��˳ʱ����תΪ������ļ�����ϵ
point2f polarcoor_by_origin(point2f origin, float length, float dir)
{
	return origin + Maths::vector2polar(length, dir);
}
point2f polarcoor_by_origin(point2f origin, float length, point2f vector_origin, point2f vector_end)
{
	return origin + Maths::vector2polar(length, angle_atob(vector_origin, vector_end));
}

//�������Լ��뼺������Ա֮�����������player��������id
int search_player_nearst_ball(const WorldModel* model, int excluded_id)
{
	int our_player_nearest_id = -1;
	const bool* our_exist_id = model->get_our_exist_id();
	const point2f& ball_pos = model->get_ball_pos();
	float dist = 9999;
	for (int i = 0; i < MAX_ROBOTS; i++){
		if (our_exist_id[i]){
			const point2f& pos = model->get_our_player_pos(i);
			float our_player_to_ball_dist = length_atob(pos, ball_pos);
			if (our_player_to_ball_dist<dist&&i != excluded_id)
			{
				dist = our_player_to_ball_dist;
				our_player_nearest_id = i;
			}
		}
	}
	const point2f& our_player_nearest_player_pos = model->get_our_player_pos(our_player_nearest_id);
	if (our_player_nearest_player_pos.x<-270 && our_player_nearest_player_pos.y>-30 && our_player_nearest_player_pos.y < 30)
	{
		our_player_nearest_id = -1;
	}
	return our_player_nearest_id;
}


//�ж����Ƿ���С����������,������ֵ��Ƕ���ֵ�ֱ�Ĭ��Ϊ16cm��30��
bool get_ball(const point2f& player_pos, const float& player_dir, const point2f& ball_pos, float len_threshold, float ang_threshold)
{
	return length_atob(ball_pos, player_pos) < len_threshold && fabs(anglemod(player_dir - angle_atob(player_pos, ball_pos))) < ang_threshold * AngularUnits;
}

PlayerTask player_plan(const WorldModel* model, int robot_id){
	PlayerTask task;
	//Player��������
	const PlayerVision& player = model->get_our_player(robot_id);
	const point2f& player_pos = model->get_our_player_pos(robot_id);
	const float& player_dir = model->get_our_player_dir(robot_id);
	const point2f& player_v = model->get_our_player_v(robot_id);
	//ball��������
	const BallVision& ball = model->get_ball();
	const point2f& ball_pos = model->get_ball_pos();
	const point2f& ball_v = model->get_ball_vel();
	//����λ����Ϣ
	const point2f& goal_center_point = FieldPoint::Goal_Center_Point;
	const point2f& goal_left_center_point = -FieldPoint::Goal_Left_Point;
	const point2f& goal_right_center_point = -FieldPoint::Goal_Right_Point;
	const point2f& opp_goal_center_point = -FieldPoint::Goal_Center_Point;
	const point2f& opp_goal_left_center_point = FieldPoint::Goal_Left_Point;
	const point2f& opp_goal_right_center_point = FieldPoint::Goal_Right_Point;
	//�����д��ڵĶ�Ա���к���Ϣ
	const bool* our_exist_id = model->get_our_exist_id();
	const bool* opp_exist_id = model->get_opp_exist_id();
	//����λ����
	int rot_flag = 1;//1Ϊ˳ʱ����ת��-1Ϊ��ʱ����ת
	//״̬λ����
	bool is_ready_for_passing = false;
	bool is_get_ball;
	//Ĭ�ϳ�ʼ������
	float dist = 9999;
	int other_our_player_id = -1;
	//�Զ���ɵ�����
	float len_threshold = 10;
	double temp_kickpower = 128;

	//�߼����
	task.needCb = false;
	task.needKick = false;
	task.isChipKick = false;
	point2f templeft;
	templeft.x = ball_pos.x - 40;
	templeft.y = ball_pos.y - 10;
	point2f tempright;
	tempright.x = ball_pos.x - 40;
	tempright.y = ball_pos.y + 10;
	point2f kicker_temp(170, 0);
	if (ball_pos.y > 0)
	{
		task.target_pos = tempright;
		task.orientate = angle_atob(player_pos, ball_pos);
		if (length_atob(player_pos, ball_pos) < 30)
		{
			task.needCb = true;
		}
		return task;
	}
	else
	{
		task.target_pos = templeft;
		task.orientate = angle_atob(player_pos, ball_pos);
		if (length_atob(player_pos, ball_pos) < 30)
		{
			task.needCb = true;
		}
		return task;
	}
}
