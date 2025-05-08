#include "MarioPlayerKeyHandler.h"

#include "Mario.h"
#include "PlayScene.h"

CMarioPlayerKeyHandler::CMarioPlayerKeyHandler(LPPLAYSCENE s) : CSceneKeyHandler(s)
{
	this->mario = dynamic_cast<CMario*>(s->GetPlayer());
	if (this->mario == NULL) {
		DebugOut(L"[ERROR] Mario object is NULL\n");
	}
}

void CMarioPlayerKeyHandler::OnKeyDown(int keyCode)
{
	if (this->mario == NULL) {
		DebugOut(L"[ERROR] Mario object is NULL\n");
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

void CMarioPlayerKeyHandler::OnKeyUp(int keyCode)
{
	if (this->mario == NULL) {
		DebugOut(L"[ERROR] Mario object is NULL\n");
		return;
	}

	if (keyCode == keyMap->GetKey(ActionKey::Jump)) {
		 mario->SetState(MARIO_STATE_RELEASE_JUMP);
	}
	else if (keyCode == keyMap->GetKey(ActionKey::Sit)) {
		 mario->SetState(MARIO_STATE_SIT_RELEASE);
	}

}

void CMarioPlayerKeyHandler::KeyState(BYTE* states)
{
	if (this->mario == NULL) {
		DebugOut(L"[ERROR] Mario object is NULL\n");
		return;
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
	if (keyMap->IsActionPressed(states, ActionKey::Sit))
	{
		mario->SetState(MARIO_STATE_SIT);
	}
}