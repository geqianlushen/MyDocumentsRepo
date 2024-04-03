#include "model.h"

extern "C"_declspec(dllexport)PlayerTask player_plan(const WorldModel* model, int robot_id);

//自定义单位
float angularUnits = PI / 180;


//自定义函数




//向量的角度
float ang(const point2f &a) {
    return a.angle();
}

//向量的长度
float len(const point2f &a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

//a到b的向量的角度
float angle_atob(const point2f &a, const point2f &b) {
    return (b - a).angle();
}

//a到b的向量长度
float length_atob(const point2f &a, const point2f &b) {
    return (b - a).length();
}

//以O为原点，x轴方向为极轴方向，顺时针旋转为正方向的极坐标系
point2f polarcoor_by_origin(const point2f& origin,const float& length,const float& dir) {
    return origin + Maths::vector2polar(length, dir);
}

point2f polarcoor_by_origin(const point2f& origin,const float& length,const point2f& vector_origin,const point2f& vector_end) {
    return origin + Maths::vector2polar(length, angle_atob(vector_origin, vector_end));
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
	bool our_is_get_ball;
	//默认初始化参数
	float dist = 9999;
	int other_our_player_id = -1;
	//自定义可调参数
	float len_threshold = 30;
	//逻辑入口
	







	return task;
}