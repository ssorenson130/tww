#ifndef D_A_OBJ_HAMI4_H
#define D_A_OBJ_HAMI4_H

#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"

class daObjHami4_c : public fopAc_ac_c {
public:

    enum Prm_e {
        PRM_SWITCH_W = 0x08,
        PRM_SWITCH_S = 0x00,

        PRM_TYPE_W = 0x01,
        PRM_TYPE_S = 0x10,
    };


    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    int prm_get_swSave() const {return daObj::PrmAbstract(this, PRM_SWITCH_W, PRM_SWITCH_S);}

    void CreateHeap();
    void CreateInit();
    void set_mtx();
    void daObjHami4_close_stop();
    void daObjHami4_open_demo_wait();
    void daObjHami4_open_demo();
    void daObjHami4_open_stop();

public:
    /* Place member variables here */
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel * mpModels[4];
    /* 0x2A8 */ dBgW* mdBgW[4];
    /* 0x2B8 */ Mtx field_0x2B8[4];
    /* 0x378 */ int field_0x378;
    /* 0x37C */ f32 field_0x37C;
};  // Size: 0x380

#endif /* D_A_OBJ_HAMI4_H */
