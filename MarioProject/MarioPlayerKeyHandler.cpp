#include "MarioPlayerKeyHandler.h"

#include "Mario.h"
#include "PlayScene.h"

CMarioPlayerKeyHandler::CMarioPlayerKeyHandler(LPPLAYSCENE s) : CSceneKeyHandler(s)
{
	this->mario = dynamic_cast<CMario*>(CPlayScene::GetPlayer());
	if (this->mario == nullptr)
	{
		DebugOut(L"[ERROR] MarioPlayerKeyHandler: Mario object is nullptr\n");
	}
}

void CMarioPlayerKeyHandler::OnKeyDown(int keyCode)
{
	if (this->mario == nullptr)
	{
		//DebugOut(L"[ERROR] MarioPlayerKeyHandler: Mario object is nullptr\n");
		return;
	}

	if (keyCode == keyMap->GetKey(ActionKey::Sit))
	{
		mario->SetState(MARIO_STATE_SIT);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::Jump))
	{
		mario->SetState(MARIO_STATE_JUMP);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::SetSmall))
	{
		mario->SetLevel(MARIO_LEVEL_SMALL);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::SetBig))
	{
		mario->SetLevel(MARIO_LEVEL_BIG);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::SetFly))
	{
		mario->SetLevel(MARIO_LEVEL_FLY);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::SetDie))
	{
		mario->SetState(MARIO_STATE_DIE);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::Reload))
	{
		//Reload();
	}
}

// On key relase
void CMarioPlayerKeyHandler::OnKeyUp(int keyCode)
{
	if (this->mario == nullptr)
	{
		//DebugOut(L"[ERROR] MarioPlayerKeyHandler: Mario object is nullptr\n");
		return;
	}

	if (keyCode == keyMap->GetKey(ActionKey::Sit))
	{
		mario->SetState(MARIO_STATE_SIT_RELEASE);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::Run))
	{
		this->mario->SetRunning(false);
		this->mario->ReleaseHoldingItem();
	}
	if (keyCode == keyMap->GetKey(ActionKey::Jump))
	{
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
	}

}

//On key pressed
void CMarioPlayerKeyHandler::KeyState(BYTE* states)
{
	if (this->mario == nullptr)
	{
		//DebugOut(L"[ERROR] MarioPlayerKeyHandler: Mario object is NULL\n");
		return;
	}

	// mario attack, or speciall ability
	if (keyMap->IsActionPressed(states, ActionKey::Run)) {
		if (mario->level == MARIO_LEVEL_FLY && !mario->IsAttacking() && !mario->IsRunning())
		{
			mario->StartAttack();
			mario->SetState(keyMap->IsActionPressed(states, ActionKey::Run)
				? MARIO_STATE_RUNNING_LEFT : MARIO_STATE_WALKING_LEFT);
		}
	}

	if (keyMap->IsActionPressed(states, ActionKey::MoveRight))
	{
		mario->SetState(keyMap->IsActionPressed(states, ActionKey::Run)
			? MARIO_STATE_RUNNING_RIGHT : MARIO_STATE_WALKING_RIGHT);
		
	}
	else if (keyMap->IsActionPressed(states, ActionKey::MoveLeft))
	{
		mario->SetState(keyMap->IsActionPressed(states, ActionKey::Run)
			? MARIO_STATE_RUNNING_LEFT : MARIO_STATE_WALKING_LEFT);
	}
	else
	{
		mario->SetState(MARIO_STATE_IDLE);
	}

	// Sitting state has higher priority 
	if (keyMap->IsActionPressed(states, ActionKey::Run))
	{
		this->mario->SetRunning(true);
	}
	else if (keyMap->IsActionPressed(states, ActionKey::Sit))
	{
		mario->SetState(MARIO_STATE_SIT);
	}
}