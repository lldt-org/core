//
// Created by User on 1/3/2021.
//

#ifndef LLDT_CORE_SERVICELOADER_H
#define LLDT_CORE_SERVICELOADER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ProgrammingLanguage {
    ProgrammingLanguage_C,
    ProgrammingLanguage_CPP
} ProgrammingLanguage;

struct PlatformServices_;

/// Structure to create plugin
typedef struct ObjectParams {
    const char* objectType;
    const struct PlatformServices_ * platformServices;
} ObjectParams;

/// To Constraint only a specific api version is wanted
typedef struct APIVersion {
    uint8_t major;
    uint8_t minor;
} APIVersion;

/// Create instance of service itself, implement by service;
typedef void * (*CreateFunc)(ObjectParams *);
/// Destroy instance of service itself, implement by service;
typedef uint8_t (*DestroyFunc)(void *);

/**
 * \param APIVersion is an optional param. When it's passed, it's service
 * responsibility to detect and throw error for user
 */
typedef struct RegisterParams
{
    APIVersion version;
    CreateFunc createFunc;
    DestroyFunc destroyFunc;
    ProgrammingLanguage programmingLanguage;
} RegisterParams;

/// Register a service, implement by service user
typedef uint8_t (*RegisterFunc)(const uint8_t * nodeType, RegisterParams);
///
typedef uint8_t (*InvokeServiceFunc)(const uint8_t * serviceName, void * serviceParams);

/**
 * Struct that aggregates all the services service user provide to service
 */
typedef struct PlatformServices
{
    APIVersion version;
    RegisterFunc  registerObject;
    InvokeServiceFunc invokeService;
} PlatformServices;

/// Exit function implement by service
typedef uint8_t (*ExitFunc)();

/// Init function implement by service
typedef ExitFunc (*InitFunc)(const PlatformServices *);

#ifndef SERVICE_API
#ifdef WIN32
#define SERVICE_API __declspec(dllimport)
#else
#define SERVICE_API
#endif
#endif

extern
#ifdef __cplusplus
"C"
#endif

/**
 * The PF_initPlugin is the actual signature of the plugin initialization function of
 * dynamic plugins (plugins deployed in dynamically linked libraries/shared libraries).
 * It is exported by name from dynamic plugins, so the plugin manager will be able to
 * call it when loading the plugin. It accepts a pointer to a PF_PlatformServices struct,
 * so all the services are immediately available upon initialization (this is the right
 * time to register objects) and it returns a pointer to an exit function.
 * @param params
 * @return
 */
SERVICE_API ExitFunc initPlugin(const PlatformServices * params);

#ifdef  __cplusplus
}
#endif

#endif //LLDT_CORE_SERVICELOADER_H


#ifndef C_OBJECT_MODEL
#define C_OBJECT_MODEL

// max string length of string fields
#define MAX_STR 64
typedef struct C_ActorInfo_
{
    uint32_t id;
    uint8_t  name[MAX_STR];
    uint32_t location_x;
    uint32_t location_y;
    uint32_t health;
    uint32_t attack;
    uint32_t defense;
    uint32_t damage;
    uint32_t movement;
} C_ActorInfo;

typedef struct C_ActorInfoIteratorHandle_ { char c; } * C_ActorInfoIteratorHandle;
typedef struct C_ActorInfoIterator_
{
    void (*reset)(C_ActorInfoIteratorHandle handle);
    C_ActorInfo * (*next)(C_ActorInfoIteratorHandle handle);

    C_ActorInfoIteratorHandle handle;
} C_ActorInfoIterator;

typedef struct C_TurnHandle_ { char c; } * C_TurnHandle;
typedef struct C_Turn_
{
    C_ActorInfo * (*getSelfInfo)(C_TurnHandle handle);
    C_ActorInfoIterator * (*getFriends)(C_TurnHandle handle);
    C_ActorInfoIterator * (*getFoes)(C_TurnHandle handle);

    void (*move)(C_TurnHandle handle, uint32_t x, uint32_t y);
    void (*attack)(C_TurnHandle handle, uint32_t id);

    C_TurnHandle handle;
} C_Turn;

typedef struct C_ActorHandle_ { char c; } * C_ActorHandle;
typedef struct C_Actor_
{
    void (*getInitialInfo)(C_ActorHandle handle, C_ActorInfo * info);
    void (*play)(C_ActorHandle handle, C_Turn * turn);

    C_ActorHandle handle;
} C_Actor;

#endif