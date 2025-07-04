//
// Generated by dtk
// Translation Unit: d_demo.cpp
//

#include "d/d_demo.h"
#include "f_op/f_op_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_mesg.h"
#include "m_Do/m_Do_printf.h"

/* 800692C4-80069330       .text __ct__13dDemo_actor_cFv */
dDemo_actor_c::dDemo_actor_c() {
    mFlags = 0;
    mTrans.setall(0.0f);
    mScale.setall(1.0f);
    mRotate.setall(0);
    mModel = NULL;
    mAnmFrameMax = FLOAT_MAX;
    mTexAnimationFrameMax = FLOAT_MAX;
}

/* 80069330-800693C0       .text __dt__13dDemo_actor_cFv */
dDemo_actor_c::~dDemo_actor_c() {
    fopAc_ac_c* actor = getActor();
    if (actor) {
        actor->demoActorID = 0;
    }
    mActorId = fpcM_ERROR_PROCESS_ID_e;
    mOldAnmId = -1;
    mBtpId = -1;
    mBtkId = -1;
    mBrkId = -1;
}

/* 800693C0-800693F4       .text getActor__13dDemo_actor_cFv */
fopAc_ac_c* dDemo_actor_c::getActor() {
    return fopAcM_SearchByID(mActorId);
}

/* 800693F4-80069434       .text setActor__13dDemo_actor_cFP10fopAc_ac_c */
void dDemo_actor_c::setActor(fopAc_ac_c* ac) {
    if (ac == NULL)
        mActorId = fpcM_ERROR_PROCESS_ID_e;
    else
        mActorId = fopAcM_GetID(ac);
    mOldAnmId = -1;
    mBtpId = -1;
    mBtkId = -1;
    mBrkId = -1;
}

/* 80069434-80069550       .text getP_BtpData__13dDemo_actor_cFPCc */
void* dDemo_actor_c::getP_BtpData(const char* name) {
    /* Nonmatching */
    if (!checkEnable(ENABLE_UNK_e))
        return NULL;
}

/* 80069550-800695E8       .text getP_BrkData__13dDemo_actor_cFPCc */
void* dDemo_actor_c::getP_BrkData(const char*) {
    /* Nonmatching */
}

/* 800695E8-8006969C       .text getP_BtkData__13dDemo_actor_cFPCc */
void* dDemo_actor_c::getP_BtkData(const char*) {
    /* Nonmatching */
}

/* 8006969C-80069838       .text getPrm_Morf__13dDemo_actor_cFv */
f32 dDemo_actor_c::getPrm_Morf() {
    if (checkEnable(ENABLE_ANM_FRAME_e)) {
        return mAnmTransition;
    }

    if (!checkEnable(ENABLE_UNK_e)) {
        return 0.0f;
    }

    dDemo_prm_data* prm = mPrm.mData;

    switch (mPrm.mId) {
    case ID_UNK_1:
        if (field_0x54 < 4) {
            return 0.0f;
        }
        return prm->field_0x4;
    case ID_UNK_2:
        if (field_0x54 < 7) {
            return 0.0f;
        }
        return prm->field_0x7;
    case ID_UNK_4:
        if (field_0x54 < 6) {
            return 0.0f;
        }
        return prm->field_0x6;
    case ID_UNK_5:
        if (field_0x54 < 0xB) {
            return 0.0f;
        }
        return prm->field_0xb;
    case ID_UNK_6:
        if (field_0x54 < 0xF) {
            return 0.0f;
        }
        return prm->field_0xf;
    default:
        return 0.0f;
    }
}

/* 80069838-800698C0       .text dDemo_getJaiPointer__FPCcUliPUs */
void* dDemo_getJaiPointer(const char* a_name, u32 bck, int num, u16* tbl) {
    if (num <= 0 || tbl == NULL)
        return NULL;

    int i;
    int var_r31;
    for (i = var_r31 = 0; i < num; i++, var_r31 += 2)
        if (tbl[var_r31 + 0] == (bck & 0xFFFF))
            return dComIfG_getObjectIDRes(a_name, tbl[var_r31 + 1]);

    return NULL;
}

#if VERSION == VERSION_DEMO
BOOL dDemo_setDemoData(fopAc_ac_c* i_actor, u8 i_flags, mDoExt_McaMorf* i_morf, const char* i_arcName,
                       int p5, u16* p6)
#else
/* 800698C0-80069BC0       .text dDemo_setDemoData__FP10fopAc_ac_cUcP14mDoExt_McaMorfPCciPUsUlSc */
BOOL dDemo_setDemoData(fopAc_ac_c* i_actor, u8 i_flags, mDoExt_McaMorf* i_morf, const char* i_arcName,
                       int p5, u16* p6, u32 mtrlSndId, s8 i_reverb)
#endif
{
    dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(i_actor->demoActorID);
    if (demo_actor == NULL)
        return FALSE;

    u8 flags = demo_actor->checkEnable(i_flags);
    if (flags & dDemo_actor_c::ENABLE_TRANS_e) {
        i_actor->old.pos = i_actor->current.pos = *demo_actor->getTrans();
    }
    if (flags & dDemo_actor_c::ENABLE_ROTATE_e) {
        i_actor->current.angle = i_actor->shape_angle = *demo_actor->getRatate();
    }
    if (flags & dDemo_actor_c::ENABLE_SCALE_e) {
        i_actor->scale = *demo_actor->getScale();
    }

    if (i_morf == NULL)
        return TRUE;

    demo_actor->setModel(i_morf->getModel());

    if (flags & dDemo_actor_c::ENABLE_ANM_e) {
        int anmID = demo_actor->getAnmId();
        if (anmID != demo_actor->getOldAnmId()) {
            const char* a_name;
            if (anmID & 0x10000) {
                a_name = dStage_roomControl_c::getDemoArcName();
                JUT_ASSERT(397, a_name != NULL);
            } else {
                a_name = i_arcName;
            }

            demo_actor->setOldAnmId(anmID);

            J3DAnmTransform* i_key = (J3DAnmTransform*)dComIfG_getObjectIDRes(a_name, anmID & 0xFFFF);
            JUT_ASSERT(408, i_key != NULL);

            void* i_sound = dDemo_getJaiPointer(a_name, anmID & 0xFFFF, p5, p6);
            f32 f1 = demo_actor->getPrm_Morf();
            i_morf->setAnm(i_key, -1, f1, 1.0f, 0.0f, -1.0f, i_sound);
            demo_actor->setAnmFrameMax(i_morf->getEndFrame());
        }
    }

    if (flags & dDemo_actor_c::ENABLE_ANM_FRAME_e) {
        f32 anm_frame = demo_actor->getAnmFrame();
        if (anm_frame > 1.0f) {
            anm_frame -= 1.0f;
            i_morf->setFrame(anm_frame);
#if VERSION == VERSION_DEMO
            i_morf->play(&i_actor->current.pos, 0, 0);
#else
            i_morf->play(&i_actor->current.pos, mtrlSndId, i_reverb);
#endif
        } else {
            i_morf->setFrame(anm_frame);
        }
    } else {
#if VERSION == VERSION_DEMO
        i_morf->play(&i_actor->current.pos, 0, 0);
#else
        i_morf->play(&i_actor->current.pos, mtrlSndId, i_reverb);
#endif
    }

    return TRUE;
}

/* 80069BC0-80069BDC       .text JSGSetData__13dDemo_actor_cFUlPCvUl */
void dDemo_actor_c::JSGSetData(u32 p0, const void* p1, u32 p2) {
    mPrm.mId = p0;
    mPrm.mData = (dDemo_prm_data*)p1;
    field_0x54 = p2;
    onEnable(ENABLE_UNK_e);
}

/* 80069BDC-80069C04       .text JSGSetTranslation__13dDemo_actor_cFRC3Vec */
void dDemo_actor_c::JSGSetTranslation(const Vec& v) {
    mTrans = v;
    onEnable(ENABLE_TRANS_e);
}

/* 80069C04-80069C2C       .text JSGSetScaling__13dDemo_actor_cFRC3Vec */
void dDemo_actor_c::JSGSetScaling(const Vec& v) {
    mScale = v;
    onEnable(ENABLE_SCALE_e);
}

/* 80069C2C-80069C90       .text JSGSetRotation__13dDemo_actor_cFRC3Vec */
void dDemo_actor_c::JSGSetRotation(const Vec& v) {
    mRotate.x = cM_deg2s(v.x);
    mRotate.y = cM_deg2s(v.y);
    mRotate.z = cM_deg2s(v.z);
    onEnable(ENABLE_ROTATE_e);
}

/* 80069C90-80069CA4       .text JSGSetShape__13dDemo_actor_cFUl */
void dDemo_actor_c::JSGSetShape(u32 id) {
    mShapeId = id;
    onEnable(ENABLE_SHAPE_e);
}

/* 80069CA4-80069CC0       .text JSGSetAnimation__13dDemo_actor_cFUl */
void dDemo_actor_c::JSGSetAnimation(u32 no) {
    mAnmId = no;
    mAnmFrameMax = FLOAT_MAX;
    onEnable(ENABLE_ANM_e);
}

/* 80069CC0-80069CD4       .text JSGSetAnimationFrame__13dDemo_actor_cFf */
void dDemo_actor_c::JSGSetAnimationFrame(f32 v) {
    mAnmFrame = v;
    onEnable(ENABLE_ANM_FRAME_e);
}

/* 80069CD4-80069CE8       .text JSGSetAnimationTransition__13dDemo_actor_cFf */
void dDemo_actor_c::JSGSetAnimationTransition(f32 v) {
    mAnmTransition = v;
    onEnable(ENABLE_ANM_FRAME_e);
}

/* 80069CE8-80069CFC       .text JSGSetTextureAnimation__13dDemo_actor_cFUl */
void dDemo_actor_c::JSGSetTextureAnimation(u32 no) {
    mTexAnimation = no;
    onEnable(ENABLE_TEX_ANM);
}

/* 80069CFC-80069D10       .text JSGSetTextureAnimationFrame__13dDemo_actor_cFf */
void dDemo_actor_c::JSGSetTextureAnimationFrame(f32 v) {
    mTexAnimationFrame = v;
    onEnable(ENABLE_TEX_ANM_FRAME_e);
}

/* 80069D10-80069D44       .text getView__Fv */
camera_class* getView() {
    if (dComIfGp_getWindowNum() == 0)
        return NULL;

    return dComIfGp_getCamera(dComIfGp_getWindow(0)->getCameraID());
}

/* 80069D44-80069D78       .text JSGGetProjectionNear__14dDemo_camera_cCFv */
f32 dDemo_camera_c::JSGGetProjectionNear() const {
    camera_class* view = getView();
    if (view == NULL)
        return 0.0f;
    return view->mNear;
}

/* 80069D78-80069D8C       .text JSGSetProjectionNear__14dDemo_camera_cFf */
void dDemo_camera_c::JSGSetProjectionNear(f32 v) {
    mProjNear = v;
    onEnable(ENABLE_PROJ_NEAR_e);
}

/* 80069D8C-80069DC0       .text JSGGetProjectionFar__14dDemo_camera_cCFv */
f32 dDemo_camera_c::JSGGetProjectionFar() const {
    camera_class* view = getView();
    if (view == NULL)
        return 1.0f;
    return view->mFar;
}

/* 80069DC0-80069DD4       .text JSGSetProjectionFar__14dDemo_camera_cFf */
void dDemo_camera_c::JSGSetProjectionFar(f32 v) {
    mProjFar = v;
    onEnable(ENABLE_PROJ_FAR_e);
}

/* 80069DD4-80069E08       .text JSGGetProjectionFovy__14dDemo_camera_cCFv */
f32 dDemo_camera_c::JSGGetProjectionFovy() const {
    camera_class* view = getView();
    if (view == NULL)
        return 60.0f;
    return view->mFovy;
}

/* 80069E08-80069E1C       .text JSGSetProjectionFovy__14dDemo_camera_cFf */
void dDemo_camera_c::JSGSetProjectionFovy(f32 v) {
    mFovy = v;
    onEnable(ENABLE_PROJ_FOVY_e);
}

/* 80069E1C-80069E50       .text JSGGetProjectionAspect__14dDemo_camera_cCFv */
f32 dDemo_camera_c::JSGGetProjectionAspect() const {
    camera_class* view = getView();
    if (view == NULL)
        return (4.0f/3.0f);
    return view->mAspect;
}

/* 80069E50-80069E64       .text JSGSetProjectionAspect__14dDemo_camera_cFf */
void dDemo_camera_c::JSGSetProjectionAspect(f32 v) {
    mAspect = v;
    onEnable(ENABLE_PROJ_ASPECT_e);
}

/* 80069E64-80069EC0       .text JSGGetViewPosition__14dDemo_camera_cCFP3Vec */
void dDemo_camera_c::JSGGetViewPosition(Vec* dst) const {
    camera_class* view = getView();
    if (view == NULL) {
        dst->x = 0.0f;
        dst->y = 0.0f;
        dst->z = 0.0f;
    }
    *dst = view->mLookat.mEye;
}

/* 80069EC0-80069EE8       .text JSGSetViewPosition__14dDemo_camera_cFRC3Vec */
void dDemo_camera_c::JSGSetViewPosition(const Vec& v) {
    mViewPosition = v;
    onEnable(ENABLE_VIEW_POS_e);
}

/* 80069EE8-80069F48       .text JSGGetViewUpVector__14dDemo_camera_cCFP3Vec */
void dDemo_camera_c::JSGGetViewUpVector(Vec* dst) const {
    camera_class* view = getView();
    if (view == NULL) {
        dst->x = 0.0f;
        dst->y = 1.0f;
        dst->z = 0.0f;
    }
    *dst = view->mLookat.mUp;
}

/* 80069F48-80069F70       .text JSGSetViewUpVector__14dDemo_camera_cFRC3Vec */
void dDemo_camera_c::JSGSetViewUpVector(const Vec& v) {
    mUpVector = v;
    onEnable(ENABLE_VIEW_UP_VEC_e);
}

/* 80069F70-80069FD0       .text JSGGetViewTargetPosition__14dDemo_camera_cCFP3Vec */
void dDemo_camera_c::JSGGetViewTargetPosition(Vec* dst) const {
    camera_class* view = getView();
    if (view == NULL) {
        dst->x = 0.0f;
        dst->y = 0.0f;
        dst->z = 1.0f;
    }
    *dst = view->mLookat.mCenter;
}

/* 80069FD0-80069FF8       .text JSGSetViewTargetPosition__14dDemo_camera_cFRC3Vec */
void dDemo_camera_c::JSGSetViewTargetPosition(const Vec& v) {
    mTargetPosition = v;
    onEnable(ENABLE_VIEW_TARG_POS_e);
}

/* 80069FF8-8006A050       .text JSGGetViewRoll__14dDemo_camera_cCFv */
f32 dDemo_camera_c::JSGGetViewRoll() const {
    camera_class* view = getView();
    if (view == NULL)
        return 0.0f;
    return cM_sht2d(view->mBank);
}

/* 8006A050-8006A064       .text JSGSetViewRoll__14dDemo_camera_cFf */
void dDemo_camera_c::JSGSetViewRoll(f32 v) {
    mRoll = v;
    onEnable(ENABLE_VIEW_ROLL_e);
}

/* 8006A064-8006A094       .text JSGSetColor__15dDemo_ambient_cF8_GXColor */
void dDemo_ambient_c::JSGSetColor(GXColor color) {
    mColor = color;
    onEnable(ENABLE_COLOR_e);
}

/* 8006A094-8006A0A8       .text JSGSetLightType__13dDemo_light_cFQ26JStage7TELight */
void dDemo_light_c::JSGSetLightType(JStage::TELight type) {
    mLightType = type;
    onEnable(ENABLE_LIGHT_TYPE_e);
}

/* 8006A0A8-8006A0D0       .text JSGSetPosition__13dDemo_light_cFRC3Vec */
void dDemo_light_c::JSGSetPosition(const Vec& v) {
    mPosition = v;
    onEnable(ENABLE_POSITION_e);
}

/* 8006A0D0-8006A100       .text JSGSetColor__13dDemo_light_cF8_GXColor */
void dDemo_light_c::JSGSetColor(GXColor v) {
    mColor = v;
    onEnable(ENABLE_COLOR_e);
}

/* 8006A100-8006A11C       .text JSGSetDistanceAttenuation__13dDemo_light_cFff13_GXDistAttnFn */
void dDemo_light_c::JSGSetDistanceAttenuation(f32 ref0, f32 ref1, GXDistAttnFn fn) {
    mDistAttn0 = ref0;
    mDistAttn1 = ref1;
    mAttnFn = fn;
    onEnable(ENABLE_DIST_ATTEN_e);
}

/* 8006A11C-8006A134       .text JSGSetAngleAttenuation__13dDemo_light_cFf9_GXSpotFn */
void dDemo_light_c::JSGSetAngleAttenuation(f32 ref, GXSpotFn fn) {
    mAngleAttn = ref;
    mSpotFn = fn;
    onEnable(ENABLE_ANGLE_ATTEN_e);
}

/* 8006A134-8006A15C       .text JSGSetDirection__13dDemo_light_cFRC3Vec */
void dDemo_light_c::JSGSetDirection(const Vec& v) {
    mDirection = v;
    onEnable(ENABLE_DIRECTION_e);
}

/* 8006A15C-8006A170       .text JSGSetFogFunction__11dDemo_fog_cF10_GXFogType */
void dDemo_fog_c::JSGSetFogFunction(GXFogType type) {
    mFogType = type;
    onEnable(ENABLE_FOG_FN_e);
}

/* 8006A170-8006A184       .text JSGSetStartZ__11dDemo_fog_cFf */
void dDemo_fog_c::JSGSetStartZ(f32 v) {
    mStartZ = v;
    onEnable(ENABLE_START_Z_e);
}

/* 8006A184-8006A198       .text JSGSetEndZ__11dDemo_fog_cFf */
void dDemo_fog_c::JSGSetEndZ(f32 v) {
    mEndZ = v;
    onEnable(ENABLE_END_Z_e);
}

/* 8006A198-8006A1C8       .text JSGSetColor__11dDemo_fog_cF8_GXColor */
void dDemo_fog_c::JSGSetColor(GXColor color) {
    mColor = color;
    onEnable(ENABLE_COLOR_e);
}

/* 8006A1C8-8006A1E4       .text __ct__14dDemo_object_cFv */
dDemo_object_c::dDemo_object_c() {
    mNumActor = 0;
    mNumLight = 0;
    mpCamera = NULL;
    mpAmbient = NULL;
    mpFog = NULL;
}

/* 8006A1E4-8006A234       .text __dt__14dDemo_object_cFv */
dDemo_object_c::~dDemo_object_c() {
    remove();
}

/* 8006A234-8006A2F8       .text appendActor__14dDemo_object_cFP10fopAc_ac_c */
dDemo_actor_c* dDemo_object_c::appendActor(fopAc_ac_c* ac) {
    dDemo_actor_c* demoActor = dComIfGp_demo_getActor(ac->demoActorID);
    if (demoActor != NULL)
        return demoActor;

    if (mNumActor >= ARRAY_SIZE(mpActors))
        return NULL;

    demoActor = new dDemo_actor_c();
    if (demoActor == NULL)
        return NULL;

    mpActors[mNumActor++] = demoActor;
    demoActor->setActor(ac);
    ac->demoActorID = mNumActor;
    return demoActor;
}

/* 8006A2F8-8006A31C       .text getActor__14dDemo_object_cFUc */
dDemo_actor_c* dDemo_object_c::getActor(u8 no) {
    if (no == 0 || no > ARRAY_SIZE(mpActors))
        return NULL;
    return mpActors[no - 1];
}

/* 8006A31C-8006A398       .text createCamera__14dDemo_object_cFv */
dDemo_camera_c* dDemo_object_c::createCamera() {
    if (mpCamera != NULL)
        return mpCamera;

    mpCamera = new dDemo_camera_c();
    return mpCamera;
}

/* 8006A398-8006A3AC       .text getActiveCamera__14dDemo_object_cFv */
dDemo_camera_c* dDemo_object_c::getActiveCamera() {
    if (getCamera() != NULL)
        return getCamera();
    return NULL;
}

/* 8006A3AC-8006A428       .text createAmbient__14dDemo_object_cFv */
dDemo_ambient_c* dDemo_object_c::createAmbient() {
    if (mpAmbient != NULL)
        return mpAmbient;

    mpAmbient = new dDemo_ambient_c();
    return mpAmbient;
}

/* 8006A428-8006A4C8       .text appendLight__14dDemo_object_cFv */
dDemo_light_c* dDemo_object_c::appendLight() {
    if (mNumLight >= ARRAY_SIZE(mpLight))
        return NULL;

    dDemo_light_c* demoLight = new dDemo_light_c();
    if (demoLight == NULL)
        return NULL;

    mpLight[mNumLight++] = demoLight;
    return demoLight;
}

/* 8006A4C8-8006A544       .text createFog__14dDemo_object_cFv */
dDemo_fog_c* dDemo_object_c::createFog() {
    if (mpFog != NULL)
        return mpFog;

    mpFog = new dDemo_fog_c();
    return mpFog;
}

/* 8006A544-8006A678       .text remove__14dDemo_object_cFv */
void dDemo_object_c::remove() {
    while (mNumActor)
        delete mpActors[--mNumActor];

    if (mpCamera != NULL) {
        delete mpCamera;
        mpCamera = NULL;
    }

    if (mpAmbient != NULL) {
        delete mpAmbient;
        mpAmbient = NULL;
    }

    while (mNumLight)
        delete mpLight[--mNumLight];

    if (mpFog != NULL) {
        delete mpFog;
        mpFog = NULL;
    }
}

/* 8006A7F8-8006A92C       .text JSGFindObject__14dDemo_system_cCFPCcQ26JStage8TEObject */
void* dDemo_system_c::JSGFindObject(const char* name, JStage::TEObject type) const {
    if (mObject == NULL)
        return NULL;

    if (type == JStage::TOBJ_ACTOR || type == JStage::TOBJ_ACTOR_UNK) {
        fopAc_ac_c* ac = fopAcM_searchFromName((char*)name, 0, 0);
        if (ac == NULL) {
            if (type == JStage::TOBJ_ACTOR && strncmp(name, "d_act", sizeof("d_act")-1) == 0) {
                ac = (fopAc_ac_c*)fopAcM_fastCreate((char*)name, 0);
                if (ac == NULL)
                    return NULL;
                fopAcM_setStageLayer(ac);
            } else {
                return NULL;
            }
        }
        return mObject->appendActor(ac);
    } else if (type == JStage::TOBJ_CAMERA) {
        return mObject->createCamera();
    } else if (type == JStage::TOBJ_AMBIENT) {
        return mObject->createAmbient();
    } else if (type == JStage::TOBJ_LIGHT) {
        return mObject->appendLight();
    } else if (type == JStage::TOBJ_FOG) {
        return mObject->createFog();
    } else {
        return NULL;
    }
}

/* 8006A92C-8006ADA0       .text __ct__15dDemo_manager_cFv */
dDemo_manager_c::dDemo_manager_c() {
    mCurFile = NULL;
    mFrame = 0;
    
    mMesgControl = new dMesg_tControl();
    JUT_ASSERT(0x5b7, mMesgControl != NULL);
    mSystem = new dDemo_system_c();
    JUT_ASSERT(0x5ba, mSystem != NULL);
    mControl = new JStudio::TControl();
    JUT_ASSERT(0x5bc, mControl != NULL);
    mStage = new JStudio_JStage::TCreateObject(mSystem);
    JUT_ASSERT(0x5be, mStage != NULL);
    mAudio = new JStudio_JAudio::TCreateObject(mDoAud_zelAudio_c::getInterface());
    JUT_ASSERT(0x5c0, mAudio != NULL);
    mParticle = new JStudio_JParticle::TCreateObject(dPa_control_c::getEmitterManager(), mSystem);
    JUT_ASSERT(0x5c3, mParticle != NULL);
    mMessage = new JStudio_JMessage::TCreateObject(mMesgControl);
    JUT_ASSERT(0x5c6, mMessage != NULL);
    mFactory = new JStudio::TFactory();
    JUT_ASSERT(0x5c9, mFactory != NULL);
    
    // This gets compiled to a double literal, but the lack of precision indicates it was written as a float literal.
    mControl->mSecondPerFrame = 1/30.0f;
    mControl->setFactory(mFactory);
    mFactory->appendCreateObject(mStage);
    mFactory->appendCreateObject(mAudio);
    mFactory->appendCreateObject(mParticle);
    mSystem->setObject(&mDemoObj);
    mFactory->appendCreateObject(mMessage);
    mMode = 0;
}

/* 8006ADA0-8006AEFC       .text __dt__15dDemo_manager_cFv */
dDemo_manager_c::~dDemo_manager_c() {
    remove();
    delete mFactory;
    delete mMessage;
    delete mParticle;
    delete mAudio;
    delete mStage;
    delete mControl;
    delete mSystem;
    delete mMesgControl;
}

/* 8006AF5C-8006AFBC       .text __dt__14dDemo_system_cFv */
dDemo_system_c::~dDemo_system_c() {}

/* 8006AFBC-8006B0D4       .text create__15dDemo_manager_cFPCUcP4cXyzf */
bool dDemo_manager_c::create(const u8* r29, cXyz* r30, f32 f31) {
    JStudio::TParse sp0C(mControl);
    const void* sp08 = r29;
    if (!sp0C.parse_next(&sp08, 0)) {
        // "Demo data loading error!!\n"
        OSReport_Error("デモデータ読み込みエラー！！\n");
        return false;
    }
    mControl->forward(0);
    if (r30 == NULL) {
        mControl->transform_enable(false);
    } else {
        mControl->transform_enable(true);
        mControl->transform_setOrigin(*r30, f31);
    }
    mFrame = 0;
    mFrameNoMsg = 0;
    mCurFile = (char*)r29;
    mMode = 1;
    return true;
}

static void dummy() {
    // "Demo data reloading error!!\n"
    OSReport_Error("デモデータ再読み込みエラー！！\n");
}

/* 8006B0D4-8006B12C       .text remove__15dDemo_manager_cFv */
void dDemo_manager_c::remove() {
    mControl->destroyObject_all();
    mDemoObj.remove();
    mCurFile = NULL;
    mMode = 0;
}

/* 8006B12C-8006B1B4       .text update__15dDemo_manager_cFv */
bool dDemo_manager_c::update() {
    if (mCurFile == NULL) {
        return false;
    }
    if (mControl->forward(1)) {
        mFrame++;
        if (!mControl->isSuspended()) {
            mFrameNoMsg++;
        }
    } else {
        mMode = 2;
    }
    return true;
}
