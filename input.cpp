#include "input.h"

Input::Input(GameState * state, Deployment *deployed, GUI *gui, Handler *handler)
{
Input::state = state;
Input::deployed = deployed;
Input::gui = gui;
Input::handler = handler;
};

void Input::GetInput(ALLEGRO_EVENT *input)
{
            if (input->type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(input->keyboard.keycode)
                {
                case ALLEGRO_KEY_P:
                    {
                    if (state->GetState() == PLAYING)
                    {
                    if (state->GamePaused() == true) state->SetPause(false);
                    else state->SetPause(true);
                    }
                    break;
                    }
                case ALLEGRO_KEY_UP:
                    {
                    if (state->GetState() == PLAYING)
                        if (gui->row_selected > 1) gui->row_selected -= 1;
                    if (state->GetState() == DEPLOYMENT)
                    {
                        if (deployed->Selected_Stage == deployed->Pregen_Stage_1) deployed->Selected_Stage = deployed->Pregen_Stage_2;
                        else if (deployed->Selected_Stage == deployed->Pregen_Stage_2) deployed->Selected_Stage = deployed->Pregen_Stage_3;
                    }
                    break;
                    }
                case ALLEGRO_KEY_DOWN:
                    {
                    if (state->GetState() == PLAYING)
                        if (gui->row_selected < 3 ) gui->row_selected += 1;
                    if (state->GetState() == DEPLOYMENT)
                    {
                        if (deployed->Selected_Stage == deployed->Pregen_Stage_3) deployed->Selected_Stage = deployed->Pregen_Stage_2;
                        else if (deployed->Selected_Stage == deployed->Pregen_Stage_2) deployed->Selected_Stage = deployed->Pregen_Stage_1;
                    }
                    break;
                    }
                case ALLEGRO_KEY_LEFT:
                    {
                    if (state->GetState() == PLAYING || state->GetState() == AFTERMATCH) gui->cameraLeft = true;
                    if (state->GetState() == DEPLOYMENT)//wybor squada podczas deploymentu
                    {
                        if (handler->sqiter == handler->AvailableSquads.begin()) handler->sqiter = std::prev(std::prev(handler->AvailableSquads.end()));
                        else handler->sqiter--;
                        while ((*handler->sqiter)->GetFraction() != DWARFKIN || (*handler->sqiter)->GetUnitType() == LEGENDARY)
                        {
                            if(handler->sqiter == handler->AvailableSquads.begin()) handler->sqiter = std::prev(std::prev(handler->AvailableSquads.end()));
                            else handler->sqiter--;
                        }
                    }
                    break;
                    }
                case ALLEGRO_KEY_RIGHT:
                    {
                    if (state->GetState() == PLAYING || state->GetState() == AFTERMATCH) gui->cameraRight = true;
                    if (state->GetState() == DEPLOYMENT)//Wybor squada podczas deploymentu
                    {
                        if (handler->sqiter == std::prev(std::prev(handler->AvailableSquads.end()))) handler->sqiter = handler->AvailableSquads.begin();
                        else handler->sqiter++;
                        while ((*handler->sqiter)->GetFraction() != DWARFKIN || (*handler->sqiter)->GetUnitType() == LEGENDARY)
                        {
                            if(handler->sqiter == std::prev(std::prev(handler->AvailableSquads.end()))) handler->sqiter = handler->AvailableSquads.begin();
                            else handler->sqiter++;
                        }
                    }
                    break;
                    }
                case ALLEGRO_KEY_1:
                    {
                    if (state->GetState() == PLAYING)
                    gui->unit_selected = 1;
                    if (state->GetState() == DEPLOYMENT)
                    {
                        //if((*handler->sqiter)->GetSquadName() != deployed->OccupiedSlot_2->GetSquadName() ||
                        //   (*handler->sqiter)->GetSquadName() != deployed->OccupiedSlot_3->GetSquadName())
                        //{
                        deployed->OccupiedSlot_1->SetDeploying(0);
                        deployed->SelectSquadForDeployment((*handler->sqiter), 1);
                        (*handler->sqiter)->SetDeploying(1);
                        //}
                    }
                    break;
                    }
                case ALLEGRO_KEY_2:
                    {
                    if (state->GetState() == PLAYING)
                    gui->unit_selected = 2;
                    if (state->GetState() == DEPLOYMENT)
                    {
                       // if((*handler->sqiter)->GetSquadName() != deployed->OccupiedSlot_1->GetSquadName() ||
                        //   (*handler->sqiter)->GetSquadName() != deployed->OccupiedSlot_3->GetSquadName())
                        //{
                        deployed->OccupiedSlot_2->SetDeploying(0);
                        deployed->SelectSquadForDeployment((*handler->sqiter), 2);
                        (*handler->sqiter)->SetDeploying(2);
                       // }
                    }
                    break;
                    }
                case ALLEGRO_KEY_3:
                    {
                    if (state->GetState() == PLAYING)
                    gui->unit_selected = 3;
                    if (state->GetState() == DEPLOYMENT)
                    {
                       // if((*handler->sqiter)->GetSquadName() != deployed->OccupiedSlot_1->GetSquadName() ||
                       //    (*handler->sqiter)->GetSquadName() != deployed->OccupiedSlot_2->GetSquadName())
                       // {
                        deployed->OccupiedSlot_3->SetDeploying(0);
                        deployed->SelectSquadForDeployment((*handler->sqiter), 3);
                        (*handler->sqiter)->SetDeploying(3);
                       // }
                    }
                    break;
                    }
            case ALLEGRO_KEY_SPACE:
                if (state->GetState() == MENU )
                {
                    state->ChangeState(DEPLOYMENT);
                    break;
                }
                if (state->GetState() == DEPLOYMENT )
                {
                   // if (deployed->Selected_Stage->StageBackground == 0) data.bgImage = al_load_bitmap("Data/BG_forest.jpg"); //Przeniesc do funkcji PlaySelectedStage
                   // else if (deployed->Selected_Stage->StageBackground == 1) data.bgImage = al_load_bitmap("Data/BG_cave.jpg");
                   // else data.bgImage = al_load_bitmap("Data/BG_swamp.jpg");
                    deployed->PlaySelectedStage();
                    state->ChangeState(PLAYING);
                    //if (sound_enabled == true)  al_play_sample(song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
                        if (Stage::STAGE_VICTORY_CONDITION == BLOODBATH)
                        {
                            Creature *stageHero = new Creature(40, 0, handler->FindSquad("Hero"));
                            deployed->ptr_to_hero = stageHero;
                            handler->objects.push_back(stageHero);
                        }
                        else if (Stage::STAGE_VICTORY_CONDITION == HERO_HUNTING)
                        {
                            Creature *stageHero = new Creature(40, 0, handler->FindSquad("Hero"));
                            deployed->ptr_to_hero = stageHero;
                            handler->objects.push_back(stageHero);
                            if (deployed->Selected_Stage->StageEnemy == 0)
                            {
                            Creature *enemyHero = new Creature(1560, 0, handler->FindSquad("Ogre"));
                            deployed->ptr_to_enemy = enemyHero;
                            handler->objects.push_back(enemyHero);
                            }
                            else
                            {
                            Creature *enemyHero = new Creature(1560, 0, handler->FindSquad("Necromancer"));
                            deployed->ptr_to_enemy = enemyHero;
                            handler->objects.push_back(enemyHero);
                            }
                        }
                    break;
                }
                if (state->GetState() == AFTERMATCH)
                {
                    handler->Remove_objects(allObj);
                    state->ChangeState(DEPLOYMENT);
                    deployed->OccupiedSlot_1->SquadUpdate();
                    deployed->OccupiedSlot_2->SquadUpdate();
                    deployed->OccupiedSlot_3->SquadUpdate();
                    deployed->GenerateStages();
                    break;
                }
                if (state->GetState() == PLAYING && state->GamePaused() == false)
                {
                    int gold_cost = deployed->GetSelectedSlot(gui->unit_selected).GetGoldCost();
                    int honor_cost = deployed->GetSelectedSlot(gui->unit_selected).GetHonorCost();
                    if (Stage::GetStageGold() >= gold_cost && Stage::GetStageHonor() >= honor_cost)
                    {
                        handler->objects.push_back(deployed->SpawnUnit(gui->row_selected, gui->unit_selected));
                        Stage::SpendGold(gold_cost);
                        //Ftext *text = new Ftext(250, 545, -0.5, -(gold_cost), 45, data.font18, data.icons, Gold);
                        //handler->objects.push_back(text);
                        if (honor_cost > 0)
                        {
                            Stage::SpendHonor(honor_cost);
                            //Ftext *text = new Ftext(250, 570, -0.5, -(honor_cost), 45, data.font18, data.icons, Honor);
                            //handler->objects.push_back(text);
                        }
                        break;
                    }
                }
                }
                }
                if(input->type == ALLEGRO_EVENT_KEY_UP)
                {
                    switch(input->keyboard.keycode)
                    {
                    case ALLEGRO_KEY_LEFT:
                        gui->cameraLeft = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        gui->cameraRight = false;
                        break;
                    }
                }
}
