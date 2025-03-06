//
// Generated by dtk
// Translation Unit: d_a_syan.cpp
//

#include "d/actor/d_a_syan.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/res/res_syan.h"

#include "weak_data_1811.h" // IWYU pragma: keep

static f32 b_pos_x[6] = { 870.0f, 420.0f, -420.0f, -880.0f, -400.0f, 440.0f };
static f32 b_pos_y[6] = { -560.0f, -760.0f, -630.0f, -710.0f, -670.0f, -690.0f };
static f32 b_pos_z[6] = { 0.0f, 750.0f, 750.0f, 0.0f, -720.0f, -750.0f };

/* 000000EC-000002D4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    J3DJoint* joint = (J3DJoint*)node;
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        syan_class* i_this = (syan_class*)model->getUserArea();
        if (i_this != NULL) {
            mDoMtx_copy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, i_this->field_0x2a4[0].y);
                cMtx_XrotM(*calc_mtx, -i_this->field_0x2a4[0].x);
                cMtx_ZrotM(*calc_mtx, i_this->field_0x2a4[0].z);
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            } else if (jntNo == 5) {
                cMtx_YrotM(*calc_mtx, i_this->field_0x2b0.y);
                cMtx_XrotM(*calc_mtx, -(i_this->field_0x2a4[1].x + i_this->field_0x2b0.x));
                cMtx_ZrotM(*calc_mtx, i_this->field_0x2b0.z);
                model->setAnmMtx(jntNo, *calc_mtx);
                cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);

                for (s32 i = 0; i < (s32)ARRAY_SIZE(b_pos_x); i++) {
                    cXyz b_pos(b_pos_x[i], b_pos_y[i], b_pos_z[i]);
                    i_this->partPosOld[i] = i_this->partPos[i];
                    MtxPosition(&b_pos, &i_this->partPos[i]);
                }
            }
        }
    }

    return TRUE;
}

/* 00000310-00000440       .text syan_draw__FP10syan_class */
void syan_draw(syan_class* i_this) {
    GXColor color;
    color.r = REG0_S(4) + 0xEB;
    color.g = REG0_S(5) + 0x7D;
    color.b = REG0_S(6);
    color.a = REG0_S(7);

    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->partPos); i++) {
        MtxTrans(i_this->partPos[i].x, i_this->partPos[i].y, i_this->partPos[i].z, false);
        f32 scale = i_this->partScale1[i] * i_this->partScale2[i];
        MtxScale(scale, scale, scale, true);
        cMtx_YrotM(*calc_mtx, i_this->partRotY[i]);
        cMtx_copy(*calc_mtx, i_this->partMtx[i]);
        dComIfGd_setAlphaModelColor(color);
        dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_TWO_SPHERES, i_this->partMtx[i], i_this->partAlpha[i]);
    }
}

/* 00000440-000004AC       .text daSyan_Draw__FP10syan_class */
static BOOL daSyan_Draw(syan_class* i_this) {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(i_this->morf->getModel(), &i_this->tevStr);
    i_this->morf->entryDL();
    syan_draw(i_this);
    return TRUE;
}

/* 000004AC-00000CA0       .text daSyan_Execute__FP10syan_class */
static BOOL daSyan_Execute(syan_class* i_this) {
    /* Nonmatching */
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->timer); i++)
        if (i_this->timer[i] != 0)
            i_this->timer[i]--;

    i_this->morf->calc();
    i_this->frameCount++;
    i_this->field_0x2c4 += i_this->field_0x2cc;
    i_this->field_0x2c8 += i_this->field_0x2d0;
    i_this->field_0x2a4[0].x = i_this->field_0x2bc * cM_ssin(i_this->field_0x2c4);
    i_this->field_0x2a4[1].x = i_this->field_0x2c0 * cM_ssin(i_this->field_0x2c8);
    i_this->field_0x2b0.y = i_this->field_0x2b8 * cM_ssin(i_this->frameCount * (REG0_S(8) + 800));
    i_this->field_0x2b0.z = i_this->field_0x2b8 * cM_ssin(i_this->frameCount * (REG0_S(9) + 700));

    switch (i_this->state) {
    case 0:
        break;
    case 1:
        cLib_addCalcAngleS2(&i_this->field_0x2b0.x, REG0_S(1) + 2500, 2, REG0_S(2) + 250);
        cLib_addCalc2(&i_this->field_0x2bc, REG0_F(1) * 100.0f + 1500.0f, 0.5f, REG0_F(12) * 100.0f + 150.0f);
        cLib_addCalc2(&i_this->field_0x2c0, 2500.0f, 0.5f, 250.0f);
        cLib_addCalc2(&i_this->field_0x2b8, 2000.0f, 0.5f, 200.0f);
        if (i_this->timer[0] == 0)
            i_this->state++;
        break;
    case 2:
        cLib_addCalc2(&i_this->field_0x2cc, REG0_F(4) * 100.0f + 500.0f, 0.1f, REG0_F(5) * 100.0f + 50.0f);
        cLib_addCalc2(&i_this->field_0x2d0, REG0_F(6) * 100.0f + 1000.0f, 0.1f, REG0_F(7) * 100.0f + 20.0f);
        cLib_addCalc2(&i_this->field_0x2bc, i_this->field_0x2dc * (REG0_F(8) * 100.0f + 300.0f), 0.1f, REG0_F(9) * 100.0f + 10.0f);
        cLib_addCalc2(&i_this->field_0x2c0, i_this->field_0x2dc * (REG0_F(10) * 100.0f + 300.0f), 0.1f, REG0_F(11) * 100.0f + 10.0f);
        cLib_addCalcAngleS2(&i_this->field_0x2b0.x, REG0_S(1) + 2500, 2, REG0_S(2) + 2000);
        cLib_addCalc2(&i_this->field_0x2b8, i_this->field_0x2dc * 500.0f, 0.2f, REG0_F(13) + 5.0f);
        break;
    }

    J3DModel* model = i_this->morf->getModel();
    i_this->scale.set(0.25f, 0.25f, 0.25f);
    model->setBaseScale(i_this->scale);
    mDoMtx_stack_c::transS(i_this->current.pos);
    mDoMtx_stack_c::lYrotM(i_this->current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    for (s32 i = 0; i < syan_class::kEmtrNum; i++) {
        if (i_this->field_0x58c[i] == 0) {
            i_this->field_0x58c[i] = cM_rndF(REG0_F(2) + 10.0f) + 5.0f + REG0_F(3);
            i_this->field_0x52c[i] = cM_rndF(REG0_F(6) + 4.0f) + 4.0f + REG0_F(7);
        }
        if (i_this->field_0x598[i] == 0) {
            i_this->field_0x598[i] = cM_rndF(6.0f) + 3.0f;
            i_this->field_0x55c[i] = cM_rndF(0.075f) + 0.75f;
        }
        cLib_addCalc2(&i_this->partAlpha[i], i_this->field_0x52c[i], 1.0f, REG0_F(4) + 0.1f);
        cLib_addCalc2(&i_this->partScale1[i], i_this->field_0x55c[i], 0.4f, 0.04f);
        i_this->partRotY[i] += 0x100;
        if (i_this->field_0x5a4[i] == 0) {
            cLib_addCalc2(&i_this->partScale2[i], REG0_F(0) + 0.75f, 0.5f, 0.05f);
            if (!i_this->emtrEnabled[i]) {
                i_this->emtrEnabled[i] = true;
                static cXyz fire_scale(0.7f, 0.7f, 0.7f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_01EA, &i_this->partPos[i], NULL, &fire_scale, 0xFF, &i_this->emtrCallBack[i]);
            } else {
                JPABaseEmitter* emtr = i_this->emtrCallBack[i].getEmitter();
                if (emtr != NULL) {
                    f32 dirX = (REG0_F(3) + -0.03f) * (i_this->partPos[i].x - i_this->partPosOld[i].x);
                    if (dirX > 1.0f) dirX = 1.0f;
                    else if (dirX < -1.0f) dirX = -1.0f;
                    f32 dirZ = (REG0_F(3) + -0.03f) * (i_this->partPos[i].z - i_this->partPosOld[i].z);
                    if (dirZ > 1.0f) dirZ = 1.0f;
                    else if (dirZ < -1.0f) dirZ = -1.0f;

                    cXyz dir(dirZ, 0.1f, dirZ);
                    emtr->setDirection(dir);

                    f32 dirMag = std::sqrtf(dirX*dirX + dirZ*dirZ);
                    f32 scaleY = (REG0_F(12) + 2.0f) * dirMag + 1.0f;
                    if (scaleY > REG0_F(13) + 4.0f)
                        scaleY = REG0_F(13) + 4.0f;

                    cXyz scale(1.0f, scaleY, 1.0f);
                    i_this->emtrCallBack[i].getEmitter()->setGlobalParticleScale(scale);

                    cXyz pos(i_this->partPos[i].x, i_this->partPos[i].y + REG0_F(7) + 20.0f, i_this->partPos[i].z);
                    dComIfGp_particle_setSimple(dPa_name::ID_COMMON_4004, &pos, 0xFF, g_whiteColor, g_whiteColor, 0);
                }
            }
        }

        if (i_this->field_0x58c[i] != 0)
            i_this->field_0x58c[i]--;
        if (i_this->field_0x598[i] != 0)
            i_this->field_0x598[i]--;
        if (i_this->field_0x5a4[i] != 0)
            i_this->field_0x5a4[i]--;
    }

    return TRUE;
}

/* 00000CA0-00000CA8       .text daSyan_IsDelete__FP10syan_class */
static BOOL daSyan_IsDelete(syan_class* i_this) {
    return TRUE;
}

/* 00000CA8-00000D1C       .text daSyan_Delete__FP10syan_class */
static BOOL daSyan_Delete(syan_class* i_this) {
    /* Nonmatching */
    dComIfG_resDelete(&i_this->mPhs, "Syan");
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->emtrCallBack); i++)
        i_this->emtrCallBack[i].~dPa_followEcallBack();
    return TRUE;
}

/* 00000D1C-00000E10       .text daSyan_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSyan_solidHeapCB(fopAc_ac_c* i_ac) {
    syan_class* i_this = (syan_class*)i_ac;
    i_this->morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Syan", SYAN_BDL_SYAN),
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Syan", SYAN_BCK_SYAN),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11000002
    );
    return i_this->morf != NULL;
}

/* 00000E10-00000FE0       .text daSyan_Create__FP10fopAc_ac_c */
static s32 daSyan_Create(fopAc_ac_c* i_ac) {
    /* Nonmatching */
    fopAcM_SetupActor(i_ac, syan_class);
    syan_class* i_this = (syan_class*)i_ac;
    s32 rt = dComIfG_resLoad(&i_this->mPhs, "Syan");
    if (rt == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, daSyan_solidHeapCB, 0x3e40) != 0) {
            J3DModel* model = i_this->morf->getModel();
            for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
                model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            }
            fopAcM_SetMin(i_this, -1000.0f, -5000.0f, -1000.0f);
            fopAcM_SetMax(i_this, 1000.0f, 5000.0f, 1000.0f);
            fopAcM_SetMtx(i_this, i_this->morf->getModel()->getBaseTRMtx());
            model->setUserArea((u32)i_this);
            i_this->field_0x2b8 = 200.0f;

            static s16 fire_time[] = { 0, 5, 10, 15, 20, 25 };
            for (s32 i = 0; i < ARRAY_SIZE(i_this->field_0x5a4); i++)
                i_this->field_0x5a4[i] = fire_time[i];
        } else {
            rt = cPhs_ERROR_e;
        }
    }
    return rt;
}

static actor_method_class l_daSyan_Method = {
    (process_method_func)daSyan_Create,
    (process_method_func)daSyan_Delete,
    (process_method_func)daSyan_Execute,
    (process_method_func)daSyan_IsDelete,
    (process_method_func)daSyan_Draw,
};

actor_process_profile_definition g_profile_SYAN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SYAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(syan_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00EF,
    /* Actor SubMtd */ &l_daSyan_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
