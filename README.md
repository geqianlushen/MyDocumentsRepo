# soccer

## 一、基础信息模块

### 1、Player基础属性

| 属性名     | 类型                | 说明                                           |
| ---------- | ------------------- | ---------------------------------------------- |
| player     | const PlayerVision& | 机器人                                         |
| player_pos | const point2f&      | 位置坐标（x，y）                               |
| player_dir | const float&        | 方位（以x为极轴，顺时针为正，范围[-π/2，π/2]） |
| player_v   | const point2f&      | 速度                                           |

### 2、ball基础属性

| 属性名   | 类型              | 说明     |
| -------- | ----------------- | -------- |
| ball     | const BallVision& | 球       |
| ball_pos | const point2f&    | 球的坐标 |
| ball_v   | const point2f&    | 球的速度 |

### 3、场景信息

| 属性名                      | 类型           | 说明             |
| --------------------------- | -------------- | ---------------- |
| goal_center_point           | const point2f& | 我方球门中心     |
| goal_left_center_point      | const point2f& | 我方球门左端点   |
| goal_right_center_point     | const point2f& | 我方球门右端点   |
| opp_goal_center_point       | const point2f& | 敌方球门中心     |
| opp_goal_left_center_point  | const point2f& | 敌方球门左端点   |
| opp_goal_right_center_point | const point2f& | 敌方球门右端点   |
| our_exist_id                | const bool*    | 我方在场球员列表 |
| opp_exist_id                | const bool*    | 敌方在场球员列表 |

### 4、单位设置

| 属性名       | 类型  | 说明             |
| ------------ | ----- | ---------------- |
| AngularUnits | float | PI / 180单位角度 |

### 5、其他设置

| 属性名          | 类型     | 说明           |
| --------------- | -------- | -------------- |
| player_head_pos | point2f& | 机器人头部坐标 |

## 二、自定义辅助标志

### 1、符号位设置（常取值为1或-1）（可自己设置）

| 属性名   | 类型 | 说明                          |
| -------- | ---- | ----------------------------- |
| rot_flag | int  | 1为顺时针旋转，-1为逆时针旋转 |

### 2、状态位设置（常用于判断是否符合某状态）（可自己设置）

| 属性名                     | 类型 | 说明                                     |
| -------------------------- | ---- | ---------------------------------------- |
| is_ball_moving             | bool | 判断小球两帧距离是否大于某阈值           |
| is_ball_beside_player_head | bool | 判断小球是否在吸球嘴附近                 |
| is_get_ball                | bool | 判断球是否在小车控球嘴上                 |
| is_opp_block_shoot         | bool | 判断两位置传球或踢球是否有敌方的球员阻挡 |
| is_ready_for_passing       | bool | 是否准备好传球                           |
| is_toward_opp_goal         | bool | 是否朝向对面球门                         |
| is_player_behind_ball      | bool | player是否在ball与opp_goal之间           |

### 3、预留初始化参数（可自己设置）

| 属性名              | 类型  | 说明 |
| ------------------- | ----- | ---- |
| dist                | float | 9999 |
| other_our_player_id | int   | -1   |

### 4、自定义可调参数（需要根据场景自行调参）

| 属性名             | 类型          | 说明                                   |
| ------------------ | ------------- | -------------------------------------- |
| receive_pos_back   | const point2f | 默认值为(ball_pos.x - 70, ball_pos.y)  |
| receive_pos_center | const point2f | 默认值为(ball_pos.x, 0)                |
| receive_pos_front  | const point2f | 默认值为(ball_pos.x + 150, ball_pos.y) |

### 5、常用的规范命名属性或标志

| 属性名        | 类型    | 说明                 |
| ------------- | ------- | -------------------- |
| target_pos    | point2f | 全局目标点           |
| orientate     | double  | 全局目标到点朝向     |
| global_vel    | point2f | 全局目标到点平动速度 |
| rot_vel       | double  | 全局目标到点转动速度 |
| rot_dir       | int     | 旋转的方向           |
| needKick      | bool    | 踢球动作执行开关     |
| isPass        | bool    | 是否进行传球         |
| needCb        | bool    | 是否吸球             |
| isChipKick    | bool    | 挑球还是平射         |
| kickPower     | double  | 踢球力度             |
| chipKickPower | double  | 挑球力度             |

## 三、自定义函数

### 1、向量的角度

` float ang(const point2f& a)`

| **Parameter** | **Type**       | **Illustrateation**      |
| ------------- | -------------- | ------------------------ |
| **a**         | const point2f& | A点坐标                  |
| **Return**    | float          | 向量A的方向角[-π/2，π/2] |

### 2、向量的长度

  `float len(const point2f& a)`

| **Parameter** | **Type**       | **Illustrateation** |
| ------------- | -------------- | ------------------- |
| **a**         | const point2f& | A点坐标             |
| **Return**    | float          | 向量A的长度         |

 

### 3、求向量ab的角度（a指向b）

`float angle_atob(const point2f& a, const point2f& b)`

| **Parameter** | **Type**       | **Illustrateation**       |
| ------------- | -------------- | ------------------------- |
| **a**         | const point2f& | A点坐标                   |
| **b**         | const point2f& | B点坐标                   |
| **Return**    | float          | 向量AB的方向角[-π/2，π/2] |

### 4、求向量ab的模长

`float length_atob(const point2f& a, const point2f& b)`

| **Parameter** | **Type**       | **Illustrateation** |
| ------------- | -------------- | ------------------- |
| **a**         | const point2f& | A点坐标             |
| **b**         | const point2f& | B点坐标             |
| **Return**    | float          | 向量AB的模长        |

### 5、变换原点的极坐标。求以O为原点，x轴方向为极轴方向，顺时针旋转为正方向的极坐标系点

   ` point2f polarcoor_by_origin(const point2f& origin,const float& length,const float& dir)`

| **Parameter** | **Type**         | **Illustrateation**              |
| ------------- | ---------------- | -------------------------------- |
| **origin**    | const point2f  & | 变换后的原点坐标                 |
| **length**    | const  float &   | 极半径                           |
| **dir**       | const float&     | 极角                             |
| **Return**    | point2f          | 变换原点后极坐标在直角坐标中的值 |

 ` point2f polarcoor_by_origin(const point2f  & origin,const  float &   length,  const point2f  &  vector_origin, const point2f  & vector_end)`

| **Parameter**     | **Type**         | **Illustrateation**              |
| ----------------- | ---------------- | -------------------------------- |
| **origin**        | const point2f  & | 变换后的原点坐标                 |
| **length**        | const  float &   | 极半径                           |
| **vector_origin** | const point2f  & | 极角向量的初始端                 |
| **vector_end**    | const point2f  & | 极角向量的末端                   |
| **Return**        | point2f          | 变换原点后极坐标在直角坐标中的值 |

### 6、球员是否朝向球门的状态

`bool toward_opp_goal(const  float & player_dir)`

| **Parameter**  | **Type**       | **Illustrateation** |
| -------------- | -------------- | ------------------- |
| **player_dir** | const  float & | 球员的转向角        |
| **Return**     | bool           | 球员是否朝向球门    |

### 7、判断小车是否在球与对面球门之间

`bool player_behind_ball(const point2f& player_pos, const point2f& ball_pos)`

| **Parameter**  | **Type**       | **Illustrateation**      |
| -------------- | -------------- | ------------------------ |
| **player_pos** | const point2f& | 球员的坐标               |
| **ball_pos**   | const point2f& | 球的坐标                 |
| **Return**     | bool           | 球是否在球与对面球门之间 |

###     8、判断小球两帧距离是否大于某阈值。若用于判断小球是否运动，则len_threshold默认0.8cm

​       `bool ball_moving(const WorldModel* model,float len_threshold)`

| **Parameter**     | **Type**          | **Illustrateation**               |
| ----------------- | ----------------- | --------------------------------- |
| **model**         | const WorldModel* | 全局参数                          |
| **len_threshold** | float             | 长度阈值                          |
| **Return**        | bool              | 小球两帧距离是否大于len_threshold |

### 9、求小球两帧距离

​       `float ball_moving(const WorldModel* model)`

| **Parameter** | **Type**          | **Illustrateation** |
| ------------- | ----------------- | ------------------- |
| **model**     | const WorldModel* | 全局参数            |
| **Return**    | float             | 小球两帧之间的距离  |

###   10、判断小球是否在吸球嘴附近。默认值为14cm与90°。

`bool ball_beside_player_head(const point2f& player_pos,const float& player_dir, const point2f& ball_pos,const float& len_threshold,const float& ang_threshold)`

| **Parameter**     | **Type**        | **Illustrateation**  |
| ----------------- | --------------- | -------------------- |
| **player_pos**    | const point2f&  | Player的坐标         |
| **player_dir**    | const  float&   | Player的朝向角       |
| **ball_pos**      | const point2f&  | 球的坐标             |
| **len_threshold** | const float  &  | 最大长度阈值         |
| **ang_threshold** | const  float  & | 最大角度阈值         |
| **Return**        | bool            | 小球是否在吸球嘴附近 |

###     11、判断球是否在小车吸球嘴上,距离阈值与角度阈值分别默认为16cm与30°。

​      ` bool get_ball(const point2f& player_pos, const float& player_dir, const point2f& ball_pos,const float& len_threshold,const float& ang_threshold)`

| **Parameter**     | **Type**       | **Illustrateation** |
| ----------------- | -------------- | ------------------- |
| **player_pos**    | const point2f& | Player的坐标        |
| **player_dir**    | const float&   | Player的朝向角      |
| **ball_pos**      | const point2f& | 球的坐标            |
| **len_threshold** | const float  & | 最大长度阈值        |
| **ang_threshold** | const float  & | 最大角度阈值        |
| **Return**        | bool           | 小球是否在吸球嘴上  |

###     12、判断两位置传球或踢球是否有敌方的球员阻挡

​      ` bool opp_block_shoot(const WorldModel* model, const point2f& kickerplayer_pos, const point2f& destination_pos )`

| **Parameter**        | **Type**          | **Illustrateation**          |
| -------------------- | ----------------- | ---------------------------- |
| **model**            | const WorldModel* | 全局参数                     |
| **kickerplayer_pos** | const point2f&    | 踢球机器人坐标               |
| **destination_pos**  | const point2f&    | 踢球目标坐标                 |
| **Return**           | bool              | 踢至目标点是否有敌方球员阻挡 |

###     13、判断两机器人是否做好传球的准备。传球的角度是否小于某个阈值，默认填29°。

​      ` bool ready_pass(const point2f& passer_pos, const point2f& ball_pos, const point2f& receiver_pos,const float& ang_threshold)`

| **Parameter**        | **Type**        | **Illustrateation**        |
| -------------------- | --------------- | -------------------------- |
| **Passer****_pos**   | const  point2f& | 传球者坐标                 |
| **Ball****_pos**     | const point2f&  | 球坐标                     |
| **Receiver****_pos** | const  point2f& | 接球者坐标                 |
| **ang_threshold**    | const float  &  | 最大角度阈值               |
| **Return**           | bool            | 两机器人是否做好传球的准备 |

###     14、判断两位置传球或踢球是否有敌方的球员阻挡，并返回敌方的阻挡球员id,无则返回-1。

   ` int get_opp_block_shoot_id(const WorldModel* model, const point2f& kickerplayer_pos, const point2f& destination_pos)`

| **Parameter**        | **Type**          | **Illustrateation** |
| -------------------- | ----------------- | ------------------- |
| **model**            | const WorldModel* | 全局参数            |
| **kickerplayer_pos** | const point2f&    | 踢球机器人坐标      |
| **destination_pos**  | const point2f&    | 踢球目标坐标        |
| **Return**           | int               | 敌方阻挡球的球员id  |

###     15、获得离搜索点最近的我方球员车号

​      ` int get_nearest_pos_our_player(const WorldModel* model, const point2f& searcher_pos)`

| **Parameter**    | **Type**       | **Illustrateation**        |
| ---------------- | -------------- | -------------------------- |
| **model**        | WorldModel*    | 全局参数                   |
| **searcher_pos** | const point2f& | 搜索发出点坐标             |
| **Return**       | int            | 离搜索点最近的我方的球员id |

###   16、获得离搜索点最近的对方球员车号

   ` int get_nearest_pos_opp_player(const WorldModel* model, const point2f& searcher_pos)`

| **Parameter**    | **Type**       | **Illustrateation**        |
| ---------------- | -------------- | -------------------------- |
| **model**        | WorldModel*    | 全局参数                   |
| **searcher_pos** | const point2f& | 搜索发出点坐标             |
| **Return**       | int            | 离搜索点最近的敌方的球员id |

###   17、搜索除自己与己方守门员之外离球最近的player并返回其id

`int search_player_nearst_ball(const WorldModel* model,const int excluded_id)`

| **Parameter**   | **Type**                | **Illustrateation**                        |
| --------------- | ----------------------- | ------------------------------------------ |
| **model**       | const WorldModel* model | 引入worldmodel模型以获取摄像头信息         |
| **excluded_id** | const int &             | 我方需要排除的player的id                   |
| **Return**      | int                     | 返回离球最近的机器人的id（己方守门员除外） |

## 四、模板

### 1、使用说明

- model应该换成自己文件的名字，其中MODEL_H也应该换成自己文件夹的名字

- model.h中#include语句需要在配置完环境后根据具体的路径进行修改
- model.cpp中的自定义函数可从myutils.cpp中直接复制粘贴至指定位置
- 在修改完上述内容后可直接从逻辑入口开始编写代码

### 2、model.h文件

```c+++
#ifndef MODEL_H
#define MODEL_H
#include "src/utils/PlayerTask.h"
#include "src/utils/worldmodel.h"
#include "src/utils/maths.h"
#include "src/utils/constants.h"
#endif
```

### 3、model.cpp文件

```c++
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
```

### 4、规范性说明

- 为了使得初学者可立即上手，保持可读性、简便性，未采用面向对象的编程操作，命名风格均采取以_代替.或->的方式。
- Player基础属性、ball基础属性、场景位置信息、场景中存在的队列序号信息均可类似得看做一个对象，里面对应的值为其属性。
- 自定义的常用位于myutils.cpp中，需要时可直接copy对应函数部分放入自定义函数中。
- 需根据实际场地调整的参数请放入自定义可调参数中，以保证代码完成后参数的查询与调试。
- 符号位取值为±1以更加直观地分别表示类似左右边对称的情况。

- 状态位常可取值为true或false，用来标志对各种状态的显示与判断。

- 默认初始化参数中常用于当临时定义的参数使用，离谱的值常表示不存在。（例如距离为9999）
- 要编辑的代码（如getball、passball等）放在逻辑入口后面。
- 最后要返回的值中，task是一个类，主要有以下几个属性可以在逻辑中更改：

| 属性名        | 类型    | 说明                 |
| ------------- | ------- | -------------------- |
| target_pos    | point2f | 全局目标点           |
| orientate     | double  | 全局目标到点朝向     |
| global_vel    | point2f | 全局目标到点平动速度 |
| rot_vel       | double  | 全局目标到点转动速度 |
| rot_dir       | int     | 旋转的方向           |
| needKick      | bool    | 踢球动作执行开关     |
| isPass        | bool    | 是否进行传球         |
| needCb        | bool    | 是否吸球             |
| isChipKick    | bool    | 挑球还是平射         |
| kickPower     | double  | 踢球力度             |
| chipKickPower | double  | 挑球力度             |

- 修改方式如下：

  ```c++
  task.target_pos=ball_pos;
  Task.needCb = true;
  ```
