void WeaponFix(WeaponData* weapon)
{
	int ItemID = 0;
	if (weapon)
		ItemID = weapon->GetItemID();
	if (!ItemID) return;

	for (DWORD64 val : semiautomatic) {
		if (ItemID == val) {
			weapon->SetRA();
			weapon->SetAA();
			//weapon->VelocityChange();
			weapon->SetAutomatic();
			weapon->FatBullet();
			return;
		}
	}
	for (DWORD64 val : sniper) {
		if (ItemID == val) {
			weapon->SetRA();
			weapon->SetAA();
			//weapon->VelocityChange();
			weapon->SetAutomatic();
			weapon->FatBullet();
			return;
		}
	}
	for (DWORD64 val : bow) {
		if (ItemID == val) {
			weapon->SetRA();
			weapon->SetAA();
			weapon->SetAutomatic();
				/*	weapon->VelocityChange();*/
					//weapon->FatBullet();
			return;
		}
	}
	for (DWORD64 val : automatic) {
		if (ItemID == val) {
			weapon->SetRA();
			weapon->SetAA();
	/*		weapon->VelocityChange();*/
			weapon->SetAutomatic();
			weapon->FatBullet();
			return;
		}
	}

	for (DWORD64 val : eoka) {
		if (ItemID == val) {
			weapon->SetRA();
			weapon->SetAA();
			/*		weapon->VelocityChange();*/
			weapon->SetAutomatic();
			weapon->FatBullet();
			weapon->Eoka();
			return;
		}
	}
}

float GetBulletSpeed()
{
	switch (LocalPlayer.BasePlayer->GetActiveWeapon()->GetItemID())
	{
	case 1796682209: //smg
		return 240.f;
	case 1588298435: //bolt
		return 656.25f;
	case -778367295: //l96
		return 1125.f;
	case 28201841: //m39
		return 469.f;
	case 1953903201: //nailgun
		return 50.f;
	case 649912614: //revolver
		return 300.f;
	case 818877484: //p250
		return 300.f;
	case -1367281941: //waterpipe, 250-green ammo, 100-other
		return 100.f;
	case -765183617: //double barrel, 250-green ammo, 100-other
		return 100.f;
	case -1812555177: //lr300
		return 375.f;
	case -852563019: //m92
		return 300.f;
	case -1123473824: //grenade launcher, shotgun - 250, other - 100
		return 100.f;
	case 442886268: //rocket launcher, unknown
		return 250.f;
	case -904863145: //semiautomatic rifle
		return 375.f;
	case -41440462: //spas12, 250-green ammo, 100-other
		return 100.f;
	case 1545779598: //ak47
		return 375.f;
	case 1443579727: //bow, 80-high speed arrow, 40 - fire arrow, 50 - normal
		return 50.f;
	case -75944661: //eoka, 250-green ammo, 100-other
		return 100.f;
	case 1318558775: //mp5a4
		return 240.f;
	case 795371088: //pomp shotgun, 250-green ammo, 100-other
		return 100.f;
	case 1965232394: //crossbow, 75 - normal, 120-high velocity, 60 - fire
		return 75.f;
	case -2069578888:
		return 488.f;
	case 1373971859: //python
		return 300.f;
	case -1758372725: //tompson
		return 300.f;
	default:
		return 250.f;
	}
}

float GetGravity(int ammoid) {
	switch (ammoid) {
	case 14241751: //fire arrow
		return 1.f;
	case -1234735557: //arrow normal
		return 0.75f;
	case 215754713: //arrow bone
		return 0.75f;
	case -1023065463: //hv arrow
		return 0.5f;
	case -2097376851: //nails
		return 0.75f;
	case -1321651331: //5.56 exp
		return 1.25f;
	default:
		return 1.f;
	}
}

float AimFov(BasePlayer* Entity) {

	Vector2 ScreenPos;
	float xs = Other::Width / 2, ys = Other::Height / 2;
	if ( !LocalPlayer.WorldToScreen ( Entity->GetBoneByID ( head ), ScreenPos ) );
		return 10000;

	return Math::Calc2D_Dist ( Vector2 ( xs, ys ), ScreenPos );
}

//void SmoothAim(Vector2& Angle, float smooth) {
//	Angle / smooth;
//}


Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone)
{
	// - //
	Vector3 bonepos = Player->GetBoneByID(head);
	float dist = Math::Calc3D_Dist(LP_Pos, bonepos);
	Vector3 vel = Player->GetVelocity();
	WeaponData* active = LocalPlayer.BasePlayer->GetActiveWeapon();
	// - //



		
			if (dist > 0.001f) {
				if (BigBullet) {
					active->FatBullet();
				}
				active->SetVelocityProjectile(1.1f);
				float bullettime = dist / GetBulletSpeed() * 1.1f;
				Vector3 vel = Player->GetVelocity();
				Vector3 PredictVel = vel * bullettime;
				float bulletdrop = 4.0f * bullettime * bullettime;
				bonepos.y += bulletdrop;
			} return bonepos;
	
	
}

void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}	 
inline float distance_cursor ( Vector2 vec )
	{
	POINT p;
	if ( GetCursorPos ( &p ) )
		{
		float ydist = (vec.y - p.y);
		float xdist = (vec.x - p.x);
		float ret = sqrt ( pow ( ydist, 2 ) + pow ( xdist, 2 ) );
		return ret;
		}

	}

void AimBotTarget(BasePlayer* player)
{
	float FOV = 1000000.f;
	if (LongNeck && GetAsyncKeyState(VK_XBUTTON2)) {
		Vector3 Local = LocalPlayer.BasePlayer->GetBoneByID(head) + Vector3(0, (1.2f), 0);
		Vector3 PlayerPos = player->GetBoneByID(head);
		PlayerPos = Prediction(Local, player, BoneList(head));
		Vector2 Offset = Math::CalcAngle(Local, PlayerPos) - LocalPlayer.BasePlayer->GetVA();
		Vector2 RecoilAng = LocalPlayer.BasePlayer->GetRA();
		/*SmoothAim(Offset, 2);*/
		Vector2 AngleToAim = LocalPlayer.BasePlayer->GetVA() + Offset;
			AngleToAim = AngleToAim - RecoilAng;
		Normalize(AngleToAim.y, AngleToAim.x);
		if (isnan(AngleToAim.x) || isnan(AngleToAim.y) || AimFov(player) > Fov) return;
		LocalPlayer.BasePlayer->SetVA(AngleToAim);
	}
	else {
		Vector3 PlayerPos = player->GetBoneByID(head);
		Vector3 Local = LocalPlayer.BasePlayer->GetBoneByID(head);
		PlayerPos = Prediction(Local, player, BoneList(head));
		Vector2 Offset = Math::CalcAngle(Local, PlayerPos) - LocalPlayer.BasePlayer->GetVA();
		Vector2 RecoilAng = LocalPlayer.BasePlayer->GetRA();
		Vector2 AngleToAim = LocalPlayer.BasePlayer->GetVA() + Offset;
			AngleToAim = AngleToAim - RecoilAng;
		Normalize(AngleToAim.y, AngleToAim.x);

		Vector2 ScreenPos;
		float CurFOV = distance_cursor ( ScreenPos );
		if ( (FOV > (CurFOV = AimFov ( player ))) ) {
			if ( CurFOV <= Fov ) {
				FOV = CurFOV;
LocalPlayer.BasePlayer->SetVA(AngleToAim);	   }

	//	if (isnan(AngleToAim.x) || isnan(AngleToAim.y) || AimFov(player) > Fov) return;
     
		
	    }	 }
}

void Aim(BasePlayer* player)
{
	if (AimBot)
	{
		AimBotTarget(player);
	}
}


