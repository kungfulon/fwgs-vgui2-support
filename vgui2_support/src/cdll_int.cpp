#include <string.h>
#include "wrect.h"
#include "cl_dll.h"
#include <FileSystem.h>
#include "interfaces/ISurface.h"
#include "vgui_controls/controls.h"

cl_enginefunc_t gEngfuncs;
cldll_func_t gClDllFuncs;

void VGui_Startup(int width, int height);

void HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed) {
	gClDllFuncs.pPostRunCmd(from, to, cmd, runfuncs, time, random_seed);
}

int COM_ExpandFileName(const char *fileName, char *nameOutBuffer, int nameOutBufferSize) {
	return vgui2::filesystem()->GetLocalPath(fileName, nameOutBuffer, nameOutBufferSize) != NULL;
}

void pfnDrawSetTextColor(float r, float g, float b) {
	vgui2::surface()->DrawSetTextColor(r * 255, g * 255, b * 255, 255);
	gEngfuncs.pfnDrawSetTextColor(r, g, b);
}

int Initialize(cl_enginefunc_t *pEnginefuncs, int iVersion) {
	if (iVersion != CLDLL_INTERFACE_VERSION) {
		return 0;
	}

	gEngfuncs = *pEnginefuncs;

	char szPath[_MAX_PATH];
	gEngfuncs.COM_ExpandFilename("cl_dlls/client.dll", szPath, sizeof(szPath));
	CSysModule *pClDllModule = Sys_LoadModule(szPath);

	if (!pClDllModule) {
		return 0;
	}

	void(*F)(void *) = (void(*)(void *))Sys_GetProcAddress(pClDllModule, "F");

	if (!F) {
		return 0;
	}

	modfuncs_t modfuncs;
	gClDllFuncs.pInitFunc = (INITIALIZE_FUNC)&modfuncs;
	F(&gClDllFuncs);
	pEnginefuncs->COM_ExpandFilename = COM_ExpandFileName;
	pEnginefuncs->pfnDrawSetTextColor = pfnDrawSetTextColor;
	
	SCREENINFO screeninfo;
	screeninfo.iSize = sizeof(SCREENINFO);
	gEngfuncs.pfnGetScreenInfo(&screeninfo);
	VGui_Startup(screeninfo.iWidth, screeninfo.iHeight);

	return 1; // gClDllFuncs.pInitFunc(pEnginefuncs, iVersion);
}

int HUD_VidInit(void) {
	return gClDllFuncs.pHudVidInitFunc();
}

void HUD_Init(void) {
	gClDllFuncs.pHudInitFunc();
}

int HUD_Redraw(float flTime, int intermission) {
	return gClDllFuncs.pHudRedrawFunc(flTime, intermission);
}

int HUD_UpdateClientData(client_data_t *cdata, float flTime) {
	return gClDllFuncs.pHudUpdateClientDataFunc(cdata, flTime);
}

void HUD_Reset(void) {
	gClDllFuncs.pHudResetFunc();
}

void HUD_PlayerMove(struct playermove_s *ppmove, int server) {
	return gClDllFuncs.pClientMove(ppmove, server);
}

void HUD_PlayerMoveInit(struct playermove_s *ppmove) {
	gClDllFuncs.pClientMoveInit(ppmove);
}

char HUD_PlayerMoveTexture(char *name) {
	return gClDllFuncs.pClientTextureType(name);
}

int HUD_ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size) {
	return gClDllFuncs.pConnectionlessPacket(net_from, args, response_buffer, response_buffer_size);
}

int HUD_GetHullBounds(int hullnumber, float *mins, float *maxs) {
	return gClDllFuncs.pGetHullBounds(hullnumber, mins, maxs);
}

void HUD_Frame(double time) {
	gClDllFuncs.pHudFrame(time);
}

void HUD_VoiceStatus(int entindex, qboolean bTalking) {
	gClDllFuncs.pVoiceStatus(entindex, bTalking);
}

void HUD_DirectorMessage(int iSize, void *pbuf) {
	gClDllFuncs.pDirectorMessage(iSize, pbuf);
}

void HUD_ChatInputPosition(int *x, int *y) {
	gClDllFuncs.pChatInputPosition(x, y);
}

void Demo_ReadBuffer(int size, unsigned char *buffer) {
	gClDllFuncs.pReadDemoBuffer(size, buffer);
}

int HUD_AddEntity(int type, struct cl_entity_s *ent, const char *modelname) {
	return gClDllFuncs.pAddEntity(type, ent, modelname);
}

void HUD_CreateEntities(void) {
	gClDllFuncs.pCreateEntities();
}

void HUD_StudioEvent(const struct mstudioevent_s *event, const struct cl_entity_s *entity) {
	gClDllFuncs.pStudioEvent(event, entity);
}

void HUD_TxferLocalOverrides(struct entity_state_s *state, const struct clientdata_s *client) {
	gClDllFuncs.pTxferLocalOverrides(state, client);
}

void HUD_ProcessPlayerState(struct entity_state_s *dst, const struct entity_state_s *src) {
	gClDllFuncs.pProcessPlayerState(dst, src);
}

void HUD_TxferPredictionData(struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd) {
	gClDllFuncs.pTxferPredictionData(ps, pps, pcd, ppcd, wd, pwd);
}

void HUD_TempEntUpdate(double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int(*Callback_AddVisibleEntity)(struct cl_entity_s *pEntity), void(*Callback_TempEntPlaySound)(struct tempent_s *pTemp, float damp)) {
	gClDllFuncs.pTempEntUpdate(frametime, client_time, cl_gravity, ppTempEntFree, ppTempEntActive, Callback_AddVisibleEntity, Callback_TempEntPlaySound);
}

struct cl_entity_s *HUD_GetUserEntity(int index) {
	return gClDllFuncs.pGetUserEntity(index);
}

void CAM_Think(void) {
	gClDllFuncs.pCamThink();
}

int CL_IsThirdPerson(void) {
	return gClDllFuncs.pCL_IsThirdPerson();
}

void CL_CameraOffset(float *ofs) {
	gClDllFuncs.pCL_GetCameraOffsets(ofs);
}

struct kbutton_s *KB_Find(const char *name) {
	return gClDllFuncs.pFindKey(name);
}

void CL_CreateMove(float frametime, struct usercmd_s *cmd, int active) {
	gClDllFuncs.pCL_CreateMove(frametime, cmd, active);
}

void HUD_Shutdown(void) {
	gClDllFuncs.pShutdown();
}

int HUD_Key_Event(int eventcode, int keynum, const char *pszCurrentBinding) {
	return gClDllFuncs.pKeyEvent(eventcode, keynum, pszCurrentBinding);
}

void IN_ActivateMouse(void) {
	gClDllFuncs.pIN_ActivateMouse();
}

void IN_DeactivateMouse(void) {
	gClDllFuncs.pIN_DeactivateMouse();
}

void IN_MouseEvent(int mstate) {
	gClDllFuncs.pIN_MouseEvent(mstate);
}

void IN_Accumulate(void) {
	gClDllFuncs.pIN_Accumulate();
}

void IN_ClearStates(void) {
	gClDllFuncs.pIN_ClearStates();
}

void HUD_DrawNormalTriangles(void) {
	gClDllFuncs.pDrawNormalTriangles();
}

void HUD_DrawTransparentTriangles(void) {
	gClDllFuncs.pDrawTransparentTriangles();
}

void V_CalcRefdef(struct ref_params_s *pparams) {
	gClDllFuncs.pCalcRefdef(pparams);
}

int HUD_GetStudioModelInterface(int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio) {
	return gClDllFuncs.pStudioInterface(version, ppinterface, pstudio);
}

int HUD_GetPlayerTeam(int iplayer) {
	if (gClDllFuncs.pGetPlayerTeam) {
		return gClDllFuncs.pGetPlayerTeam(iplayer);
	}

	return 0;
}

extern "C" void EXPORT F(void *pv) {
	cldll_func_t *pcldll_func = (cldll_func_t *)pv;

	cldll_func_t cldll_func = {
		Initialize,
		HUD_Init,
		HUD_VidInit,
		HUD_Redraw,
		HUD_UpdateClientData,
		HUD_Reset,
		HUD_PlayerMove,
		HUD_PlayerMoveInit,
		HUD_PlayerMoveTexture,
		IN_ActivateMouse,
		IN_DeactivateMouse,
		IN_MouseEvent,
		IN_ClearStates,
		IN_Accumulate,
		CL_CreateMove,
		CL_IsThirdPerson,
		CL_CameraOffset,
		KB_Find,
		CAM_Think,
		V_CalcRefdef,
		HUD_AddEntity,
		HUD_CreateEntities,
		HUD_DrawNormalTriangles,
		HUD_DrawTransparentTriangles,
		HUD_StudioEvent,
		HUD_PostRunCmd,
		HUD_Shutdown,
		HUD_TxferLocalOverrides,
		HUD_ProcessPlayerState,
		HUD_TxferPredictionData,
		Demo_ReadBuffer,
		HUD_ConnectionlessPacket,
		HUD_GetHullBounds,
		HUD_Frame,
		HUD_Key_Event,
		HUD_TempEntUpdate,
		HUD_GetUserEntity,
		HUD_VoiceStatus,
		HUD_DirectorMessage,
		HUD_GetStudioModelInterface,
		HUD_ChatInputPosition,
		HUD_GetPlayerTeam
	};

	*pcldll_func = cldll_func;
}
