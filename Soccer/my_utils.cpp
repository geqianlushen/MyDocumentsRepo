#include "src/utils/PlayerTask.h"
#include "src/utils/worldmodel.h"
#include "src/utils/maths.h"
#include "src/utils/constants.h"

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

//搜索除自己与己方守门员之外离球最近的player并返回其id
int search_player_nearst_ball(const WorldModel* model,const  int& excluded_id)
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
bool get_ball(const point2f& player_pos, const float& player_dir, const point2f& ball_pos,const float& len_threshold,const float& ang_threshold)
{
	return length_atob(ball_pos, player_pos) < len_threshold && fabs(anglemod(player_dir - angle_atob(player_pos, ball_pos))) < ang_threshold * AngularUnits;
}

