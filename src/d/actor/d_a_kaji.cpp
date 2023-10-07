//
// Generated by dtk
// Translation Unit: d_a_kaji.cpp
//

#include "f_op/f_op_actor_mng.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

struct daKaji_c : fopAc_ac_c {
public:
    BOOL CreateHeap();
    inline s32 _create();
    inline BOOL _delete();
    inline BOOL _execute();
    inline bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 pad[0x29C - 0x298];
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ Mtx mMtx;
    
    static const char M_arcname[];
};

static daObjPirateship::Act_c* l_p_ship;

const char daKaji_c::M_arcname[] = "Kaji";

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daKaji_c*)i_this)->CreateHeap();
}

/* 00000098-000001F4       .text CreateHeap__8daKaji_cFv */
BOOL daKaji_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 0x11); // asoda.bdl
    JUT_ASSERT(0x55, modelData != 0);
    
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Kaji", 0xE), // kj_wait.bck
        J3DFrameCtrl::LOOP_REPEAT_e, 0.0f, 0, -1, 1,
        dComIfG_getObjectRes("Kaji", 0x8), // kj_wait.bas
        0x00080000,
        0x11000002
    );
    
    return mpMorf && mpMorf->getModel();
}

s32 daKaji_c::_create() {
    fopAcM_SetupActor(this, daKaji_c);
    
    s32 phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, (heapCallbackFunc)&CheckCreateHeap, 0x660)) {
            mDoMtx_stack_c::transS(getPosition());
            mDoMtx_stack_c::YrotM(shape_angle.y);
            mDoMtx_stack_c::scaleM(mScale);
            MTXCopy(mDoMtx_stack_c::get(), mMtx);
            
            l_p_ship = (daObjPirateship::Act_c*)fopAcM_SearchByID(mParentPcId);
        } else {
            return cPhs_ERROR_e;
        }
        
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -80.0f, -80.0f, -20.0f, 80.0f, 80.0f, 20.0f);
        
        MTXCopy(mpMorf->getModel()->getBaseTRMtx(), mMtx);
    }
    
    return phase_state;
}

BOOL daKaji_c::_delete() {
    dComIfG_resDelete(&mPhs, M_arcname);
    return TRUE;
}

BOOL daKaji_c::_execute() {
    // Copy the ship's transform (plus an offset) to the helm.
    cXyz* offset = &cXyz(0.0f, 740.0f, -858.0f);
    offset->y += g_regHIO.mChild[10].mFloatRegs[10];
    offset->z += g_regHIO.mChild[10].mFloatRegs[11];
    cMtx_multVec(l_p_ship->mpModel->getBaseTRMtx(), offset, &current.pos);
    
    daObjPirateship::Act_c* ship = l_p_ship;
    shape_angle = ship->shape_angle;
    current.angle = shape_angle;
    
    mpMorf->play(NULL, 0, 0);
    
    mpMorf->getModel()->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
    
    return FALSE;
}

bool daKaji_c::_draw() {
    if (!l_p_ship->unk2CC) {
        return true;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &mTevStr);
    mpMorf->update();
    return true;
}

/* 000001F4-00000344       .text daKajiCreate__FPv */
static s32 daKajiCreate(void* i_this) {
    return ((daKaji_c*)i_this)->_create();
}

/* 00000344-00000374       .text daKajiDelete__FPv */
static BOOL daKajiDelete(void* i_this) {
    return ((daKaji_c*)i_this)->_delete();
}

/* 00000374-000004D4       .text daKajiExecute__FPv */
static BOOL daKajiExecute(void* i_this) {
    return ((daKaji_c*)i_this)->_execute();
}

/* 000004D4-00000568       .text daKajiDraw__FPv */
static BOOL daKajiDraw(void* i_this) {
    return ((daKaji_c*)i_this)->_draw();
}

/* 00000568-00000570       .text daKajiIsDelete__FPv */
static BOOL daKajiIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daKajiMethodTable = {
    (process_method_func)daKajiCreate,
    (process_method_func)daKajiDelete,
    (process_method_func)daKajiExecute,
    (process_method_func)daKajiIsDelete,
    (process_method_func)daKajiDraw,
};

extern actor_process_profile_definition g_profile_Kaji = {
    fpcLy_CURRENT_e,
    3,
    fpcLy_CURRENT_e,
    PROC_Kaji,
    &g_fpcLf_Method.mBase,
    sizeof(daKaji_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01AC,
    &daKajiMethodTable,
    fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
