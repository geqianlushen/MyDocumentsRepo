gPlayTable.CreatePlay{

firstState = "GotoPosition",

["GotoPosition"] = {
	switch = function()
		if Cbuf_cnt(CRole2TargetDist("Receiver") < 20,30 ) then
			return "GetBall"
		end
	end,
	Kicker = task.KickerTask("kicker_gotoposition_zhongdian"),
	Receiver = task.ReceiverTask("receiver_gotoposition_coner1"),
},
["GetBall"] = {
	switch = function()
		if Cbuf_cnt(CBall2RoleDist("Receiver") < 20 ,150 ) then
			return "passball"
		end
	end,
	Kicker = task.KickerTask("kicker_gotoposition_zhongdian"),
	Receiver = task.ReceiverTask("receiver_gotoposition_corner2"),
},
["passball"] = {
	switch = function ()
		if  Cbuf_cnt(CBall2RoleDist("Kicker") < 20,80 ) then
			return "shoot"
		end
	end,
	Kicker   = task.KickerTask("kicker_receive_center1"),
	Receiver = task.ReceiverTask("receiver_pass_zhongdiancv"),
	--Receiver= task.PassBall("Receiver","Kicker"),
},
["shoot"] = {
	switch = function ()
		if Cbuf_cnt(CIsGetBall("Kicker"),20)  then
			return "delay"
		end
	end,
	Receiver = task.ReceiverTask("kaiqiustop_front4dui"),
	Kicker   = task.KickerTask("lll3dui"),
},

["delay"] = {
	switch = function()
		if  CIsBallKick("Kicker") or  Cbuf_cnt(true,300) then
			return "finish"
		end
	end,
   	Receiver   = task.ReceiverTask("kaiqiustop_front4dui"),
	--Kicker   = task.KickerTask("yyy3dui"),
	Kicker   = task.Shoot("Kicker"),
},
name = "cornertest"
}