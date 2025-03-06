//
// Generated by dtk
// Translation Unit: d_door.cpp
//

#include "d/d_door.h"
#include "d/d_com_inf_game.h"
#include "d/d_vibration.h"
#include "d/res/res_key.h"
#include "d/res/res_hkyo.h"
#include "d/actor/d_a_player.h"
#include "SSystem/SComponent/c_angle.h"

/* 8006B39C-8006B3A8       .text getSwbit__12dDoor_info_cFv */
u8 dDoor_info_c::getSwbit() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 8006B3A8-8006B3B4       .text getSwbit2__12dDoor_info_cFv */
u8 dDoor_info_c::getSwbit2() {
    return (fopAcM_GetParam(this) >> 0x14) & 0xFF;
}

/* 8006B3B4-8006B3C0       .text getType__12dDoor_info_cFv */
u8 dDoor_info_c::getType() {
    return (fopAcM_GetParam(this) >> 0x08) & 0xF;
}

/* 8006B3C0-8006B3EC       .text setType__12dDoor_info_cFUc */
void dDoor_info_c::setType(u8 type) {
    if (type >= 0x10)
        return;
    fopAcM_SetParam(this, fopAcM_GetParam(this) & ~(0xF << 0x08));
    fopAcM_SetParam(this, fopAcM_GetParam(this) | ((type << 0x08) & (0xFF << 0x08)));
}

/* 8006B3EC-8006B3F8       .text getEventNo__12dDoor_info_cFv */
u8 dDoor_info_c::getEventNo() {
    return (fopAcM_GetParam(this) >> 0x0C) & 0xFF;
}

/* 8006B3F8-8006B404       .text getFRoomNo__12dDoor_info_cFv */
u8 dDoor_info_c::getFRoomNo() {
    return home.angle.x & 0x3F;
}

/* 8006B404-8006B410       .text getBRoomNo__12dDoor_info_cFv */
u8 dDoor_info_c::getBRoomNo() {
    return (home.angle.x >> 0x06) & 0x3F;
}

/* 8006B410-8006B41C       .text getShipId__12dDoor_info_cFv */
u8 dDoor_info_c::getShipId() {
    return home.angle.z & 0x3F;
}

/* 8006B41C-8006B428       .text getArg1__12dDoor_info_cFv */
u8 dDoor_info_c::getArg1() {
    return (home.angle.z >> 0x08) & 0xFF;
}

/* 8006B428-8006B4C4       .text adjoinPlayer__12dDoor_info_cFv */
BOOL dDoor_info_c::adjoinPlayer() {
    int frontRoomNo = getFRoomNo();
    int backRoomNo = getBRoomNo();
    if (frontRoomNo == 0x3F || backRoomNo == 0x3F)
        return TRUE;
    if (dComIfGp_roomControl_checkRoomDisp(frontRoomNo) ||
        dComIfGp_roomControl_checkRoomDisp(backRoomNo))
    {
        return TRUE;
    }
    return FALSE;
}

/* 8006B4C4-8006B554       .text getViewRoomNo__12dDoor_info_cFv */
u8 dDoor_info_c::getViewRoomNo() {
    cXyz delta = dComIfGd_getView()->mLookat.mEye - current.pos;
    if (delta.inprodXZ(mAngleVec) < 0.0f)
        return getBRoomNo();
    else
        return getFRoomNo();
}

/* 8006B554-8006B5E4       .text frontCheckOld__12dDoor_info_cFv */
s32 dDoor_info_c::frontCheckOld() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cSGlobe globe(player->current.pos - current.pos);
    cSAngle angle1;
    angle1 = (globe.U() - current.angle.y);
    s16 angle = angle1.Abs();
    if (angle < 0x4000 && angle >= 0)
        return 0;
    else
        return 1;
}

/* 8006B65C-8006B6F4       .text frontCheck__12dDoor_info_cFv */
s32 dDoor_info_c::frontCheck() {
    s32 stayNo = dComIfGp_roomControl_getStayNo();
    if (getFRoomNo() == getBRoomNo())
        return frontCheckOld();

    return stayNo == getFRoomNo() ? 0 :
        stayNo == getBRoomNo() ? 1 : 2;
}

/* 8006B6F4-8006B824       .text drawCheck_local__12dDoor_info_cFv */
s32 dDoor_info_c::drawCheck_local() {
    if (!adjoinPlayer() && !eventInfo.checkCommandDemoAccrpt() && !eventInfo.checkCommandDoor())
        return 0;

    if (getFRoomNo() == 0x3F || getBRoomNo() == 0x3F)
        tevStr.mRoomNo = dComIfGp_roomControl_getStayNo();
    else
        tevStr.mRoomNo = getViewRoomNo();

    current.roomNo = tevStr.mRoomNo;

    u8 front = frontCheck();
    if (front == 2)
        mRoomNo = -1;
    else
        mRoomNo = dComIfGp_roomControl_getStayNo();

    if (!dComIfGp_roomControl_checkRoomDisp(tevStr.mRoomNo))
        return 1;

    if (getViewRoomNo() == 0x3F && (getFRoomNo() != 0x3F || getBRoomNo() != 0x3F))
        return 1;
    else
        return 2;
}

/* 8006B824-8006B8AC       .text drawCheck__12dDoor_info_cFi */
u8 dDoor_info_c::drawCheck(int mode) {
    s32 rt = drawCheck_local();
    if (rt != 0) {
        if (mode) {
            fopAcM_SetStatusMap(this, 0x0A);
        }  else {
            fopAcM_SetStatusMap(this, 0x09);
        }
    } else {
        fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
    }
    return rt == 2;
}

/* 8006B8AC-8006B954       .text checkExecute__12dDoor_info_cFv */
u8 dDoor_info_c::checkExecute() {
    mFrontCheck = frontCheck();
    if (fopAcM_CheckStatus(this, fopAcStts_UNK1000_e))
        return 1;

    if (eventInfo.checkCommandDemoAccrpt() || eventInfo.checkCommandDoor())
        return 2;

    if (mRoomNo2 != dComIfGp_roomControl_getStayNo())
        return 0;

    if (mFrontCheck != 2 && adjoinPlayer())
        return 2;

    return 0;
}

/* 8006B954-8006BA30       .text startDemoProc__12dDoor_info_cFv */
void dDoor_info_c::startDemoProc() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    mStaffId = dComIfGp_evmng_getMyStaffId("SHUTTER_DOOR");
    shape_angle.y = current.angle.y;
    JUT_ASSERT(0x112, player);
    s16 delta = player->home.angle.y - home.angle.y;
    if (delta < 0)
        delta = -delta;
    if (delta < 0x1000 && delta > -1000)
        shape_angle.y += 0x7FFF;
}

/* 8006BA30-8006BB5C       .text makeEventId__12dDoor_info_cFi */
void dDoor_info_c::makeEventId(int spl) {
    static const char* table[] = {
        "DEFAULT_STOP_OPEN",
        "DEFAULT_STOP_OPEN",
        "DEFAULT_SHUTTER_DOOR_F",
        "DEFAULT_SHUTTER_DOOR_F",
        "DEFAULT_SHUTTER_DOOR_F_STOP",
        "DEFAULT_SHUTTER_DOOR_F_STOP",
        "DEFAULT_BS_SHUTTER_F",
        "DEFAULT_KNOB_DOOR_F_OPEN",
        "DEFAULT_KNOB_DOOR_B_OPEN",
        "DEFAULT_KNOB_TALK",
        "HKYO_DOOR",
        "SHUTTER_DROP_CARRY",
    };

    for (s32 i = 0; i < 12; i++) {
        mToolId[i] = dComIfGp_evmng_getToolId(getEventNo(), i);
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(table[i], mToolId[i]);
    }

    switch (spl) {
    case 1:
        mEventIdx[2] = dComIfGp_evmng_getEventIdx("DEFAULT_SHUTTER_DOOR_10", mToolId[2]);
        mEventIdx[3] = dComIfGp_evmng_getEventIdx("DEFAULT_SHUTTER_DOOR_10", mToolId[3]);
        break;
    case 2:
        mEventIdx[2] = dComIfGp_evmng_getEventIdx("DEFAULT_SHUTTER_DOOR_12", mToolId[2]);
        mEventIdx[3] = dComIfGp_evmng_getEventIdx("DEFAULT_SHUTTER_DOOR_12", mToolId[3]);
        break;
    }
}

/* 8006BB5C-8006BBB0       .text initProc__12dDoor_info_cFi */
void dDoor_info_c::initProc(int spl) {
    mAngleVec.set(cM_ssin(home.angle.y), 0.0f, cM_scos(home.angle.y));
    makeEventId(spl);
}

/* 8006BBB0-8006BC50       .text initOpenDemo__12dDoor_info_cFi */
void dDoor_info_c::initOpenDemo(int evt) {
    if (field_0x2c6 != 9)
        dComIfGp_map_setAGBMapSendStopFlg();

    shape_angle.y = current.angle.y;
    if (mFrontCheck == 1)
        shape_angle.y += 0x7FFF;

    mStaffId = dComIfGp_evmng_getMyStaffId("SHUTTER_DOOR");
    if (evt)
        dComIfGp_event_onEventFlag(2);
}

/* 8006BC50-8006BDBC       .text checkArea__12dDoor_info_cFfff */
BOOL dDoor_info_c::checkArea(f32 f1, f32 f2, f32 distXZSqMax) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz delta = player->current.pos - current.pos;
    f32 distXZSq = delta.abs2XZ();
    if (distXZSq > distXZSqMax)
        return FALSE;

    delta.normalize();
    f32 dot = delta.inprodXZ(mAngleVec);
    f32 d3 = distXZSq * dot * dot;
    if (d3 > f2)
        return FALSE;

    if (distXZSq - d3 > f1)
        return FALSE;

    s16 checkAngle = current.angle.y;
    if (mFrontCheck == 1)
        checkAngle += 0x7FFF;
    if (abs((s16)(checkAngle - player->current.angle.y)) < 0x5000)
        return FALSE;

    return TRUE;
}

/* 8006BDBC-8006BE94       .text openInitCom__12dDoor_info_cFi */
void dDoor_info_c::openInitCom(int ship) {
    if (mFrontCheck == 0) {
        mFromRoomNo = getFRoomNo();
        mToRoomNo = getBRoomNo();
    } else {
        mFromRoomNo = getBRoomNo();
        mToRoomNo = getFRoomNo();
    }

    if (mFromRoomNo != mToRoomNo && mFromRoomNo != 0x3F && mToRoomNo != 0x3F)
        dComIfGp_roomControl_offStatusFlag(mToRoomNo, 0x08);

    if (ship && valShipId())
        dStage_setShipPos(getShipId(), mToRoomNo);
}

/* 8006BE94-8006BF74       .text openProcCom__12dDoor_info_cFv */
void dDoor_info_c::openProcCom() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    s16 angle = shape_angle.y + 0x7FFF;
    cXyz target;
    cXyz playerPos = player->current.pos;
    target = current.pos;
    target.x += cM_ssin(angle) * -100.0f;
    target.z += cM_scos(angle) * -100.0f;
    playerPos.x = playerPos.x * 0.9f + target.x * 0.1f;
    playerPos.z = playerPos.z * 0.9f + target.z * 0.1f;
    player->setPlayerPosAndAngle(&playerPos, player->current.angle.y);
}

/* 8006BF74-8006C0A4       .text closeEndCom__12dDoor_info_cFv */
void dDoor_info_c::closeEndCom() {
    if (mFromRoomNo != mToRoomNo && mFromRoomNo != 0x3F && mToRoomNo != 0x3F)
        dComIfGp_roomControl_onStatusFlag(mFromRoomNo, 0x08);

    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz delta = player->current.pos - current.pos;
    f32 dot = delta.inprodXZ(mAngleVec);
    f32 rad = dot < 0.0f ? 180.0f : -180.0f;

    cXyz pos(current.pos.x - rad * mAngleVec.x, current.pos.y, current.pos.z - rad * mAngleVec.z);
    s8 roomNo = fopAcM_GetRoomNo(player);
    s16 angle;
    if (dot > 0.0f) {
        angle = current.angle.y;
    } else {
        angle = current.angle.y + 0x8000;
    }
    dComIfGs_setRestartRoom(pos, angle, roomNo);
}

/* 8006C0A4-8006C0EC       .text getDemoAction__12dDoor_info_cFv */
s32 dDoor_info_c::getDemoAction() {
    static char* action_table[] = {
        "WAIT",
        "STOP_OPEN",
        "STOP_CLOSE",
        "OPEN",
        "CLOSE",
        "SMOKE",
        "SMOKE_END",
        "SETGOAL",
        "UNLOCK",
        "SETSTART",
        "SETANGLE",
        "ADJUSTMENT",
        "OPEN_PUSH",
        "OPEN_PULL",
        "OPEN_PUSH2",
        "OPEN_PULL2",
        "TALK",
        "SETSTART_PUSH",
        "SETSTART_PULL",
        "END_CHECK",
        "DROP_BF",
        "DROP_AF",
    };

    return dComIfGp_evmng_getMyActIdx(mStaffId, action_table, ARRAY_SIZE(action_table), FALSE, 0);
}

/* 8006C0EC-8006C1D8       .text setGoal__12dDoor_info_cFv */
void dDoor_info_c::setGoal() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz playerPos = player->current.pos;
    cXyz target = current.pos;
    s16 angle = shape_angle.y + 0x7FFF;
    playerPos.x += cM_ssin(angle) * 350.0f;
    playerPos.z += cM_scos(angle) * 350.0f;
    target.x += cM_ssin(angle) * 250.0f;
    target.z += cM_scos(angle) * 250.0f;
    playerPos.x = playerPos.x * 0.8f + target.x * 0.2f;
    playerPos.z = playerPos.z * 0.8f + target.z * 0.2f;
    dComIfGp_evmng_setGoal(&playerPos);
}

/* 8006C1D8-8006C200       .text setPlayerAngle__12dDoor_info_cFi */
void dDoor_info_c::setPlayerAngle(BOOL flip) {
    s16 angle = shape_angle.y;
    daPy_py_c* link = (daPy_py_c*)dComIfGp_getLinkPlayer();
    if (flip) {
        angle += 0x7FFF;
    }
    link->changeDemoMoveAngle(angle);
}

/* 8006C200-8006C2BC       .text setPosAndAngle__12dDoor_info_cFP4cXyzs */
void dDoor_info_c::setPosAndAngle(cXyz* pPos, s16 angle) {
    if (eventInfo.checkCommandDemoAccrpt() || eventInfo.checkCommandDoor()) {
        return;
    }
    if (pPos) {
        attention_info.position = current.pos = *pPos;
        attention_info.position.y += 150.0f;
        eyePos = attention_info.position;
    }
    current.angle.y = angle;
    shape_angle.y = current.angle.y;
    mAngleVec.set(cM_ssin(current.angle.y), 0.0f, cM_scos(current.angle.y));
}

/* 8006C2BC-8006C388       .text smokeInit__13dDoor_smoke_cFP12dDoor_info_c */
void dDoor_smoke_c::smokeInit(dDoor_info_c* door) {
    mPos = door->current.pos;
    mRot.y = door->shape_angle.y;
    JPABaseEmitter* emtr = dComIfGp_particle_set(dPa_name::ID_COMMON_2022, &mPos, &mRot, NULL, 0xAA, &mSmokeCb, fopAcM_GetRoomNo(door));
    m34 = 0;
    m35 = 0;
    if (emtr != NULL) {
        emtr->setRate(16.0f);
        emtr->setSpread(0.35f);
        emtr->mGlobalDynamicsScale.x = 2.0f;
        emtr->mGlobalDynamicsScale.y = 2.0f;
        emtr->mGlobalDynamicsScale.z = 2.0f;
        emtr->mGlobalParticleScale.x = 2.0f;
        emtr->mGlobalParticleScale.y = 2.0f;
        emtr->mGlobalParticleScale.z = 2.0f;
    }
}

/* 8006C388-8006C41C       .text smokeProc__13dDoor_smoke_cFP12dDoor_info_c */
void dDoor_smoke_c::smokeProc(dDoor_info_c* door) {
    if (m35 != 0) {
        f32 wave = (m34 * 20) * ((m34 & 1) ? 1.0f : -1.0f);
        m34++;
        mPos.x += wave * door->mAngleVec.z;
        mPos.z += wave * door->mAngleVec.x;
    } else {
        m35 = 1;
    }
}

/* 8006C41C-8006C448       .text smokeEnd__13dDoor_smoke_cFv */
void dDoor_smoke_c::smokeEnd() {
    mSmokeCb.end();
}

/* 8006C448-8006C478       .text keyResLoad__12dDoor_key2_cFv */
void dDoor_key2_c::keyResLoad() {
    dComIfG_resLoad(&mPhs, "Key");
}

/* 8006C478-8006C4A8       .text keyResDelete__12dDoor_key2_cFv */
void dDoor_key2_c::keyResDelete() {
    dComIfG_resDelete(&mPhs, "Key");
}

/* 8006C4A8-8006C5E8       .text keyInit__12dDoor_key2_cFP12dDoor_info_c */
void dDoor_key2_c::keyInit(dDoor_info_c* door) {
    if (mpModel != NULL && mbEnabled && !door->mFrontCheck) {
        if ((int)door->getSwbit() < 0x80)
            dComIfGs_onSwitch(door->getSwbit(), -1);
        if (!mbIsBossDoor)
            dComIfGp_setItemKeyNumCount(-1);
        switch (mbIsBossDoor) {
        case 1: fopAcM_seStart(door, JA_SE_OBJ_BOSS_LOCK_OPEN, 0); break;
        default: fopAcM_seStart(door, JA_SE_OBJ_DOOR_CHAIN_OPEN, 0); break;
        }
        m20 = 1;
    } else {
        m20 = 0;
    }
}

/* 8006C5E8-8006C650       .text keyProc__12dDoor_key2_cFv */
BOOL dDoor_key2_c::keyProc() {
    if (m20) {
        if (mBckAnim.play()) {
            keyOff();
            m20 = 0;
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return TRUE;
    }
}

/* 8006C650-8006C764       .text keyCreate_Nkey__12dDoor_key2_cFv */
BOOL dDoor_key2_c::keyCreate_Nkey() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Key", KEY_BDL_VLOCN);
    JUT_ASSERT(0x2cc, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel == NULL)
        return FALSE;

    J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes("Key", KEY_BCK_VLOCN);
    if (!mBckAnim.init(modelData, bck, TRUE, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, 0, -1, false))
        return FALSE;

    return TRUE;
}

/* 8006C764-8006C910       .text keyCreate_Bkey__12dDoor_key2_cFv */
BOOL dDoor_key2_c::keyCreate_Bkey() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Key", KEY_BDL_VLOCB);
    JUT_ASSERT(0x2e4, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel == NULL)
        return FALSE;

    J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes("Key", KEY_BCK_VLOCB);
    if (!mBckAnim.init(modelData, bck, TRUE, J3DFrameCtrl::LOOP_ONCE_e, 1.0f, 0, -1, false))
        return FALSE;

    J3DSkinDeform* deform = new J3DSkinDeform();
    if (deform == NULL)
        return FALSE;

    switch (mpModel->setSkinDeform(deform, 1)) {
    case J3DErrType_OutOfMemory:
        return FALSE;
    default:
        JUT_ASSERT(0x306, FALSE);
    case J3DErrType_Success:
        return TRUE;
    }
}

/* 8006C910-8006C948       .text keyCreate__12dDoor_key2_cFi */
BOOL dDoor_key2_c::keyCreate(int type) {
    mbIsBossDoor = type;
    switch (type) {
    case 1: return keyCreate_Bkey();
    default: return keyCreate_Nkey();
    }
}

/* 8006C948-8006C954       .text keyOn__12dDoor_key2_cFv */
void dDoor_key2_c::keyOn() {
    mbEnabled = true;
}

/* 8006C954-8006C960       .text keyOff__12dDoor_key2_cFv */
void dDoor_key2_c::keyOff() {
    mbEnabled = false;
}

/* 8006C960-8006CA10       .text calcMtx__12dDoor_key2_cFP12dDoor_info_c */
void dDoor_key2_c::calcMtx(dDoor_info_c* door) {
    if (mbEnabled) {
        mDoMtx_stack_c::transS(door->current.pos);
        mDoMtx_stack_c::YrotM(door->current.angle.y);
        switch (mbIsBossDoor) {
        case 1: mDoMtx_stack_c::transM(0.0f, 230.0f, 20.0f); break;
        default: mDoMtx_stack_c::transM(0.0f, 150.0f, 20.0f); break;
        }
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 8006CA10-8006CA78       .text draw__12dDoor_key2_cFP12dDoor_info_c */
void dDoor_key2_c::draw(dDoor_info_c* door) {
    J3DModelData* modelData = mpModel->getModelData();
    g_env_light.setLightTevColorType(mpModel, &door->tevStr);
    mBckAnim.entry(modelData);
    mDoExt_modelUpdateDL(mpModel);
}

/* 8006CA78-8006CB28       .text calcMtx__12dDoor_stop_cFP12dDoor_info_c */
void dDoor_stop_c::calcMtx(dDoor_info_c* door) {
    if (m8 == 0 || mpModel == NULL)
        return;
    mDoMtx_stack_c::transS(door->current.pos.x, door->current.pos.y + mOffsY, door->current.pos.z);
    mDoMtx_stack_c::YrotM(door->current.angle.y);
    if (mFrontCheck == 1)
        mDoMtx_stack_c::YrotM(0x7FFF);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 8006CB28-8006CBFC       .text closeInit__12dDoor_stop_cFP12dDoor_info_c */
void dDoor_stop_c::closeInit(dDoor_info_c* door) {
    mOffsY = 300.0f;
    fopAcM_SetSpeedF(door, 0.0f);
    if (door->getArg1() == 17) {
        fopAcM_seStart(door, JA_SE_OBJ_CAGE_CLOSE, 0);
    } else {
        fopAcM_seStart(door, JA_SE_OBJ_STN_DOOR_STL_BAR, 0);
    }
    mB = 1;
}

/* 8006CBFC-8006CC80       .text closeProc__12dDoor_stop_cFP12dDoor_info_c */
s32 dDoor_stop_c::closeProc(dDoor_info_c* door) {
    if (!mB)
        return 1;

    cLib_chaseF(&door->speedF, 60.0f, 6.0f);
    if (cLib_chaseF(&mOffsY, 0.0f, door->speedF)) {
        mB = FALSE;
        return 2;
    } else {
        return 0;
    }
}

/* 8006CC80-8006CD50       .text openInit__12dDoor_stop_cFP12dDoor_info_c */
void dDoor_stop_c::openInit(dDoor_info_c* door) {
    mOffsY = 0.0f;
    fopAcM_SetSpeedF(door, 0.0f);
    if (door->getArg1() == 17) {
        fopAcM_seStart(door, JA_SE_OBJ_CAGE_OPEN, 0);
    } else {
        fopAcM_seStart(door, JA_SE_OBJ_STN_DOOR_STL_BAR, 0);
    }
    mB = 1;
}

/* 8006CD50-8006CDD8       .text openProc__12dDoor_stop_cFP12dDoor_info_c */
s32 dDoor_stop_c::openProc(dDoor_info_c* door) {
    if (!mB)
        return 1;

    cLib_chaseF(&door->speedF, 30.0f, 4.0f);
    if (cLib_chaseF(&mOffsY, 300.0f, door->speedF)) {
        mB = FALSE;
        m8 = FALSE;
        return 2;
    } else {
        return 0;
    }
}

/* 8006CDD8-8006CE8C       .text create__12dDoor_stop_cFv */
BOOL dDoor_stop_c::create() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getStageRes("Stage", "stop10.bmd");
    if (modelData == NULL)
        modelData = (J3DModelData*)dComIfG_getStageRes("Stage", "stop10.bdl");

    if (modelData != NULL) {
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (mpModel == NULL)
            return FALSE;
    }

    return TRUE;
}

/* 8006CE8C-8006CEA8       .text init__11dDoor_msg_cFs */
void dDoor_msg_c::init(s16 msg_id) {
    mMsgId = msg_id;
    mMsgPId = fpcM_ERROR_PROCESS_ID_e;
    m_msg = NULL;
    mState = 0;
}

/* 8006CEA8-8006D0DC       .text proc__11dDoor_msg_cFP4cXyz */
BOOL dDoor_msg_c::proc(cXyz* pos) {
    switch (mState) {
    case 0:
        mMsgPId = fopMsgM_messageSet(mMsgId, pos);
        if (mMsgPId != fpcM_ERROR_PROCESS_ID_e)
            mState++;
        break;
    case 1:
        m_msg = fopMsgM_SearchByID(mMsgPId);
        if (m_msg != NULL)
            mState++;
        break;
    case 2:
        JUT_ASSERT(0x3ba, m_msg);
        if (m_msg->mStatus == fopMsgStts_MSG_TYPING_e) {
            switch (mMsgId) {
            case 0x1BBD:
            case 0x06A8:
                dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                break;
            }
            mState++;
        }
        break;
    case 3:
        JUT_ASSERT(0x3ca, m_msg);
        if (m_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            switch (mMsgId) {
            case 0x1BBD:
            case 0x1BC0:
            case 0x1BC1:
            case 0x1BC2:
                mMsgId++;
                m_msg->mStatus = fopMsgStts_MSG_CONTINUES_e;
                fopMsgM_messageSet(mMsgId);
                break;
            default:
                mState++;
                m_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                break;
            }
        }
        break;
    }

    if (m_msg != NULL && m_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
        m_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 8006D0DC-8006D11C       .text resLoad__12dDoor_hkyo_cFv */
s32 dDoor_hkyo_c::resLoad() {
    if (m11 == 0) {
        return cPhs_COMPLEATE_e;
    }
    return dComIfG_resLoad(&mPhs, "Hkyo");
}

/* 8006D11C-8006D154       .text resDelete__12dDoor_hkyo_cFv */
void dDoor_hkyo_c::resDelete() {
    if (m11 == 0) {
        return;
    }
    dComIfG_resDelete(&mPhs, "Hkyo");
}

/* 8006D154-8006D2D4       .text create__12dDoor_hkyo_cFv */
BOOL dDoor_hkyo_c::create() {
    if (m11 == 0)
        return TRUE;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hkyo", HKYO_BDL_HKYO1);
    JUT_ASSERT(0x41c, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000202);
    if (mpModel == NULL)
        return FALSE;

    mpBrkAnm = new mDoExt_brkAnm();
    if (mpBrkAnm == NULL)
        return FALSE;

    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Hkyo", HKYO_BRK_HKYO1B);
    if (!mpBrkAnm->init(modelData, brk, TRUE, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0))
        return FALSE;

    return TRUE;
}

/* 8006D2D4-8006D3A8       .text setAnm__12dDoor_hkyo_cFUc */
void dDoor_hkyo_c::setAnm(u8 idx) {
    if (mAnmIdx == idx)
        return;

    mAnmIdx = idx;
    if (idx == 0)
        return;

    u32 fileIndex;
    switch (idx) {
    case 1: fileIndex = HKYO_BRK_HKYO1A; break;
    case 2: fileIndex = HKYO_BRK_HKYO1B; break;
    default: fileIndex = HKYO_BRK_HKYO1C; break;
    }

    J3DModelData* modelData = mpModel->getModelData();
    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Hkyo", fileIndex);
    mpBrkAnm->init(modelData, brk, TRUE, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, true, 0);
}

/* 8006D3A8-8006D3B4       .text init__12dDoor_hkyo_cFv */
void dDoor_hkyo_c::init() {
    mAnmIdx = 0;
}

/* 8006D3B4-8006D464       .text calcMtx__12dDoor_hkyo_cFP12dDoor_info_cf */
void dDoor_hkyo_c::calcMtx(dDoor_info_c* door, f32 offsY) {
    if (m11 == 0 || mpModel == NULL)
        return;
    mDoMtx_stack_c::transS(door->current.pos);
    mDoMtx_stack_c::YrotM(door->current.angle.y);
    mDoMtx_stack_c::transM(0.0f, offsY, 0.0f);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 8006D464-8006D500       .text draw__12dDoor_hkyo_cFP12dDoor_info_c */
void dDoor_hkyo_c::draw(dDoor_info_c* door) {
    if (m11 == 0 || mAnmIdx == 0 || mpModel == NULL)
        return;
    if (!chkFirst()) {
        J3DModelData* modelData = mpModel->getModelData();
        g_env_light.setLightTevColorType(mpModel, &door->tevStr);
        mpBrkAnm->entry(modelData);
        mDoExt_modelUpdateDL(mpModel);
    }
}

/* 8006D500-8006D71C       .text proc__12dDoor_hkyo_cFP12dDoor_info_c */
void dDoor_hkyo_c::proc(dDoor_info_c* door) {
    if (m11 == 0 || mpModel == NULL)
        return;

    switch (m11) {
    case 1:
        if (dComIfGs_isTmpBit(0x108))
            setAnm(1);
        else if (dComIfGs_isTmpBit(0x110))
            setAnm(2);
        else
            setAnm(0);
        break;
    case 4:
        if (dComIfGs_isEventBit(0x1710))
            setAnm(0);
        else
            setAnm(3);
        break;
    case 3:
        if (!dComIfGs_isTact(2) || dComIfGs_isEventBit(0x1704))
            setAnm(0);
        else
            setAnm(3);
        break;
    case 2:
        if (!dComIfGs_isEventBit(0x1704) || dComIfGs_isEventBit(0x1b01))
            setAnm(0);
        else
            setAnm(3);
        break;
    default:
        setAnm(0);
        break;
    }

    if (mAnmIdx != 0) {
        mpBrkAnm->play();
        fopAcM_seStart(door, JA_SE_OBJ_RES_DOOR_BLINK, 0);
    }
}

/* 8006D71C-8006D784       .text chkFirst__12dDoor_hkyo_cFv */
BOOL dDoor_hkyo_c::chkFirst() {
    if (m11 != 1)
        return FALSE;

    switch (mAnmIdx) {
    case 1:
        if (!dComIfGs_isEventBit(0x2602))
            return TRUE;
        break;
    }

    return FALSE;
}

/* 8006D784-8006D7E8       .text onFirst__12dDoor_hkyo_cFv */
void dDoor_hkyo_c::onFirst() {
    switch (mAnmIdx) {
    case 1: dComIfGs_onEventBit(0x2602); break;
    case 2: dComIfGs_onEventBit(0x2601); break;
    }
}

/* 8006D7E8-8006D800       .text chkStart__12dDoor_hkyo_cFv */
BOOL dDoor_hkyo_c::chkStart() {
    return daPy_getPlayerActorClass()->getGrabUpEnd();
}
