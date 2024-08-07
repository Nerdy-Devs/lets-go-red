.set LOCALID_SS_ANNE, 1
.set LOCALID_MEW_POKEBALL, 3

SSAnne_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SSAnne_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAnne_Exterior_OnFrame
	.byte 0

SSAnne_Exterior_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SSANNE_EXTERIOR
	end

SSAnne_Exterior_OnFrame::
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 1, SSAnne_Exterior_ExitSSAnne
	.2byte 0

SSAnne_Exterior_ExitSSAnne::
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_le VAR_0x8005, 6, SSAnne_Exterior_WalkDown
	call_if_ge VAR_0x8005, 7, SSAnne_Exterior_WalkInPlaceDown
	fadenewbgm MUS_SURF
	delay 50
	special DoSSAnneDepartureCutscene
	waitstate
	removeobject LOCALID_SS_ANNE
	applymovement OBJ_EVENT_ID_PLAYER, SSAnne_Exterior_Movement_Exit
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 2
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	warp MAP_VERMILION_CITY, 23, 34
	waitstate
	releaseall
	end

SSAnne_Exterior_EventScript_MewBall::
	lock
	faceplayer
	setvar VAR_TEMP_1, SPECIES_MEW
	givemon SPECIES_MEW, 25
	goto_if_eq VAR_RESULT, 0, SSAnne_Exterior_EventScript_GetMewParty
	goto_if_eq VAR_RESULT, 1, SSAnne_Exterior_EventScript_GetMewPC
	goto_if_eq VAR_RESULT, 2, EventScript_NoMoreRoomForPokemon
	release
	end

SSAnne_Exterior_EventScript_GetMewParty::
	removeobject LOCALID_MEW_POKEBALL
	playfanfare MUS_LEVEL_UP
	message SSAnne_EXterior_Get_Mew_Text
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_MEW
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSAnne_Exterior_EventScript_SetGotMew
	call EventScript_GetGiftMonPartySlot
	call EventScript_ChangePokemonNickname
	goto SSAnne_Exterior_EventScript_SetGotMew
	end

SSAnne_Exterior_EventScript_GetMewPC::
	removeobject LOCALID_MEW_POKEBALL
	playfanfare MUS_LEVEL_UP
	message SSAnne_EXterior_Get_Mew_Text
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_MEW
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SSAnne_Exterior_EventScript_TransferMewToPC
	call EventScript_NameReceivedBoxMon
	goto SSAnne_Exterior_EventScript_TransferMewToPC
	end

SSAnne_Exterior_EventScript_TransferMewToPC::
	call EventScript_TransferredToPC
	goto SSAnne_Exterior_EventScript_SetGotMew
	end

SSAnne_Exterior_EventScript_SetGotMew::
	setflag FLAG_GOT_MEW
	release
	end

SSAnne_Exterior_WalkDown::
	applymovement OBJ_EVENT_ID_PLAYER, SSAnne_Exterior_Movement_WalkDown
	waitmovement 0
	return

SSAnne_Exterior_WalkInPlaceDown::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

SSAnne_Exterior_Movement_Exit::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SSAnne_Exterior_Movement_WalkDown::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
