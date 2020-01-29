#ifndef boxcar_ref_h
#define boxcar_ref_h

typedef enum eRefType {
    REF_SEMVER,
    REF_NAME,
} RefType;

typedef char* Ref;

#endif