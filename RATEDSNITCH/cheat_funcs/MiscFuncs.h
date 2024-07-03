void Misc()
{
	/*safe_write(TodCycle + 0x10, 12.f, float);*/

	//if (Gravity) {
	//	LocalPlayer.BasePlayer->SetGravity(2.0f);
	//}

	//if (AlwaysDay) {
	//	safe_write(TodCycle + 0x10, 12.00f, float);
	//}


	auto item_id = LocalPlayer.BasePlayer->GetActiveWeapon ( )->GetItemID ( );
	if ( item_id && AntiRecoil ) {
			/*if ( item_id == 1373971859 || item_id == 649912614 || item_id == -765183617 || item_id == -41440462 || item_id == 28201841 || item_id == 1588298435 || item_id == 143473650 || item_id == 795371088 )
				LocalPlayer.BasePlayer->GetActiveWeapon ( )->no_recoil2 ( 0 );
			else if ( item_id == 1796682209 || item_id == -1214542497 || item_id ==  -904863145
				|| item_id == 1545779598 || item_id == -1506397857 || item_id == 1318558775 || item_id == -852563019 || item_id == -1758372725 || item_id == -1812555177 )*/
			//LocalPlayer.BasePlayer->GetActiveWeapon ( )->no_recoil ( 0 );

		if (item_id == 1373971859 || item_id == 649912614 || item_id == -765183617 || item_id == -41440462 || item_id == 28201841 || item_id == 1588298435 || item_id == 143473650 || item_id == 795371088 || item_id == 1953903201 || item_id == -1367281941)
		{
			LocalPlayer.BasePlayer->GetActiveWeapon()->no_recoil2();
		}
		else
		{
			LocalPlayer.BasePlayer->GetActiveWeapon()->no_recoil();

		}


	}

	if (item_id && AntiSpread)
	{
		LocalPlayer.BasePlayer->GetActiveWeapon()->no_spread(); //FatBullet

	}

	if (item_id && SuperEoka)
	{
		if (item_id == -75944661) {
			LocalPlayer.BasePlayer->GetActiveWeapon()->Eoka(); //FatBullet
		}
	}
	
	if (item_id && Automatic)
	{

		LocalPlayer.BasePlayer->GetActiveWeapon()->SetAutomatic(); //FatBullet
	}
	//uint64_t g_Base;
	if (CustomFovBool) {
		DWORD64 convar = safe_read(g_Base + 52895712, DWORD64); //"  "Signature": "ConVar_Graphics_c*" 
		DWORD64 graphics = safe_read(convar + 0xb8, DWORD64);
		safe_write((const uintptr_t)graphics + 0x18, CustomFov, float); //update
	}


	if (item_id && BigBullet)
	{
		LocalPlayer.BasePlayer->GetActiveWeapon()->FatBullet(); //FatBullet

	}
	//if (!CustomFovBool) {
	//{
	//		DWORD64 convar = safe_read(g_Base + 52895712, DWORD64); //"  "Signature": "ConVar_Graphics_c*" 
	//		DWORD64 graphics = safe_read(convar + 0xb8, DWORD64);
	//		safe_write((const uintptr_t)graphics + 0x18, CustomFov2, float); //update;
	//}
	/*if (Vars::Misc::zoom) {
		DWORD64 convar = safe_read(g_Base + convar_graphichs, DWORD64);
		DWORD64 graphics = safe_read(convar + 0xb8, DWORD64);

		if (GetAsyncKeyState(VK_CAPITAL)) {
			safe_write((const uintptr_t)graphics + 0x18, 10, float);
		}
		else {
			if (!zoomFovSave)
				zoomFovSave = safe_read(graphics + 0x18, float);
			if (!Vars::Misc::CustomFov)
				safe_write((const uintptr_t)graphics + 0x18, zoomFovSave, float);
			zoomFovSave = safe_read(graphics + 0x18, float);
		}
	}*/


	if (LongNeck && GetAsyncKeyState(VK_XBUTTON2)) {
		LocalPlayer.BasePlayer->LongNeck();
	}

	if (FakeAdmin) {
		LocalPlayer.BasePlayer->FakeAdmin(4);
	}


	if ( RCS )
		LocalPlayer.BasePlayer->Debug ( );

	if ( !RCS )
		LocalPlayer.BasePlayer->DebugOff ( );

	if (InfinityJump) {
		LocalPlayer.BasePlayer->InfinityJump();
	}

	/*LocalPlayer.BasePlayer->SetRemoveFlag(4);*/

	if (SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();



















}
