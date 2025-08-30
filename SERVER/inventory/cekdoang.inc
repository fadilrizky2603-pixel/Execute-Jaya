if(IsPlayerInRangeOfPoint(playerid, 2, 2349.3899,-1342.8055,23.8125)) // ring 2
			{
				MoveObject(Ball, 2349.3899,-1342.8055,26.9120, 7.5); // masuk ke ring 2
				SetPlayerPos(playerid, 2349.3899,-1342.8055,23.8125);
				ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk",4.0,1,0,0,0,0);
				HavingBall[playerid] = 0;
				SetTimerEx("ClearAnim", 1100, 0, "d", playerid);
				SetTimerEx("BallDown2Ring2", 1100, 0, "d", playerid);
				return 1;
			}
            else if(IsPlayerInRangeOfPoint(playerid, 4, 2349.3899,-1342.8055,23.8125) && IsPlayerFacingPoint(playerid, 20, 2349.3899,-1342.8055,23.8125))
			{
				new rand = random(1);
				if(rand == 0)
				{
					MoveObject(Ball, 2349.3899,-1342.8055,26.9120, 10.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 2;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMissRing2(playerid);
				return 1;
			}
            else if(IsPlayerInRangeOfPoint(playerid, 7, 2349.3899,-1342.8055,23.8125) && IsPlayerFacingPoint(playerid, 20, 2349.3899,-1342.8055,23.8125))
			{
				new rand = random(2);
				if(rand == 0)
				{
					MoveObject(Ball, 2349.3899,-1342.8055,26.9120, 11.0+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 2;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMissRing2(playerid);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10, 2349.3899,-1342.8055,23.8125) && IsPlayerFacingPoint(playerid, 20, 2349.3899,-1342.8055,23.8125))
			{
				new rand = random(3);
				if(rand == 0)
				{
					MoveObject(Ball, 2349.3899,-1342.8055,26.9120, 11.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 2;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMissRing2(playerid);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 2, 2768.3669,-2019.6644,23.8125))
			{
				MoveObject(Ball, 2768.6289,-2019.7227,15.6287, 7.5);
				SetPlayerPos(playerid, 2768.3669,-2019.6644,23.8125);
				ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk",4.0,1,0,0,0,0);
				HavingBall[playerid] = 0;
				SetTimerEx("ClearAnim", 800, 0, "d", playerid);
				SetTimerEx("BallDown3Ring2", 1100, 0, "d", playerid);
				return 1;
			}
            else if(IsPlayerInRangeOfPoint(playerid, 4, 2768.3669,-2019.6644,23.8125) && IsPlayerFacingPoint(playerid, 20, 2768.3669,-2019.6644,23.8125))
			{
				new rand = random(1);
				if(rand == 0)
				{
					MoveObject(Ball, 2768.6289,-2019.7227,15.6287, 10.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 3;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss2Ring2(playerid);
				return 1;
			}
            else if(IsPlayerInRangeOfPoint(playerid, 7, 2768.3669,-2019.6644,23.8125) && IsPlayerFacingPoint(playerid, 20, 2768.3669,-2019.6644,23.8125))
			{
				new rand = random(2);
				if(rand == 0)
				{
					MoveObject(Ball, 2768.6289,-2019.7227,15.6287, 11.0+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 3;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss2Ring2(playerid);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10, 2768.3669,-2019.6644,23.8125) && IsPlayerFacingPoint(playerid, 20, 2768.3669,-2019.6644,23.8125))
			{
				new rand = random(3);
				if(rand == 0)
				{
					MoveObject(Ball, 2768.6289,-2019.7227,15.6287, 11.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 3;
					HavingBall[playerid] = 0;
					return 1;
				}
                ShootMiss2Ring2(playerid);
				return 1;
			}

forward BallDown2Ring2(playerid);
public BallDown2Ring2(playerid)
{
	MoveObject(Ball, 2349.3899,-1342.8055,23.8125-0.8, 10.0+random(3));
	Baller = 999;
	ShootingBall = 0;
	GameTextForPlayer(playerid, "~g~Goal!", 3000, 3);
	BallBounce = 1;
	return 1;
}

forward BallDown3Ring2(playerid);
public BallDown3Ring2(playerid)
{
	MoveObject(Ball, 2768.3669,-2019.6644,23.8125-0.8, 10.0+random(3));
	Baller = 999;
	ShootingBall = 0;
	GameTextForPlayer(playerid, "~g~Goal!", 3000, 3);
	BallBounce = 1;
	return 1;
}

forward BallDown4Ring2(playerid);
public BallDown4Ring2(playerid)
{
	MoveObject(Ball, 2349.2891+random(5),-1316.5941+random(5),23.8125-0.8, 10.0+random(3));
	Baller = 999;
	ShootingBall = 0;
	GameTextForPlayer(playerid, "~r~Miss!", 3000, 3);
	BallBounce = 1;
	return 1;
}

forward BallDown5Ring2(playerid);
public BallDown5Ring2(playerid)
{
	MoveObject(Ball, 2768.3669+random(5),-2019.6644+random(5),23.8125-0.8, 10.0+random(3));
	Baller = 999;
	ShootingBall = 0;
	GameTextForPlayer(playerid, "~r~Miss!", 3000, 3);
	BallBounce = 1;
	return 1;
}

forward ShootMissRing2(playerid);
public ShootMissRing2(playerid)
{
	MoveObject(Ball, 2768.6289+random(2), -2019.7227+random(2), 23.9120+random(2), 12.5+random(4));
	ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
	ShootingBall = 4;
	HavingBall[playerid] = 0;
	return 1;
}

forward ShootMiss2Ring2(playerid);
public ShootMiss2Ring2(playerid)
{
	MoveObject(Ball, 2768.6289+random(2),-2019.7227+random(2),23.9120+random(2), 12.5+random(4));
	ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
	ShootingBall = 5;
	HavingBall[playerid] = 0;
	return 1;
}