//
// Generated by dtk
// Translation Unit: jstudio-object.cpp
//

#include "JSystem/JStudio/JStudio/jstudio-object.h"
#include "dolphin/types.h"

/* 8026E8F8-8026E940       .text __dt__Q37JStudio14TVariableValue7TOutputFv */
JStudio::TVariableValue::TOutput::~TOutput() {}

/* 8026E940-8026E9A4       .text update__Q27JStudio14TVariableValueFdPQ27JStudio8TAdaptor */
void JStudio::TVariableValue::update(f64 param_0, JStudio::TAdaptor* param_1) {
    if (field_0x8) {
        field_0x8(this, param_0);
        (*pOutput_)(mValue, param_1);
    }
}

/* 8026E9A4-8026E9B8       .text update_immediate___Q27JStudio14TVariableValueFPQ27JStudio14TVariableValued */
void JStudio::TVariableValue::update_immediate_(JStudio::TVariableValue* param_0, f64 param_1) {
    param_0->mValue = param_0->field_0xc.val;
    param_0->field_0x8 = NULL;
}

/* 8026E9B8-8026E9F4       .text update_time___Q27JStudio14TVariableValueFPQ27JStudio14TVariableValued */
void JStudio::TVariableValue::update_time_(JStudio::TVariableValue* param_0, f64 param_1) {
    param_0->mValue = param_0->field_0xc.val * (param_0->field_0x4 * param_1);
}

/* 8026E9F4-8026EA58       .text update_functionValue___Q27JStudio14TVariableValueFPQ27JStudio14TVariableValued */
void JStudio::TVariableValue::update_functionValue_(JStudio::TVariableValue* param_0, f64 param_1) {
    param_0->mValue = param_0->field_0xc.fv->getValue(param_0->field_0x4 * param_1);
}

/* 8026EA58-8026EAB8       .text __dt__Q37JStudio14TVariableValue13TOutput_none_Fv */
JStudio::TVariableValue::TOutput_none_::~TOutput_none_() {
    /* Nonmatching */
}

/* 8026EAB8-8026EABC       .text __cl__Q37JStudio14TVariableValue13TOutput_none_CFfPQ27JStudio8TAdaptor */
void JStudio::TVariableValue::TOutput_none_::operator()(f32 param_0, JStudio::TAdaptor* param_1) const {}

/* 8026EABC-8026EB04       .text __dt__Q27JStudio8TAdaptorFv */
JStudio::TAdaptor::~TAdaptor() {}

/* 8026EB04-8026EB08       .text adaptor_do_prepare__Q27JStudio8TAdaptorFPCQ27JStudio7TObject */
void JStudio::TAdaptor::adaptor_do_prepare(const JStudio::TObject* param_0) {}

/* 8026EB08-8026EB0C       .text adaptor_do_begin__Q27JStudio8TAdaptorFPCQ27JStudio7TObject */
void JStudio::TAdaptor::adaptor_do_begin(const JStudio::TObject* param_0) {}

/* 8026EB0C-8026EB10       .text adaptor_do_end__Q27JStudio8TAdaptorFPCQ27JStudio7TObject */
void JStudio::TAdaptor::adaptor_do_end(const JStudio::TObject* param_0) {}

/* 8026EB10-8026EB14       .text adaptor_do_update__Q27JStudio8TAdaptorFPCQ27JStudio7TObjectUl */
void JStudio::TAdaptor::adaptor_do_update(const JStudio::TObject* param_0, u32 param_1) {}

/* 8026EB14-8026EB18       .text adaptor_do_data__Q27JStudio8TAdaptorFPCQ27JStudio7TObjectPCvUlPCvUl */
void JStudio::TAdaptor::adaptor_do_data(const JStudio::TObject* param_0, const void* param_1, u32 param_2, const void* param_3, u32 param_4) {}

/* 8026EB18-8026EBB8       .text adaptor_setVariableValue__Q27JStudio8TAdaptorFPQ27JStudio7TObjectUlQ37JStudio4data15TEOperationDataPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue(JStudio::TObject* pObject, u32 param_2, JStudio::data::TEOperationData param_3, const void* param_4, u32 param_5) {
    /* Nonmatching */
    setVarFunc func;
    switch (param_3) {
    case JStudio::data::UNK_0x1:
        func = &adaptor_setVariableValue_VOID_;
        break;
    case JStudio::data::UNK_0x2:
        func = &adaptor_setVariableValue_IMMEDIATE_;
        break;
    case JStudio::data::UNK_0x3:
        func = &adaptor_setVariableValue_TIME_;
        break;
    case JStudio::data::UNK_0x10:
        func = &adaptor_setVariableValue_FVR_NAME_;
        break;
    case JStudio::data::UNK_0x12:
        func = &adaptor_setVariableValue_FVR_INDEX_;
        break;
     default:
        return;
    }

    (*func)(this, pObject, param_2, param_4, param_5);
}

/* 8026EBB8-8026ECAC       .text adaptor_setVariableValue_n__Q27JStudio8TAdaptorFPQ27JStudio7TObjectPCUlUlQ37JStudio4data15TEOperationDataPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue_n(JStudio::TObject* pObject, const u32* param_2, u32 param_3, JStudio::data::TEOperationData param_4, const void* param_5, u32 param_6) {
    setVarFunc pcVar6;
    u32 iVar7;
    switch(param_4) {
    case JStudio::data::UNK_0x1:
        iVar7 = 0;
        pcVar6 = adaptor_setVariableValue_VOID_;
        break;
    case JStudio::data::UNK_0x2:
        iVar7 = 4;
        pcVar6 = adaptor_setVariableValue_IMMEDIATE_;
        break;
    case JStudio::data::UNK_0x3:
        iVar7 = 4;
        pcVar6 = adaptor_setVariableValue_TIME_;
        break;
    case JStudio::data::UNK_0x12:
        iVar7 = 4;
        pcVar6 = adaptor_setVariableValue_FVR_INDEX_;
        break;
    default:
        return;
    }
    
    JGadget::TEnumerator<const u32*> enumerator(param_2, param_2 + param_3);
    while (enumerator) {
        (*pcVar6)(this, pObject, **enumerator, param_5, iVar7);
        param_5 = (const void*)((int)param_5 + iVar7);
    }
}

/* 8026ECAC-8026ECF0       .text adaptor_setVariableValue_immediate__Q27JStudio8TAdaptorFPCQ37JStudio8TAdaptor27TSetVariableValue_immediate */
void JStudio::TAdaptor::adaptor_setVariableValue_immediate(const JStudio::TAdaptor::TSetVariableValue_immediate* param_0) {
    u32 uVar1;
    while ((uVar1 = param_0->field_0x0) != 0xffffffff) {
        adaptor_setVariableValue_immediate(uVar1, param_0->field_0x4);
        param_0++;
    }
}

/* 8026ECF0-8026ED60       .text adaptor_setVariableValue_Vec__Q27JStudio8TAdaptorFPCUlRC3Vec */
void JStudio::TAdaptor::adaptor_setVariableValue_Vec(const u32* puIndex, const Vec& param_2) {
    adaptor_referVariableValue(puIndex[0])->setValue_immediate(param_2.x);
    adaptor_referVariableValue(puIndex[1])->setValue_immediate(param_2.y);
    adaptor_referVariableValue(puIndex[2])->setValue_immediate(param_2.z);
}

/* 8026ED60-8026EDA0       .text adaptor_getVariableValue_Vec__Q27JStudio8TAdaptorCFP3VecPCUl */
void JStudio::TAdaptor::adaptor_getVariableValue_Vec(Vec* param_1, const u32* param_2) const {
    param_1->x = adaptor_getVariableValue(param_2[0])->getValue();
    param_1->y = adaptor_getVariableValue(param_2[1])->getValue();
    param_1->z = adaptor_getVariableValue(param_2[2])->getValue();
}

/* 8026EDA0-8026EE80       .text adaptor_setVariableValue_GXColor__Q27JStudio8TAdaptorFPCUlRC8_GXColor */
void JStudio::TAdaptor::adaptor_setVariableValue_GXColor(const u32* puIndex, const GXColor& param_2) {
    adaptor_referVariableValue(puIndex[0])->setValue_immediate(param_2.r);
    adaptor_referVariableValue(puIndex[1])->setValue_immediate(param_2.g);
    adaptor_referVariableValue(puIndex[2])->setValue_immediate(param_2.b);
    adaptor_referVariableValue(puIndex[3])->setValue_immediate(param_2.a);
}

/* 8026EE80-8026EFCC       .text adaptor_getVariableValue_GXColor__Q27JStudio8TAdaptorCFP8_GXColorPCUl */
void JStudio::TAdaptor::adaptor_getVariableValue_GXColor(GXColor* param_1, const u32* param_2) const {
    param_1->r = adaptor_getVariableValue(param_2[0])->getValue_uint8();
    param_1->g = adaptor_getVariableValue(param_2[1])->getValue_uint8();
    param_1->b = adaptor_getVariableValue(param_2[2])->getValue_uint8();
    param_1->a = adaptor_getVariableValue(param_2[3])->getValue_uint8();
}

/* 8026EFCC-8026F064       .text adaptor_updateVariableValue__Q27JStudio8TAdaptorFPQ27JStudio7TObjectUl */
void JStudio::TAdaptor::adaptor_updateVariableValue(JStudio::TObject* pObject, u32 param_2) {
    TControl* pControl = pObject->getControl();
    f64 dVar3 = pControl->getSecondPerFrame();
    JGadget::TEnumerator<JStudio::TVariableValue*> enumerator(pValue_, pValue_ + u);
    while (enumerator) {
        JStudio::TVariableValue* value = *enumerator;
        value->forward(param_2);
        value->update(dVar3, this);
    }
}

/* 8026F064-8026F07C       .text adaptor_setVariableValue_VOID___Q27JStudio8TAdaptorFPQ27JStudio8TAdaptorPQ27JStudio7TObjectUlPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue_VOID_(JStudio::TAdaptor* param_1, JStudio::TObject* param_2, u32 param_3, const void* param_4, u32 uSize) {
    param_1->pValue_[param_3].setValue_none();
}

/* 8026F07C-8026F0A8       .text adaptor_setVariableValue_IMMEDIATE___Q27JStudio8TAdaptorFPQ27JStudio8TAdaptorPQ27JStudio7TObjectUlPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue_IMMEDIATE_(JStudio::TAdaptor* param_1, JStudio::TObject* param_2, u32 param_3, const void* param_4, u32 param_5) {
    TVariableValue* value = &param_1->pValue_[param_3];
    value->setValue_immediate(*(f32*)param_4);
}

/* 8026F0A8-8026F0D4       .text adaptor_setVariableValue_TIME___Q27JStudio8TAdaptorFPQ27JStudio8TAdaptorPQ27JStudio7TObjectUlPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue_TIME_(JStudio::TAdaptor* param_1, JStudio::TObject* param_2, u32 param_3, const void* param_4, u32 param_5) {
    TVariableValue* value = &param_1->pValue_[param_3];
    value->setValue_time(*(f32*)param_4);
}

/* 8026F0D4-8026F144       .text adaptor_setVariableValue_FVR_NAME___Q27JStudio8TAdaptorFPQ27JStudio8TAdaptorPQ27JStudio7TObjectUlPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue_FVR_NAME_(JStudio::TAdaptor* param_1, JStudio::TObject* param_2, u32 param_3, const void* param_4, u32 param_5) {
    TVariableValue* value = &param_1->pValue_[param_3];
    value->setValue_functionValue(param_2->getControl()->getFunctionValue(param_4,param_5));
}

/* 8026F144-8026F1B0       .text adaptor_setVariableValue_FVR_INDEX___Q27JStudio8TAdaptorFPQ27JStudio8TAdaptorPQ27JStudio7TObjectUlPCvUl */
void JStudio::TAdaptor::adaptor_setVariableValue_FVR_INDEX_(JStudio::TAdaptor* param_1, JStudio::TObject* param_2, u32 param_3, const void* param_4, u32 param_5) {
    TVariableValue* value = &param_1->pValue_[param_3];
    value->setValue_functionValue(param_2->getControl()->getFunctionValue_index(*(u32*)param_4));
}

/* 8026F1B0-8026F234       .text __dt__Q27JStudio7TObjectFv */
JStudio::TObject::~TObject() {
    delete mpAdaptor;
}

/* 8026F234-8026F2A0       .text forward_value__Q27JStudio7TObjectFUl */
void JStudio::TObject::forward_value(u32 param_0) {
    TAdaptor* adaptor = getAdaptor();
    if (adaptor != NULL) {
        adaptor->adaptor_updateVariableValue(this, param_0);
        adaptor->adaptor_do_update(this, param_0);
    }
}

/* 8026F2A0-8026F2DC       .text do_begin__Q27JStudio7TObjectFv */
void JStudio::TObject::do_begin() {
    TAdaptor* adaptor = getAdaptor();
    if (adaptor != NULL) {
        adaptor->adaptor_do_begin(this);
    }
}

/* 8026F2DC-8026F318       .text do_end__Q27JStudio7TObjectFv */
void JStudio::TObject::do_end() {
    TAdaptor* adaptor = getAdaptor();
    if (adaptor != NULL) {
        adaptor->adaptor_do_end(this);
    }
}

/* 8026F318-8026F338       .text do_wait__Q27JStudio7TObjectFUl */
void JStudio::TObject::do_wait(u32 param_0) {
    forward_value(param_0);
}

/* 8026F338-8026F394       .text do_data__Q27JStudio7TObjectFPCvUlPCvUl */
void JStudio::TObject::do_data(const void* param_0, u32 param_1, const void* param_2, u32 param_3) {
    TAdaptor* adaptor = getAdaptor();
    if (adaptor != NULL) {
        adaptor->adaptor_do_data(this, param_0, param_1, param_2, param_3);
    }
}

/* 8026F394-8026F3E0       .text __ct__Q27JStudio7TObjectFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio8TAdaptor */
JStudio::TObject::TObject(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor* param_1) : stb::TObject(param_0), mpAdaptor(param_1) {}

/* 8026F3E0-8026F440       .text __dt__Q27JStudio14TAdaptor_actorFv */
JStudio::TAdaptor_actor::~TAdaptor_actor() {}

/* 8026F440-8026F47C       .text __ct__Q27JStudio13TObject_actorFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio14TAdaptor_actor */
JStudio::TObject_actor::TObject_actor(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_actor* param_1) : TObject(param_0, param_1) {}

/* 8026F47C-8026F7B0       .text do_paragraph__Q27JStudio13TObject_actorFUlPCvUl */
void JStudio::TObject_actor::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 8026F7B0-8026F810       .text __dt__Q27JStudio21TAdaptor_ambientLightFv */
JStudio::TAdaptor_ambientLight::~TAdaptor_ambientLight() {}

/* 8026F810-8026F84C       .text __ct__Q27JStudio20TObject_ambientLightFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio21TAdaptor_ambientLight */
JStudio::TObject_ambientLight::TObject_ambientLight(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_ambientLight* param_1) : TObject(param_0, param_1) {}

/* 8026F84C-8026F928       .text do_paragraph__Q27JStudio20TObject_ambientLightFUlPCvUl */
void JStudio::TObject_ambientLight::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 8026F928-8026F988       .text __dt__Q27JStudio15TAdaptor_cameraFv */
JStudio::TAdaptor_camera::~TAdaptor_camera() {}

/* 8026F988-8026F9C4       .text __ct__Q27JStudio14TObject_cameraFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio15TAdaptor_camera */
JStudio::TObject_camera::TObject_camera(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_camera* param_1) : TObject(param_0, param_1) {}

/* 8026F9C4-8026FBFC       .text do_paragraph__Q27JStudio14TObject_cameraFUlPCvUl */
void JStudio::TObject_camera::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 8026FBFC-8026FC5C       .text __dt__Q27JStudio12TAdaptor_fogFv */
JStudio::TAdaptor_fog::~TAdaptor_fog() {}

/* 8026FC5C-8026FC98       .text __ct__Q27JStudio11TObject_fogFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio12TAdaptor_fog */
JStudio::TObject_fog::TObject_fog(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_fog* param_1) : TObject(param_0, param_1) {}

/* 8026FC98-8026FD80       .text do_paragraph__Q27JStudio11TObject_fogFUlPCvUl */
void JStudio::TObject_fog::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 8026FD80-8026FDE0       .text __dt__Q27JStudio14TAdaptor_lightFv */
JStudio::TAdaptor_light::~TAdaptor_light() {}

/* 8026FDE0-8026FE1C       .text __ct__Q27JStudio13TObject_lightFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio14TAdaptor_light */
JStudio::TObject_light::TObject_light(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_light* param_1) : TObject(param_0, param_1) {}

/* 8026FE1C-80270058       .text do_paragraph__Q27JStudio13TObject_lightFUlPCvUl */
void JStudio::TObject_light::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 80270058-802700B8       .text __dt__Q27JStudio16TAdaptor_messageFv */
JStudio::TAdaptor_message::~TAdaptor_message() {}

/* 802700B8-802700F4       .text __ct__Q27JStudio15TObject_messageFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio16TAdaptor_message */
JStudio::TObject_message::TObject_message(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_message* param_1) : TObject(param_0, param_1) {}

/* 802700F4-80270184       .text do_paragraph__Q27JStudio15TObject_messageFUlPCvUl */
void JStudio::TObject_message::do_paragraph(u32 param_1, const void* param_2, u32 param_3) {
    /* Nonmatching */
    TAdaptor* adaptor = getAdaptor();
    if (adaptor != NULL) {
        u32 uVar1 = (param_1 >> 5);
        param_1 &= 0x1f;
        paragraphFunc pmfn_ = NULL;
        switch (uVar1) {
        case 0x42:
            pmfn_ = &TObject::do_paragraph;
            break;
        default:
            return;
        }
        (((TObject*)adaptor)->*pmfn_)(param_1, param_2, param_3);
    }
}

/* 80270184-802701E4       .text __dt__Q27JStudio17TAdaptor_particleFv */
JStudio::TAdaptor_particle::~TAdaptor_particle() {}

/* 802701E4-80270220       .text __ct__Q27JStudio16TObject_particleFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio17TAdaptor_particle */
JStudio::TObject_particle::TObject_particle(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_particle* param_1) : TObject(param_0, param_1) {}

/* 80270220-802704E4       .text do_paragraph__Q27JStudio16TObject_particleFUlPCvUl */
void JStudio::TObject_particle::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 802704E4-80270544       .text __dt__Q27JStudio14TAdaptor_soundFv */
JStudio::TAdaptor_sound::~TAdaptor_sound() {}

/* 80270544-80270580       .text __ct__Q27JStudio13TObject_soundFRCQ47JStudio3stb4data20TParse_TBlock_objectPQ27JStudio14TAdaptor_sound */
JStudio::TObject_sound::TObject_sound(const JStudio::stb::data::TParse_TBlock_object& param_0, JStudio::TAdaptor_sound* param_1) : TObject(param_0, param_1) {}

/* 80270580-80270778       .text do_paragraph__Q27JStudio13TObject_soundFUlPCvUl */
void JStudio::TObject_sound::do_paragraph(u32, const void*, u32) {
    /* Nonmatching */
}

/* 80270778-802707D8       .text __dt__Q27JStudio13TObject_soundFv */
JStudio::TObject_sound::~TObject_sound() {}

/* 802707D8-80270838       .text __dt__Q27JStudio16TObject_particleFv */
JStudio::TObject_particle::~TObject_particle() {}

/* 80270838-80270898       .text __dt__Q27JStudio15TObject_messageFv */
JStudio::TObject_message::~TObject_message() {}

/* 80270898-802708F8       .text __dt__Q27JStudio13TObject_lightFv */
JStudio::TObject_light::~TObject_light() {}

/* 802708F8-80270958       .text __dt__Q27JStudio11TObject_fogFv */
JStudio::TObject_fog::~TObject_fog() {}

/* 80270958-802709B8       .text __dt__Q27JStudio14TObject_cameraFv */
JStudio::TObject_camera::~TObject_camera() {}

/* 802709B8-80270A18       .text __dt__Q27JStudio20TObject_ambientLightFv */
JStudio::TObject_ambientLight::~TObject_ambientLight() {}

/* 80270A18-80270A78       .text __dt__Q27JStudio13TObject_actorFv */
JStudio::TObject_actor::~TObject_actor() {}
