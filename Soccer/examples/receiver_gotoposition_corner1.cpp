#include "goReceivePosKickoffCenter.h"

extern "C"_declspec(dllexport)PlayerTask player_plan(const WorldModel* model, int robot_id);

//自定义单位
float AngularUnits = PI / 180;


//自定义函数



//向量的角度
float ang(point2f a)
{
	return a.angle();
}

//向量的长度
float len(point2f a)
{
	return sqrt(a.x*a.x + a.y*a.y);
}

//a到b的向量的角度
float angle_atob(const point2f& a, const point2f& b)
{
	return (b - a).angle();
}

//a到b的向量长度
float length_atob(const point2f& a, const point2f& b)
{
	return (b - a).length();
}

//以O为原点，x轴方向为极轴方向，顺时针旋转为正方向的极坐标系
point2f polarcoor_by_origin(point2f origin, float length, float dir)
{
	return origin + Maths::vector2polar(length, dir);
}
point2f polarcoor_by_origin(point2f origin, float length, point2f vector_origin, point2f vector_end)
{
	return origin + Maths::vector2polar(length, angle_atob(vector_origin, vector_end));
}

//搜索除自己与己方守门员之外离球最近的player并返回其id
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


//判断球是否在小车控球嘴上,距离阈值与角度阈值分别默认为16cm与30°
bool get_ball(const point2f& player_pos, const float& player_dir, const point2f& ball_pos, float len_threshold, float ang_threshold)
{
	return length_atob(ball_pos, player_pos) < len_threshold && fabs(anglemod(player_dir - angle_atob(player_pos, ball_pos))) < ang_threshold * AngularUnits;
}

PlayerTask player_plan(const WorldModel* model, int robot_id){
	PlayerTask task;
	//Player基本属性
	const PlayerVision& player = model->get_our_player(robot_id);
	const point2f& player_pos = model->get_our_player_pos(robot_id);
	const float& player_dir = model->get_our_player_dir(robot_id);
	const point2f& player_v = model->get_our_player_v(robot_id);
	//ball基本设置
	const BallVision& ball = model->get_ball();
	const point2f& ball_pos = model->get_ball_pos();
	const point2f& ball_v = model->get_ball_vel();
	//场景位置信息
	const point2f& goal_center_point = FieldPoint::Goal_Center_Point;
	const point2f& goal_left_center_point = -FieldPoint::Goal_Left_Point;
	const point2f& goal_right_center_point = -FieldPoint::Goal_Right_Point;
	const point2f& opp_goal_center_point = -FieldPoint::Goal_Center_Point;
	const point2f& opp_goal_left_center_point = FieldPoint::Goal_Left_Point;
	const point2f& opp_goal_right_center_point = FieldPoint::Goal_Right_Point;
	//场景中存在的队员序列号信息
	const bool* our_exist_id = model->get_our_exist_id();
	const bool* opp_exist_id = model->get_opp_exist_id();
	//符号位设置
	int rot_flag = 1;//1为顺时针旋转，-1为逆时针旋转
	//状态位设置
	bool is_ready_for_passing = false;
	bool is_get_ball;
	//默认初始化参数
	float dist = 9999;
	int other_our_player_id = -1;
	//自定义可调参数
	float len_threshold = 10;
	double temp_kickpower = 128;

	//逻辑入口
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
