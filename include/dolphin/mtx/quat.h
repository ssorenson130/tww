#ifndef QUAT_H
#define QUAT_H

#include "dolphin/mtx/vec.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

void C_QUATMultiply(const Quaternion* a, const Quaternion* b, Quaternion* ab);
void PSQUATMultiply(const Quaternion* a, const Quaternion* b, Quaternion* ab);
void C_QUATNormalize(const Quaternion* src, Quaternion* unit);
void PSQUATNormalize(const Quaternion* src, Quaternion* unit);
void C_QUATRotAxisRad(Quaternion* q, const Vec* axis, f32 rad);
void C_QUATSlerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t);

/* When compiling in debug mode, use C implementations */
#if defined(DEBUG) || !defined(__MWERKS__)
#define QUATMultiply C_QUATMultiply
#define QUATNormalize C_QUATNormalize
#else
#define QUATMultiply PSQUATMultiply
#define QUATNormalize PSQUATNormalize
#endif

#ifdef __cplusplus
};
#endif

#endif /* QUAT_H */
